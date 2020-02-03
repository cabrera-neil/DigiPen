#include "ADC.h"
#include "TM4C123GH6PM.h"

// ********************ADC Init********************
// Initialise ADC
// Input: none
// Output: none
void ADC_Init(void)
{
    volatile unsigned long delay;
 
	// PortF: Bit 5 |= 0x20
	// PortE: Bit 4 |= 0x10
	// PortD: Bit 3 |= 0x08
	// PortC: Bit 2 |= 0x04
	// PortB: Bit 1 |= 0x02
	// PortA: Bit 0 |= 0x01
	// NOTE: PD7 and PF0 are Locked, Use Magic Number and Commit to Unlock
	SYSCTL->RCGC2 |= 0x10;				// Enable Clock Gating
	delay 				= SYSCTL->RCGC2;// Stabilise

	GPIOE->DIR 		&= ~0x04;       // Set PE2 as Input
	GPIOE->AFSEL 	|= 0x04;        // Enable AFSEL for PE2
	GPIOE->PCTL 	= 0;            // Clear PCTL for PE2
	GPIOE->DEN 		&= ~0x04;       // Disable Digital for PE2
	GPIOE->AMSEL 	|= 0x04;        // Enable AMSEL for PC3-PC0
    
	// Analog Initialization:
	SYSCTL->RCGC0 |= 0x10000;			// Enable the ADC clock
	delay 				= SYSCTL->RCGC0;// Stabilise
	SYSCTL->RCGC0 &= ~0x300;      // Configure for 125K samples/second
	ADC0->SSPRI 	&= ~0x3000;     // Set Highest Priority = 0
	ADC0->ACTSS 	&= ~0x08;       // Disable sample sequencer 3
	ADC0->EMUX 		&= ~0xF000;     // Use software trigger - SysTick
	ADC0->SSMUX3 	|= 0x01;        // Choose Ain channel 1
	ADC0->SSCTL3 	|= 0x06;        // Clear TS0, D0; Set IE0, END0
	ADC0->ACTSS 	|= 0x08;        // Enable Sample sequencer 3
}

// ********************ADC In********************
// Read Input from ADC
// Input: none
// Output: 12-bit Result of ADC Conversion
unsigned long ADC_In(void)
{
		unsigned long result;
 
    ADC0->PSSI |= 0x08; 						// initiate SS3
 
    while ((ADC0->RIS & 0x08) == 0);// Wait until conversion is done:
    
		result = ADC0->SSFIFO3 & 0xFFF; // Mask with 12-bit binary
    ADC0->ISC |= 0x08;              // Clear the flag to start capturing another Sample
    
		return result;
}
