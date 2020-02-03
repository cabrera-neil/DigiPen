; Assignment 1 File
; Assembly File for Question 12a
; Title: ASM file for 12a
; Date: 13-Sep 2019
; Name: Neil Cabrera

	AREA MyData, DATA, READWRITE
VALUE1 EQU 0x89ABCDEF
	GLOBAL __main				
	AREA Main, CODE, READONLY	
	ALIGN 4						
	ENTRY						

__main
	; NOTE: Set Breakpoint at the next line to demonstrate
	LDR R0, =VALUE1		;Assign value 0x89ABCDEF to the register R0.
	ORR R0, #0x10		;Set R0’s bit 4 to “1”.
	AND R0, #0xFFFFFFF7	;Clear R0’s bit 3 to “0”.
	
	;Change R0’s bit 27 - 24 to pattern “1110”.
	AND R0, #0xF0FFFFFF
	ORR R0, #0x0E000000
	
halt
	NOP
	NOP
	B halt			; Endless Loop
	END