/*
    Calculator
    cs 3990 lab5
    winter 2022
    Mitchell Vanderhoek

    Purpose:    This generates my buttons, events and how the math is performed.
*/

// Select elements
const input_element = document.querySelector('.input');
const output_operation_element = document.querySelector('.operation .value');
const output_result_element = document.querySelector('.result .value');


// Variables
const OPERATORS = ["+", "-", "*", "/"];
const POWER = "POWER(", FACTORIAL = "FACTORIAL";


let data = {
    operation : [],
    formula : []
}
let ans = 0;


/*
 *   These are the calculator buttons that'll be created using javscript code. Symbols can be numeric characters
 *   or they can be Strings. The formula property is how JS will interpret it. 
 */
let calculator_buttons = [
    {
        name : "rad",
        symbol : "Rad",
        formula : false,
        type : "key"
    },
    {
        name : "deg",
        symbol : "Deg",
        formula : false,
        type : "key"
    },
    {
        name : "factorial",
        symbol : "n!",
        formula : FACTORIAL,
        type : "math_function"
    },
    {
        name : "open-parenthesis",
        symbol : "(",
        formula : "(",
        type : "number"
    },
    {
        name : "close-parenthesis",
        symbol : ")",
        formula : ")",
        type : "number"
    },
    {
        name : "clear",
        symbol : "C",
        formula : false,
        type : "key"
    },
    {
        name : "delete",
        symbol : "⌫",
        formula : false,
        type : "key"
    },
    //Row 2
    {
        name : "second",
        symbol: "2ⁿᵈ",
        formula : false,
        type : "key"
    },
    {
        name : "sin",
        symbol : "sin",
        formula : "trigo(Math.sin,",
        type : "trigo_function"
    },
    {
        name : "ln",
        symbol : "ln",
        formula : "Math.log",
        type : "math_function"
    },
    {
        name : "7",
        symbol : 7,
        formula : 7,
        type : "number"
    },{
        name : "8",
        symbol : 8,
        formula : 8,
        type : "number"
    },{
        name : "9",
        symbol : 9,
        formula : 9,
        type : "number"
    },
    {
        name : "division",
        symbol : "÷",
        formula : "/",
        type : "operator"
    },
    // Row 3
    {
        name : "pi",
        symbol : "π",
        formula : "Math.PI",
        type : "number"
    },
    {
        name : "cos",
        symbol : "cos",
        formula : "trigo(Math.cos,",
        type : "trigo_function"
    },{
        name : "log",
        symbol : "log",
        formula : "Math.log10",
        type : "math_function"
    },
    {
        name : "4",
        symbol : 4,
        formula : 4,
        type : "number"
    },{
        name : "5",
        symbol : 5,
        formula : 5,
        type : "number"
    },{
        name : "6",
        symbol : 6,
        formula : 6,
        type : "number"
    },{
        name : "multiplication",
        symbol : "x",
        formula : "*",
        type : "operator"
    },
    // row 4
    {
        name : "e",
        symbol : "e",
        formula : "Math.E",
        type : "number"
    },
    {
        name : "tan",
        symbol : "tan",
        formula : "trigo(Math.tan,",
        type : "trigo_function"
    },
    {
        name : "square-root",
        symbol : "√",
        formula : "Math.sqrt",
        type : "math_function"
    },
    {
        name : "1",
        symbol : 1,
        formula : 1,
        type : "number"
    },{
        name : "2",
        symbol : 2,
        formula : 2,
        type : "number"
    },{
        name : "3",
        symbol : 3,
        formula : 3,
        type : "number"
    },{
        name : "subtraction",
        symbol : "-",
        formula : "-",
        type : "operator"
    },
    // Row 5
    {
        name : "ANS",
        symbol : "ANS",
        formula : "ans",
        type : "number"
    },
    {
        name : "exp",
        symbol : "exp",
        formula : "Math.exp",
        type : "math_function"
    },{
        name : "power",
        symbol : "xʸ",
        formula : POWER,
        type : "math_function"
    },{
        name : "comma",
        symbol : ".",
        formula : ".",
        type : "number"
    },{
        name : "0",
        symbol : 0,
        formula : 0,
        type : "number"
    },{
        name : "calculate",
        symbol : "=",
        formula : "=",
        type : "calculate"
    },{
        name : "addition",
        symbol : "+",
        formula : "+",
        type : "operator"
    }
];

/*
    Creates the html elements for the buttons.
*/
function createCalculatorButtons(){
    const btns_per_row = 7;
    let added_btns = 0;

    calculator_buttons.forEach((button, index) => {
        if(added_btns % btns_per_row == 0){
            input_element.innerHTML+= `<div class="row"></div>`;
        }

        const row = document.querySelector(".row:last-child");
        row.innerHTML += `<button id="${button.name}">
                            ${button.symbol}
                          </button>`;
        added_btns++;
        
    });
}
createCalculatorButtons();


/**
 * Add the ability to toggle between radians and degrees.
 */
let RADIAN = true; // radians and degree 
let SECONDED = false; // This tracks state of calculator by 2nd toggle.

const rad_btn = document.getElementById("rad");
const deg_btn = document.getElementById("deg");

rad_btn.classList.add("active-angle");

function angleToggler(){
    rad_btn.classList.toggle("active-angle");
    deg_btn.classList.toggle("active-angle");
}

/*
    Click Event Listener

    Adds event handler for all the buttons on the calculator.
*/
input_element.addEventListener("click", event => {
    const target_btn = event.target;

    calculator_buttons.forEach(button => {
        if(button.name == target_btn.id) calculator(button);
    });

    // These add the events for the change
    whenSeconded.forEach(button => {
        if(button.name == target_btn.id) calculator(button);
    });
});

/**
 * Performs operation based on the button type. Each button is an object
 * from the calculator_buttons array. 
 */
function calculator(button){
    if(button.type == "operator"){
        data.operation.push(button.symbol);
        data.formula.push(button.formula);

    }
    else if(button.type == "number"){
        data.operation.push(button.symbol);
        data.formula.push(button.formula);

    }
    else if(button.type == "trigo_function"){

        data.operation.push(button.symbol + "(");
        data.formula.push(button.formula);
        
    }

    // Checks if specific type of math_function to apply special circumstances.
    else if(button.type == "math_function"){
        let symbol, formula;

        if(button.name == "factorial"){
            symbol = "!";
            formula = button.formula;

            data.operation.push(symbol);
            data.formula.push(formula);
        }
        else if(button.name == "power"){
            symbol = "^(";
            formula = button.formula;

            data.operation.push(symbol);
            data.formula.push(formula);
        }
        else if(button.name == "square"){
            symbol = "^(";
            formula = button.formula;

            data.operation.push(symbol);
            data.formula.push(formula);

            data.operation.push("2)");
            data.formula.push("2)");
        }
        else if(button.name == "ten-power"){
            symbol = "10^(";
            formula = "10**(";

            data.operation.push(symbol);
            data.formula.push(formula);
        }
        else{
            symbol = button.symbol + "(";
            formula = button.formula + "(";

            data.operation.push(symbol);
            data.formula.push(formula);
        }
        
    }else if(button.type == "key"){

        if(button.name == "clear"){
            data.operation = [];
            data.formula =[];

            updateOutputResult(0);
        }
        else if(button.name == "delete"){
            data.operation.pop();
            data.formula.pop();

        }else if(button.name == "rad"){
            RADIAN = true;
            angleToggler();

        }
        else if(button.name == "deg"){
            RADIAN = false;
            angleToggler();
        }
        else if(button.name == "second"){
            // Check if already on.
            (SECONDED === true)? SECONDED = false: SECONDED = true; 
            secondChangesButtons(); // Change state.
        }        
    }else if(button.type == "calculate"){
        formula_str = data.formula.join('');

        let POWER_SEARCH_RESULT = search(data.formula, POWER);
        let FACTORIAL_SEARCH_RESULT = search(data.formula, FACTORIAL);

        // Get power base and replace with the right formula.
        const BASES = powerBaseGetter(data.formula, POWER_SEARCH_RESULT);
        BASES.forEach(base => {
            let toReplace = base + POWER;
            let replacement = "Math.pow(" + base + ",";

            formula_str = formula_str.replace(toReplace, replacement);
        });

        // Get factorial and replace with the right formula.
        const NUMBERS = factorialNumberGetter(data.formula, FACTORIAL_SEARCH_RESULT);
        NUMBERS.forEach(factorial => {
            formula_str = formula_str.replace(factorial.toReplace, factorial.replacement);
        });
        
        // Output result into larger calculator field.
        let result;
        try{
            console.log(formula_str);
            result = eval(formula_str);
        }catch(error){
            if(error instanceof SyntaxError){
                result = "Syntax Error!"
                updateOutputResult(result);
                return;
            }
        }

        ans = result;
        data.operation = [result];
        data.formula = [result];

        updateOutputResult(result);
        return;
    }
    //console.log(data.operation); // See current array
    updateOutputOperation(data.operation.join(''));
}

// These arrays make modifying the page's html in secondChangesButtons() easier.
let whenSeconded = [
    {
        name : "sinh",
        symbol : "sinh" ,
        formula : "trigo(Math.sinh,",
        type : "trigo_function"
    },
    {
        name : "cosh",
        symbol : "cosh" ,
        formula : "trigo(Math.cosh,",
        type : "trigo_function"
    },
    {
        name : "tanh",
        symbol : "tanh" ,
        formula : "trigo(Math.tanh,",
        type : "trigo_function"
    },
    {
        name : "cube-root",
        symbol : "∛" ,
        formula : "Math.cbrt",
        type : "math_function"
    },
    {
        name : "ten-power",
        symbol : "10ˣ",
        formula : "10**",
        type : "math_function"
    }
];

let whenNotSeconded = [
    {
        name : "sin",
        symbol : "sin",
        formula : "trigo(Math.sin,",
        type : "trigo_function"
    },
    {
        name : "cos",
        symbol : "cos",
        formula : "trigo(Math.cos,",
        type : "trigo_function"
    },
    {
        name : "tan",
        symbol : "tan",
        formula : "trigo(Math.tan,",
        type : "trigo_function"
    },
    {
        name : "square-root",
        symbol : "√",
        formula : "Math.sqrt",
        type : "math_function"
    },
    {
        name : "log",
        symbol : "log",
        formula : "Math.log10",
        type : "math_function"
    }
];

function secondChangesButtons(){
    // Will need to replace elements in calculator_buttons[] because it's relied upon by our event handler.
    // The html must also be modified so the user sees the change.
    if(SECONDED){  
        for(let i = 0; i < whenSeconded.length; i++){
            let index = calculator_buttons.indexOf(whenNotSeconded[i].name);
            
            calculator_buttons[index] = whenSeconded[i];

            // Modify the id and innertext.
            let element = document.getElementById(whenNotSeconded[i].name);
            element.id = whenSeconded[i].name;
            element.innerText = `${whenSeconded[i].symbol}`;
        
        }
    }else{
        for(let i = 0; i < whenSeconded.length; i++){
            let index = calculator_buttons.indexOf(whenSeconded[i].name);
            
            calculator_buttons[index] = whenNotSeconded[i];

            // Modify the id and innertext.
            let element = document.getElementById(whenSeconded[i].name);
            element.id = whenNotSeconded[i].name;
            element.innerText = `${whenNotSeconded[i].symbol}`;
        }
    }
}


function factorialNumberGetter(formula, FACTORIAL_SEARCH_RESULT){
    let numbers = []; // Save numbers of the whole formula
    let factorial_sequence = 0;

    FACTORIAL_SEARCH_RESULT.forEach(factorial_index =>{
        let number = [];

        let next_index = factorial_index + 1;
        let next_input = formula[next_index];

        if(next_input == FACTORIAL){
            factorial_sequence +=1;
            return;
        }

        // Get the index of the first factorial number
        let first_factorial_index = factorial_index - factorial_sequence;
        let previous_index = first_factorial_index - 1;
        let parenthesis_count = 0;

        // Adds closing parenthesis in the right places for factorials
        while( previous_index >= 0){
            if(formula[previous_index] == "(") parenthesis_count--;
            if(formula[previous_index] == ")") parenthesis_count++;

            let is_operator = false;
            OPERATORS.forEach(OPERATOR => {
                if(formula[previous_index] == OPERATOR) is_operator = true;
            });

            if(is_operator && parenthesis_count == 0) break;

            number.unshift(formula[previous_index]);
            previous_index--; // go to next one.

        }
        let number_str = number.join('');
        const factorial = "factorial(", close_parenthesis = ")";
        let times = factorial_sequence + 1;

        let toReplace = number_str + FACTORIAL.repeat(times);
        let replacement = factorial.repeat(times) + number_str + close_parenthesis.repeat(times);

        numbers.push({
            toReplace : toReplace,
            replacement : replacement
        });

        // Reset factorial sequence.
        factorial_sequence = 0;

    })

    return numbers;
}

function powerBaseGetter(formula, POWER_SEARCH_RESULT){
    let powers_bases = []; // Stores all bases of formula.

    POWER_SEARCH_RESULT.forEach(power_index => {
        let base = []; // current base

        let parenthesis_count = 0;
        let previous_index = power_index - 1;

        // Generate equal closing braces for the amount of opening braces.
        while( previous_index >= 0){
            if(formula[previous_index] == "(") parenthesis_count--;
            if(formula[previous_index] == ")") parenthesis_count++;

            let is_operator = false;

            OPERATORS.forEach(OPERATOR => {
                if(formula[previous_index] == OPERATOR) is_operator = true;
            });

            let is_power = formula[previous_index] == POWER;

            if( (is_operator && parenthesis_count == 0) || is_power) break;

            base.unshift(formula[previous_index]);
            previous_index--; // go to next one.

        }

        powers_bases.push(base.join(''));
    });

    return powers_bases;

}

// Search the array
function search(array, keyword){
    let search_result = [];

    array.forEach( (element,index) => {
        if(element == keyword) search_result.push(index);
    });

    return search_result;
}

// Updates the output.
function updateOutputOperation(operation){
    output_operation_element.innerHTML = operation;
}

// Updates the result.
function updateOutputResult(result){
    output_result_element.innerHTML = result;
}

// This performs a number of checks on factorial.
function factorial(number) {
    // Check to do numbers like 0.25
    if(number % 1 != 0) return gamma(number + 1);
    if(number === 0 || number === 1) return 1;
    
    // Compute factorial.
    let result = 1;
    for(let i = 1; i <= number; i++){
        result *= i;
        if(result === Infinity) return Infinity;
    }
    return result;
}

/*
    Trigometric functions.

    @param callback
    @param angle This is converted into radians if the radian button is active.
    @return
    callback(angle).
*/
function trigo(callback, angle){
    if(!RADIAN){
        angle = angle * Math.PI/180;
    }
    return callback(angle);
}

function inv_trigo(callback, value){
    let angle = callback(value);

    if(!RADIAN){
        angle = angle * 180/Math.PI;
    }
    
    return angle;
}

/*  Gamma Function:
    This lets me do factorials for values <1.

    Source: This was taken directly from the Swedish wiki. https://sv.wikipedia.org/wiki/Gammafunktionen 
*/
function gamma(n) {  // accurate to about 15 decimal places
    //some magic constants 
    var g = 7, // g represents the precision desired, p is the values of p[i] to plug into Lanczos' formula
        p = [0.99999999999980993, 676.5203681218851, -1259.1392167224028, 771.32342877765313, -176.61502916214059, 12.507343278686905, -0.13857109526572012, 9.9843695780195716e-6, 1.5056327351493116e-7];
    if(n < 0.5) {
      return Math.PI / Math.sin(n * Math.PI) / gamma(1 - n);
    }
    else {
      n--;
      var x = p[0];
      for(var i = 1; i < g + 2; i++) {
        x += p[i] / (n + i);
      }
      var t = n + g + 0.5;
      return Math.sqrt(2 * Math.PI) * Math.pow(t, (n + 0.5)) * Math.exp(-t) * x;
    }
}
