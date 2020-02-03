; Due Date: 01-Aug 2019
; Student Name: Neil Cabrera
; Student DigiPen Email Address: cabrera.n@digipen.edu
; Section:
; ? 2019 DigiPen, All Rights Reserved.

; Assembly Directive Reference
; http://www.keil.com/support/man/docs/armasm/armasm_doml361290000455.htm
; Area of data named "MyData" that is Read/Write
	AREA MyData, DATA, READWRITE

value1 EQU 0x05			; The label value1 equates to the hexadecimal literal 0x05
						; EQU gives a symbolic meaning to a numeric constant
value2 SPACE 4			; The label value2 is a "space" of zeroed data of size 4;
						; It defines 4 bytes of zeroed store

	GLOBAL __main				; Global Main Function
	AREA Main, CODE, READONLY	; Area of Code named "Main" that is read-only
	ALIGN 2						; Align the data boundary to a multiple of 2
	ENTRY						; Entry into the code segment

; Assembly Directive Reference
; http://www.keil.com/support/man/docs/armasm/armasm_doml361290000455.htm
__main
	LDR R0, =value2		; Load "address" value2 into Register R0
	STR R1, [R0]		; Store the value in Register R1 into the "address" of Register R0
	MOV R1, #2_1010		; Move the literal (binary) 10 (ten) into Register R1
	MOV R0, #value1		; Move value1 into Register R0
	PUSH {LR}			; Push the Link Register onto the Stack to save its value
	BL __add_register	; Branch WITH link to the label "__add_register"
						; Saves the next instruction's address in the Link Register
	POP {LR}			; Pop the Old Link Register value off the stack back into the Link Register

; Infinitely loop when we're done
__loop
	B __loop			; Branch to the label __loop

; Registers Used:
; R0 - Left Operand
; R1 - Right Operand
; R2 - Result

__add_register			; "Function" label __add_register
	; Add the values "passed in" through R0 and R1
	ADD R2, R0, R1		; R2 = R0 + R1
	; Use the Link Address to Return
	MOV PC, LR			; MOV BX, LR is preferred over this traditional method
	NOP					; No Operation, use NOP for padding before END to avoid warning A1581W
	END					; End of File