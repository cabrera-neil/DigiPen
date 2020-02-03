; Assignment 1 File
; Assembly File for Question 12c
; Title: Fast Exp Implementation
; Date: 13-Sep 2019
; Author: Neil Cabrera

	AREA |.text|, CODE, READONLY
		EXPORT fast_exp

; fast_exp has 2 parameters: unsigned int a, unsigned int m
; as per the requirements, store a in r6 and m in r7
fast_exp PROC
	; parameters are received from r0 and r1
	; store r0 to r6
	; store r1 to r7
	; result is in r8
	MOV R6, R0	; variable base
	MOV R7, R1	; variable exponent
	MOV R8, #1	; variable result
	
check_e
	; Check if exponent is 0
	; If 0 result is 1 and then exit
	CMP R7, #0
	BLE exit
	
	; Check if exponent is 1
	; If 1, multiple base to the current result
	ANDS R9, R7, #1
	BLS shift
	MUL R8, R8, R6
	SUB R7, R7, #1
	B check_e
shift
	; If exponent is > 1
	; Multiply base by base and store the result in r6
	MUL R6, R6, R6
	LSR R7, R7, #1
	B check_e
exit
	MOV R0, R8	; store result (r8) in r0 and return
	BX LR
	
	ENDP
		
	END
		