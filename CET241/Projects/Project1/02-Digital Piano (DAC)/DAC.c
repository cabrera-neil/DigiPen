#include "TM4C123GH6PM.h"
#include "DAC.h"

// ********************DAC Init********************
// Initialise 4-Bit DAC
// Input: none
// Output: none
void DAC_Init(void)
{
	unsigned long delay;
	// Use Port B for Output
	// PortF: Bit 5 |= 0x20
	// PortE: Bit 4 |= 0x10
	// PortD: Bit 3 |= 0x08
	// PortC: Bit 2 |= 0x04
	// PortB: Bit 1 |= 0x02
	// PortA: Bit 0 |= 0x01
	// NOTE: PD7 and PF0 are Locked, Use Magic Number and Commit to Unlock
	SYSCTL->RCGC2 |=	0x02;					// Enable Clock Gating
	delay					=		SYSCTL->RCC2;	// Stabilise
	
	GPIOB->AMSEL	&=	~0x0F;				// Disable AMSEL for PB3-PB0
	GPIOB->AFSEL	&=	~0x0F;				// Disable AFSEL for PB3-PB0
	GPIOB->PCTL		&=	~0xFFFF;			// Clear PCTL for PB3-PB0
	GPIOB->DIR		|=	0x0F;					// Set PB3-PB0 as Output
	GPIOB->DR8R		|=	0x0F;					// Enable 8mA output
	GPIOB->DEN		|=	0x0F;					// Enable Digital for PB3-PB0
}

// ********************DAC Out********************
// Output to DAC
// Input: 4-bit data, 0 to 15
// Output: none
void DAC_Out(unsigned long data)
{
	GPIOB->DATA	=	data;
}
