/*
Title: Finite State Machine Implementation with Stepper Motor

Where:
	when you press SW1, Rotate CCW
	when you press SW2, Rotate CW
	when nothing is pressed, no rotation

Date: 26-August 2019
Author: Neil Cabrera
*/

#include "TM4C123GH6PM.h"

// SysTick Parameters
#define NVIC_ST_CTRL_R 			(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R 		(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R 	(*((volatile unsigned long *)0xE000E018))
#define NVIC_SYS_PRI3_R 		(*((volatile unsigned long *)0xE000ED20))

// S FSM
struct State
{
	uint32_t out;		//4 bit output
	uint8_t next[2];//next if 2-bit input is 0-3
};

typedef const struct State StateType;

// STATES DEFINITION
#define S0	0x00
#define S1 	0x01
#define S2	0x02
#define S3	0x03

// DEFINE MOORE FSM
StateType mooreFSM[4] = {
	{0x05, {S1, S3}},	// S0
	{0x06, {S2, S0}},	// S1
	{0x0A, {S3, S1}},	// S2, Initial Position
	{0x09, {S0, S2}}	// S3
};

// DEFINE DIRECTION OF ROTATION
enum Direction {CW, CCW, S};

// GLOBAL VARIABLE FOR CURRENT STATE
volatile unsigned char cState;

// CLOCK INITIALISATION
void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);

// PORT INITIALISATION
void PortD_Init(void);
void PortF_Init(void);

// FUNCTION TO CONTROL THE STEPPER MOTOR
void Stepper(enum Direction StepperDirection, unsigned long delay);

int main(void)
{
	SysTick_Init();
	PortD_Init();
	PortF_Init();
	
	// Set Initial Values
	cState = S2;
	
	while(1)
	{
		if((GPIOF->DATA & 0x10) == 0x00)
			Stepper(CCW, 80000);
		else if((GPIOF->DATA & 0x01) == 0x00)
			Stepper(CW, 80000);
		else
			Stepper(S, 80000);
	}
}

// ********************PLL 50Mhz Init********************
// Set PLL to 50-Mhz
// Input: none
// Output: none
void PLL_Init50(void)
{
		SYSCTL->RCC2	|=	0x80000000;
		SYSCTL->RCC2	|=	0x00000800;
		SYSCTL->RCC		=		(SYSCTL->RCC &~0x000007C0)+(0x15<<6);
		SYSCTL->RCC2	&=	~0x00000070;
		SYSCTL->RCC2	&= 	~0x00002000;
		
    SYSCTL->RCC2	|= 0x40000000;
		SYSCTL->RCC2 	= (SYSCTL->RCC2&~0x1FC00000)+(7<<22);

		while((SYSCTL->RIS&0x00000040)==0);

		SYSCTL->RCC2 &= ~0x00000800;
}

// ********************SysTick Init********************
// Call the PLL and SysTick Initalisation
// Input: none
// Output: none
void SysTick_Init(void) 
{
		// PLL Initialisation - 50 Mhz
		PLL_Init50();
    
		// SysTick Initialization
    NVIC_ST_CTRL_R 		= 0;          // Disable SysTick during setup
    NVIC_ST_RELOAD_R 	= 0x00FFFFFF;	// Set the Maximum Reload Value to 16777215
    NVIC_ST_CURRENT_R = 0;         	// Set Current Count to 0
    
		// Set Priority 1
    NVIC_SYS_PRI3_R 	= (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
    NVIC_ST_CTRL_R 		= 0x0005;       // Enable the Clock Source and Systick
}

void SysTick_Wait(unsigned long delay)
{
    NVIC_ST_RELOAD_R  = delay;  	// reload value
    NVIC_ST_CURRENT_R = 0;       	// any write to current clears it
    
    while((NVIC_ST_CTRL_R&0x00010000) == 0); //wait for count flag
}

// ********************PortC Init********************
// Port D for Motor Output, Use PD3-PD0
// Input: none
// Output: none
void PortD_Init(void)
{
	unsigned long delay;
	
	// PortF: Bit 5 |= 0x20
	// PortE: Bit 4 |= 0x10
	// PortD: Bit 3 |= 0x08
	// PortC: Bit 2 |= 0x04
	// PortB: Bit 1 |= 0x02
	// PortA: Bit 0 |= 0x01
	// NOTE: PD7 and PF0 are Locked, Use Magic Number and Commit to Unlock
	SYSCTL->RCGC2 |=	0x08;					// Enable Clock Gating
	delay					=		SYSCTL->RCC2;	// Stabilise
	
	GPIOD->AMSEL	&=	~0x0F;				// Disable AMSEL for PC3-PC0
	GPIOD->AFSEL	&=	~0x0F;				// Disable AFSEL for PC3-PC0
	GPIOD->PCTL		&=	~0xFFFF;			// Clear PCTL for PC3-PC0
	GPIOD->DIR		|=	0x0F;					// Set PC3-PC0 as Output
	GPIOD->DEN		|=	0x0F;					// Enable Digital for PC3-PC0
}

// ********************PortF Init********************
// Port F for Switch Input, Use PC4 and PF0
// Input: none
// Output: none
void PortF_Init(void)
{
	unsigned long delay;
	
	// PortF: Bit 5 |= 0x20
	// PortE: Bit 4 |= 0x10
	// PortD: Bit 3 |= 0x08
	// PortC: Bit 2 |= 0x04
	// PortB: Bit 1 |= 0x02
	// PortA: Bit 0 |= 0x01
	// NOTE: PD7 and PF0 are Locked, Use Magic Number and Commit to Unlock
	SYSCTL->RCGC2 |=	0x20;					// Enable Clock Gating
	delay					=		SYSCTL->RCC2;	// Stabilise
	
	GPIOF->LOCK  	= 0X4C4F434B;			// Enable PF0
	GPIOF->CR 		|= 0x01;					// Enable PF0
	
	GPIOF->AMSEL	&=	~0x11;				// Disable AMSEL for PF4 and PF0
	GPIOF->AFSEL	&=	~0x11;				// Disable AFSEL for PF4 and PF0
	GPIOF->PCTL		&=	~0xF000F;			// Clear PCTL for PF4 and PF0
	GPIOF->DIR		&=	~0x11;				// Set PF4 and PF0 as Input
	GPIOF->PUR		|= 	0x11;					// Set Pull Up Resistor for PF4 and PF0
	GPIOF->DEN		|=	0x11;					// Enable Digital for PF4 and PF0
}

// ********************PortF Init********************
// Port F for Switch Input, Use PC4 and PF0
// Input: none
// Output: none
void Stepper(enum Direction StepperDirection, unsigned long delay)
{
	if(StepperDirection!=S)
	{
		GPIOD->DATA = mooreFSM[cState].out;
		cState = mooreFSM[cState].next[StepperDirection];
		
		SysTick_Wait(delay);
	}
}
