; Assignment 1 File
; Assembly File for Question 12d
; Title: Odd_Event_Sort Implementation
; Date: 13-Sep 2019
; Author: Neil Cabrera

	AREA |.text|, CODE, READONLY
		EXPORT odd_even_sort

odd_even_sort PROC
	; Parameters are received from R0 and R1
	; R0 contains address of array
	; R1 contains size of array
	
	; Start looping into the array
	; R4 will be the current index of the array
	MOV R4, #0
	
loop
	CMP R4, R1
	BGE exit
	
	; Check if current index is odd or even
	TST R4, #1
	BNE even
	; Initiate inner loop index
	; If odd, start count is 2
	; If even, start count is 1
odd
	MOV R6, #2
	B odd_even_loop
even
	MOV R6, #1
	
odd_even_loop	
	CMP R6, R1
	BGE inc_loop
	
	; Prepare offset in r9 and r10
	MOV R9, R6, LSL#2
	SUB R10, R9, #4
	
	; Load values based on the offset
	LDR R7, [R0, R9]
	LDR R8, [R0, R10]
	
	CMP R7, R8
	BGE inc_odd_even	
	
	; Preserve everything
	PUSH {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, LR}
	
	; Prepare parameters for swap function
	; Pass the address with offset
	ADD R1, R0, R10
	ADD R0, R0, R9
	BL swap
	
	; Recover everything
	POP {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, LR}
	
inc_odd_even
	ADD R6, R6, #2
	B odd_even_loop

inc_loop
	; Increment by 1
	ADD R4, R4, #1
	B loop

exit
	BX LR
	
	ENDP
		
swap PROC
	; Parameters are received from R0 and R1
	; Both parameters are pointers
	
	; perform swap
	LDR R2, [R0]
	LDR R3, [R1]
	STR R2, [R1]
	STR R3, [R0]
	
	BX LR
	
	ENDP
		
	END
		