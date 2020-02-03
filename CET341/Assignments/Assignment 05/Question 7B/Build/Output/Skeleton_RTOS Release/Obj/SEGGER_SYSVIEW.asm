	.cpu cortex-m7
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"SEGGER_SYSVIEW.c"
	.text
	.section	.text._TrySendOverflowPacket,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	_TrySendOverflowPacket, %function
_TrySendOverflowPacket:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
	ldr	r4, .L14
	sub	sp, sp, #20
	movs	r3, #1
	ldr	r1, [r4, #20]
	add	r2, sp, #5
	strb	r3, [sp, #4]
	cmp	r1, #127
	bls	.L2
.L3:
	orn	r3, r1, #127
	lsrs	r1, r1, #7
	cmp	r1, #127
	strb	r3, [r2], #1
	bhi	.L3
.L2:
	ldr	r0, .L14+4
	ldr	r3, [r4, #12]
	strb	r1, [r2], #1
	ldr	r5, [r0]
	subs	r3, r5, r3
	cmp	r3, #127
	bls	.L4
.L5:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L5
.L4:
	add	r1, sp, #4
	strb	r3, [r2], #1
	movs	r0, #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbnz	r0, .L13
	ldr	r3, [r4, #20]
	adds	r3, r3, #1
	str	r3, [r4, #20]
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, pc}
.L13:
	ldrb	r3, [r4]	@ zero_extendqisi2
	str	r5, [r4, #12]
	subs	r3, r3, #1
	strb	r3, [r4]
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, pc}
.L15:
	.align	2
.L14:
	.word	.LANCHOR0
	.word	-536866812
	.size	_TrySendOverflowPacket, .-_TrySendOverflowPacket
	.section	.text.SEGGER_SYSVIEW_Init,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_Init
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_Init, %function
SEGGER_SYSVIEW_Init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, lr}
	movs	r4, #0
	sub	sp, sp, #12
	ldr	r5, .L18
	mov	r8, r0
	mov	r7, r1
	mov	r9, r2
	mov	r6, r3
	mov	r1, r5
	str	r4, [sp]
	mov	r3, #1024
	ldr	r2, .L18+4
	movs	r0, #1
	bl	SEGGER_RTT_ConfigUpBuffer
	mov	r1, r5
	str	r4, [sp]
	movs	r3, #8
	ldr	r2, .L18+8
	movs	r0, #1
	bl	SEGGER_RTT_ConfigDownBuffer
	ldr	r2, .L18+12
	ldr	r3, .L18+16
	mov	r1, #268435456
	ldr	r2, [r2]
	str	r9, [r3, #32]
	str	r6, [r3, #36]
	strb	r4, [r3]
	strd	r8, r7, [r3, #4]
	strd	r2, r1, [r3, #12]
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, pc}
.L19:
	.align	2
.L18:
	.word	.LC0
	.word	.LANCHOR1
	.word	.LANCHOR2
	.word	-536866812
	.word	.LANCHOR0
	.size	SEGGER_SYSVIEW_Init, .-SEGGER_SYSVIEW_Init
	.section	.text.SEGGER_SYSVIEW_SetRAMBase,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_SetRAMBase
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_SetRAMBase, %function
SEGGER_SYSVIEW_SetRAMBase:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L21
	str	r0, [r3, #16]
	bx	lr
.L22:
	.align	2
.L21:
	.word	.LANCHOR0
	.size	SEGGER_SYSVIEW_SetRAMBase, .-SEGGER_SYSVIEW_SetRAMBase
	.section	.text.SEGGER_SYSVIEW_SendTaskList,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_SendTaskList
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_SendTaskList, %function
SEGGER_SYSVIEW_SendTaskList:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L31
	ldr	r3, [r3, #32]
	cbz	r3, .L23
	ldr	r3, [r3, #4]
	cbz	r3, .L23
	bx	r3	@ indirect register sibling call
.L23:
	bx	lr
.L32:
	.align	2
.L31:
	.word	.LANCHOR0
	.size	SEGGER_SYSVIEW_SendTaskList, .-SEGGER_SYSVIEW_SendTaskList
	.section	.text.SEGGER_SYSVIEW_EncodeU32,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_EncodeU32
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_EncodeU32, %function
SEGGER_SYSVIEW_EncodeU32:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	.L37
.L35:
	orn	r3, r1, #127
	lsrs	r1, r1, #7
	strb	r3, [r0], #1
.L37:
	cmp	r1, #127
	bhi	.L35
	strb	r1, [r0], #1
	bx	lr
	.size	SEGGER_SYSVIEW_EncodeU32, .-SEGGER_SYSVIEW_EncodeU32
	.section	.text.SEGGER_SYSVIEW_EncodeString,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_EncodeString
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_EncodeString, %function
SEGGER_SYSVIEW_EncodeString:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L62
	mov	r3, r1
	push	{r4, r5, r6, r7, lr}
	mov	r5, r1
	rsb	r7, r1, #1
.L41:
	adds	r6, r7, r3
	ldrb	r4, [r3, #1]!	@ zero_extendqisi2
	cmp	r4, #0
	bne	.L41
	cmp	r2, r6
	it	cs
	movcs	r2, r6
	cmp	r2, #254
	uxtb	r6, r2
	bls	.L63
	lsrs	r3, r2, #8
	strb	r6, [r0, #1]
	adds	r4, r0, #3
	movs	r6, #255
	strb	r3, [r0, #2]
	strb	r6, [r0]
.L43:
	adds	r3, r4, #4
	adds	r0, r1, #4
	cmp	r4, r0
	it	cc
	cmpcc	r1, r3
	bcc	.L44
	cmp	r2, #26
	bls	.L44
	cmp	r2, #0
	mov	ip, r4
	mov	r3, r4
	ite	ne
	movne	r7, r2
	moveq	r7, #1
	bic	r6, r7, #3
	add	r6, r6, r1
.L45:
	mov	r0, r3
	ldr	lr, [r5], #4	@ unaligned
	adds	r0, r0, #4
	cmp	r5, r6
	str	lr, [ip], #4	@ unaligned
	mov	r3, r0
	bne	.L45
	bic	r3, r7, #3
	cmp	r7, r3
	add	r6, r1, r3
	add	r5, r4, r3
	beq	.L38
	ldrb	r0, [r1, r3]	@ zero_extendqisi2
	adds	r1, r3, #1
	cmp	r1, r2
	strb	r0, [r4, r3]
	add	r0, r5, #1
	bcs	.L38
	adds	r3, r3, #2
	ldrb	r1, [r6, #1]	@ zero_extendqisi2
	adds	r0, r5, #2
	cmp	r2, r3
	strb	r1, [r5, #1]
	bls	.L38
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	adds	r0, r5, #3
	strb	r3, [r5, #2]
.L38:
	pop	{r4, r5, r6, r7, pc}
.L63:
	mov	r4, r0
	strb	r6, [r4], #1
	cmp	r2, #0
	bne	.L43
	mov	r0, r4
	pop	{r4, r5, r6, r7, pc}
.L44:
	mov	r0, r4
	subs	r4, r1, #1
.L48:
	adds	r3, r4, #2
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	adds	r4, r4, #1
	subs	r3, r3, r1
	strb	r5, [r0], #1
	cmp	r2, r3
	bhi	.L48
	pop	{r4, r5, r6, r7, pc}
.L62:
	strb	r3, [r0], #1
	bx	lr
	.size	SEGGER_SYSVIEW_EncodeString, .-SEGGER_SYSVIEW_EncodeString
	.section	.text.SEGGER_SYSVIEW_EncodeData,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_EncodeData
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_EncodeData, %function
SEGGER_SYSVIEW_EncodeData:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5, r6}
	mov	r5, r0
	strb	r2, [r5], #1
	cbz	r2, .L64
	adds	r3, r1, #4
	adds	r4, r0, #5
	cmp	r1, r4
	it	cc
	cmpcc	r5, r3
	bcc	.L66
	subs	r3, r2, #1
	cmp	r3, #7
	bls	.L66
	bic	r6, r2, #3
	mov	r3, r1
	mov	r4, r5
	add	r6, r6, r1
.L67:
	ldr	r0, [r3], #4	@ unaligned
	cmp	r3, r6
	str	r0, [r4], #4	@ unaligned
	bne	.L67
	bic	r3, r2, #3
	cmp	r2, r3
	add	r4, r1, r3
	add	r0, r5, r3
	beq	.L71
	ldrb	r6, [r1, r3]	@ zero_extendqisi2
	adds	r1, r3, #1
	cmp	r2, r1
	strb	r6, [r5, r3]
	bls	.L71
	adds	r3, r3, #2
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	cmp	r2, r3
	strb	r1, [r0, #1]
	bls	.L71
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r0, #2]
.L71:
	add	r5, r5, r2
.L64:
	mov	r0, r5
	pop	{r4, r5, r6}
	bx	lr
.L66:
	adds	r4, r1, r2
.L70:
	ldrb	r3, [r1], #1	@ zero_extendqisi2
	cmp	r1, r4
	strb	r3, [r0, #1]!
	bne	.L70
	b	.L71
	.size	SEGGER_SYSVIEW_EncodeData, .-SEGGER_SYSVIEW_EncodeData
	.section	.text.SEGGER_SYSVIEW_EncodeId,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_EncodeId
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_EncodeId, %function
SEGGER_SYSVIEW_EncodeId:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L89
	ldr	r3, [r3, #16]
	subs	r1, r1, r3
	lsrs	r1, r1, #2
	cmp	r1, #127
	bls	.L86
.L87:
	orn	r3, r1, #127
	lsrs	r1, r1, #7
	cmp	r1, #127
	strb	r3, [r0], #1
	bhi	.L87
.L86:
	strb	r1, [r0], #1
	bx	lr
.L90:
	.align	2
.L89:
	.word	.LANCHOR0
	.size	SEGGER_SYSVIEW_EncodeId, .-SEGGER_SYSVIEW_EncodeId
	.section	.text.SEGGER_SYSVIEW_ShrinkId,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_ShrinkId
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_ShrinkId, %function
SEGGER_SYSVIEW_ShrinkId:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L92
	ldr	r3, [r3, #16]
	subs	r0, r0, r3
	lsrs	r0, r0, #2
	bx	lr
.L93:
	.align	2
.L92:
	.word	.LANCHOR0
	.size	SEGGER_SYSVIEW_ShrinkId, .-SEGGER_SYSVIEW_ShrinkId
	.section	.text.SEGGER_SYSVIEW_SendModule,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_SendModule
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_SendModule, %function
SEGGER_SYSVIEW_SendModule:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L140
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L136
	push	{r4, r5, r6, r7, r8, lr}
	cmp	r0, #0
	beq	.L96
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L94
	movs	r2, #0
	b	.L97
.L98:
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L94
.L97:
	adds	r2, r2, #1
	cmp	r2, r0
	bne	.L98
	.syntax unified
@ 2437 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r0, #127
	bls	.L139
	ldr	r2, .L140+4
	strb	r0, [r2, #4]
	adds	r2, r2, #5
	movs	r0, #1
.L110:
	mov	r1, r2
	strb	r0, [r1], #1
	ldr	r2, [r3, #8]
	cmp	r2, #127
	bls	.L100
.L101:
	orn	r0, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r0, [r1], #1
	bhi	.L101
.L100:
	mov	r7, r1
	strb	r2, [r7], #2
	ldr	r6, [r3]
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L102
	mov	r5, r6
	mov	r3, r6
	rsb	ip, r6, #1
.L103:
	add	r0, ip, r3
	ldrb	r2, [r3, #1]!	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L103
	cmp	r0, #128
	add	r2, r6, #4
	add	r3, r1, #6
	mov	ip, r0
	it	cs
	movcs	ip, #128
	cmp	r6, r3
	it	cc
	cmpcc	r7, r2
	strb	ip, [r1, #1]
	bcc	.L115
	cmp	r0, #26
	bls	.L115
	cmp	r0, #0
	mov	r3, r7
	mov	r2, r7
	ite	ne
	movne	r8, ip
	moveq	r8, #1
	bic	lr, r8, #3
	add	lr, lr, r6
.L108:
	mov	r0, r3
	ldr	r1, [r5], #4	@ unaligned
	adds	r0, r0, #4
	cmp	r5, lr
	str	r1, [r2], #4	@ unaligned
	mov	r3, r0
	bne	.L108
	bic	r3, r8, #3
	cmp	r3, r8
	add	r5, r6, r3
	add	r2, r7, r3
	beq	.L112
	adds	r1, r3, #1
	ldrb	r0, [r6, r3]	@ zero_extendqisi2
	cmp	ip, r1
	strb	r0, [r7, r3]
	add	r0, r2, #1
	bls	.L112
	adds	r3, r3, #2
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	adds	r0, r2, #2
	cmp	ip, r3
	strb	r1, [r2, #1]
	bls	.L112
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	adds	r0, r2, #3
	strb	r3, [r2, #2]
.L112:
	movs	r1, #22
	bl	_SendPacket.constprop.4
	.syntax unified
@ 2448 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
.L94:
	pop	{r4, r5, r6, r7, r8, pc}
.L136:
	bx	lr
.L115:
	subs	r6, r6, #1
	mov	r0, r7
.L106:
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	strb	r3, [r0], #1
	subs	r3, r0, #2
	subs	r3, r3, r1
	cmp	ip, r3
	bhi	.L106
	b	.L112
.L102:
	strb	r3, [r1, #1]
	mov	r0, r7
	b	.L112
.L96:
	.syntax unified
@ 2437 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r2, .L140+8
	b	.L110
.L139:
	ldr	r2, .L140+8
	b	.L110
.L141:
	.align	2
.L140:
	.word	.LANCHOR4
	.word	.LANCHOR3
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_SendModule, .-SEGGER_SYSVIEW_SendModule
	.section	.text._HandleIncomingPacket,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	_HandleIncomingPacket, %function
_HandleIncomingPacket:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
	movs	r2, #1
	sub	sp, sp, #12
	mov	r0, r2
	add	r1, sp, #7
	bl	SEGGER_RTT_ReadNoLock
	cmp	r0, #0
	ble	.L142
	ldrb	r3, [sp, #7]	@ zero_extendqisi2
	cmp	r3, #4
	beq	.L145
	bls	.L179
	cmp	r3, #6
	beq	.L151
	bcc	.L152
	cmp	r3, #7
	beq	.L153
	cmp	r3, #128
	bne	.L150
	movs	r2, #1
	add	r1, sp, #7
	mov	r0, r2
	bl	SEGGER_RTT_ReadNoLock
	cmp	r0, #0
	bgt	.L180
.L142:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, pc}
.L179:
	cmp	r3, #2
	beq	.L147
	bhi	.L148
	cmp	r3, #1
	bne	.L150
	bl	SEGGER_SYSVIEW_Start
	b	.L142
.L148:
	bl	SEGGER_SYSVIEW_RecordSystime
	b	.L142
.L153:
	ldr	r3, .L183
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L142
.L160:
	ldr	r3, [r4, #12]
	cbz	r3, .L158
.L181:
	blx	r3
	ldr	r4, [r4, #16]
	cmp	r4, #0
	beq	.L142
	ldr	r3, [r4, #12]
	cmp	r3, #0
	bne	.L181
.L158:
	ldr	r4, [r4, #16]
	cmp	r4, #0
	bne	.L160
	b	.L142
.L150:
	lsls	r3, r3, #24
	bpl	.L142
	movs	r2, #1
	add	r1, sp, #7
	mov	r0, r2
	bl	SEGGER_RTT_ReadNoLock
	b	.L142
.L147:
	.syntax unified
@ 1675 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r4, .L183+4
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbnz	r3, .L182
.L155:
	.syntax unified
@ 1681 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	b	.L142
.L152:
	bl	SEGGER_SYSVIEW_GetSysDesc
	b	.L142
.L151:
	.syntax unified
@ 2485 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, .L183+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	lsls	r2, r3, #24
	bpl	.L161
	ldr	r0, .L183+12
	strb	r3, [r0, #4]
	adds	r0, r0, #5
	movs	r3, #1
.L157:
	movs	r1, #27
	strb	r3, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 2489 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	b	.L142
.L145:
	ldr	r3, .L183+4
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L142
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L142
	blx	r3
	b	.L142
.L180:
	ldrb	r0, [sp, #7]	@ zero_extendqisi2
	bl	SEGGER_SYSVIEW_SendModule
	b	.L142
.L182:
	movs	r1, #11
	ldr	r0, .L183+16
	bl	_SendPacket.constprop.4
	movs	r3, #0
	strb	r3, [r4]
	b	.L155
.L161:
	ldr	r0, .L183+16
	b	.L157
.L184:
	.align	2
.L183:
	.word	.LANCHOR4
	.word	.LANCHOR0
	.word	.LANCHOR5
	.word	.LANCHOR3
	.word	.LANCHOR3+4
	.size	_HandleIncomingPacket, .-_HandleIncomingPacket
	.section	.text._SendPacket,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	_SendPacket, %function
_SendPacket:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	ldr	r5, .L208
	sub	sp, sp, #12
	mov	r4, r0
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L191
	cbz	r3, .L190
	cmp	r3, #2
	beq	.L203
.L191:
	cmp	r2, #31
	bhi	.L204
	ldr	r3, [r5, #28]
	lsrs	r3, r3, r2
	lsls	r3, r3, #31
	bmi	.L190
	cmp	r2, #23
	uxtb	r3, r2
	bhi	.L188
	subs	r0, r4, #1
	strb	r3, [r4, #-1]
.L193:
	ldr	r2, .L208+4
	ldr	r3, [r5, #12]
	ldr	r6, [r2]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L197
.L198:
	orn	r4, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r4, [r1], #1
	bhi	.L198
.L197:
	mov	r2, r1
	mov	r1, r0
	strb	r3, [r2], #1
	subs	r2, r2, r0
	movs	r0, #1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L199
	str	r6, [r5, #12]
.L190:
	ldr	r3, .L208+8
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L185
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L205
.L185:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L204:
	uxtb	r3, r2
.L188:
	subs	r6, r1, r4
	cmp	r6, #127
	uxtb	r0, r6
	bhi	.L206
	cmp	r2, #127
	add	r6, r4, #-1
	strb	r0, [r4, #-1]
	bls	.L196
.L207:
	lsrs	r2, r2, #7
	orn	r3, r3, #127
	subs	r0, r6, #2
	strb	r2, [r6, #-1]
	strb	r3, [r6, #-2]
	b	.L193
.L205:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L199:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L190
.L206:
	orn	r7, r0, #127
	cmp	r2, #127
	ubfx	r0, r6, #7, #8
	sub	r6, r4, #2
	strb	r7, [r4, #-2]
	strb	r0, [r4, #-1]
	bhi	.L207
.L196:
	subs	r0, r6, #1
	strb	r3, [r6, #-1]
	b	.L193
.L203:
	strd	r1, r2, [sp]
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L190
	ldrd	r1, r2, [sp]
	b	.L191
.L209:
	.align	2
.L208:
	.word	.LANCHOR0
	.word	-536866812
	.word	_SEGGER_RTT
	.size	_SendPacket, .-_SendPacket
	.section	.text._PrintUnsigned,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	_PrintUnsigned, %function
_PrintUnsigned:
	@ args = 8, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r5, r2
	sub	sp, sp, #12
	mov	r7, r1
	mov	r6, r0
	cmp	r1, r5
	mov	r10, r3
	ldrd	r9, r2, [sp, #48]
	bcc	.L240
	mov	r3, r1
	mov	r8, #1
.L212:
	add	r8, r8, #1
	udiv	r3, r3, r5
	cmp	r5, r3
	bls	.L212
.L211:
	cmp	r8, r10
	ldr	r1, [r6, #16]
	it	cc
	movcc	r8, r10
	lsls	r0, r2, #31
	bpl	.L213
	adds	r3, r9, #0
	add	r0, r1, #1
	it	ne
	movne	r3, #1
	str	r3, [sp, #4]
.L214:
	movs	r4, #1
	b	.L227
.L270:
	add	r10, r10, #-1
.L225:
	mul	r4, r5, r4
.L227:
	cmp	r10, #1
	bhi	.L270
	udiv	r2, r7, r4
	cmp	r5, r2
	bls	.L225
	ldr	r10, .L275
	mov	fp, #0
	b	.L226
.L229:
	cmp	r4, r5
	udiv	r2, r4, r5
	bcc	.L271
.L243:
	mov	r4, r2
	adds	r0, r1, #1
	udiv	r2, r7, r2
.L226:
	cmp	r0, #128
	mls	r7, r4, r2, r7
	bhi	.L228
	ldr	r3, [r6, #4]
	mov	r1, r0
	ldrb	r2, [r10, r2]	@ zero_extendqisi2
	add	lr, r3, #1
	str	lr, [r6, #4]
	strb	r2, [r3]
	str	r0, [r6, #16]
.L228:
	cmp	r1, #128
	bne	.L229
	ldr	r2, [r6, #8]
	strb	r1, [r2]
	ldr	r2, [r6, #12]
	ldr	r0, [r6, #4]
	cmp	r2, #127
	bls	.L230
.L231:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r0], #1
	bhi	.L231
.L230:
	strb	r2, [r0]
	adds	r1, r0, #2
	strb	fp, [r0, #1]
	movs	r2, #26
	ldr	r0, [r6, #8]
	bl	_SendPacket
	ldr	r2, [r6]
	cmp	r4, r5
	mov	r1, #0
	add	r0, r2, #4
	add	r2, r2, #5
	str	fp, [r6, #16]
	strd	r2, r0, [r6, #4]
	udiv	r2, r4, r5
	bcs	.L243
.L271:
	ldr	r3, [sp, #4]
	cmp	r3, #0
	bne	.L272
.L210:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L213:
	cmp	r9, #0
	beq	.L241
	lsls	r3, r2, #30
	bpl	.L244
	cmp	r10, #0
	bne	.L244
	movs	r4, #48
.L215:
	cmp	r9, r8
	add	r0, r1, #1
	bls	.L222
	mov	fp, #0
	b	.L221
.L218:
	adds	r0, r1, #1
	cmp	r9, #0
	beq	.L222
.L273:
	cmp	r9, r8
	bls	.L222
.L221:
	cmp	r0, #128
	add	r9, r9, #-1
	bhi	.L217
	ldr	r3, [r6, #4]
	mov	r1, r0
	adds	r2, r3, #1
	str	r2, [r6, #4]
	strb	r4, [r3]
	str	r0, [r6, #16]
.L217:
	cmp	r1, #128
	bne	.L218
	ldr	r3, [r6, #8]
	strb	r1, [r3]
	ldr	r3, [r6, #12]
	ldr	r2, [r6, #4]
	cmp	r3, #127
	bls	.L219
.L220:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L220
.L219:
	strb	r3, [r2]
	adds	r1, r2, #2
	strb	fp, [r2, #1]
	movs	r2, #26
	ldr	r0, [r6, #8]
	bl	_SendPacket
	ldr	r3, [r6]
	movs	r1, #0
	str	fp, [r6, #16]
	adds	r2, r3, #4
	adds	r3, r3, #5
	adds	r0, r1, #1
	strd	r3, r2, [r6, #4]
	cmp	r9, #0
	bne	.L273
.L222:
	movs	r3, #0
	str	r3, [sp, #4]
	b	.L214
.L241:
	str	r9, [sp, #4]
	adds	r0, r1, #1
	b	.L214
.L272:
	cmp	r9, r8
	bls	.L210
	cmp	r9, #0
	beq	.L210
	movs	r4, #32
	movs	r5, #0
.L233:
	ldr	r3, [r6, #16]
	add	r9, r9, #-1
	adds	r2, r3, #1
	cmp	r2, #128
	bhi	.L235
	ldr	r1, [r6, #4]
	mov	r3, r2
	adds	r0, r1, #1
	str	r0, [r6, #4]
	strb	r4, [r1]
	str	r2, [r6, #16]
.L235:
	cmp	r3, #128
	beq	.L274
.L236:
	cmp	r9, #0
	beq	.L210
	cmp	r9, r8
	bhi	.L233
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L274:
	ldr	r2, [r6, #8]
	strb	r3, [r2]
	ldr	r3, [r6, #12]
	ldr	r2, [r6, #4]
	cmp	r3, #127
	bls	.L237
.L238:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L238
.L237:
	strb	r3, [r2]
	adds	r1, r2, #2
	strb	r5, [r2, #1]
	movs	r2, #26
	ldr	r0, [r6, #8]
	bl	_SendPacket
	ldr	r3, [r6]
	str	r5, [r6, #16]
	adds	r2, r3, #4
	adds	r3, r3, #5
	strd	r3, r2, [r6, #4]
	b	.L236
.L244:
	movs	r4, #32
	b	.L215
.L240:
	mov	r8, #1
	b	.L211
.L276:
	.align	2
.L275:
	.word	.LANCHOR6
	.size	_PrintUnsigned, .-_PrintUnsigned
	.section	.text._SendPacket.constprop.4,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	_SendPacket.constprop.4, %function
_SendPacket.constprop.4:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	ldr	r5, .L305
	sub	sp, sp, #12
	mov	r4, r0
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L283
	cbz	r3, .L282
	cmp	r3, #2
	beq	.L300
.L283:
	cmp	r1, #31
	bhi	.L301
	ldr	r3, [r5, #28]
	lsrs	r3, r3, r1
	lsls	r3, r3, #31
	bmi	.L282
	cmp	r1, #23
	uxtb	r0, r1
	ldr	r2, .L305+4
	bhi	.L285
	strb	r0, [r2, #3]!
.L286:
	ldr	r1, .L305+8
	ldr	r3, [r5, #12]
	ldr	r6, [r1]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L289
.L290:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r4], #1
	bhi	.L290
.L289:
	mov	r1, r2
	strb	r3, [r4], #1
	movs	r0, #1
	subs	r2, r4, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L291
	str	r6, [r5, #12]
.L282:
	ldr	r3, .L305+12
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L277
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L302
.L277:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L301:
	ldr	r2, .L305+4
	adds	r3, r2, #4
	subs	r3, r4, r3
	cmp	r3, #127
	uxtb	r6, r3
	bhi	.L303
	cmp	r1, #127
	add	r3, r2, #3
	uxtb	r0, r1
	strb	r6, [r2, #3]
	bls	.L288
.L304:
	lsrs	r1, r1, #7
	orn	r0, r0, #127
	subs	r2, r3, #2
	strb	r1, [r3, #-1]
	strb	r0, [r3, #-2]
	b	.L286
.L302:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L291:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L282
.L303:
	uxtb	r0, r1
.L293:
	orn	r7, r6, #127
	cmp	r1, #127
	ubfx	r6, r3, #7, #8
	ldr	r3, .L305+16
	strb	r7, [r2, #2]
	strb	r6, [r2, #3]
	bhi	.L304
.L288:
	subs	r2, r3, #1
	strb	r0, [r3, #-1]
	b	.L286
.L300:
	str	r1, [sp, #4]
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L282
	ldr	r1, [sp, #4]
	b	.L283
.L285:
	adds	r3, r2, #4
	subs	r3, r4, r3
	cmp	r3, #127
	uxtb	r6, r3
	bhi	.L293
	mov	r3, r2
	strb	r6, [r3, #3]!
	b	.L288
.L306:
	.align	2
.L305:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	_SEGGER_RTT
	.word	.LANCHOR3+2
	.size	_SendPacket.constprop.4, .-_SendPacket.constprop.4
	.section	.text.SEGGER_SYSVIEW_RecordU32,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32, %function
SEGGER_SYSVIEW_RecordU32:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r3, r1
	.syntax unified
@ 1287 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r3, #127
	ldr	r2, .L313
	bls	.L308
.L309:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L309
.L308:
	mov	r1, r0
	strb	r3, [r2], #1
	mov	r0, r2
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1292 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, pc}
.L314:
	.align	2
.L313:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32, .-SEGGER_SYSVIEW_RecordU32
	.section	.text.SEGGER_SYSVIEW_RecordU32x2,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x2
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x2, %function
SEGGER_SYSVIEW_RecordU32x2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r4, r1
	.syntax unified
@ 1310 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r4, #127
	ldr	r3, .L324
	bls	.L316
.L317:
	orn	r1, r4, #127
	lsrs	r4, r4, #7
	cmp	r4, #127
	strb	r1, [r3], #1
	bhi	.L317
.L316:
	cmp	r2, #127
	strb	r4, [r3], #1
	bls	.L318
.L319:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L319
.L318:
	mov	r1, r0
	strb	r2, [r3], #1
	mov	r0, r3
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1316 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, pc}
.L325:
	.align	2
.L324:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x2, .-SEGGER_SYSVIEW_RecordU32x2
	.section	.text._VPrintHost,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	_VPrintHost, %function
_VPrintHost:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r5, r1
	sub	sp, sp, #76
	movs	r4, #0
	mov	r1, r0
.L327:
	ldrb	r3, [r1], #1	@ zero_extendqisi2
	cbz	r3, .L374
	cmp	r3, #37
	bne	.L327
	add	r3, sp, #72
	ldr	r6, [r2]
	add	r7, r3, r4, lsl #2
	adds	r3, r4, #1
	add	ip, r6, #4
	ldr	r6, [r6]
	cmp	r3, #16
	mov	r4, r3
	str	ip, [r2]
	str	r6, [r7, #-64]
	bne	.L327
	movs	r2, #15
	str	r3, [sp, #4]
	b	.L329
.L374:
	uxtb	r3, r4
	subs	r2, r4, #1
	str	r3, [sp, #4]
.L329:
	.syntax unified
@ 787 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r8, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldrb	r1, [r0]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L331
	mov	r1, r0
	mov	r3, r0
	rsb	ip, r0, #1
.L332:
	add	r7, ip, r3
	ldrb	r6, [r3, #1]!	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L332
	ldr	r6, .L377
	cmp	r7, #128
	add	r3, r0, #4
	mov	r9, r7
	add	r10, r6, #5
	add	ip, r6, #9
	it	cs
	movcs	r9, #128
	cmp	ip, r0
	it	hi
	cmphi	r3, r10
	strb	r9, [r6, #4]
	bhi	.L351
	cmp	r7, #26
	bls	.L351
	cmp	r7, #0
	mov	r6, r10
	mov	r7, r10
	ite	ne
	movne	fp, r9
	moveq	fp, #1
	bic	lr, fp, #3
	add	lr, lr, r0
.L337:
	mov	r3, r6
	ldr	ip, [r1], #4	@ unaligned
	adds	r3, r3, #4
	cmp	r1, lr
	str	ip, [r7], #4	@ unaligned
	mov	r6, r3
	bne	.L337
	bic	r1, fp, #3
	cmp	r1, fp
	add	r7, r0, r1
	add	r6, r10, r1
	beq	.L373
	ldrb	r3, [r0, r1]	@ zero_extendqisi2
	adds	r0, r1, #1
	cmp	r9, r0
	strb	r3, [r10, r1]
	add	r3, r6, #1
	bls	.L373
	adds	r1, r1, #2
	ldrb	r0, [r7, #1]	@ zero_extendqisi2
	adds	r3, r6, #2
	cmp	r9, r1
	strb	r0, [r6, #1]
	bls	.L373
	ldrb	r1, [r7, #2]	@ zero_extendqisi2
	cmp	r5, #127
	add	r3, r6, #3
	strb	r1, [r6, #2]
	bls	.L375
.L340:
	orn	r1, r5, #127
	lsrs	r5, r5, #7
	strb	r1, [r3], #1
.L373:
	cmp	r5, #127
	bhi	.L340
.L375:
	mov	r1, r3
	cmp	r4, #127
	strb	r5, [r1], #1
	bhi	.L342
	b	.L376
.L354:
	mov	r1, r3
.L342:
	orn	r0, r4, #127
	lsrs	r4, r4, #7
	mov	r3, r1
	cmp	r4, #127
	strb	r0, [r3], #1
	bhi	.L354
	adds	r1, r1, #2
	strb	r4, [r3]
.L348:
	add	r4, sp, #8
.L347:
	ldr	r3, [r4], #4
	cmp	r3, #127
	bls	.L345
.L346:
	orn	r0, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r0, [r1], #1
	bhi	.L346
.L345:
	mov	r0, r1
	subs	r2, r2, #1
	strb	r3, [r0], #1
	adds	r3, r2, #1
	mov	r1, r0
	bne	.L347
.L344:
	movs	r1, #26
	bl	_SendPacket.constprop.4
	.syntax unified
@ 797 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r8  
	
@ 0 "" 2
	.thumb
	.syntax unified
	movs	r0, #0
	add	sp, sp, #76
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L351:
	subs	r6, r0, #1
	ldr	r3, .L377+4
.L335:
	adds	r1, r6, #2
	ldrb	r7, [r6, #1]	@ zero_extendqisi2
	adds	r6, r6, #1
	subs	r1, r1, r0
	strb	r7, [r3], #1
	cmp	r9, r1
	bhi	.L335
	b	.L373
.L331:
	ldr	r3, .L377
	strb	r1, [r3, #4]
	adds	r3, r3, #5
	b	.L373
.L376:
	ldr	r1, [sp, #4]
	adds	r0, r3, #2
	strb	r1, [r3, #1]
	cmp	r4, #0
	beq	.L344
	mov	r1, r0
	b	.L348
.L378:
	.align	2
.L377:
	.word	.LANCHOR3
	.word	.LANCHOR3+5
	.size	_VPrintHost, .-_VPrintHost
	.section	.text.SEGGER_SYSVIEW_RecordU32x3,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x3, %function
SEGGER_SYSVIEW_RecordU32x3:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r6, r0
	mov	r4, r1
	.syntax unified
@ 1335 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r4, #127
	ldr	r1, .L394
	bls	.L391
.L381:
	orn	r0, r4, #127
	lsrs	r4, r4, #7
	cmp	r4, #127
	strb	r0, [r1], #1
	bhi	.L381
	cmp	r2, #127
	strb	r4, [r1], #1
	bls	.L392
.L383:
	orn	r4, r2, #127
	lsrs	r2, r2, #7
.L391:
	cmp	r2, #127
	strb	r4, [r1], #1
	bhi	.L383
	cmp	r3, #127
	strb	r2, [r1], #1
	bls	.L393
.L385:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
.L392:
	cmp	r3, #127
	strb	r2, [r1], #1
	bhi	.L385
.L393:
	mov	r0, r1
	mov	r1, r6
	strb	r3, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1342 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L395:
	.align	2
.L394:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x3, .-SEGGER_SYSVIEW_RecordU32x3
	.section	.text.SEGGER_SYSVIEW_RecordU32x4,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x4
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x4, %function
SEGGER_SYSVIEW_RecordU32x4:
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	ldr	r4, [sp, #24]
	mov	r7, r0
	mov	r5, r1
	.syntax unified
@ 1362 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r5, #127
	ldr	r1, .L414
	bls	.L397
.L398:
	orn	r0, r5, #127
	lsrs	r5, r5, #7
	cmp	r5, #127
	strb	r0, [r1], #1
	bhi	.L398
.L397:
	cmp	r2, #127
	strb	r5, [r1], #1
	bls	.L411
.L400:
	orn	r0, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r0, [r1], #1
	bhi	.L400
	cmp	r3, #127
	strb	r2, [r1], #1
	bls	.L412
.L402:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
.L411:
	cmp	r3, #127
	strb	r2, [r1], #1
	bhi	.L402
	cmp	r4, #127
	strb	r3, [r1], #1
	bls	.L413
.L404:
	orn	r3, r4, #127
	lsrs	r4, r4, #7
.L412:
	cmp	r4, #127
	strb	r3, [r1], #1
	bhi	.L404
.L413:
	mov	r0, r1
	mov	r1, r7
	strb	r4, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1370 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L415:
	.align	2
.L414:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x4, .-SEGGER_SYSVIEW_RecordU32x4
	.section	.text.SEGGER_SYSVIEW_RecordU32x5,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x5
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x5, %function
SEGGER_SYSVIEW_RecordU32x5:
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r7, r0
	mov	r0, r1
	ldrd	r5, r4, [sp, #24]
	.syntax unified
@ 1391 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r0, #127
	ldr	r1, .L438
	bls	.L434
.L418:
	orn	ip, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	ip, [r1], #1
	bhi	.L418
	cmp	r2, #127
	strb	r0, [r1], #1
	bls	.L435
.L420:
	orn	r0, r2, #127
	lsrs	r2, r2, #7
.L434:
	cmp	r2, #127
	strb	r0, [r1], #1
	bhi	.L420
	cmp	r3, #127
	strb	r2, [r1], #1
	bls	.L436
.L422:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
.L435:
	cmp	r3, #127
	strb	r2, [r1], #1
	bhi	.L422
	cmp	r5, #127
	strb	r3, [r1], #1
	bls	.L437
.L424:
	orn	r3, r5, #127
	lsrs	r5, r5, #7
.L436:
	cmp	r5, #127
	strb	r3, [r1], #1
	bhi	.L424
.L437:
	cmp	r4, #127
	strb	r5, [r1], #1
	bls	.L425
.L426:
	orn	r3, r4, #127
	lsrs	r4, r4, #7
	cmp	r4, #127
	strb	r3, [r1], #1
	bhi	.L426
.L425:
	mov	r0, r1
	mov	r1, r7
	strb	r4, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1400 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L439:
	.align	2
.L438:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x5, .-SEGGER_SYSVIEW_RecordU32x5
	.section	.text.SEGGER_SYSVIEW_RecordU32x6,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x6
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x6, %function
SEGGER_SYSVIEW_RecordU32x6:
	@ args = 12, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	ip, r1
	mov	r7, r0
	ldr	r4, [sp, #32]
	ldrd	r0, r5, [sp, #24]
	.syntax unified
@ 1422 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	ip, #127
	ldr	r1, .L465
	bls	.L461
.L442:
	orn	lr, ip, #127
	lsr	ip, ip, #7
	cmp	ip, #127
	strb	lr, [r1], #1
	bhi	.L442
	cmp	r2, #127
	strb	ip, [r1], #1
	bls	.L462
.L444:
	orn	ip, r2, #127
	lsrs	r2, r2, #7
.L461:
	cmp	r2, #127
	strb	ip, [r1], #1
	bhi	.L444
	cmp	r3, #127
	strb	r2, [r1], #1
	bls	.L463
.L446:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
.L462:
	cmp	r3, #127
	strb	r2, [r1], #1
	bhi	.L446
	cmp	r0, #127
	strb	r3, [r1], #1
	bls	.L464
.L448:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
.L463:
	cmp	r0, #127
	strb	r3, [r1], #1
	bhi	.L448
.L464:
	cmp	r5, #127
	strb	r0, [r1], #1
	bls	.L449
.L450:
	orn	r3, r5, #127
	lsrs	r5, r5, #7
	cmp	r5, #127
	strb	r3, [r1], #1
	bhi	.L450
.L449:
	cmp	r4, #127
	strb	r5, [r1], #1
	bls	.L451
.L452:
	orn	r3, r4, #127
	lsrs	r4, r4, #7
	cmp	r4, #127
	strb	r3, [r1], #1
	bhi	.L452
.L451:
	mov	r0, r1
	mov	r1, r7
	strb	r4, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1432 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L466:
	.align	2
.L465:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x6, .-SEGGER_SYSVIEW_RecordU32x6
	.section	.text.SEGGER_SYSVIEW_RecordU32x7,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x7
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x7, %function
SEGGER_SYSVIEW_RecordU32x7:
	@ args = 16, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	mov	lr, r1
	ldrd	ip, r7, [sp, #24]
	ldrd	r0, r4, [sp, #32]
	.syntax unified
@ 1455 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	lr, #127
	ldr	r1, .L495
	bls	.L491
.L469:
	orn	r8, lr, #127
	lsr	lr, lr, #7
	cmp	lr, #127
	strb	r8, [r1], #1
	bhi	.L469
	cmp	r2, #127
	strb	lr, [r1], #1
	bls	.L492
.L471:
	orn	lr, r2, #127
	lsrs	r2, r2, #7
.L491:
	cmp	r2, #127
	strb	lr, [r1], #1
	bhi	.L471
	cmp	r3, #127
	strb	r2, [r1], #1
	bls	.L493
.L473:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
.L492:
	cmp	r3, #127
	strb	r2, [r1], #1
	bhi	.L473
	cmp	ip, #127
	strb	r3, [r1], #1
	bls	.L494
.L475:
	orn	r3, ip, #127
	lsr	ip, ip, #7
.L493:
	cmp	ip, #127
	strb	r3, [r1], #1
	bhi	.L475
.L494:
	cmp	r7, #127
	strb	ip, [r1], #1
	bls	.L476
.L477:
	orn	r3, r7, #127
	lsrs	r7, r7, #7
	cmp	r7, #127
	strb	r3, [r1], #1
	bhi	.L477
.L476:
	cmp	r0, #127
	strb	r7, [r1], #1
	bls	.L478
.L479:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r1], #1
	bhi	.L479
.L478:
	cmp	r4, #127
	strb	r0, [r1], #1
	bls	.L480
.L481:
	orn	r3, r4, #127
	lsrs	r4, r4, #7
	cmp	r4, #127
	strb	r3, [r1], #1
	bhi	.L481
.L480:
	mov	r0, r1
	mov	r1, r6
	strb	r4, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1466 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, r7, r8, pc}
.L496:
	.align	2
.L495:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x7, .-SEGGER_SYSVIEW_RecordU32x7
	.section	.text.SEGGER_SYSVIEW_RecordU32x8,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x8
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x8, %function
SEGGER_SYSVIEW_RecordU32x8:
	@ args = 20, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, lr}
	ldr	r4, [sp, #48]
	mov	r7, r0
	mov	r8, r1
	ldrd	lr, ip, [sp, #32]
	ldrd	r0, r5, [sp, #40]
	.syntax unified
@ 1490 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r8, #127
	ldr	r1, .L528
	bls	.L524
.L499:
	orn	r9, r8, #127
	lsr	r8, r8, #7
	cmp	r8, #127
	strb	r9, [r1], #1
	bhi	.L499
	cmp	r2, #127
	strb	r8, [r1], #1
	bls	.L525
.L501:
	orn	r8, r2, #127
	lsrs	r2, r2, #7
.L524:
	cmp	r2, #127
	strb	r8, [r1], #1
	bhi	.L501
	cmp	r3, #127
	strb	r2, [r1], #1
	bls	.L526
.L503:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
.L525:
	cmp	r3, #127
	strb	r2, [r1], #1
	bhi	.L503
	cmp	lr, #127
	strb	r3, [r1], #1
	bls	.L527
.L505:
	orn	r3, lr, #127
	lsr	lr, lr, #7
.L526:
	cmp	lr, #127
	strb	r3, [r1], #1
	bhi	.L505
.L527:
	cmp	ip, #127
	strb	lr, [r1], #1
	bls	.L506
.L507:
	orn	r3, ip, #127
	lsr	ip, ip, #7
	cmp	ip, #127
	strb	r3, [r1], #1
	bhi	.L507
.L506:
	cmp	r0, #127
	strb	ip, [r1], #1
	bls	.L508
.L509:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r1], #1
	bhi	.L509
.L508:
	cmp	r5, #127
	strb	r0, [r1], #1
	bls	.L510
.L511:
	orn	r3, r5, #127
	lsrs	r5, r5, #7
	cmp	r5, #127
	strb	r3, [r1], #1
	bhi	.L511
.L510:
	cmp	r4, #127
	strb	r5, [r1], #1
	bls	.L512
.L513:
	orn	r3, r4, #127
	lsrs	r4, r4, #7
	cmp	r4, #127
	strb	r3, [r1], #1
	bhi	.L513
.L512:
	mov	r0, r1
	mov	r1, r7
	strb	r4, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1502 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L529:
	.align	2
.L528:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x8, .-SEGGER_SYSVIEW_RecordU32x8
	.section	.text.SEGGER_SYSVIEW_RecordU32x9,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x9
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x9, %function
SEGGER_SYSVIEW_RecordU32x9:
	@ args = 24, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r9, r0
	mov	r0, r1
	ldrd	lr, ip, [sp, #32]
	ldrd	r7, r6, [sp, #40]
	ldrd	r5, r4, [sp, #48]
	.syntax unified
@ 1527 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r8, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r0, #127
	ldr	r1, .L564
	bls	.L560
.L532:
	orn	r10, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r10, [r1], #1
	bhi	.L532
	cmp	r2, #127
	strb	r0, [r1], #1
	bls	.L561
.L534:
	orn	r0, r2, #127
	lsrs	r2, r2, #7
.L560:
	cmp	r2, #127
	strb	r0, [r1], #1
	bhi	.L534
	cmp	r3, #127
	strb	r2, [r1], #1
	bls	.L562
.L536:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
.L561:
	cmp	r3, #127
	strb	r2, [r1], #1
	bhi	.L536
	cmp	lr, #127
	strb	r3, [r1], #1
	bls	.L563
.L538:
	orn	r3, lr, #127
	lsr	lr, lr, #7
.L562:
	cmp	lr, #127
	strb	r3, [r1], #1
	bhi	.L538
.L563:
	mov	r0, r1
	cmp	ip, #127
	strb	lr, [r0], #1
	bls	.L539
.L540:
	orn	r3, ip, #127
	lsr	ip, ip, #7
	cmp	ip, #127
	strb	r3, [r0], #1
	bhi	.L540
.L539:
	cmp	r7, #127
	strb	ip, [r0], #1
	bls	.L541
.L542:
	orn	r3, r7, #127
	lsrs	r7, r7, #7
	cmp	r7, #127
	strb	r3, [r0], #1
	bhi	.L542
.L541:
	cmp	r6, #127
	strb	r7, [r0], #1
	bls	.L543
.L544:
	orn	r3, r6, #127
	lsrs	r6, r6, #7
	cmp	r6, #127
	strb	r3, [r0], #1
	bhi	.L544
.L543:
	cmp	r5, #127
	strb	r6, [r0], #1
	bls	.L545
.L546:
	orn	r3, r5, #127
	lsrs	r5, r5, #7
	cmp	r5, #127
	strb	r3, [r0], #1
	bhi	.L546
.L545:
	cmp	r4, #127
	strb	r5, [r0], #1
	bls	.L547
.L548:
	orn	r3, r4, #127
	lsrs	r4, r4, #7
	cmp	r4, #127
	strb	r3, [r0], #1
	bhi	.L548
.L547:
	mov	r1, r9
	strb	r4, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1540 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r8  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L565:
	.align	2
.L564:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x9, .-SEGGER_SYSVIEW_RecordU32x9
	.section	.text.SEGGER_SYSVIEW_RecordU32x10,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordU32x10
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordU32x10, %function
SEGGER_SYSVIEW_RecordU32x10:
	@ args = 28, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	ldr	r4, [sp, #64]
	mov	r10, r0
	mov	r0, r1
	ldrd	r8, lr, [sp, #40]
	ldrd	ip, r7, [sp, #48]
	ldrd	r6, r5, [sp, #56]
	.syntax unified
@ 1566 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r9, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r0, #127
	ldr	r1, .L603
	bls	.L599
.L568:
	orn	fp, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	fp, [r1], #1
	bhi	.L568
	cmp	r2, #127
	strb	r0, [r1], #1
	bls	.L600
.L570:
	orn	r0, r2, #127
	lsrs	r2, r2, #7
.L599:
	cmp	r2, #127
	strb	r0, [r1], #1
	bhi	.L570
	cmp	r3, #127
	strb	r2, [r1], #1
	bls	.L601
.L572:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
.L600:
	cmp	r3, #127
	strb	r2, [r1], #1
	bhi	.L572
	cmp	r8, #127
	strb	r3, [r1], #1
	bls	.L602
.L574:
	orn	r3, r8, #127
	lsr	r8, r8, #7
.L601:
	cmp	r8, #127
	strb	r3, [r1], #1
	bhi	.L574
.L602:
	mov	r0, r1
	cmp	lr, #127
	strb	r8, [r0], #1
	bls	.L575
.L576:
	orn	r3, lr, #127
	lsr	lr, lr, #7
	cmp	lr, #127
	strb	r3, [r0], #1
	bhi	.L576
.L575:
	cmp	ip, #127
	strb	lr, [r0], #1
	bls	.L577
.L578:
	orn	r3, ip, #127
	lsr	ip, ip, #7
	cmp	ip, #127
	strb	r3, [r0], #1
	bhi	.L578
.L577:
	cmp	r7, #127
	strb	ip, [r0], #1
	bls	.L579
.L580:
	orn	r3, r7, #127
	lsrs	r7, r7, #7
	cmp	r7, #127
	strb	r3, [r0], #1
	bhi	.L580
.L579:
	cmp	r6, #127
	strb	r7, [r0], #1
	bls	.L581
.L582:
	orn	r3, r6, #127
	lsrs	r6, r6, #7
	cmp	r6, #127
	strb	r3, [r0], #1
	bhi	.L582
.L581:
	cmp	r5, #127
	strb	r6, [r0], #1
	bls	.L583
.L584:
	orn	r3, r5, #127
	lsrs	r5, r5, #7
	cmp	r5, #127
	strb	r3, [r0], #1
	bhi	.L584
.L583:
	cmp	r4, #127
	strb	r5, [r0], #1
	bls	.L585
.L586:
	orn	r3, r4, #127
	lsrs	r4, r4, #7
	cmp	r4, #127
	strb	r3, [r0], #1
	bhi	.L586
.L585:
	mov	r1, r10
	strb	r4, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1580 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r9  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L604:
	.align	2
.L603:
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordU32x10, .-SEGGER_SYSVIEW_RecordU32x10
	.section	.text.SEGGER_SYSVIEW_RecordString,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordString
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordString, %function
SEGGER_SYSVIEW_RecordString:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r6, r0
	mov	r5, r1
	.syntax unified
@ 1601 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L606
	mov	r0, r5
	mov	r3, r5
	rsb	r1, r5, #1
.L607:
	add	ip, r1, r3
	ldrb	r2, [r3, #1]!	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L607
	ldr	r2, .L628
	mov	r1, ip
	adds	r3, r5, #4
	cmp	r1, #128
	add	r7, r2, #5
	add	lr, r2, #9
	it	cs
	movcs	r1, #128
	cmp	lr, r5
	it	hi
	cmphi	r3, r7
	strb	r1, [r2, #4]
	bhi	.L616
	cmp	ip, #26
	bls	.L616
	cmp	ip, #0
	mov	lr, r7
	mov	ip, r7
	ite	ne
	movne	r8, r1
	moveq	r8, #1
	bic	r9, r8, #3
	add	r9, r9, r5
.L612:
	mov	r3, ip
	ldr	r10, [r0], #4	@ unaligned
	adds	r2, r3, #4
	cmp	r0, r9
	str	r10, [lr], #4	@ unaligned
	mov	ip, r2
	bne	.L612
	bic	r3, r8, #3
	mov	r0, r2
	cmp	r8, r3
	add	ip, r5, r3
	add	r2, r7, r3
	beq	.L617
	ldrb	r0, [r5, r3]	@ zero_extendqisi2
	adds	r5, r3, #1
	cmp	r5, r1
	strb	r0, [r7, r3]
	add	r0, r2, #1
	bcs	.L617
	adds	r3, r3, #2
	ldrb	r5, [ip, #1]	@ zero_extendqisi2
	adds	r0, r2, #2
	cmp	r1, r3
	strb	r5, [r2, #1]
	bls	.L617
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	adds	r0, r2, #3
	strb	r3, [r2, #2]
.L617:
	mov	r1, r6
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1605 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L616:
	subs	r2, r5, #1
	ldr	r0, .L628+4
.L610:
	adds	r3, r2, #2
	ldrb	r7, [r2, #1]	@ zero_extendqisi2
	adds	r2, r2, #1
	subs	r3, r3, r5
	strb	r7, [r0], #1
	cmp	r1, r3
	bhi	.L610
	b	.L617
.L606:
	ldr	r0, .L628
	strb	r3, [r0, #4]
	adds	r0, r0, #5
	b	.L617
.L629:
	.align	2
.L628:
	.word	.LANCHOR3
	.word	.LANCHOR3+5
	.size	SEGGER_SYSVIEW_RecordString, .-SEGGER_SYSVIEW_RecordString
	.section	.text.SEGGER_SYSVIEW_SendTaskInfo,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_SendTaskInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_SendTaskInfo, %function
SEGGER_SYSVIEW_SendTaskInfo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, lr}
	mov	r6, r0
	.syntax unified
@ 1723 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r7, .L686
	ldr	r2, [r0]
	ldr	r3, [r7, #16]
	ldr	r4, .L686+4
	subs	r2, r2, r3
	mov	r3, r4
	lsrs	r2, r2, #2
	cmp	r2, #127
	bls	.L631
.L632:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L632
.L631:
	strb	r2, [r3], #1
	ldr	r2, [r6, #8]
	cmp	r2, #127
	bls	.L633
.L634:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L634
.L633:
	mov	r0, r3
	strb	r2, [r0], #2
	ldr	ip, [r6, #4]
	ldrb	r2, [ip]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L635
	mov	r2, ip
	rsb	r8, ip, #1
.L636:
	add	lr, r8, r2
	ldrb	r1, [r2, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L636
	mov	r1, lr
	add	r8, ip, #4
	adds	r2, r3, #6
	cmp	r1, #32
	it	cs
	movcs	r1, #32
	cmp	ip, r2
	it	cc
	cmpcc	r0, r8
	strb	r1, [r3, #1]
	bcc	.L650
	cmp	lr, #26
	bls	.L650
	cmp	lr, #0
	ldr	r2, [ip]	@ unaligned
	add	lr, r0, #4
	ite	ne
	movne	r8, r1
	moveq	r8, #1
	str	r2, [r3, #2]	@ unaligned
	lsr	r2, r8, #2
	cmp	r2, #1
	beq	.L641
	ldr	r9, [ip, #4]	@ unaligned
	cmp	r2, #2
	add	lr, r0, #8
	str	r9, [r3, #6]	@ unaligned
	beq	.L641
	ldr	r9, [ip, #8]	@ unaligned
	cmp	r2, #3
	add	lr, r0, #12
	str	r9, [r3, #10]	@ unaligned
	beq	.L641
	ldr	r9, [ip, #12]	@ unaligned
	cmp	r2, #4
	add	lr, r0, #16
	str	r9, [r3, #14]	@ unaligned
	beq	.L641
	ldr	r9, [ip, #16]	@ unaligned
	cmp	r2, #5
	add	lr, r0, #20
	str	r9, [r3, #18]	@ unaligned
	beq	.L641
	ldr	r9, [ip, #20]	@ unaligned
	cmp	r2, #6
	add	lr, r0, #24
	str	r9, [r3, #22]	@ unaligned
	beq	.L641
	ldr	r9, [ip, #24]	@ unaligned
	cmp	r2, #8
	add	lr, r0, #28
	str	r9, [r3, #26]	@ unaligned
	bne	.L641
	ldr	r2, [ip, #28]	@ unaligned
	adds	r0, r0, #32
	str	r2, [r3, #30]	@ unaligned
.L651:
	movs	r1, #9
	bl	_SendPacket.constprop.4
	ldr	r3, [r7, #16]
	ldr	r2, [r6]
	subs	r2, r2, r3
	mov	r3, r4
	lsrs	r2, r2, #2
	cmp	r2, #127
	bls	.L642
.L643:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L643
.L642:
	strb	r2, [r3], #1
	ldr	r2, [r6, #12]
	cmp	r2, #127
	bls	.L644
.L645:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L645
.L644:
	strb	r2, [r3], #1
	ldr	r2, [r6, #16]
	cmp	r2, #127
	bls	.L646
.L647:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L647
.L646:
	movs	r4, #0
	adds	r0, r3, #2
	movs	r1, #21
	strb	r2, [r3]
	strb	r4, [r3, #1]
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1737 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L641:
	bic	r3, r8, #3
	cmp	r3, r8
	add	r2, r0, r3
	add	r9, ip, r3
	beq	.L653
	ldrb	lr, [ip, r3]	@ zero_extendqisi2
	add	ip, r3, #1
	mov	r0, r2
	cmp	r1, ip
	strb	lr, [r0], #1
	bls	.L651
	adds	r3, r3, #2
	ldrb	ip, [r9, #1]	@ zero_extendqisi2
	adds	r0, r2, #2
	cmp	r1, r3
	strb	ip, [r2, #1]
	bls	.L651
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	adds	r0, r2, #3
	strb	r3, [r2, #2]
	b	.L651
.L650:
	add	ip, ip, #-1
.L639:
	ldrb	r2, [ip, #1]!	@ zero_extendqisi2
	strb	r2, [r0], #1
	subs	r2, r0, #2
	subs	r2, r2, r3
	cmp	r1, r2
	bhi	.L639
	b	.L651
.L635:
	strb	r2, [r3, #1]
	b	.L651
.L653:
	mov	r0, lr
	b	.L651
.L687:
	.align	2
.L686:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_SendTaskInfo, .-SEGGER_SYSVIEW_SendTaskInfo
	.section	.text.SEGGER_SYSVIEW_RegisterModule,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RegisterModule
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RegisterModule, %function
SEGGER_SYSVIEW_RegisterModule:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r4, r0
	.syntax unified
@ 2341 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r1, .L722
	ldr	r2, [r1]
	cmp	r2, #0
	beq	.L721
	ldr	r7, .L722+4
	ldr	r3, [r2, #8]
	ldr	r5, [r2, #4]
	ldrb	r0, [r7]	@ zero_extendqisi2
	add	r3, r3, r5
	str	r2, [r4, #16]
	adds	r0, r0, #1
	str	r4, [r1]
	str	r3, [r4, #8]
	uxtb	r2, r3
	strb	r0, [r7]
	.syntax unified
@ 2437 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r7, .L722+8
	movs	r1, #0
	cmp	r3, #127
	strb	r1, [r7, #4]
	add	r7, r7, #5
	bls	.L691
.L692:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r7], #1
	bhi	.L692
	uxtb	r2, r3
.L691:
	mov	r1, r7
	strb	r2, [r1], #2
	ldr	r3, [r4]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L693
	mov	r2, r3
	mov	r0, r3
	rsb	r8, r3, #1
.L694:
	add	lr, r8, r0
	ldrb	ip, [r0, #1]!	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L694
	cmp	lr, #128
	add	r8, r3, #4
	add	r0, r7, #6
	mov	ip, lr
	it	cs
	movcs	ip, #128
	cmp	r3, r0
	it	cc
	cmpcc	r1, r8
	strb	ip, [r7, #1]
	bcc	.L704
	cmp	lr, #26
	bls	.L704
	cmp	lr, #0
	mov	r7, r1
	mov	lr, r1
	ite	ne
	movne	r9, ip
	moveq	r9, #1
	bic	r8, r9, #3
	add	r8, r8, r3
.L699:
	mov	r0, r7
	ldr	r10, [r2], #4	@ unaligned
	adds	r0, r0, #4
	cmp	r2, r8
	str	r10, [lr], #4	@ unaligned
	mov	r7, r0
	bne	.L699
	bic	r2, r9, #3
	cmp	r9, r2
	add	lr, r3, r2
	add	r7, r1, r2
	beq	.L705
	ldrb	r0, [r3, r2]	@ zero_extendqisi2
	adds	r3, r2, #1
	cmp	r3, ip
	strb	r0, [r1, r2]
	add	r0, r7, #1
	bcs	.L705
	adds	r2, r2, #2
	ldrb	r3, [lr, #1]	@ zero_extendqisi2
	adds	r0, r7, #2
	cmp	ip, r2
	strb	r3, [r7, #1]
	bls	.L705
	ldrb	r3, [lr, #2]	@ zero_extendqisi2
	adds	r0, r7, #3
	strb	r3, [r7, #2]
.L705:
	movs	r1, #22
	bl	_SendPacket.constprop.4
	.syntax unified
@ 2448 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, [r4, #12]
	cbz	r3, .L701
	blx	r3
.L701:
	.syntax unified
@ 2367 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L721:
	str	r2, [r0, #16]
	mov	r5, #512
	ldr	r3, .L722+4
	movs	r0, #1
	str	r4, [r1]
	str	r5, [r4, #8]
	strb	r0, [r3]
	.syntax unified
@ 2437 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, .L722+8
	movs	r1, #128
	strb	r2, [r3, #4]
	adds	r7, r3, #6
	strb	r1, [r3, #5]
	movs	r3, #4
	uxtb	r2, r3
	b	.L691
.L704:
	subs	r3, r3, #1
	mov	r0, r1
.L697:
	ldrb	r2, [r3, #1]!	@ zero_extendqisi2
	strb	r2, [r0], #1
	subs	r2, r0, #2
	subs	r2, r2, r7
	cmp	ip, r2
	bhi	.L697
	b	.L705
.L693:
	strb	r2, [r7, #1]
	mov	r0, r1
	b	.L705
.L723:
	.align	2
.L722:
	.word	.LANCHOR4
	.word	.LANCHOR5
	.word	.LANCHOR3
	.size	SEGGER_SYSVIEW_RegisterModule, .-SEGGER_SYSVIEW_RegisterModule
	.section	.text.SEGGER_SYSVIEW_RecordSystime,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordSystime
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordSystime, %function
SEGGER_SYSVIEW_RecordSystime:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	ldr	r3, .L745
	ldr	r3, [r3, #32]
	cbz	r3, .L725
	ldr	r3, [r3]
	cbz	r3, .L725
	blx	r3
	mov	r4, r1
	mov	r2, r1
	.syntax unified
@ 1310 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r0, #127
	ldr	r3, .L745+4
	bls	.L726
.L727:
	orn	r1, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r1, [r3], #1
	bhi	.L727
.L726:
	cmp	r4, #127
	strb	r0, [r3], #1
	bls	.L728
.L729:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L729
.L728:
	mov	r0, r3
	movs	r1, #13
	strb	r2, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1316 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, pc}
.L725:
	ldr	r3, .L745+8
	ldr	r3, [r3]
	.syntax unified
@ 1287 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r3, #127
	ldr	r0, .L745+4
	bls	.L731
.L732:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r0], #1
	bhi	.L732
.L731:
	movs	r1, #12
	strb	r3, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1292 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, pc}
.L746:
	.align	2
.L745:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	-536866812
	.size	SEGGER_SYSVIEW_RecordSystime, .-SEGGER_SYSVIEW_RecordSystime
	.section	.text.SEGGER_SYSVIEW_Start,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_Start
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_Start, %function
SEGGER_SYSVIEW_Start:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	ldr	r4, .L774
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbz	r3, .L773
	pop	{r4, r5, r6, pc}
.L773:
	movs	r0, #1
	strb	r0, [r4]
	.syntax unified
@ 1633 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	movs	r2, #10
	ldr	r1, .L774+4
	bl	SEGGER_RTT_WriteSkipNoLock
	.syntax unified
@ 1635 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
@ 1266 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	movs	r1, #10
	ldr	r0, .L774+8
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1269 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
@ 1640 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r2, [r4, #4]
	ldr	r3, .L774+8
	cmp	r2, #127
	bls	.L749
.L750:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L750
.L749:
	ldr	r1, [r4, #8]
	strb	r2, [r3], #1
	cmp	r1, #127
	bls	.L751
.L752:
	orn	r2, r1, #127
	lsrs	r1, r1, #7
	cmp	r1, #127
	strb	r2, [r3], #1
	bhi	.L752
.L751:
	ldr	r2, [r4, #16]
	strb	r1, [r3], #1
	cmp	r2, #127
	bls	.L753
.L754:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L754
.L753:
	movs	r6, #2
	strb	r2, [r3]
	movs	r1, #24
	adds	r0, r3, r6
	strb	r6, [r3, #1]
	bl	_SendPacket.constprop.4
	.syntax unified
@ 1648 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, [r4, #36]
	cbz	r3, .L755
	blx	r3
.L755:
	bl	SEGGER_SYSVIEW_RecordSystime
	ldr	r3, [r4, #32]
	cbz	r3, .L756
	ldr	r3, [r3, #4]
	cbz	r3, .L756
	blx	r3
.L756:
	.syntax unified
@ 2485 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, .L774+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	lsls	r2, r3, #24
	bpl	.L759
	ldr	r0, .L774+16
	strb	r3, [r0, #4]
	adds	r0, r0, #5
	movs	r3, #1
.L757:
	movs	r1, #27
	strb	r3, [r0], #1
	bl	_SendPacket.constprop.4
	.syntax unified
@ 2489 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L759:
	ldr	r0, .L774+8
	b	.L757
.L775:
	.align	2
.L774:
	.word	.LANCHOR0
	.word	.LANCHOR7
	.word	.LANCHOR3+4
	.word	.LANCHOR5
	.word	.LANCHOR3
	.size	SEGGER_SYSVIEW_Start, .-SEGGER_SYSVIEW_Start
	.section	.text.SEGGER_SYSVIEW_SendPacket,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_SendPacket
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_SendPacket, %function
SEGGER_SYSVIEW_SendPacket:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	mov	r6, r0
	sub	sp, sp, #12
	mov	r4, r1
	.syntax unified
@ 2184 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r7, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L799
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L782
	cbz	r3, .L781
	cmp	r3, #2
	beq	.L794
.L782:
	cmp	r2, #31
	bhi	.L795
	ldr	r3, [r5, #28]
	lsrs	r3, r3, r2
	lsls	r3, r3, #31
	bmi	.L781
	cmp	r2, #23
	uxtb	r1, r2
	bhi	.L779
	adds	r2, r6, #3
	strb	r1, [r6, #3]
.L784:
	ldr	r1, .L799+4
	ldr	r3, [r5, #12]
	ldr	r6, [r1]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L788
.L789:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r4], #1
	bhi	.L789
.L788:
	mov	r1, r2
	strb	r3, [r4], #1
	movs	r0, #1
	subs	r2, r4, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L790
	str	r6, [r5, #12]
.L781:
	ldr	r3, .L799+8
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L791
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L796
.L791:
	.syntax unified
@ 2188 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r7  
	
@ 0 "" 2
	.thumb
	.syntax unified
	movs	r0, #0
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L795:
	uxtb	r1, r2
.L779:
	adds	r3, r6, #4
	subs	r3, r4, r3
	cmp	r3, #127
	uxtb	r0, r3
	bhi	.L797
	mov	r3, r0
	cmp	r2, #127
	add	ip, r6, #3
	strb	r3, [r6, #3]
	bls	.L787
.L798:
	lsrs	r3, r2, #7
	orn	r1, r1, #127
	sub	r2, ip, #2
	strb	r3, [ip, #-1]
	strb	r1, [ip, #-2]
	b	.L784
.L796:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	b	.L791
.L790:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L781
.L797:
	orn	r0, r0, #127
	ubfx	r3, r3, #7, #8
	cmp	r2, #127
	add	ip, r6, #2
	strb	r0, [r6, #2]
	strb	r3, [r6, #3]
	bhi	.L798
.L787:
	add	r2, ip, #-1
	strb	r1, [ip, #-1]
	b	.L784
.L794:
	str	r2, [sp, #4]
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L781
	ldr	r2, [sp, #4]
	b	.L782
.L800:
	.align	2
.L799:
	.word	.LANCHOR0
	.word	-536866812
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_SendPacket, .-SEGGER_SYSVIEW_SendPacket
	.section	.text._StoreChar,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	_StoreChar, %function
_StoreChar:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	ldr	r3, [r0, #16]
	adds	r2, r3, #1
	cmp	r2, #128
	bhi	.L802
	ldr	r4, [r0, #4]
	mov	r3, r2
	adds	r5, r4, #1
	str	r5, [r0, #4]
	strb	r1, [r4]
	str	r2, [r0, #16]
.L802:
	cmp	r3, #128
	beq	.L822
	pop	{r3, r4, r5, r6, r7, pc}
.L822:
	ldr	r2, [r0, #8]
	strb	r3, [r2]
	ldr	r3, [r0, #12]
	ldr	r4, [r0, #4]
	cmp	r3, #127
	bls	.L804
.L805:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r4], #1
	bhi	.L805
.L804:
	ldr	r6, .L825
	movs	r2, #0
	strb	r3, [r4]
	mov	r5, r0
	ldrb	r3, [r6]	@ zero_extendqisi2
	strb	r2, [r4, #1]
	cmp	r3, #1
	ldr	r7, [r0, #8]
	beq	.L811
	cbz	r3, .L810
	cmp	r3, #2
	beq	.L823
.L811:
	ldr	r3, [r6, #28]
	lsls	r3, r3, #5
	bmi	.L810
	adds	r4, r4, #2
	subs	r2, r4, r7
	cmp	r2, #127
	uxtb	r3, r2
	bls	.L812
	orn	r0, r3, #127
	subs	r1, r7, #2
	ubfx	r3, r2, #7, #8
	strb	r0, [r7, #-2]
.L813:
	mov	ip, #26
	ldr	r0, .L825+4
	strb	r3, [r7, #-1]
	subs	r2, r1, #1
	strb	ip, [r1, #-1]
	ldr	r3, [r6, #12]
	ldr	r7, [r0]
	subs	r3, r7, r3
	cmp	r3, #127
	bls	.L814
.L815:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r4], #1
	bhi	.L815
.L814:
	mov	r1, r2
	strb	r3, [r4], #1
	movs	r0, #1
	subs	r2, r4, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L816
	str	r7, [r6, #12]
.L810:
	ldr	r3, .L825+8
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L817
	ldrb	r4, [r6, #2]	@ zero_extendqisi2
	cbz	r4, .L824
.L817:
	ldr	r3, [r5]
	movs	r1, #0
	adds	r2, r3, #4
	adds	r3, r3, #5
	str	r1, [r5, #16]
	strd	r3, r2, [r5, #4]
	pop	{r3, r4, r5, r6, r7, pc}
.L824:
	movs	r3, #1
	strb	r3, [r6, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r6, #2]
	b	.L817
.L812:
	subs	r1, r7, #1
	b	.L813
.L816:
	ldrb	r3, [r6]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r6]
	b	.L810
.L823:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L810
	b	.L811
.L826:
	.align	2
.L825:
	.word	.LANCHOR0
	.word	-536866812
	.word	_SEGGER_RTT
	.size	_StoreChar, .-_StoreChar
	.section	.text._VPrintTarget,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	_VPrintTarget, %function
_VPrintTarget:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r5, r0
	sub	sp, sp, #52
	mov	r0, r1
	mov	r9, r2
	.syntax unified
@ 1032 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   fp, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r2, .L973
	movs	r1, #0
	str	r0, [sp, #40]
	str	r1, [sp, #44]
	adds	r0, r2, #4
	adds	r1, r2, #5
	ldrb	r3, [r5]	@ zero_extendqisi2
	str	r2, [sp, #28]
	str	r0, [sp, #36]
	ldr	r10, .L973+4
	str	r1, [sp, #32]
	b	.L887
.L952:
	ldr	r2, [sp, #44]
	adds	r1, r2, #1
	cmp	r1, #128
	bhi	.L884
	ldr	r0, [sp, #32]
	mov	r2, r1
	adds	r4, r0, #1
	str	r4, [sp, #32]
	strb	r3, [r0]
	str	r1, [sp, #44]
.L884:
	cmp	r2, #128
	beq	.L963
.L883:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L888
.L887:
	adds	r5, r5, #1
	cmp	r3, #0
	beq	.L888
	cmp	r3, #37
	bne	.L952
	movs	r6, #0
.L831:
	mov	r3, r5
	ldrb	r2, [r3], #1	@ zero_extendqisi2
	sub	r1, r2, #35
	mov	r7, r3
	cmp	r1, #13
	bhi	.L833
	tbb	[pc, r1]
.L835:
	.byte	(.L838-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L837-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L836-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L833-.L835)/2
	.byte	(.L834-.L835)/2
	.p2align 1
.L834:
	orr	r6, r6, #2
	mov	r5, r3
	b	.L831
.L836:
	orr	r6, r6, #1
	mov	r5, r3
	b	.L831
.L837:
	orr	r6, r6, #4
	mov	r5, r3
	b	.L831
.L838:
	orr	r6, r6, #8
	mov	r5, r3
	b	.L831
.L833:
	sub	r1, r2, #48
	cmp	r1, #9
	bhi	.L900
	movs	r4, #0
	b	.L841
.L901:
	mov	r5, r3
	adds	r3, r3, #1
.L841:
	add	r4, r4, r4, lsl #2
	mov	r0, r3
	add	r4, r2, r4, lsl #1
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	r1, r2, #48
	subs	r4, r4, #48
	cmp	r1, #9
	bls	.L901
	cmp	r2, #46
	add	r7, r5, #2
	beq	.L964
.L902:
	movs	r3, #0
.L842:
	and	r1, r2, #251
	cmp	r1, #104
	beq	.L845
	b	.L965
.L906:
	mov	r0, r1
.L845:
	mov	r1, r0
	ldrb	r2, [r1], #1	@ zero_extendqisi2
	and	r5, r2, #251
	cmp	r5, #104
	beq	.L906
	cmp	r2, #100
	add	r5, r0, #2
	beq	.L846
.L967:
	bhi	.L847
	cmp	r2, #88
	beq	.L848
	cmp	r2, #99
	beq	.L849
	cmp	r2, #37
	bne	.L883
	ldr	r3, [sp, #44]
	adds	r1, r3, #1
	cmp	r1, #128
	bhi	.L879
	ldr	r0, [sp, #32]
	mov	r3, r1
	adds	r4, r0, #1
	str	r4, [sp, #32]
	strb	r2, [r0]
	str	r1, [sp, #44]
.L879:
	cmp	r3, #128
	bne	.L883
	ldr	r2, [sp, #36]
	strb	r3, [r2]
	ldr	r3, [sp, #40]
	ldr	r0, [sp, #32]
	cmp	r3, #127
	bls	.L885
.L882:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r0], #1
	bhi	.L882
.L885:
	movs	r4, #0
	strb	r3, [r0]
	adds	r1, r0, #2
	movs	r2, #26
	strb	r4, [r0, #1]
	ldr	r0, [sp, #36]
	bl	_SendPacket
	ldr	r3, [sp, #28]
	str	r4, [sp, #44]
	adds	r2, r3, #4
	adds	r3, r3, #5
	strd	r3, r2, [sp, #32]
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L887
.L888:
	ldr	r3, [sp, #44]
	cbz	r3, .L830
	ldr	r2, [sp, #36]
	strb	r3, [r2]
	ldr	r3, [sp, #40]
	ldr	r0, [sp, #32]
	cmp	r3, #127
	bls	.L889
.L890:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r0], #1
	bhi	.L890
.L889:
	mov	r4, r0
	movs	r5, #0
	movs	r2, #26
	strb	r3, [r4], #2
	mov	r1, r4
	strb	r5, [r0, #1]
	ldr	r0, [sp, #36]
	str	r4, [sp, #32]
	bl	_SendPacket
.L830:
	.syntax unified
@ 1161 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, fp  
	
@ 0 "" 2
	.thumb
	.syntax unified
	add	sp, sp, #52
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L847:
	cmp	r2, #117
	beq	.L852
	cmp	r2, #120
	beq	.L848
	cmp	r2, #112
	bne	.L883
	ldr	r3, [r9]
	movs	r0, #8
	movs	r6, #0
	movs	r2, #16
	adds	r4, r3, #4
	ldr	r1, [r3]
	str	r6, [sp, #4]
	mov	r3, r0
	str	r4, [r9]
	str	r0, [sp]
	add	r0, sp, #28
	bl	_PrintUnsigned
	b	.L883
.L963:
	ldr	r3, [sp, #36]
	strb	r2, [r3]
	ldr	r3, [sp, #40]
	ldr	r0, [sp, #32]
	cmp	r3, #127
	bls	.L885
.L886:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r0], #1
	bhi	.L886
	b	.L885
.L900:
	cmp	r2, #46
	mov	r0, r5
	mov	r4, #0
	bne	.L902
.L964:
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	sub	r3, r2, #48
	cmp	r3, #9
	bhi	.L966
	movs	r3, #0
	b	.L843
.L904:
	mov	r7, r0
.L843:
	add	r3, r3, r3, lsl #2
	adds	r0, r7, #1
	add	r3, r2, r3, lsl #1
	ldrb	r2, [r7, #1]	@ zero_extendqisi2
	sub	r1, r2, #48
	subs	r3, r3, #48
	cmp	r1, #9
	bls	.L904
	and	r1, r2, #251
	adds	r7, r7, #2
	cmp	r1, #104
	beq	.L845
.L965:
	cmp	r2, #100
	mov	r5, r7
	bne	.L967
.L846:
	ldr	r2, [r9]
	movs	r0, #1
	ldr	r7, [r2]
	adds	r2, r2, #4
	eor	r1, r7, r7, asr #31
	str	r2, [r9]
	sub	r1, r1, r7, asr #31
	cmp	r1, #9
	ble	.L858
.L859:
	umull	ip, r2, r10, r1
	cmp	r1, #99
	add	r0, r0, #1
	lsr	r2, r2, #3
	mov	r1, r2
	bgt	.L859
.L858:
	cmp	r0, r3
	eor	r2, r6, #2
	mov	r1, r0
	ubfx	r2, r2, #1, #1
	it	cc
	movcc	r1, r3
	cmp	r3, #0
	it	ne
	movne	r2, #1
	str	r1, [sp, #12]
	cbz	r4, .L860
	cmp	r7, #0
	blt	.L861
	ands	r1, r6, #4
	beq	.L968
	subs	r4, r4, #1
	cbz	r2, .L897
.L895:
	lsls	r1, r6, #31
	bmi	.L860
	cbz	r4, .L860
	ldr	r2, [sp, #12]
	cmp	r4, r2
	bls	.L860
.L898:
	mov	r8, #0
	strd	r3, r5, [sp, #16]
	ldr	r5, [sp, #12]
.L868:
	ldr	r2, [sp, #44]
	subs	r4, r4, #1
	adds	r1, r2, #1
	cmp	r1, #128
	bhi	.L864
	ldr	r0, [sp, #32]
	mov	r2, r1
	adds	r3, r0, #1
	str	r3, [sp, #32]
	mov	r3, #32
	strb	r3, [r0]
	str	r1, [sp, #44]
.L864:
	cmp	r2, #128
	beq	.L969
.L865:
	cbz	r4, .L958
	cmp	r4, r5
	bhi	.L868
.L958:
	ldrd	r3, r5, [sp, #16]
.L860:
	cmp	r7, #0
	blt	.L896
	and	r1, r6, #4
.L897:
	cmp	r1, #0
	bne	.L954
.L921:
	add	r8, sp, #28
.L871:
	and	r2, r6, #3
	cmp	r2, #2
	bne	.L872
	cmp	r3, #0
	beq	.L970
.L872:
	mov	r1, r7
	mov	r0, r8
	movs	r2, #10
	strd	r4, r6, [sp]
	bl	_PrintUnsigned
	b	.L883
.L974:
	.align	2
.L973:
	.word	.LANCHOR3
	.word	-858993459
.L848:
	ldr	r1, [r9]
	movs	r2, #16
.L962:
	adds	r7, r1, #4
	add	r0, sp, #28
	ldr	r1, [r1]
	str	r6, [sp, #4]
	str	r7, [r9]
	str	r4, [sp]
	bl	_PrintUnsigned
	b	.L883
.L849:
	ldr	r3, [sp, #44]
	ldr	r1, [r9]
	adds	r2, r3, #1
	adds	r0, r1, #4
	cmp	r2, #128
	str	r0, [r9]
	bhi	.L854
	ldr	r0, [sp, #32]
	mov	r3, r2
	ldr	r1, [r1]
	adds	r4, r0, #1
	str	r4, [sp, #32]
	strb	r1, [r0]
	str	r2, [sp, #44]
.L854:
	cmp	r3, #128
	bne	.L883
	ldr	r2, [sp, #36]
	strb	r3, [r2]
	ldr	r3, [sp, #40]
	ldr	r0, [sp, #32]
	cmp	r3, #127
	bls	.L885
.L857:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r0], #1
	bhi	.L857
	b	.L885
.L852:
	ldr	r1, [r9]
	movs	r2, #10
	b	.L962
.L954:
	add	r8, sp, #28
	movs	r1, #43
	str	r3, [sp, #16]
	mov	r0, r8
	bl	_StoreChar
	ldr	r3, [sp, #16]
	b	.L871
.L861:
	subs	r4, r4, #1
	cmp	r2, #0
	bne	.L895
.L896:
	add	r8, sp, #28
	movs	r1, #45
	str	r3, [sp, #16]
	rsbs	r7, r7, #0
	mov	r0, r8
	bl	_StoreChar
	ldr	r3, [sp, #16]
	b	.L871
.L970:
	cmp	r4, #0
	beq	.L872
.L892:
	ldr	r2, [sp, #12]
	cmp	r2, r4
	bcs	.L872
	strd	r3, r5, [sp, #12]
	mov	r5, r2
.L877:
	ldr	r2, [sp, #44]
	subs	r4, r4, #1
	adds	r1, r2, #1
	cmp	r1, #128
	bhi	.L873
	ldr	r0, [sp, #32]
	mov	r2, r1
	adds	r3, r0, #1
	str	r3, [sp, #32]
	mov	r3, #48
	strb	r3, [r0]
	str	r1, [sp, #44]
.L873:
	cmp	r2, #128
	beq	.L971
.L874:
	cbz	r4, .L959
	cmp	r4, r5
	bhi	.L877
.L959:
	ldrd	r3, r5, [sp, #12]
	b	.L872
.L968:
	cmp	r2, #0
	beq	.L972
	lsls	r2, r6, #31
	bmi	.L921
	ldr	r2, [sp, #12]
	cmp	r2, r4
	bcc	.L898
	b	.L921
.L969:
	ldr	r1, [sp, #36]
	strb	r2, [r1]
	ldr	r2, [sp, #40]
	ldr	r0, [sp, #32]
	cmp	r2, #127
	bls	.L866
.L867:
	orn	r3, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r3, [r0], #1
	bhi	.L867
.L866:
	strb	r2, [r0]
	adds	r1, r0, #2
	strb	r8, [r0, #1]
	movs	r2, #26
	ldr	r0, [sp, #36]
	bl	_SendPacket
	ldr	r2, [sp, #28]
	str	r8, [sp, #44]
	adds	r1, r2, #4
	adds	r2, r2, #5
	strd	r2, r1, [sp, #32]
	b	.L865
.L971:
	ldr	r1, [sp, #36]
	strb	r2, [r1]
	ldr	r2, [sp, #40]
	ldr	r0, [sp, #32]
	cmp	r2, #127
	bls	.L875
.L876:
	orn	r3, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r3, [r0], #1
	bhi	.L876
.L875:
	mov	r3, #0
	strb	r2, [r0]
	adds	r1, r0, #2
	movs	r2, #26
	strb	r3, [r0, #1]
	ldr	r0, [sp, #36]
	bl	_SendPacket
	ldr	r2, [sp, #28]
	movs	r3, #0
	adds	r1, r2, #4
	adds	r2, r2, #5
	str	r3, [sp, #44]
	strd	r2, r1, [sp, #32]
	b	.L874
.L972:
	and	r2, r6, #3
	cmp	r2, #2
	bne	.L961
	cbz	r3, .L923
.L961:
	add	r8, sp, #28
	b	.L872
.L966:
	mov	r0, r7
	movs	r3, #0
	adds	r7, r7, #1
	b	.L842
.L923:
	add	r8, sp, #28
	b	.L892
	.size	_VPrintTarget, .-_VPrintTarget
	.section	.text.SEGGER_SYSVIEW_RecordExitISR,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordExitISR
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordExitISR, %function
SEGGER_SYSVIEW_RecordExitISR:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 1843 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r4, .L992
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L981
	cbz	r3, .L980
	cmp	r3, #2
	beq	.L990
.L981:
	ldr	r3, [r4, #28]
	lsls	r3, r3, #28
	bmi	.L980
	ldr	r2, .L992+4
	movs	r3, #3
	ldr	r1, .L992+8
	strb	r3, [r2, #3]
	adds	r2, r2, #4
	ldr	r3, [r4, #12]
	ldr	r6, [r1]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L982
.L983:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L983
.L982:
	ldr	r1, .L992+12
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L984
	str	r6, [r4, #12]
.L980:
	ldr	r3, .L992+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L985
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cbz	r6, .L991
.L985:
	.syntax unified
@ 1846 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L991:
	movs	r3, #1
	strb	r3, [r4, #2]
	bl	_HandleIncomingPacket
	strb	r6, [r4, #2]
	.syntax unified
@ 1846 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L984:
	ldrb	r3, [r4]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r4]
	b	.L980
.L990:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L980
	b	.L981
.L993:
	.align	2
.L992:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_RecordExitISR, .-SEGGER_SYSVIEW_RecordExitISR
	.section	.text.SEGGER_SYSVIEW_RecordExitISRToScheduler,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordExitISRToScheduler
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordExitISRToScheduler, %function
SEGGER_SYSVIEW_RecordExitISRToScheduler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 1865 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r4, .L1011
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1000
	cbz	r3, .L999
	cmp	r3, #2
	beq	.L1009
.L1000:
	ldr	r3, [r4, #28]
	lsls	r3, r3, #13
	bmi	.L999
	ldr	r2, .L1011+4
	movs	r3, #18
	ldr	r1, .L1011+8
	strb	r3, [r2, #3]
	adds	r2, r2, #4
	ldr	r3, [r4, #12]
	ldr	r6, [r1]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L1001
.L1002:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1002
.L1001:
	ldr	r1, .L1011+12
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1003
	str	r6, [r4, #12]
.L999:
	ldr	r3, .L1011+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1004
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cbz	r6, .L1010
.L1004:
	.syntax unified
@ 1868 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1010:
	movs	r3, #1
	strb	r3, [r4, #2]
	bl	_HandleIncomingPacket
	strb	r6, [r4, #2]
	.syntax unified
@ 1868 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1003:
	ldrb	r3, [r4]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r4]
	b	.L999
.L1009:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L999
	b	.L1000
.L1012:
	.align	2
.L1011:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_RecordExitISRToScheduler, .-SEGGER_SYSVIEW_RecordExitISRToScheduler
	.section	.text.SEGGER_SYSVIEW_RecordExitTimer,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordExitTimer
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordExitTimer, %function
SEGGER_SYSVIEW_RecordExitTimer:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 1901 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r4, .L1030
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1019
	cbz	r3, .L1018
	cmp	r3, #2
	beq	.L1028
.L1019:
	ldr	r3, [r4, #28]
	lsls	r3, r3, #11
	bmi	.L1018
	ldr	r2, .L1030+4
	movs	r3, #20
	ldr	r1, .L1030+8
	strb	r3, [r2, #3]
	adds	r2, r2, #4
	ldr	r3, [r4, #12]
	ldr	r6, [r1]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L1020
.L1021:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1021
.L1020:
	ldr	r1, .L1030+12
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1022
	str	r6, [r4, #12]
.L1018:
	ldr	r3, .L1030+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1023
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cbz	r6, .L1029
.L1023:
	.syntax unified
@ 1904 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1029:
	movs	r3, #1
	strb	r3, [r4, #2]
	bl	_HandleIncomingPacket
	strb	r6, [r4, #2]
	.syntax unified
@ 1904 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1022:
	ldrb	r3, [r4]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r4]
	b	.L1018
.L1028:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1018
	b	.L1019
.L1031:
	.align	2
.L1030:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_RecordExitTimer, .-SEGGER_SYSVIEW_RecordExitTimer
	.section	.text.SEGGER_SYSVIEW_OnIdle,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnIdle
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnIdle, %function
SEGGER_SYSVIEW_OnIdle:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 1960 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r4, .L1049
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1038
	cbz	r3, .L1037
	cmp	r3, #2
	beq	.L1047
.L1038:
	ldr	r3, [r4, #28]
	lsls	r3, r3, #14
	bmi	.L1037
	ldr	r2, .L1049+4
	movs	r3, #17
	ldr	r1, .L1049+8
	strb	r3, [r2, #3]
	adds	r2, r2, #4
	ldr	r3, [r4, #12]
	ldr	r6, [r1]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L1039
.L1040:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1040
.L1039:
	ldr	r1, .L1049+12
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1041
	str	r6, [r4, #12]
.L1037:
	ldr	r3, .L1049+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1042
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cbz	r6, .L1048
.L1042:
	.syntax unified
@ 1963 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1048:
	movs	r3, #1
	strb	r3, [r4, #2]
	bl	_HandleIncomingPacket
	strb	r6, [r4, #2]
	.syntax unified
@ 1963 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1041:
	ldrb	r3, [r4]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r4]
	b	.L1037
.L1047:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1037
	b	.L1038
.L1050:
	.align	2
.L1049:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnIdle, .-SEGGER_SYSVIEW_OnIdle
	.section	.text.SEGGER_SYSVIEW_OnTaskStopExec,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnTaskStopExec
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnTaskStopExec, %function
SEGGER_SYSVIEW_OnTaskStopExec:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 2048 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r4, .L1068
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1057
	cbz	r3, .L1056
	cmp	r3, #2
	beq	.L1066
.L1057:
	ldr	r3, [r4, #28]
	lsls	r3, r3, #26
	bmi	.L1056
	ldr	r2, .L1068+4
	movs	r3, #5
	ldr	r1, .L1068+8
	strb	r3, [r2, #3]
	adds	r2, r2, #4
	ldr	r3, [r4, #12]
	ldr	r6, [r1]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L1058
.L1059:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1059
.L1058:
	ldr	r1, .L1068+12
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1060
	str	r6, [r4, #12]
.L1056:
	ldr	r3, .L1068+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1061
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cbz	r6, .L1067
.L1061:
	.syntax unified
@ 2051 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1067:
	movs	r3, #1
	strb	r3, [r4, #2]
	bl	_HandleIncomingPacket
	strb	r6, [r4, #2]
	.syntax unified
@ 2051 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1060:
	ldrb	r3, [r4]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r4]
	b	.L1056
.L1066:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1056
	b	.L1057
.L1069:
	.align	2
.L1068:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnTaskStopExec, .-SEGGER_SYSVIEW_OnTaskStopExec
	.section	.text.SEGGER_SYSVIEW_SendSysDesc,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_SendSysDesc
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_SendSysDesc, %function
SEGGER_SYSVIEW_SendSysDesc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, lr}
	.syntax unified
@ 1775 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1071
	mov	r3, r0
	mov	r2, r0
	rsb	r4, r0, #1
.L1072:
	adds	r7, r4, r2
	ldrb	r1, [r2, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1072
	ldr	r6, .L1107
	cmp	r7, #128
	add	r4, r0, #4
	mov	r2, r7
	add	r1, r6, #5
	add	ip, r6, #9
	it	cs
	movcs	r2, #128
	cmp	ip, r0
	it	hi
	cmphi	r4, r1
	strb	r2, [r6, #4]
	bhi	.L1091
	cmp	r7, #26
	bls	.L1091
	cmp	r7, #0
	mov	ip, r1
	mov	r7, r1
	ite	ne
	movne	lr, r2
	moveq	lr, #1
	bic	r8, lr, #3
	add	r8, r8, r0
.L1077:
	mov	r4, r7
	ldr	r9, [r3], #4	@ unaligned
	adds	r4, r4, #4
	cmp	r3, r8
	str	r9, [ip], #4	@ unaligned
	mov	r7, r4
	bne	.L1077
	bic	r3, lr, #3
	cmp	lr, r3
	add	ip, r0, r3
	add	r7, r1, r3
	beq	.L1092
	ldrb	r4, [r0, r3]	@ zero_extendqisi2
	adds	r0, r3, #1
	cmp	r2, r0
	strb	r4, [r1, r3]
	add	r4, r7, #1
	bls	.L1092
	adds	r3, r3, #2
	ldrb	r1, [ip, #1]	@ zero_extendqisi2
	adds	r4, r7, #2
	cmp	r2, r3
	strb	r1, [r7, #1]
	bls	.L1092
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	adds	r4, r7, #3
	strb	r3, [r7, #2]
.L1092:
	ldr	r7, .L1107+4
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1084
	cbz	r3, .L1083
	cmp	r3, #2
	beq	.L1105
.L1084:
	ldr	r3, [r7, #28]
	lsls	r3, r3, #17
	bmi	.L1083
	movs	r3, #14
	ldr	r2, .L1107+8
	strb	r3, [r6, #3]
	ldr	r3, [r7, #12]
	ldr	r6, [r2]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L1085
.L1086:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r4], #1
	bhi	.L1086
.L1085:
	ldr	r1, .L1107+12
	movs	r0, #1
	strb	r3, [r4], #1
	subs	r2, r4, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1087
	str	r6, [r7, #12]
.L1083:
	ldr	r3, .L1107+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1088
	ldrb	r4, [r7, #2]	@ zero_extendqisi2
	cbz	r4, .L1106
.L1088:
	.syntax unified
@ 1779 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L1106:
	movs	r3, #1
	strb	r3, [r7, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r7, #2]
	.syntax unified
@ 1779 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L1087:
	ldrb	r3, [r7]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r7]
	b	.L1083
.L1105:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1083
	b	.L1084
.L1091:
	subs	r1, r0, #1
	ldr	r4, .L1107+20
.L1075:
	adds	r3, r1, #2
	ldrb	r7, [r1, #1]	@ zero_extendqisi2
	adds	r1, r1, #1
	subs	r3, r3, r0
	strb	r7, [r4], #1
	cmp	r2, r3
	bhi	.L1075
	b	.L1092
.L1071:
	ldr	r6, .L1107
	strb	r3, [r6, #4]
	adds	r4, r6, #5
	b	.L1092
.L1108:
	.align	2
.L1107:
	.word	.LANCHOR3
	.word	.LANCHOR0
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.word	.LANCHOR3+5
	.size	SEGGER_SYSVIEW_SendSysDesc, .-SEGGER_SYSVIEW_SendSysDesc
	.section	.text.SEGGER_SYSVIEW_OnUserStart,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnUserStart
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnUserStart, %function
SEGGER_SYSVIEW_OnUserStart:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 2113 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r0, #127
	ldr	r4, .L1129
	bls	.L1110
.L1111:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r4], #1
	bhi	.L1111
.L1110:
	ldr	r6, .L1129+4
	strb	r0, [r4]
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1117
	cbz	r3, .L1116
	cmp	r3, #2
	beq	.L1127
.L1117:
	ldr	r3, [r6, #28]
	lsls	r3, r3, #16
	bmi	.L1116
	ldr	r3, .L1129+8
	movs	r0, #15
	ldr	r1, .L1129+12
	adds	r2, r4, #1
	strb	r0, [r3, #3]
	ldr	r3, [r6, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1118
.L1119:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1119
.L1118:
	ldr	r1, .L1129+16
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1120
	str	r4, [r6, #12]
.L1116:
	ldr	r3, .L1129+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1121
	ldrb	r4, [r6, #2]	@ zero_extendqisi2
	cbz	r4, .L1128
.L1121:
	.syntax unified
@ 2118 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1128:
	movs	r3, #1
	strb	r3, [r6, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r6, #2]
	.syntax unified
@ 2118 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1120:
	ldrb	r3, [r6]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r6]
	b	.L1116
.L1127:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1116
	b	.L1117
.L1130:
	.align	2
.L1129:
	.word	.LANCHOR3+4
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnUserStart, .-SEGGER_SYSVIEW_OnUserStart
	.section	.text.SEGGER_SYSVIEW_OnUserStop,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnUserStop
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnUserStop, %function
SEGGER_SYSVIEW_OnUserStop:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 2134 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r0, #127
	ldr	r4, .L1151
	bls	.L1132
.L1133:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r4], #1
	bhi	.L1133
.L1132:
	ldr	r6, .L1151+4
	strb	r0, [r4]
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1139
	cbz	r3, .L1138
	cmp	r3, #2
	beq	.L1149
.L1139:
	ldrh	r3, [r6, #30]
	lsls	r3, r3, #31
	bmi	.L1138
	ldr	r3, .L1151+8
	movs	r0, #16
	ldr	r1, .L1151+12
	adds	r2, r4, #1
	strb	r0, [r3, #3]
	ldr	r3, [r6, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1140
.L1141:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1141
.L1140:
	ldr	r1, .L1151+16
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1142
	str	r4, [r6, #12]
.L1138:
	ldr	r3, .L1151+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1143
	ldrb	r4, [r6, #2]	@ zero_extendqisi2
	cbz	r4, .L1150
.L1143:
	.syntax unified
@ 2139 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1150:
	movs	r3, #1
	strb	r3, [r6, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r6, #2]
	.syntax unified
@ 2139 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1142:
	ldrb	r3, [r6]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r6]
	b	.L1138
.L1149:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1138
	b	.L1139
.L1152:
	.align	2
.L1151:
	.word	.LANCHOR3+4
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnUserStop, .-SEGGER_SYSVIEW_OnUserStop
	.section	.text.SEGGER_SYSVIEW_RecordEnterISR,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordEnterISR
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordEnterISR, %function
SEGGER_SYSVIEW_RecordEnterISR:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #8
	.syntax unified
@ 1818 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, .L1171
	ldr	r3, [r3]
	ubfx	r0, r3, #0, #9
	tst	r3, #384
	uxtb	r2, r0
	beq	.L1165
	orn	r1, r2, #127
	ldr	r3, .L1171+4
	lsrs	r2, r0, #7
	strb	r1, [r3, #4]
	adds	r3, r3, #5
.L1154:
	ldr	r5, .L1171+8
	strb	r2, [r3]
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1160
	cbz	r2, .L1159
	cmp	r2, #2
	beq	.L1169
.L1160:
	ldr	r2, [r5, #28]
	lsls	r2, r2, #29
	bmi	.L1159
	ldr	r2, .L1171+4
	movs	r0, #2
	ldr	r1, .L1171+12
	adds	r3, r3, #1
	strb	r0, [r2, #3]
	ldr	r2, [r5, #12]
	ldr	r6, [r1]
	subs	r2, r6, r2
	cmp	r2, #127
	bls	.L1161
.L1162:
	orn	r1, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r1, [r3], #1
	bhi	.L1162
.L1161:
	ldr	r1, .L1171+16
	movs	r0, #1
	strb	r2, [r3], #1
	subs	r2, r3, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1163
	str	r6, [r5, #12]
.L1159:
	ldr	r3, .L1171+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1164
	ldrb	r6, [r5, #2]	@ zero_extendqisi2
	cbz	r6, .L1170
.L1164:
	.syntax unified
@ 1824 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, pc}
.L1170:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r6, [r5, #2]
	.syntax unified
@ 1824 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, pc}
.L1163:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1159
.L1169:
	str	r3, [sp, #4]
	bl	_TrySendOverflowPacket
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1159
	ldr	r3, [sp, #4]
	b	.L1160
.L1165:
	ldr	r3, .L1171+24
	b	.L1154
.L1172:
	.align	2
.L1171:
	.word	-536810236
	.word	.LANCHOR3
	.word	.LANCHOR0
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordEnterISR, .-SEGGER_SYSVIEW_RecordEnterISR
	.section	.text.SEGGER_SYSVIEW_RecordEnterTimer,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordEnterTimer
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordEnterTimer, %function
SEGGER_SYSVIEW_RecordEnterTimer:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 1884 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L1193
	ldr	r4, .L1193+4
	ldr	r3, [r5, #16]
	subs	r0, r0, r3
	lsrs	r0, r0, #2
	cmp	r0, #127
	bls	.L1174
.L1175:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r4], #1
	bhi	.L1175
.L1174:
	ldrb	r3, [r5]	@ zero_extendqisi2
	strb	r0, [r4]
	cmp	r3, #1
	beq	.L1181
	cbz	r3, .L1180
	cmp	r3, #2
	beq	.L1191
.L1181:
	ldr	r3, [r5, #28]
	lsls	r3, r3, #12
	bmi	.L1180
	ldr	r3, .L1193+8
	movs	r0, #19
	ldr	r1, .L1193+12
	adds	r2, r4, #1
	strb	r0, [r3, #3]
	ldr	r3, [r5, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1182
.L1183:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1183
.L1182:
	ldr	r1, .L1193+16
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1184
	str	r4, [r5, #12]
.L1180:
	ldr	r3, .L1193+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1185
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L1192
.L1185:
	.syntax unified
@ 1889 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1192:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	.syntax unified
@ 1889 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1184:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1180
.L1191:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1180
	b	.L1181
.L1194:
	.align	2
.L1193:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_RecordEnterTimer, .-SEGGER_SYSVIEW_RecordEnterTimer
	.section	.text.SEGGER_SYSVIEW_OnTaskStartReady,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnTaskStartReady
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnTaskStartReady, %function
SEGGER_SYSVIEW_OnTaskStartReady:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 2067 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L1215
	ldr	r4, .L1215+4
	ldr	r3, [r5, #16]
	subs	r0, r0, r3
	lsrs	r0, r0, #2
	cmp	r0, #127
	bls	.L1196
.L1197:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r4], #1
	bhi	.L1197
.L1196:
	ldrb	r3, [r5]	@ zero_extendqisi2
	strb	r0, [r4]
	cmp	r3, #1
	beq	.L1203
	cbz	r3, .L1202
	cmp	r3, #2
	beq	.L1213
.L1203:
	ldr	r3, [r5, #28]
	lsls	r3, r3, #25
	bmi	.L1202
	ldr	r3, .L1215+8
	movs	r0, #6
	ldr	r1, .L1215+12
	adds	r2, r4, #1
	strb	r0, [r3, #3]
	ldr	r3, [r5, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1204
.L1205:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1205
.L1204:
	ldr	r1, .L1215+16
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1206
	str	r4, [r5, #12]
.L1202:
	ldr	r3, .L1215+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1207
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L1214
.L1207:
	.syntax unified
@ 2073 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1214:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	.syntax unified
@ 2073 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1206:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1202
.L1213:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1202
	b	.L1203
.L1216:
	.align	2
.L1215:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnTaskStartReady, .-SEGGER_SYSVIEW_OnTaskStartReady
	.section	.text.SEGGER_SYSVIEW_OnTaskStartExec,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnTaskStartExec
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnTaskStartExec, %function
SEGGER_SYSVIEW_OnTaskStartExec:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 2029 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L1237
	ldr	r4, .L1237+4
	ldr	r3, [r5, #16]
	subs	r0, r0, r3
	lsrs	r0, r0, #2
	cmp	r0, #127
	bls	.L1218
.L1219:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r4], #1
	bhi	.L1219
.L1218:
	ldrb	r3, [r5]	@ zero_extendqisi2
	strb	r0, [r4]
	cmp	r3, #1
	beq	.L1225
	cbz	r3, .L1224
	cmp	r3, #2
	beq	.L1235
.L1225:
	ldr	r3, [r5, #28]
	lsls	r3, r3, #27
	bmi	.L1224
	ldr	r3, .L1237+8
	movs	r0, #4
	ldr	r1, .L1237+12
	adds	r2, r4, #1
	strb	r0, [r3, #3]
	ldr	r3, [r5, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1226
.L1227:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1227
.L1226:
	ldr	r1, .L1237+16
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1228
	str	r4, [r5, #12]
.L1224:
	ldr	r3, .L1237+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1229
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L1236
.L1229:
	.syntax unified
@ 2035 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1236:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	.syntax unified
@ 2035 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1228:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1224
.L1235:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1224
	b	.L1225
.L1238:
	.align	2
.L1237:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnTaskStartExec, .-SEGGER_SYSVIEW_OnTaskStartExec
	.section	.text.SEGGER_SYSVIEW_OnTaskCreate,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnTaskCreate
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnTaskCreate, %function
SEGGER_SYSVIEW_OnTaskCreate:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 1980 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L1259
	ldr	r4, .L1259+4
	ldr	r3, [r5, #16]
	subs	r0, r0, r3
	lsrs	r0, r0, #2
	cmp	r0, #127
	bls	.L1240
.L1241:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r4], #1
	bhi	.L1241
.L1240:
	ldrb	r3, [r5]	@ zero_extendqisi2
	strb	r0, [r4]
	cmp	r3, #1
	beq	.L1247
	cbz	r3, .L1246
	cmp	r3, #2
	beq	.L1257
.L1247:
	ldr	r3, [r5, #28]
	lsls	r3, r3, #23
	bmi	.L1246
	ldr	r3, .L1259+8
	movs	r0, #8
	ldr	r1, .L1259+12
	adds	r2, r4, #1
	strb	r0, [r3, #3]
	ldr	r3, [r5, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1248
.L1249:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1249
.L1248:
	ldr	r1, .L1259+16
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1250
	str	r4, [r5, #12]
.L1246:
	ldr	r3, .L1259+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1251
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L1258
.L1251:
	.syntax unified
@ 1986 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1258:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	.syntax unified
@ 1986 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1250:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1246
.L1257:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1246
	b	.L1247
.L1260:
	.align	2
.L1259:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnTaskCreate, .-SEGGER_SYSVIEW_OnTaskCreate
	.section	.text.SEGGER_SYSVIEW_OnTaskStopReady,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnTaskStopReady
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnTaskStopReady, %function
SEGGER_SYSVIEW_OnTaskStopReady:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r3, r1
	.syntax unified
@ 2090 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L1284
	ldr	r4, .L1284+4
	ldr	r2, [r5, #16]
	subs	r0, r0, r2
	lsrs	r0, r0, #2
	cmp	r0, #127
	bls	.L1262
.L1263:
	orn	r2, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r2, [r4], #1
	bhi	.L1263
.L1262:
	cmp	r3, #127
	strb	r0, [r4], #1
	bls	.L1264
.L1265:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r4], #1
	bhi	.L1265
.L1264:
	ldrb	r2, [r5]	@ zero_extendqisi2
	strb	r3, [r4]
	cmp	r2, #1
	beq	.L1271
	cbz	r2, .L1270
	cmp	r2, #2
	beq	.L1282
.L1271:
	ldr	r3, [r5, #28]
	lsls	r3, r3, #24
	bmi	.L1270
	ldr	r3, .L1284+8
	movs	r0, #7
	ldr	r1, .L1284+12
	adds	r2, r4, #1
	strb	r0, [r3, #3]
	ldr	r3, [r5, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1272
.L1273:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1273
.L1272:
	ldr	r1, .L1284+16
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1274
	str	r4, [r5, #12]
.L1270:
	ldr	r3, .L1284+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1275
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L1283
.L1275:
	.syntax unified
@ 2097 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1283:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	.syntax unified
@ 2097 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1274:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1270
.L1282:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1270
	b	.L1271
.L1285:
	.align	2
.L1284:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnTaskStopReady, .-SEGGER_SYSVIEW_OnTaskStopReady
	.section	.text.SEGGER_SYSVIEW_RecordEndCall,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordEndCall
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordEndCall, %function
SEGGER_SYSVIEW_RecordEndCall:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	.syntax unified
@ 1920 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r7, .L1308
	cmp	r0, #127
	mov	r4, r7
	bls	.L1287
.L1288:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r4], #1
	bhi	.L1288
.L1287:
	ldr	r6, .L1308+4
	strb	r0, [r4]
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1294
	cbz	r3, .L1293
	cmp	r3, #2
	beq	.L1306
.L1294:
	ldr	r3, [r6, #28]
	lsls	r3, r3, #3
	bmi	.L1293
	adds	r4, r4, #1
	ldr	r2, .L1308+8
	subs	r7, r4, r7
	cmp	r7, #127
	uxtb	r1, r7
	bls	.L1301
	orn	r0, r1, #127
	mov	r3, r2
	ubfx	r1, r7, #7, #8
	strb	r0, [r3, #2]!
.L1295:
	strb	r1, [r2, #3]
	movs	r0, #28
	ldr	r1, .L1308+12
	subs	r2, r3, #1
	strb	r0, [r3, #-1]
	ldr	r3, [r6, #12]
	ldr	r7, [r1]
	subs	r3, r7, r3
	cmp	r3, #127
	bls	.L1296
.L1297:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r4], #1
	bhi	.L1297
.L1296:
	mov	r1, r2
	strb	r3, [r4], #1
	movs	r0, #1
	subs	r2, r4, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1298
	str	r7, [r6, #12]
.L1293:
	ldr	r3, .L1308+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1299
	ldrb	r4, [r6, #2]	@ zero_extendqisi2
	cbz	r4, .L1307
.L1299:
	.syntax unified
@ 1925 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L1307:
	movs	r3, #1
	strb	r3, [r6, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r6, #2]
	.syntax unified
@ 1925 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L1301:
	adds	r3, r2, #3
	b	.L1295
.L1298:
	ldrb	r3, [r6]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r6]
	b	.L1293
.L1306:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1293
	b	.L1294
.L1309:
	.align	2
.L1308:
	.word	.LANCHOR3+4
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_RecordEndCall, .-SEGGER_SYSVIEW_RecordEndCall
	.section	.text.SEGGER_SYSVIEW_OnTaskTerminate,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_OnTaskTerminate
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_OnTaskTerminate, %function
SEGGER_SYSVIEW_OnTaskTerminate:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	.syntax unified
@ 2005 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L1332
	ldr	r7, .L1332+4
	ldr	r3, [r5, #16]
	mov	r4, r7
	subs	r0, r0, r3
	lsrs	r0, r0, #2
	cmp	r0, #127
	bls	.L1311
.L1312:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r4], #1
	bhi	.L1312
.L1311:
	ldrb	r3, [r5]	@ zero_extendqisi2
	strb	r0, [r4]
	cmp	r3, #1
	beq	.L1318
	cbz	r3, .L1317
	cmp	r3, #2
	beq	.L1330
.L1318:
	ldr	r3, [r5, #28]
	lsls	r3, r3, #2
	bmi	.L1317
	adds	r4, r4, #1
	ldr	r2, .L1332+8
	subs	r7, r4, r7
	cmp	r7, #127
	uxtb	r1, r7
	bls	.L1325
	orn	r0, r1, #127
	mov	r3, r2
	ubfx	r1, r7, #7, #8
	strb	r0, [r3, #2]!
.L1319:
	strb	r1, [r2, #3]
	movs	r0, #29
	ldr	r1, .L1332+12
	subs	r2, r3, #1
	strb	r0, [r3, #-1]
	ldr	r3, [r5, #12]
	ldr	r7, [r1]
	subs	r3, r7, r3
	cmp	r3, #127
	bls	.L1320
.L1321:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r4], #1
	bhi	.L1321
.L1320:
	mov	r1, r2
	strb	r3, [r4], #1
	movs	r0, #1
	subs	r2, r4, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1322
	str	r7, [r5, #12]
.L1317:
	ldr	r3, .L1332+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1323
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L1331
.L1323:
	.syntax unified
@ 2011 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L1331:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	.syntax unified
@ 2011 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L1325:
	adds	r3, r2, #3
	b	.L1319
.L1322:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1317
.L1330:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1317
	b	.L1318
.L1333:
	.align	2
.L1332:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	.LANCHOR3
	.word	-536866812
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_OnTaskTerminate, .-SEGGER_SYSVIEW_OnTaskTerminate
	.section	.text.SEGGER_SYSVIEW_RecordModuleDescription,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordModuleDescription
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordModuleDescription, %function
SEGGER_SYSVIEW_RecordModuleDescription:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1391
	ldr	r3, [r3]
	cmp	r3, r0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r6, r1
	beq	.L1387
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L1388
	cmp	r0, r3
	beq	.L1367
	ldr	r2, [r3, #16]
	movs	r3, #2
	cbnz	r2, .L1342
	b	.L1341
.L1381:
	ldr	r2, [r2, #16]
	uxtb	r3, r1
	cbz	r2, .L1341
.L1342:
	cmp	r0, r2
	add	r1, r3, #1
	bne	.L1381
.L1341:
	.syntax unified
@ 2397 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	cmp	r3, #127
	bls	.L1369
	ldr	r2, .L1391+4
	strb	r3, [r2, #4]
	adds	r2, r2, #5
	movs	r3, #1
.L1336:
	strb	r3, [r2], #1
	ldr	r3, [r0, #8]
	cmp	r3, #127
	bls	.L1343
.L1344:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1344
.L1343:
	mov	r7, r2
	strb	r3, [r7], #2
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1345
	mov	r0, r6
	mov	r3, r6
	rsb	ip, r6, #1
.L1346:
	add	r4, ip, r3
	ldrb	r1, [r3, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1346
	cmp	r4, #128
	add	r1, r6, #4
	add	r3, r2, #6
	mov	ip, r4
	it	cs
	movcs	ip, #128
	cmp	r6, r3
	it	cc
	cmpcc	r7, r1
	strb	ip, [r2, #1]
	bcc	.L1366
	cmp	r4, #26
	bls	.L1366
	cmp	r4, #0
	mov	r3, r7
	mov	r2, r7
	ite	ne
	movne	r8, ip
	moveq	r8, #1
	bic	lr, r8, #3
	add	lr, lr, r6
.L1351:
	mov	r4, r3
	ldr	r1, [r0], #4	@ unaligned
	adds	r4, r4, #4
	cmp	r0, lr
	str	r1, [r2], #4	@ unaligned
	mov	r3, r4
	bne	.L1351
	bic	r3, r8, #3
	cmp	r3, r8
	add	r0, r6, r3
	add	r2, r7, r3
	beq	.L1363
	adds	r1, r3, #1
	ldrb	r4, [r6, r3]	@ zero_extendqisi2
	cmp	r1, ip
	strb	r4, [r7, r3]
	add	r4, r2, #1
	bcs	.L1363
	adds	r3, r3, #2
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	adds	r4, r2, #2
	cmp	ip, r3
	strb	r1, [r2, #1]
	bls	.L1363
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	adds	r4, r2, #3
	strb	r3, [r2, #2]
.L1363:
	ldr	r6, .L1391+8
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1358
	cbz	r3, .L1357
	cmp	r3, #2
	beq	.L1389
.L1358:
	ldr	r3, [r6, #28]
	lsls	r3, r3, #9
	bmi	.L1357
	ldr	r3, .L1391+4
	movs	r1, #22
	ldr	r2, .L1391+12
	strb	r1, [r3, #3]
	ldr	r3, [r6, #12]
	ldr	r7, [r2]
	subs	r3, r7, r3
	cmp	r3, #127
	bls	.L1359
.L1360:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r4], #1
	bhi	.L1360
.L1359:
	ldr	r1, .L1391+16
	movs	r0, #1
	strb	r3, [r4], #1
	subs	r2, r4, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1361
	str	r7, [r6, #12]
.L1357:
	ldr	r3, .L1391+20
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1362
	ldrb	r4, [r6, #2]	@ zero_extendqisi2
	cbz	r4, .L1390
.L1362:
	.syntax unified
@ 2408 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, r7, r8, pc}
.L1390:
	movs	r3, #1
	strb	r3, [r6, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r6, #2]
	.syntax unified
@ 2408 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, r7, r8, pc}
.L1361:
	ldrb	r3, [r6]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r6]
	b	.L1357
.L1389:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1357
	b	.L1358
.L1366:
	subs	r6, r6, #1
	mov	r4, r7
.L1349:
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	strb	r3, [r4], #1
	subs	r3, r4, #2
	subs	r3, r3, r2
	cmp	ip, r3
	bhi	.L1349
	b	.L1363
.L1345:
	strb	r3, [r2, #1]
	mov	r4, r7
	b	.L1363
.L1387:
	.syntax unified
@ 2397 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	movs	r3, #0
	ldr	r2, .L1391+24
	b	.L1336
.L1388:
	.syntax unified
@ 2397 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	movs	r3, #1
	ldr	r2, .L1391+24
	b	.L1336
.L1367:
	movs	r3, #1
	b	.L1341
.L1369:
	ldr	r2, .L1391+24
	b	.L1336
.L1392:
	.align	2
.L1391:
	.word	.LANCHOR4
	.word	.LANCHOR3
	.word	.LANCHOR0
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_RecordModuleDescription, .-SEGGER_SYSVIEW_RecordModuleDescription
	.section	.text.SEGGER_SYSVIEW_NameResource,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_NameResource
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_NameResource, %function
SEGGER_SYSVIEW_NameResource:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r7, r1
	.syntax unified
@ 2156 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L1436
	ldr	r8, .L1436+16
	ldr	r3, [r5, #16]
	mov	r2, r8
	subs	r0, r0, r3
	lsrs	r0, r0, #2
	cmp	r0, #127
	bls	.L1394
.L1395:
	orn	r3, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r3, [r2], #1
	bhi	.L1395
.L1394:
	mov	lr, r2
	strb	r0, [lr], #2
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1396
	mov	r1, r7
	mov	r3, r7
	rsb	ip, r7, #1
.L1397:
	add	r4, ip, r3
	ldrb	r0, [r3, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1397
	cmp	r4, #128
	add	r0, r7, #4
	add	r3, r2, #6
	mov	r9, r4
	it	cs
	movcs	r9, #128
	cmp	r7, r3
	it	cc
	cmpcc	lr, r0
	strb	r9, [r2, #1]
	bcc	.L1417
	cmp	r4, #26
	bls	.L1417
	cmp	r4, #0
	mov	r3, lr
	mov	r0, lr
	ite	ne
	movne	r10, r9
	moveq	r10, #1
	bic	fp, r10, #3
	add	fp, fp, r7
.L1402:
	mov	r4, r3
	ldr	ip, [r1], #4	@ unaligned
	adds	r4, r4, #4
	cmp	r1, fp
	str	ip, [r0], #4	@ unaligned
	mov	r3, r4
	bne	.L1402
	bic	r3, r10, #3
	cmp	r3, r10
	add	r0, r7, r3
	add	r2, lr, r3
	beq	.L1418
	adds	r1, r3, #1
	ldrb	r4, [r7, r3]	@ zero_extendqisi2
	cmp	r9, r1
	strb	r4, [lr, r3]
	add	r4, r2, #1
	bls	.L1418
	adds	r3, r3, #2
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	adds	r4, r2, #2
	cmp	r9, r3
	strb	r1, [r2, #1]
	bls	.L1418
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	adds	r4, r2, #3
	strb	r3, [r2, #2]
.L1418:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1409
	cbz	r3, .L1408
	cmp	r3, #2
	beq	.L1434
.L1409:
	ldr	r3, [r5, #28]
	lsls	r3, r3, #6
	bmi	.L1408
	sub	r8, r4, r8
	ldr	r2, .L1436+4
	cmp	r8, #127
	uxtb	r1, r8
	bls	.L1420
	orn	r0, r1, #127
	mov	r3, r2
	ubfx	r1, r8, #7, #8
	strb	r0, [r3, #2]!
.L1410:
	strb	r1, [r2, #3]
	movs	r0, #25
	ldr	r1, .L1436+8
	subs	r2, r3, #1
	strb	r0, [r3, #-1]
	ldr	r3, [r5, #12]
	ldr	r7, [r1]
	subs	r3, r7, r3
	cmp	r3, #127
	bls	.L1411
.L1412:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r4], #1
	bhi	.L1412
.L1411:
	mov	r1, r2
	strb	r3, [r4], #1
	movs	r0, #1
	subs	r2, r4, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1413
	str	r7, [r5, #12]
.L1408:
	ldr	r3, .L1436+12
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1414
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L1435
.L1414:
	.syntax unified
@ 2162 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L1435:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	.syntax unified
@ 2162 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L1420:
	adds	r3, r2, #3
	b	.L1410
.L1413:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1408
.L1434:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1408
	b	.L1409
.L1417:
	subs	r7, r7, #1
	mov	r4, lr
.L1400:
	ldrb	r3, [r7, #1]!	@ zero_extendqisi2
	strb	r3, [r4], #1
	subs	r3, r4, #2
	subs	r3, r3, r2
	cmp	r9, r3
	bhi	.L1400
	b	.L1418
.L1396:
	strb	r3, [r2, #1]
	mov	r4, lr
	b	.L1418
.L1437:
	.align	2
.L1436:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	_SEGGER_RTT
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_NameResource, .-SEGGER_SYSVIEW_NameResource
	.section	.text.SEGGER_SYSVIEW_RecordEndCallU32,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordEndCallU32
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordEndCallU32, %function
SEGGER_SYSVIEW_RecordEndCallU32:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r3, r1
	.syntax unified
@ 1942 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r7, .L1463
	cmp	r0, #127
	mov	r4, r7
	bls	.L1439
.L1440:
	orn	r2, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r2, [r4], #1
	bhi	.L1440
.L1439:
	cmp	r3, #127
	strb	r0, [r4], #1
	bls	.L1441
.L1442:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r4], #1
	bhi	.L1442
.L1441:
	ldr	r6, .L1463+4
	strb	r3, [r4]
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1448
	cbz	r3, .L1447
	cmp	r3, #2
	beq	.L1461
.L1448:
	ldr	r3, [r6, #28]
	lsls	r3, r3, #3
	bmi	.L1447
	adds	r4, r4, #1
	ldr	r2, .L1463+8
	subs	r7, r4, r7
	cmp	r7, #127
	uxtb	r1, r7
	bls	.L1455
	orn	r0, r1, #127
	mov	r3, r2
	ubfx	r1, r7, #7, #8
	strb	r0, [r3, #2]!
.L1449:
	strb	r1, [r2, #3]
	movs	r0, #28
	ldr	r1, .L1463+12
	subs	r2, r3, #1
	strb	r0, [r3, #-1]
	ldr	r3, [r6, #12]
	ldr	r7, [r1]
	subs	r3, r7, r3
	cmp	r3, #127
	bls	.L1450
.L1451:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r4], #1
	bhi	.L1451
.L1450:
	mov	r1, r2
	strb	r3, [r4], #1
	movs	r0, #1
	subs	r2, r4, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1452
	str	r7, [r6, #12]
.L1447:
	ldr	r3, .L1463+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1453
	ldrb	r4, [r6, #2]	@ zero_extendqisi2
	cbz	r4, .L1462
.L1453:
	.syntax unified
@ 1948 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L1462:
	movs	r3, #1
	strb	r3, [r6, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r6, #2]
	.syntax unified
@ 1948 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, pc}
.L1455:
	adds	r3, r2, #3
	b	.L1449
.L1452:
	ldrb	r3, [r6]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r6]
	b	.L1447
.L1461:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1447
	b	.L1448
.L1464:
	.align	2
.L1463:
	.word	.LANCHOR3+4
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_RecordEndCallU32, .-SEGGER_SYSVIEW_RecordEndCallU32
	.section	.text.SEGGER_SYSVIEW_RecordVoid,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_RecordVoid
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_RecordVoid, %function
SEGGER_SYSVIEW_RecordVoid:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r5, r0
	.syntax unified
@ 1266 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r4, .L1488
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1471
	cbz	r3, .L1470
	cmp	r3, #2
	beq	.L1485
.L1471:
	cmp	r5, #31
	bhi	.L1486
	ldr	r3, [r4, #28]
	lsrs	r3, r3, r5
	ands	r3, r3, #1
	bne	.L1470
	cmp	r5, #23
	uxtb	r2, r5
	bhi	.L1473
	ldr	r0, .L1488+4
	strb	r2, [r0, #3]!
.L1474:
	ldr	r2, .L1488+8
	ldr	r3, [r4, #12]
	ldr	r5, [r2]
	ldr	r2, .L1488+12
	subs	r3, r5, r3
	cmp	r3, #127
	bls	.L1476
.L1477:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1477
.L1476:
	mov	r1, r0
	strb	r3, [r2], #1
	subs	r2, r2, r0
	movs	r0, #1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1478
	str	r5, [r4, #12]
.L1470:
	ldr	r3, .L1488+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1479
	ldrb	r5, [r4, #2]	@ zero_extendqisi2
	cbz	r5, .L1487
.L1479:
	.syntax unified
@ 1269 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1486:
	ldr	r1, .L1488+4
	movs	r3, #0
	cmp	r5, #127
	uxtb	r2, r5
	strb	r3, [r1, #3]
	bls	.L1475
	lsrs	r5, r5, #7
	orn	r2, r2, #127
	mov	r0, r1
	strb	r5, [r1, #2]
	strb	r2, [r0, #1]!
	b	.L1474
.L1487:
	movs	r3, #1
	strb	r3, [r4, #2]
	bl	_HandleIncomingPacket
	strb	r5, [r4, #2]
	.syntax unified
@ 1269 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1478:
	ldrb	r3, [r4]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r4]
	b	.L1470
.L1473:
	ldr	r1, .L1488+4
	strb	r3, [r1, #3]
.L1475:
	ldr	r0, .L1488+20
	strb	r2, [r1, #2]
	b	.L1474
.L1485:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1470
	b	.L1471
.L1489:
	.align	2
.L1488:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+4
	.word	_SEGGER_RTT
	.word	.LANCHOR3+2
	.size	SEGGER_SYSVIEW_RecordVoid, .-SEGGER_SYSVIEW_RecordVoid
	.section	.text.SEGGER_SYSVIEW_GetSysDesc,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_GetSysDesc
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_GetSysDesc, %function
SEGGER_SYSVIEW_GetSysDesc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	.syntax unified
@ 1695 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r6, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r5, .L1520
	ldr	r7, .L1520+4
	ldr	r3, [r5, #4]
	mov	r4, r7
	cmp	r3, #127
	bls	.L1491
.L1492:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r4], #1
	bhi	.L1492
.L1491:
	ldr	r2, [r5, #8]
	strb	r3, [r4], #1
	cmp	r2, #127
	bls	.L1493
.L1494:
	orn	r3, r2, #127
	lsrs	r2, r2, #7
	cmp	r2, #127
	strb	r3, [r4], #1
	bhi	.L1494
.L1493:
	ldr	r3, [r5, #16]
	strb	r2, [r4], #1
	cmp	r3, #127
	bls	.L1495
.L1496:
	orn	r2, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r2, [r4], #1
	bhi	.L1496
.L1495:
	strb	r3, [r4]
	movs	r2, #2
	ldrb	r3, [r5]	@ zero_extendqisi2
	strb	r2, [r4, #1]
	cmp	r3, #1
	beq	.L1502
	cbz	r3, .L1501
	cmp	r3, #2
	beq	.L1517
.L1502:
	ldrb	r3, [r5, #31]	@ zero_extendqisi2
	lsls	r3, r3, #31
	bmi	.L1501
	adds	r4, r4, #2
	ldr	r2, .L1520+8
	subs	r7, r4, r7
	cmp	r7, #127
	uxtb	r1, r7
	bls	.L1510
	orn	r0, r1, #127
	mov	r3, r2
	ubfx	r1, r7, #7, #8
	strb	r0, [r3, #2]!
.L1503:
	strb	r1, [r2, #3]
	movs	r0, #24
	ldr	r1, .L1520+12
	subs	r2, r3, #1
	strb	r0, [r3, #-1]
	ldr	r3, [r5, #12]
	ldr	r7, [r1]
	subs	r3, r7, r3
	cmp	r3, #127
	bls	.L1504
.L1505:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r4], #1
	bhi	.L1505
.L1504:
	mov	r1, r2
	strb	r3, [r4], #1
	movs	r0, #1
	subs	r2, r4, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1506
	str	r7, [r5, #12]
.L1501:
	ldr	r3, .L1520+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1507
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	cbz	r4, .L1518
.L1507:
	.syntax unified
@ 1703 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, [r5, #36]
	cbz	r3, .L1490
.L1519:
	pop	{r4, r5, r6, r7, r8, lr}
	bx	r3	@ indirect register sibling call
.L1518:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r5, #2]
	.syntax unified
@ 1703 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r6  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, [r5, #36]
	cmp	r3, #0
	bne	.L1519
.L1490:
	pop	{r4, r5, r6, r7, r8, pc}
.L1510:
	adds	r3, r2, #3
	b	.L1503
.L1506:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1501
.L1517:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1501
	b	.L1502
.L1521:
	.align	2
.L1520:
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	.LANCHOR3
	.word	-536866812
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_GetSysDesc, .-SEGGER_SYSVIEW_GetSysDesc
	.section	.text.SEGGER_SYSVIEW_Stop,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_Stop
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_Stop, %function
SEGGER_SYSVIEW_Stop:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	.syntax unified
@ 1675 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r4, .L1545
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbnz	r3, .L1543
	.syntax unified
@ 1681 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1543:
	cmp	r3, #2
	beq	.L1524
.L1527:
	ldr	r3, [r4, #28]
	lsls	r3, r3, #20
	bmi	.L1528
	ldr	r2, .L1545+4
	movs	r3, #11
	ldr	r1, .L1545+8
	strb	r3, [r2, #3]
	adds	r2, r2, #4
	ldr	r3, [r4, #12]
	ldr	r6, [r1]
	subs	r3, r6, r3
	cmp	r3, #127
	bls	.L1529
.L1530:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1530
.L1529:
	ldr	r1, .L1545+12
	movs	r0, #1
	strb	r3, [r2], #1
	subs	r2, r2, r1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1531
	str	r6, [r4, #12]
.L1528:
	ldr	r3, .L1545+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1532
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cbz	r6, .L1544
.L1532:
	movs	r3, #0
	strb	r3, [r4]
	.syntax unified
@ 1681 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r4, r5, r6, pc}
.L1544:
	movs	r3, #1
	strb	r3, [r4, #2]
	bl	_HandleIncomingPacket
	strb	r6, [r4, #2]
	b	.L1532
.L1531:
	ldrb	r3, [r4]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r4]
	b	.L1528
.L1524:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1527
	b	.L1528
.L1546:
	.align	2
.L1545:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	-536866812
	.word	.LANCHOR3+3
	.word	_SEGGER_RTT
	.size	SEGGER_SYSVIEW_Stop, .-SEGGER_SYSVIEW_Stop
	.section	.text.SEGGER_SYSVIEW_SendModuleDescription,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_SendModuleDescription
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_SendModuleDescription, %function
SEGGER_SYSVIEW_SendModuleDescription:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1559
	push	{r4, lr}
	ldr	r4, [r3]
	cbz	r4, .L1547
.L1551:
	ldr	r3, [r4, #12]
	cbz	r3, .L1549
	blx	r3
	ldr	r4, [r4, #16]
	cmp	r4, #0
	bne	.L1551
.L1547:
	pop	{r4, pc}
.L1549:
	ldr	r4, [r4, #16]
	cmp	r4, #0
	bne	.L1551
	pop	{r4, pc}
.L1560:
	.align	2
.L1559:
	.word	.LANCHOR4
	.size	SEGGER_SYSVIEW_SendModuleDescription, .-SEGGER_SYSVIEW_SendModuleDescription
	.section	.text.SEGGER_SYSVIEW_SendNumModules,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_SendNumModules
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_SendNumModules, %function
SEGGER_SYSVIEW_SendNumModules:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	sub	sp, sp, #12
	.syntax unified
@ 2485 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r4, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, .L1581
	ldrb	r2, [r3]	@ zero_extendqisi2
	lsls	r1, r2, #24
	bpl	.L1574
	ldr	r3, .L1581+4
	strb	r2, [r3, #4]
	adds	r3, r3, #5
	movs	r2, #1
.L1562:
	ldr	r5, .L1581+8
	strb	r2, [r3]
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1568
	cbz	r2, .L1567
	cmp	r2, #2
	beq	.L1579
.L1568:
	ldr	r2, [r5, #28]
	lsls	r2, r2, #4
	bmi	.L1567
	ldr	r1, .L1581+4
	adds	r3, r3, #1
	adds	r2, r1, #4
	subs	r2, r3, r2
	cmp	r2, #127
	uxtb	r6, r2
	bls	.L1575
	orn	r7, r6, #127
	mov	r0, r1
	ubfx	r6, r2, #7, #8
	strb	r7, [r0, #2]!
.L1569:
	strb	r6, [r1, #3]
	movs	r7, #27
	ldr	r1, .L1581+12
	subs	r2, r0, #1
	strb	r7, [r0, #-1]
	ldr	r0, [r5, #12]
	ldr	r6, [r1]
	subs	r0, r6, r0
	cmp	r0, #127
	bls	.L1570
.L1571:
	orn	r1, r0, #127
	lsrs	r0, r0, #7
	cmp	r0, #127
	strb	r1, [r3], #1
	bhi	.L1571
.L1570:
	strb	r0, [r3], #1
	mov	r1, r2
	movs	r0, #1
	subs	r2, r3, r2
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1572
	str	r6, [r5, #12]
.L1567:
	ldr	r3, .L1581+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1573
	ldrb	r6, [r5, #2]	@ zero_extendqisi2
	cbz	r6, .L1580
.L1573:
	.syntax unified
@ 2489 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L1580:
	movs	r3, #1
	strb	r3, [r5, #2]
	bl	_HandleIncomingPacket
	strb	r6, [r5, #2]
	.syntax unified
@ 2489 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r4  
	
@ 0 "" 2
	.thumb
	.syntax unified
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L1575:
	adds	r0, r1, #3
	b	.L1569
.L1572:
	ldrb	r3, [r5]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r5]
	b	.L1567
.L1579:
	str	r3, [sp, #4]
	bl	_TrySendOverflowPacket
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1567
	ldr	r3, [sp, #4]
	b	.L1568
.L1574:
	ldr	r3, .L1581+20
	b	.L1562
.L1582:
	.align	2
.L1581:
	.word	.LANCHOR5
	.word	.LANCHOR3
	.word	.LANCHOR0
	.word	-536866812
	.word	_SEGGER_RTT
	.word	.LANCHOR3+4
	.size	SEGGER_SYSVIEW_SendNumModules, .-SEGGER_SYSVIEW_SendNumModules
	.section	.text.SEGGER_SYSVIEW_PrintfHostEx,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_PrintfHostEx
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_PrintfHostEx, %function
SEGGER_SYSVIEW_PrintfHostEx:
	@ args = 4, pretend = 12, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 1
	push	{r1, r2, r3}
	push	{lr}
	sub	sp, sp, #8
	add	r3, sp, #12
	add	r2, sp, #4
	ldr	r1, [r3], #4
	str	r3, [sp, #4]
	bl	_VPrintHost
	add	sp, sp, #8
	@ sp needed
	ldr	lr, [sp], #4
	add	sp, sp, #12
	bx	lr
	.size	SEGGER_SYSVIEW_PrintfHostEx, .-SEGGER_SYSVIEW_PrintfHostEx
	.section	.text.SEGGER_SYSVIEW_PrintfHost,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_PrintfHost
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_PrintfHost, %function
SEGGER_SYSVIEW_PrintfHost:
	@ args = 4, pretend = 16, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 1
	push	{r0, r1, r2, r3}
	push	{lr}
	sub	sp, sp, #12
	movs	r1, #0
	add	r3, sp, #16
	add	r2, sp, #4
	ldr	r0, [r3], #4
	str	r3, [sp, #4]
	bl	_VPrintHost
	add	sp, sp, #12
	@ sp needed
	ldr	lr, [sp], #4
	add	sp, sp, #16
	bx	lr
	.size	SEGGER_SYSVIEW_PrintfHost, .-SEGGER_SYSVIEW_PrintfHost
	.section	.text.SEGGER_SYSVIEW_WarnfHost,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_WarnfHost
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_WarnfHost, %function
SEGGER_SYSVIEW_WarnfHost:
	@ args = 4, pretend = 16, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 1
	push	{r0, r1, r2, r3}
	push	{lr}
	sub	sp, sp, #12
	movs	r1, #1
	add	r3, sp, #16
	add	r2, sp, #4
	ldr	r0, [r3], #4
	str	r3, [sp, #4]
	bl	_VPrintHost
	add	sp, sp, #12
	@ sp needed
	ldr	lr, [sp], #4
	add	sp, sp, #16
	bx	lr
	.size	SEGGER_SYSVIEW_WarnfHost, .-SEGGER_SYSVIEW_WarnfHost
	.section	.text.SEGGER_SYSVIEW_ErrorfHost,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_ErrorfHost
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_ErrorfHost, %function
SEGGER_SYSVIEW_ErrorfHost:
	@ args = 4, pretend = 16, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 1
	push	{r0, r1, r2, r3}
	push	{lr}
	sub	sp, sp, #12
	movs	r1, #2
	add	r3, sp, #16
	add	r2, sp, #4
	ldr	r0, [r3], #4
	str	r3, [sp, #4]
	bl	_VPrintHost
	add	sp, sp, #12
	@ sp needed
	ldr	lr, [sp], #4
	add	sp, sp, #16
	bx	lr
	.size	SEGGER_SYSVIEW_ErrorfHost, .-SEGGER_SYSVIEW_ErrorfHost
	.section	.text.SEGGER_SYSVIEW_PrintfTargetEx,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_PrintfTargetEx
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_PrintfTargetEx, %function
SEGGER_SYSVIEW_PrintfTargetEx:
	@ args = 4, pretend = 12, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 1
	push	{r1, r2, r3}
	push	{lr}
	sub	sp, sp, #8
	add	r3, sp, #12
	add	r2, sp, #4
	ldr	r1, [r3], #4
	str	r3, [sp, #4]
	bl	_VPrintTarget
	add	sp, sp, #8
	@ sp needed
	ldr	lr, [sp], #4
	add	sp, sp, #12
	bx	lr
	.size	SEGGER_SYSVIEW_PrintfTargetEx, .-SEGGER_SYSVIEW_PrintfTargetEx
	.section	.text.SEGGER_SYSVIEW_PrintfTarget,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_PrintfTarget
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_PrintfTarget, %function
SEGGER_SYSVIEW_PrintfTarget:
	@ args = 4, pretend = 16, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 1
	push	{r0, r1, r2, r3}
	push	{lr}
	sub	sp, sp, #12
	movs	r1, #0
	add	r3, sp, #16
	add	r2, sp, #4
	ldr	r0, [r3], #4
	str	r3, [sp, #4]
	bl	_VPrintTarget
	add	sp, sp, #12
	@ sp needed
	ldr	lr, [sp], #4
	add	sp, sp, #16
	bx	lr
	.size	SEGGER_SYSVIEW_PrintfTarget, .-SEGGER_SYSVIEW_PrintfTarget
	.section	.text.SEGGER_SYSVIEW_WarnfTarget,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_WarnfTarget
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_WarnfTarget, %function
SEGGER_SYSVIEW_WarnfTarget:
	@ args = 4, pretend = 16, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 1
	push	{r0, r1, r2, r3}
	push	{lr}
	sub	sp, sp, #12
	movs	r1, #1
	add	r3, sp, #16
	add	r2, sp, #4
	ldr	r0, [r3], #4
	str	r3, [sp, #4]
	bl	_VPrintTarget
	add	sp, sp, #12
	@ sp needed
	ldr	lr, [sp], #4
	add	sp, sp, #16
	bx	lr
	.size	SEGGER_SYSVIEW_WarnfTarget, .-SEGGER_SYSVIEW_WarnfTarget
	.section	.text.SEGGER_SYSVIEW_ErrorfTarget,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_ErrorfTarget
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_ErrorfTarget, %function
SEGGER_SYSVIEW_ErrorfTarget:
	@ args = 4, pretend = 16, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 1
	push	{r0, r1, r2, r3}
	push	{lr}
	sub	sp, sp, #12
	movs	r1, #2
	add	r3, sp, #16
	add	r2, sp, #4
	ldr	r0, [r3], #4
	str	r3, [sp, #4]
	bl	_VPrintTarget
	add	sp, sp, #12
	@ sp needed
	ldr	lr, [sp], #4
	add	sp, sp, #16
	bx	lr
	.size	SEGGER_SYSVIEW_ErrorfTarget, .-SEGGER_SYSVIEW_ErrorfTarget
	.section	.text.SEGGER_SYSVIEW_Print,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_Print
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_Print, %function
SEGGER_SYSVIEW_Print:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, lr}
	.syntax unified
@ 2725 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1600
	mov	r3, r0
	mov	r2, r0
	rsb	r4, r0, #1
.L1601:
	adds	r7, r4, r2
	ldrb	r1, [r2, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1601
	ldr	r6, .L1638
	cmp	r7, #128
	add	r4, r0, #4
	mov	r2, r7
	add	r1, r6, #5
	add	ip, r6, #9
	it	cs
	movcs	r2, #128
	cmp	ip, r0
	it	hi
	cmphi	r4, r1
	strb	r2, [r6, #4]
	bhi	.L1621
	cmp	r7, #26
	bls	.L1621
	cmp	r7, #0
	mov	ip, r1
	mov	r7, r1
	ite	ne
	movne	lr, r2
	moveq	lr, #1
	bic	r8, lr, #3
	add	r8, r8, r0
.L1606:
	mov	r4, r7
	ldr	r9, [r3], #4	@ unaligned
	adds	r4, r4, #4
	cmp	r3, r8
	str	r9, [ip], #4	@ unaligned
	mov	r7, r4
	bne	.L1606
	bic	r3, lr, #3
	cmp	r3, lr
	add	ip, r0, r3
	add	r7, r1, r3
	beq	.L1622
	ldrb	r4, [r0, r3]	@ zero_extendqisi2
	adds	r0, r3, #1
	cmp	r2, r0
	strb	r4, [r1, r3]
	add	r4, r7, #1
	bls	.L1622
	adds	r3, r3, #2
	ldrb	r1, [ip, #1]	@ zero_extendqisi2
	adds	r4, r7, #2
	cmp	r2, r3
	strb	r1, [r7, #1]
	bls	.L1622
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	adds	r4, r7, #3
	strb	r3, [r7, #2]
.L1622:
	ldr	r7, .L1638+4
	movs	r2, #0
	ldrb	r3, [r7]	@ zero_extendqisi2
	strb	r2, [r4]
	cmp	r3, #1
	strb	r2, [r4, #1]
	beq	.L1613
	cbz	r3, .L1612
	cmp	r3, #2
	beq	.L1636
.L1613:
	ldr	r3, [r7, #28]
	lsls	r3, r3, #5
	bmi	.L1612
	adds	r2, r4, #2
	ldr	r3, .L1638+8
	subs	r1, r2, r3
	cmp	r1, #127
	uxtb	r0, r1
	bls	.L1623
	orn	r4, r0, #127
	subs	r3, r3, #2
	ubfx	r0, r1, #7, #8
	strb	r4, [r6, #2]
.L1614:
	movs	r4, #26
	ldr	r1, .L1638+12
	strb	r0, [r6, #3]
	subs	r0, r3, #1
	strb	r4, [r3, #-1]
	ldr	r3, [r7, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1615
.L1616:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1616
.L1615:
	mov	r1, r0
	strb	r3, [r2], #1
	subs	r2, r2, r0
	movs	r0, #1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1617
	str	r4, [r7, #12]
.L1612:
	ldr	r3, .L1638+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1618
	ldrb	r4, [r7, #2]	@ zero_extendqisi2
	cbz	r4, .L1637
.L1618:
	.syntax unified
@ 2731 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L1637:
	movs	r3, #1
	strb	r3, [r7, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r7, #2]
	.syntax unified
@ 2731 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L1623:
	subs	r3, r3, #1
	b	.L1614
.L1617:
	ldrb	r3, [r7]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r7]
	b	.L1612
.L1636:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1612
	b	.L1613
.L1621:
	subs	r1, r0, #1
	ldr	r4, .L1638+20
.L1604:
	adds	r3, r1, #2
	ldrb	r7, [r1, #1]	@ zero_extendqisi2
	adds	r1, r1, #1
	subs	r3, r3, r0
	strb	r7, [r4], #1
	cmp	r2, r3
	bhi	.L1604
	b	.L1622
.L1600:
	ldr	r6, .L1638
	strb	r3, [r6, #4]
	adds	r4, r6, #5
	b	.L1622
.L1639:
	.align	2
.L1638:
	.word	.LANCHOR3
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	-536866812
	.word	_SEGGER_RTT
	.word	.LANCHOR3+5
	.size	SEGGER_SYSVIEW_Print, .-SEGGER_SYSVIEW_Print
	.section	.text.SEGGER_SYSVIEW_Warn,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_Warn
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_Warn, %function
SEGGER_SYSVIEW_Warn:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, lr}
	.syntax unified
@ 2747 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1641
	mov	r3, r0
	mov	r2, r0
	rsb	r4, r0, #1
.L1642:
	adds	r7, r4, r2
	ldrb	r1, [r2, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1642
	ldr	r6, .L1679
	cmp	r7, #128
	add	r4, r0, #4
	mov	r2, r7
	add	r1, r6, #5
	add	ip, r6, #9
	it	cs
	movcs	r2, #128
	cmp	ip, r0
	it	hi
	cmphi	r4, r1
	strb	r2, [r6, #4]
	bhi	.L1662
	cmp	r7, #26
	bls	.L1662
	cmp	r7, #0
	mov	ip, r1
	mov	r7, r1
	ite	ne
	movne	lr, r2
	moveq	lr, #1
	bic	r8, lr, #3
	add	r8, r8, r0
.L1647:
	mov	r4, r7
	ldr	r9, [r3], #4	@ unaligned
	adds	r4, r4, #4
	cmp	r3, r8
	str	r9, [ip], #4	@ unaligned
	mov	r7, r4
	bne	.L1647
	bic	r3, lr, #3
	cmp	r3, lr
	add	ip, r0, r3
	add	r7, r1, r3
	beq	.L1663
	ldrb	r4, [r0, r3]	@ zero_extendqisi2
	adds	r0, r3, #1
	cmp	r2, r0
	strb	r4, [r1, r3]
	add	r4, r7, #1
	bls	.L1663
	adds	r3, r3, #2
	ldrb	r1, [ip, #1]	@ zero_extendqisi2
	adds	r4, r7, #2
	cmp	r2, r3
	strb	r1, [r7, #1]
	bls	.L1663
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	adds	r4, r7, #3
	strb	r3, [r7, #2]
.L1663:
	ldr	r7, .L1679+4
	movs	r1, #1
	movs	r2, #0
	ldrb	r3, [r7]	@ zero_extendqisi2
	strb	r1, [r4]
	cmp	r3, r1
	strb	r2, [r4, #1]
	beq	.L1654
	cbz	r3, .L1653
	cmp	r3, #2
	beq	.L1677
.L1654:
	ldr	r3, [r7, #28]
	lsls	r3, r3, #5
	bmi	.L1653
	adds	r2, r4, #2
	ldr	r3, .L1679+8
	subs	r1, r2, r3
	cmp	r1, #127
	uxtb	r0, r1
	bls	.L1664
	orn	r4, r0, #127
	subs	r3, r3, #2
	ubfx	r0, r1, #7, #8
	strb	r4, [r6, #2]
.L1655:
	movs	r4, #26
	ldr	r1, .L1679+12
	strb	r0, [r6, #3]
	subs	r0, r3, #1
	strb	r4, [r3, #-1]
	ldr	r3, [r7, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1656
.L1657:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1657
.L1656:
	mov	r1, r0
	strb	r3, [r2], #1
	subs	r2, r2, r0
	movs	r0, #1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1658
	str	r4, [r7, #12]
.L1653:
	ldr	r3, .L1679+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1659
	ldrb	r4, [r7, #2]	@ zero_extendqisi2
	cbz	r4, .L1678
.L1659:
	.syntax unified
@ 2753 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L1678:
	movs	r3, #1
	strb	r3, [r7, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r7, #2]
	.syntax unified
@ 2753 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L1664:
	subs	r3, r3, #1
	b	.L1655
.L1658:
	ldrb	r3, [r7]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r7]
	b	.L1653
.L1677:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1653
	b	.L1654
.L1662:
	subs	r1, r0, #1
	ldr	r4, .L1679+20
.L1645:
	adds	r3, r1, #2
	ldrb	r7, [r1, #1]	@ zero_extendqisi2
	adds	r1, r1, #1
	subs	r3, r3, r0
	strb	r7, [r4], #1
	cmp	r2, r3
	bhi	.L1645
	b	.L1663
.L1641:
	ldr	r6, .L1679
	strb	r3, [r6, #4]
	adds	r4, r6, #5
	b	.L1663
.L1680:
	.align	2
.L1679:
	.word	.LANCHOR3
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	-536866812
	.word	_SEGGER_RTT
	.word	.LANCHOR3+5
	.size	SEGGER_SYSVIEW_Warn, .-SEGGER_SYSVIEW_Warn
	.section	.text.SEGGER_SYSVIEW_Error,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_Error
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_Error, %function
SEGGER_SYSVIEW_Error:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, lr}
	.syntax unified
@ 2769 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	mrs   r5, basepri  
	mov   r1, #32       
	msr   basepri, r1  
	
@ 0 "" 2
	.thumb
	.syntax unified
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1682
	mov	r3, r0
	mov	r2, r0
	rsb	r4, r0, #1
.L1683:
	adds	r7, r4, r2
	ldrb	r1, [r2, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1683
	ldr	r6, .L1720
	cmp	r7, #128
	add	r4, r0, #4
	mov	r2, r7
	add	r1, r6, #5
	add	ip, r6, #9
	it	cs
	movcs	r2, #128
	cmp	ip, r0
	it	hi
	cmphi	r4, r1
	strb	r2, [r6, #4]
	bhi	.L1703
	cmp	r7, #26
	bls	.L1703
	cmp	r7, #0
	mov	ip, r1
	mov	r7, r1
	ite	ne
	movne	lr, r2
	moveq	lr, #1
	bic	r8, lr, #3
	add	r8, r8, r0
.L1688:
	mov	r4, r7
	ldr	r9, [r3], #4	@ unaligned
	adds	r4, r4, #4
	cmp	r3, r8
	str	r9, [ip], #4	@ unaligned
	mov	r7, r4
	bne	.L1688
	bic	r3, lr, #3
	cmp	r3, lr
	add	ip, r0, r3
	add	r7, r1, r3
	beq	.L1704
	ldrb	r4, [r0, r3]	@ zero_extendqisi2
	adds	r0, r3, #1
	cmp	r2, r0
	strb	r4, [r1, r3]
	add	r4, r7, #1
	bls	.L1704
	adds	r3, r3, #2
	ldrb	r1, [ip, #1]	@ zero_extendqisi2
	adds	r4, r7, #2
	cmp	r2, r3
	strb	r1, [r7, #1]
	bls	.L1704
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	adds	r4, r7, #3
	strb	r3, [r7, #2]
.L1704:
	ldr	r7, .L1720+4
	movs	r1, #2
	movs	r2, #0
	ldrb	r3, [r7]	@ zero_extendqisi2
	strb	r1, [r4]
	cmp	r3, #1
	strb	r2, [r4, #1]
	beq	.L1695
	cbz	r3, .L1694
	cmp	r3, #2
	beq	.L1718
.L1695:
	ldr	r3, [r7, #28]
	lsls	r3, r3, #5
	bmi	.L1694
	adds	r2, r4, #2
	ldr	r3, .L1720+8
	subs	r1, r2, r3
	cmp	r1, #127
	uxtb	r0, r1
	bls	.L1705
	orn	r4, r0, #127
	subs	r3, r3, #2
	ubfx	r0, r1, #7, #8
	strb	r4, [r6, #2]
.L1696:
	movs	r4, #26
	ldr	r1, .L1720+12
	strb	r0, [r6, #3]
	subs	r0, r3, #1
	strb	r4, [r3, #-1]
	ldr	r3, [r7, #12]
	ldr	r4, [r1]
	subs	r3, r4, r3
	cmp	r3, #127
	bls	.L1697
.L1698:
	orn	r1, r3, #127
	lsrs	r3, r3, #7
	cmp	r3, #127
	strb	r1, [r2], #1
	bhi	.L1698
.L1697:
	mov	r1, r0
	strb	r3, [r2], #1
	subs	r2, r2, r0
	movs	r0, #1
	bl	SEGGER_RTT_WriteSkipNoLock
	cbz	r0, .L1699
	str	r4, [r7, #12]
.L1694:
	ldr	r3, .L1720+16
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1700
	ldrb	r4, [r7, #2]	@ zero_extendqisi2
	cbz	r4, .L1719
.L1700:
	.syntax unified
@ 2775 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L1719:
	movs	r3, #1
	strb	r3, [r7, #2]
	bl	_HandleIncomingPacket
	strb	r4, [r7, #2]
	.syntax unified
@ 2775 "/home/neil/Dropbox/DigiPen/CET341SU19/Assignments/Assignment 05/Unittest_RTOS_LED - Copy/Src/BSP/MCU/SEGGER_SYSVIEW.c" 1
	msr   basepri, r5  
	
@ 0 "" 2
	.thumb
	.syntax unified
	pop	{r3, r4, r5, r6, r7, r8, r9, pc}
.L1705:
	subs	r3, r3, #1
	b	.L1696
.L1699:
	ldrb	r3, [r7]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r7]
	b	.L1694
.L1718:
	bl	_TrySendOverflowPacket
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1694
	b	.L1695
.L1703:
	subs	r1, r0, #1
	ldr	r4, .L1720+20
.L1686:
	adds	r3, r1, #2
	ldrb	r7, [r1, #1]	@ zero_extendqisi2
	adds	r1, r1, #1
	subs	r3, r3, r0
	strb	r7, [r4], #1
	cmp	r2, r3
	bhi	.L1686
	b	.L1704
.L1682:
	ldr	r6, .L1720
	strb	r3, [r6, #4]
	adds	r4, r6, #5
	b	.L1704
.L1721:
	.align	2
.L1720:
	.word	.LANCHOR3
	.word	.LANCHOR0
	.word	.LANCHOR3+4
	.word	-536866812
	.word	_SEGGER_RTT
	.word	.LANCHOR3+5
	.size	SEGGER_SYSVIEW_Error, .-SEGGER_SYSVIEW_Error
	.section	.text.SEGGER_SYSVIEW_EnableEvents,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_EnableEvents
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_EnableEvents, %function
SEGGER_SYSVIEW_EnableEvents:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L1723
	ldr	r3, [r2, #28]
	bic	r0, r3, r0
	str	r0, [r2, #28]
	bx	lr
.L1724:
	.align	2
.L1723:
	.word	.LANCHOR0
	.size	SEGGER_SYSVIEW_EnableEvents, .-SEGGER_SYSVIEW_EnableEvents
	.section	.text.SEGGER_SYSVIEW_DisableEvents,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_DisableEvents
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_DisableEvents, %function
SEGGER_SYSVIEW_DisableEvents:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L1726
	ldr	r3, [r2, #28]
	orrs	r0, r0, r3
	str	r0, [r2, #28]
	bx	lr
.L1727:
	.align	2
.L1726:
	.word	.LANCHOR0
	.size	SEGGER_SYSVIEW_DisableEvents, .-SEGGER_SYSVIEW_DisableEvents
	.section	.text.SEGGER_SYSVIEW_IsStarted,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SEGGER_SYSVIEW_IsStarted
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv5-d16
	.type	SEGGER_SYSVIEW_IsStarted, %function
SEGGER_SYSVIEW_IsStarted:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	ldr	r3, .L1734
	ldr	r4, .L1734+4
	ldr	r2, [r3, #132]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	beq	.L1729
	ldrb	r5, [r4, #2]	@ zero_extendqisi2
	cbz	r5, .L1733
.L1729:
	ldrb	r0, [r4]	@ zero_extendqisi2
	pop	{r3, r4, r5, pc}
.L1733:
	movs	r3, #1
	strb	r3, [r4, #2]
	bl	_HandleIncomingPacket
	strb	r5, [r4, #2]
	ldrb	r0, [r4]	@ zero_extendqisi2
	pop	{r3, r4, r5, pc}
.L1735:
	.align	2
.L1734:
	.word	_SEGGER_RTT
	.word	.LANCHOR0
	.size	SEGGER_SYSVIEW_IsStarted, .-SEGGER_SYSVIEW_IsStarted
	.section	.bss._DownBuffer,"aw",%nobits
	.align	2
	.set	.LANCHOR2,. + 0
	.type	_DownBuffer, %object
	.size	_DownBuffer, 8
_DownBuffer:
	.space	8
	.section	.bss._NumModules,"aw",%nobits
	.set	.LANCHOR5,. + 0
	.type	_NumModules, %object
	.size	_NumModules, 1
_NumModules:
	.space	1
	.section	.bss._SYSVIEW_Globals,"aw",%nobits
	.align	2
	.set	.LANCHOR0,. + 0
	.type	_SYSVIEW_Globals, %object
	.size	_SYSVIEW_Globals, 40
_SYSVIEW_Globals:
	.space	40
	.section	.bss._UpBuffer,"aw",%nobits
	.align	2
	.set	.LANCHOR1,. + 0
	.type	_UpBuffer, %object
	.size	_UpBuffer, 1024
_UpBuffer:
	.space	1024
	.section	.bss._aPacket,"aw",%nobits
	.align	2
	.set	.LANCHOR3,. + 0
	.type	_aPacket, %object
	.size	_aPacket, 227
_aPacket:
	.space	227
	.section	.bss._pFirstModule,"aw",%nobits
	.align	2
	.set	.LANCHOR4,. + 0
	.type	_pFirstModule, %object
	.size	_pFirstModule, 4
_pFirstModule:
	.space	4
	.section	.rodata.SEGGER_SYSVIEW_Init.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"SysView\000"
	.section	.rodata._aV2C.6123,"a"
	.align	2
	.set	.LANCHOR6,. + 0
	.type	_aV2C.6123, %object
	.size	_aV2C.6123, 16
_aV2C.6123:
	.byte	48
	.byte	49
	.byte	50
	.byte	51
	.byte	52
	.byte	53
	.byte	54
	.byte	55
	.byte	56
	.byte	57
	.byte	65
	.byte	66
	.byte	67
	.byte	68
	.byte	69
	.byte	70
	.section	.rodata._abSync,"a"
	.align	2
	.set	.LANCHOR7,. + 0
	.type	_abSync, %object
	.size	_abSync, 10
_abSync:
	.space	10
	.ident	"GCC: (GNU) 8.3.1 20190703 (release) [gcc-8-branch revision 273027]"
