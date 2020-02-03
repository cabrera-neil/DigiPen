/*
Title: Simple button/LEDs control using LaunchPad built-in

Where:
	SW1 left switch is negative logic PF4 on the LaunchPad
	red LED connected to PF1 on the LaunchPad
	blue LED connected to PF2 on the LaunchPad
	green LED connected to PF3 on the LaunchPad

Date: 29-July 2019
Author: Neil Cabrera
Outputs: RBG LEDs (PF3, PF2, PF1)
Function Description:
	red and blue LEDs blink alterntively without SW1-pressed;
	green and blue LEDs blink alternatively with SW1-pressed
*/

// 1. Pre-Processor Directives Section
// Constant declarations to access port registers using symbolic names instead of addresses
#define GPIO_PORTF_DATA_R (*((volatile unsigned long *) 0x400253FC))
#define GPIO_PORTF_DIR_R (*((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_AFSEL_R (*((volatile unsigned long *) 0x40025420))
#define GPIO_PORTF_PUR_R (*((volatile unsigned long *) 0x40025510))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long *) 0x4002551C))
#define GPIO_PORTF_LOCK_R (*((volatile unsigned long *) 0x40025520))
#define GPIO_PORTF_CR_R (*((volatile unsigned long *) 0x40025524))
#define GPIO_PORTF_AMSEL_R (*((volatile unsigned long *) 0x40025528))
#define GPIO_PORTF_PCTL_R (*((volatile unsigned long *) 0x4002552C))
#define SYSCTL_RCGC2_R (*((volatile unsigned long *) 0x400FE108))

// 2. Declarations Section
// Global Variables
unsigned long In; // input from PF4
unsigned long Out; // outputs to PF3, PF2, PF1 (multicolour LED)

// Function Prototypes
void PortF_Init_Lab0(void);
void Delay(void);

// 3. Subroutines Section
// main: Mandatory for a C program to be executable
int main(void)
{
	unsigned long Test = 0x12345678;
	Test *= 1;
	
	PortF_Init_Lab0();
	while(1)
	{
		In = GPIO_PORTF_DATA_R & 0x10;
		if(In==0x00)
		{
			GPIO_PORTF_DATA_R |= 0x08;
			GPIO_PORTF_DATA_R &= ~0x06;
		}
		else
		{
			//GPIO_PORTF_DATA_R |= 0x02;
			//GPIO_PORTF_DATA_R &= ~0x0C;
			GPIO_PORTF_DATA_R |= 0x0A;
			GPIO_PORTF_DATA_R &= ~0x04;
		}
		
		Delay();
		
		GPIO_PORTF_DATA_R |= 0x04;
		GPIO_PORTF_DATA_R &= ~0x0A;
		
		Delay();
	}
}

void PortF_Init_Lab0(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020;
	delay = SYSCTL_RCGC2_R;
	
	GPIO_PORTF_AMSEL_R &= ~0x1E;
	GPIO_PORTF_PCTL_R &= ~0xFFFFF0;
	GPIO_PORTF_DIR_R &= ~0x10;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_AFSEL_R &= ~0x1E;
	GPIO_PORTF_PUR_R |= 0x10;
	GPIO_PORTF_DEN_R |= 0x1E;
}

void Delay(void)
{
	unsigned long volatile time;
	time = 1600000;
	
	while(time>0)
	{
		time--;
	}
}