/**
 * Game of Life
 * cs3990 Winter-2022
 * Mitchell VanderHoek 
 */

$(function(){
    let length = 16, width = 32, speed = 500; // These are for the sliders.
    let generation = 0; // How many intervals.
    let squares = [];   
    let original = []; // This is used to save the state of the board on the first click of play.
    const gameBoard = $(".life");

    $("#slider-speed").slider({
        min: 0,
        max: 5000,
        value: speed,
        slide:function(event, ui){
            $('#speed').text(ui.value.toString() + " ms");
            speed = ui.value;
        }
    });
    
    $('#speed').val($('#slider-speed').slider("value"));

    $("#length-cells").slider({
        min: 8,
        max: 100,
        value: length,
        slide:function(event, ui){
            $('#length-cells-value').text(length.toString() + " cells");
            length = ui.value;
        }
    });

    $('#length-cells-value').val($('#length-cells').slider("value"));

    $("#width-cells").slider({
        min: 16,
        max: 256,
        value: width,
        slide:function(event, ui){
            $('#width-cells-value').text(width.toString() + " cells");
            width = ui.value;
        }
    });

    $('#width-cells-value').val($('#width-cells').slider("value"));
    
    // Help overlay pop-up
    $('.help').on('click', ()=>{
        $('.helper').toggleClass('active');
        $('.game').toggleClass('active');
        
    });
    $('.helper .close-button').on('click', function(){
        $('.helper').toggleClass('active');
        $('.game').toggleClass('active');
    });

    // Settings overlay pop-up
    $('.settings').on('click', ()=>{
        $('.setter').toggleClass('active');
        $('.game').toggleClass('active'); 
    });

    $('.setter .close-button').on('click', function(){
        $('.setter').toggleClass('active');
        $('.game').toggleClass('active');
        gameBoard.children().remove('div');
        squares = [];
        original = [];
        createBoard();
    });

    // Generates the gameboard along with all the cells. This is done using a string to create the elements all at once.
    // Were I to create each element, individually, there would be a higher overhead of ~5ms per element on my machine.
    function createBoard(){
        let buffer = [];

        // Push new elements as a string to buffer. 
        for(let newCellCount = 0; newCellCount < width + 2; newCellCount++){
            buffer.push('<div class="cell hidden"></div>'); // hidden top row
            squares.push(2);
        }
        for(let i = 0; i < length; i++){
            buffer.push('<div class="cell hidden"></div>'); // hidden 0 column cell
            squares.push(2);
            for(let newCellCount = 0; newCellCount < width; newCellCount++){
                buffer.push('<div class="cell"></div>');
                squares.push(0);
            }
            buffer.push('<div class="cell hidden"></div>'); // hidden 51 column cell
            squares.push(2);
        }
        for(let newCellCount = 0; newCellCount < width + 2; newCellCount++){
            buffer.push('<div class="cell hidden"></div>'); // hidden bottom row.
            squares.push(2);
        }
        // Join the array as a single large string then append to DOM tree.
        gameBoard.append(buffer.join(''));

        // Create the grid layout by appending the css with cell length and width calculated so all cells fix container.
        gameBoard.css('grid-template-columns', 'repeat(' + width + ' ,1fr)');
        $(".cell").css('width',  '1fr');    // width of cell
        $(".cell").css('height',  '1fr');   // length of cell
        $(".count").text(generation);

        // Slider bar background.
        $('.fill' ).on( 'input', function() {
            $(this).css('background', 'linear-gradient(to right, green 0%, green '+ this.value +'%, #fff ' + this.value + '%, white 100%)');
        });

        // Handle click to giveth life or taketh away.
        $(".cell").on('click', function(){
            
            if($(this).hasClass('alive')){    
                //$(this).attr('state', 'dead');
                squares[$(this).index()] = 0;
            }else{
                //$(this).attr('state', 'alive');
                squares[$(this).index()] = 1;
            }
            $(this).toggleClass('alive');
        });       
    }
    createBoard();  // Board created.
    // Event handler for the play button.
    let playDeez; // Runs once an interval.
    $('.play').on("click", function() {
        if($('.play').text() == "Play"){
            if(generation == 0){
                original = JSON.parse(JSON.stringify(squares));
            }
            $('.play').text("Pause");
            $('.clear').text("Reset"); // Reset puts things to the original state.
            playDeez = setInterval(play, speed);
        }else{
            $('.play').text("Play");
            clearInterval(playDeez);
        }
    });

    $('.next').on("click", play); // Event handler for step function.

    // Removes class from elements and updates the list.
    $('.clear').on("click", function(){
        if($('.clear').text() == "Reset"){
            for(let cell = width + 3; cell < ((length + 2 ) * (width+2) - (width-2)); cell++){
                // Avoid the unnecessary. 
                if(squares[cell] == 2 || original[cell] == 2){
                    continue;
                }

                let result = squares[cell] - original[cell]; // Difference
                // original was dead.
                if(result == 1){
                    gameBoard.children().eq(cell).removeClass('alive');
                    squares[cell] = 0;
                } // original was alive.
                else if(result == -1){
                    gameBoard.children().eq(cell).addClass('alive');
                    squares[cell] = 1;
                }// else equal & do nothing     
            }
            $('.clear').text("Clear");
            $('.count').text((generation = 0));
        }else{
            // Iterate through all containers with .alive and set array at the same index to 0.
            $('.alive').each(function(){
                squares[$(this).index()] = 0;
                $(this).removeClass('alive');
            });
        }
    });
    
    /*
     *  There's far more efficient ways to do this, but I don't have the time to code a quad-tree that uses a hash table store 
     *  the nodes. Many of the same patterns will appear on the board, and therefore, hash to the same position. Additionally, 
     *  I could use WebGL to be able to have many more cells.
     */
    let indexOfCellsToChange; // Used for what it's called at the end of the interval.
    function play (){
        let aliveCount;
        let prevRow = 0 - width - 2;
        let nextRow = width + 2;
        let stopAtThisCell = (length + 2 ) * nextRow - nextRow; // Don't need to do top and bottom rows (they're hidden).
        
        nextState = JSON.parse(JSON.stringify(squares)); // Deep copy string, thanks franco.
        indexOfCellsToChange = [];                       // Reset state.

        for(let cell = nextRow + 1; cell < stopAtThisCell; cell++){   
            
            // Check currentCell is a boundary cell. These are ignored.
            if(squares[cell] == 2){
                continue;
            }

            aliveCount = 0; // Refresh count.

            // Neighborhood lookup. It could be sped up by saving the already compared values for
            // the next loop or by using an adjacency matrix.
            let neighbors = [
                squares[cell + prevRow - 1], // nw
                squares[cell + prevRow],     // n
                squares[cell + prevRow + 1], // ne
                squares[cell - 1],           // w
                squares[cell + 1],           // e
                squares[cell + nextRow - 1], // sw
                squares[cell + nextRow],     // s
                squares[cell + nextRow + 1]  // se
            ];
            
            // Check if cells in neighborhood are alive.
            for(let i = 0; i < neighbors.length; i++){
                if(neighbors[i] == 2)   // Avoid hidden cells.
                    continue;
                aliveCount += neighbors[i]; // Add a 0 or 1. A 1 is alive, 0 is dead.
            }

            // The attribute "state" is added to the div element. This state can be alive or dead.
            // The class, alive, will be removed/added upon the next generation.
            if(squares[cell] == 1){
                if(aliveCount < 2){
                    nextState[cell] = 0;
                    indexOfCellsToChange.push(cell); // add index to cell update list.
                }
                else if(aliveCount > 3){
                    nextState[cell] = 0;
                    indexOfCellsToChange.push(cell); // add index to cell update list.
                }else if(aliveCount == 2 || aliveCount == 3) {
                    nextState[cell] = 1;
                    indexOfCellsToChange.push(cell); // add index to cell update list.
                }
            }
            else if(aliveCount == 3){ // Check if a cell can be alive.
                nextState[cell] = 1;
                indexOfCellsToChange.push(cell);
            }
        }

        // Apply changes on indices that need it, and avoid unnecessary calls to the dom tree.
        for(let i = 0; i < indexOfCellsToChange.length; i++){
            (nextState[indexOfCellsToChange[i]] == 1)?
                gameBoard.children().eq(indexOfCellsToChange[i]).addClass('alive'):
                gameBoard.children().eq(indexOfCellsToChange[i]).removeClass('alive');
        }

        squares = JSON.parse(JSON.stringify(nextState)); // Save changes 
        $('.count').text(++generation);
    }
       
});

    