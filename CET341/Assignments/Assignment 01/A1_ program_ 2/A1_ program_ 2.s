; Assignment 1 File
; Assembly File for Question 12b
; Title: 64-bit by 64-bit Unsigned Multiplication to 128-bit Result
; Date: 13-Sep 2019
; Name: Neil Cabrera

	AREA MyData, DATA, READWRITE
	; Change the Values Here for Testing Purposes
	; 0xFFFFFFFF was used to test the maximum possible value
	; for multiplication
VAL1L EQU 0xFFFFFFFF
VAL1H EQU 0xFFFFFFFF
VAL2L EQU 0xFFFFFFFF
VAL2H EQU 0xFFFFFFFF
	GLOBAL __main				
	AREA Main, CODE, READONLY	
	ALIGN 2						
	ENTRY						

__main
	; NOTE: Set Breakpoint at the next line to demonstrate

	; Load the Values for Value1 and Value2 High and Low
	LDR R2, =VAL2L
	LDR R3, =VAL2H
	LDR R0, =VAL1L
	LDR R1, =VAL1H
	
	; Use R11, R10, R9 and R8 to Store the Results
	; R11 will contain the MSB, R8 will contain the LSB
	
	; Multiply Val1 Low and Val2 Low First
	; Store the Product to LSB R8 and MSB R9
	UMAAL R8, R9, R0, R2
	
	; Multiply Val1 Low and Val2 High
	; Store the Product to LSB R9 and MSB R10
	UMAAL R9, R10, R0, R3
	
	; Multiply Val1 High and Val2 Low
	; Store the Product to LSB R4 and MSB R5
	UMAAL R4, R5, R1, R2
	
	; Multiply Val1 High and Val2 High
	; Add the Product to R5 and the Carry to R6
	UMAAL R5, R6, R1, R3
		
	ADDS	R9,	R4		; Add R4 to R9 and Store in R9, Set the Flag in case of Overflow		
	ADDCS 	R10,#0x01	; Conditional Addition if C=1 from Previous Operation
		
	ADDS	R10,R5		; Add R5 to R10 and Store in 10, Set the Flag in case of Overflow	
	ADDCS	R11,#0x01	; Conditional Addition if C=1 from Previous Operation
	
	ADDS	R11,R6		; Add R6 to R11 and Store in 10, Set the Flag in case of Overflow

halt
	NOP
	NOP
	B halt				; Endless Loop
	END