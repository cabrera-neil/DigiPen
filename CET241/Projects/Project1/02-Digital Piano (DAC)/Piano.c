#include "TM4C123GH6PM.h"
#include "Piano.h"

// store the index value of the corresponding input
unsigned short freq_index;

// ********************Piano Init********************
// Initialise Piano Key Inputs
// Input: none
// Output: none
void Piano_Init(void)
{
	unsigned long delay;
	// Use Port B for Input
	// PortF: Bit 5 |= 0x20
	// PortE: Bit 4 |= 0x10
	// PortD: Bit 3 |= 0x08
	// PortC: Bit 2 |= 0x04
	// PortB: Bit 1 |= 0x02
	// PortA: Bit 0 |= 0x01
	// NOTE: PD7 and PF0 are Locked, Use Magic Number and Commit to Unlock
	SYSCTL->RCGC2 |=	0x10;					// Enable Clock Gating
	delay					=		SYSCTL->RCC2;	// Stabilise
	
	GPIOE->AMSEL	&=	~0x3F;				// Disable AMSEL for PE5-PE0
	GPIOE->AFSEL	&=	~0x3F;				// Disable AFSEL for PE5-PE0
	GPIOE->PCTL		&=	~0xFFFFFF;		// Clear PCTL for PE5-PE0
	GPIOE->DIR		&=	~0x3F;				// Set PE5-PE0 as Input
	GPIOE->PUR		&=	~0x3F;				// Disable Pull Up Resistors
	GPIOE->DEN		|=	0x3F;					// Enable Digital for PE5-PE0
	
	// PE5 to PE0 used for A, G, F, E, D, C
	// PA6 and PA7 used for B, C6
	// PA5 for DEMO Mode
	SYSCTL->RCGC2 |=	0x01;					// Enable Clock Gating
	delay					=		SYSCTL->RCC2;	// Stabilise
		
	GPIOA->AMSEL	&=	~0xE0;				// Disable AMSEL for PA7 to PA5
	GPIOA->AFSEL	&=	~0xE0;				// Disable AFSEL for PA7 to PA5
	GPIOA->PCTL		&=	~0xFFF00000;	// Clear PCTL for PA7 to PA5
	GPIOA->DIR		&=	~0xE0;				// Set PA7 to PA5 as Input 
	GPIOA->PUR		&=	~0xE0;				// Disable Pull Up Resistors
	GPIOA->DEN		|=	0xE0;					// Enable Digital for PA7 to PA5
}

// ********************Piano Out********************
// Input from Piano Key Inputs
// Input: none
// Output: none
void Piano_In(void)
{
		if (GPIOE->DATA == 0x01) {        // C Note,
        freq_index = 0;               // store "Key 0 is pressed"
    } else if (GPIOE->DATA == 0x02) { // D Note,
        freq_index = 1;               // store "Key 1 is pressed"
    } else if (GPIOE->DATA == 0x04) { // E Note,
        freq_index = 2;               // store "Key 2 is pressed"
    } else if (GPIOE->DATA == 0x08) { // F Note,
        freq_index = 3;               // store "Key 3 is pressed"
		} else if (GPIOE->DATA == 0x10) { // G Note,
        freq_index = 4;               // store "Key 4 is pressed"
		} else if (GPIOE->DATA == 0x20) { // A Note,
        freq_index = 5;               // store "Key 5 is pressed"
		} else if (GPIOA->DATA == 0x40) { // B Note,
        freq_index = 6;               // store "Key 6 is pressed"
		} else if (GPIOA->DATA == 0x80) { // C6 Note,
        freq_index = 7;               // store "Key 7 is pressed"
		} else if (GPIOA->DATA == 0x20) { // Demo
        freq_index = 9;               // store "Key 9 is pressed"
    } else {                          // otherwise,
        freq_index = 8;               // store "No key is pressed"
    }
}
