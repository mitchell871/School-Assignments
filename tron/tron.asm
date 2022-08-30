include	Irvine32.inc

.data


board		BYTE	80 dup(1), 28 dup(1, 78 dup(0), 1), 80 dup(1)	; there are 30 rows with 80 columns
ranCol		BYTE	0
ranRow		BYTE	0
posY		BYTE	0
posX		BYTE	0
direct		SDWORD	0
del 		BYTE	0
colLen		BYTE	80
row			BYTE	?		; This'll be the current row
col 		BYTE 	?		; This'll be the current column
delayTime	dword	110
score 		dword	0
obstacleX	BYTE	?		; width
obstacleY	BYTE	?		; height
obstacleRow	BYTE	?
obstacleCol	BYTE	?
obstacle	BYTE 	?		; where it begins
msg_Score	BYTE	"Score : ", 0
msg_Level	BYTE	"Level : ", 0
msg_hScore	BYTE	"High Score: ", 0
msg_NScore	BYTE	"Score needed for next level: ", 0
level		BYTE	0
speedLevel  BYTE	0
highscore	DWORD	0
score_need  DWORD 	100

.code

gamespeed = 100 ; Player tick before redrawn.
square = 219
colsinrow = 80

main PROC
	call Randomize
	
	gameloop:
		call clrscr
		call printarray		; draw the underlay
		call createborder	; create the border
		mov dl, 0
		mov dh, 33
		call goToXY
		mov edx, offset msg_Level
		call writeString
		movzx eax, level
		call writeDec
		
		; Skip this part if on level 0
		movzx ecx, level
		cmp ecx, 0
		je cont
		
		Obsticleloop:
			push ecx
			call obstacleGen
			call drawObst
			pop ecx
		loop Obsticleloop
			
		cont:
		call controls 		; This starts the game.

		NextLevel::
		call resetArray
		movzx ecx, level
		inc ecx
		mov level, cl
		mov eax, score
		add highscore, eax
		mov score, 0
		mov delayTime, 120
		mov eax, score_need
		add eax, 50
		mov score_need, eax
	jmp gameloop	
		
	quiter::
	; Debugging tools for values of the array.
	call clrscr
	mov edx, offset msg_Score
	call writeString
	mov eax, highscore
	add eax, score
	call writeDec
	
	exit
main ENDP

resetArray PROC
	mov ecx, lengthof board
	mov esi, offset board
	L1:
		mov byte ptr [esi], 0
		inc esi
	loop L1
	ret
resetArray ENDP

checkIfGood PROC
	pushad
	mov esi, offset board
	movzx ecx, posY
	inc ecx
	
	L1:
		add esi, colsinrow
	loop L1
	
	movzx ebx, posX
	add esi, ebx
	cmp byte ptr [esi], 1
	jb goodMove
	jmp quiter	; Bad move.
	
	goodMove:	; The array didn't have a 1 at that location
	mov eax, 10
	call Delay
	inc byte ptr [esi]
	mov ecx, score
	inc ecx
	mov score, ecx
	; Update values that are wring to the screen.
	mov dl, 0
	mov dh, 32 
	call goToXY
	mov edx, offset msg_Score
	call writeString
	mov eax, score
	call writeDec
	mov dl, 0
	mov dh, 33 
	call goToXY
	mov edx, offset msg_NScore
	call writeString
	mov eax, score_need
	sub eax, score
	call writeDec
	popad	
	ret
checkIfGood ENDP

draw PROC
	pushad
	call checkIfGood
	
	; begining condition
	mov dl, posX
	mov dh, posY
	call goToXY
	
	mov eax, blue + (black * 16)
	call setTextColor
	mov al, square
	call writeChar
	mov eax, delayTime
	cmp eax, 0
	jle done 
	dec eax
	mov delayTime, eax
	call Delay			; delay looking drawing char
	done:
	mov eax, white + (black * 16)
	call setTextColor
	
	popad
	ret
draw ENDP

controls PROC
	; With respect to the offset:
	; going up is -80 and going down is +80
	; going left is -1 and going right is +1.
	; The row boundry is 0 or 29 while the Col boundry is 0 or 79.
	; When a key is pressed, the character continues until the course is altered.
	call spawn
	call draw			; First draw call.
	
	Begin:
	
		push eax
		push edx
		mov eax, score
		cmp eax, score_need 
		jae NextLevel
		pop edx
		mov eax, 10
		call delay
		call readKey
		pop eax	
			
		cmp dx, VK_LEFT
		je left
		cmp dx, VK_DOWN
		je down
		cmp dx, VK_UP
		je up
		cmp dx, VK_RIGHT
		je right
		cmp dx, VK_SPACE
		je space
		
		; This check is for when a key hasn't been pressed
		cmp direct, 0
		jg contPos
		jl contNeg
	right:
		mov eax, 1
		mov direct, eax
		jmp contPos
	left:
		mov eax, -1
		mov direct, eax
		jmp contNeg
	up:
		mov eax, -80
		mov direct, eax
		jmp contNeg
	down:
		mov eax, 80
		mov direct, eax
		jmp yInc
	space: 
		call pauseP
		jmp Begin
	; posX and posY are used for tracking a draw location. 
	; currOffset is used for updating the array as to which position in memory
	; needs to be set to 1. It's also used for checking whether it's a bad/good move.
	
	; Going down or right.
	contPos:
			; right
			cmp eax, 1
			jne yInc
			mov bl, posX
			inc bl
			mov posX, bl
			call draw
			jmp Begin
		; down
		yInc:
			mov bl, posY
			inc bl
			mov posY, bl
			call draw
			jmp Begin
	
	; Going up or left.
	contNeg:
			; left
			cmp eax, -1
			jl yDec
			mov bl, posX
			dec bl
			mov posX, bl
			call draw
			jmp Begin
		
		yDec:
			; down
			mov bl, posY
			dec bl
			mov posY, bl
			call draw
			jmp Begin
	
	gameova:
		mov dh, 40
		mov dl, 0
		call goToXY
	ret
controls ENDP

spawn PROC
	; Determine a random row & column within predefined boundries.
	
	; random row 10 - 15
	mov eax, 5
	call randomRange
	add eax, 10
	mov posY, al
	; random columns 35 - 40
	mov eax, 5
	call randomRange
	add eax, 35
	mov posX, al
	; Set player start position
	movzx ebx, colLen
	movzx ecx, posY
	mov esi, offset board
	inc ecx
	L1: 
		add esi, colsinrow
	loop L1
	
	ret
spawn ENDP


printarray PROC
	mov esi, 0
	mov ecx, 0
	print:
		cmp ecx, 80		; Check for when to put a crlf
		jne cont
		mov ecx, 0
		call crlf
	cont:
		movzx eax, board[esi]
		cmp eax, 0
		;call writeDec  ; Enable for debugging.
		inc esi
		inc ecx
		cmp esi, lengthof board
	jb print
	
	ret
printarray ENDP

drawObst PROC
	mov  eax, red+(black*16)
    call SetTextColor
	
	mov dh, obstacleRow
	mov dl, obstacleCol
	call goToXY
	mov eax, square
	movzx ecx, obstacleY
	L1:
		push ecx
		movzx ecx, obstacleX
		inner:
			mov al, square
			call writeChar
			mov eax, 10
			call delay
		loop inner
		
		inc dh
		mov dl, obstacleCol
		call goToXY	
		pop ecx
	loop L1
	
	mov  eax, white+(black*16)
    call SetTextColor
	
	ret
drawObst ENDP


obstacleGen PROC
	; Can't be within the player spawn area
		
	; Generate the size of the obstacle
	mov eax, 6
	call RandomRange
	add eax, 4
	mov obstacleX, al
	
	mov eax, 6
	call RandomRange
	add eax, 4
	mov obstacleY, al
	
	mov eax, 15
	call randomRange
	add eax, 4
	mov obstacleRow, al
	
	; Avoid rows where player spawns, 10 -15
	cmp al, 15
	ja good
	cmp al, 1
	jbe	good
	add al, 13
	
	; Now I put the values into the array
	good:
	
	movzx ecx, obstacleRow
	inc ecx
	mov esi, offset board
	getToRow:
		add esi, 80
	loop getToRow
	
	mov eax, 69 ; Rectangle is max 10.
	call randomRange
	inc eax
	mov obstacleCol, al
	
	add esi, eax
	
	movzx ecx, obstacleY
	outer:
		push ecx
		movzx ecx, obstacleX
		L1: 
			add byte ptr [esi], 1
			inc esi
		loop L1
		
		pop ecx
		add esi, 80
	
		movzx ebx, obstacleX
		sub esi, ebx
	loop outer
	
	ret
obstacleGen ENDP

createborder PROC
	mov  eax, lightGray+(lightGray*16)
    call SetTextColor
	
	mov dh, 0 
	mov dl, 0
	call goToXY
	drawBorderTop:	
		mov al, square
		call writeChar
		inc dl
		cmp dl, 79
	jbe drawBorderTop
	
	;Draw at 0 and 79 columns then go to next row.
	drawmid:
		inc dh
		mov dl, 0
		call goToXY
		mov al, square
		call writeChar
		mov dl, 79
		call goToXY
		mov al, square
		call writeChar
		cmp dh, 28
	jb drawmid
	
	; Draw final row of the border.
	mov dh, 29
	mov dl, 0
	call goToXY
	drawBorderBottom:
		mov al, square
		call writeChar
		inc dl
		cmp dl, 79
	jbe drawBorderBottom	
	
	mov  eax, white+(black*16)
    call SetTextColor
	
	ret
createborder ENDP

;Run pause procedure until user hits it again.
pauseP PROC
	
	paused:	
		mov eax, 10
		call Delay
		call readKey
		jz paused		; There's no point executing the following code if no key is pressed
		cmp dx, VK_ESCAPE	
		je quiter	
		cmp dx, VK_SPACE
	jne paused	; If key is not pressed, then it jumps again.

	ret
pauseP ENDP

END main