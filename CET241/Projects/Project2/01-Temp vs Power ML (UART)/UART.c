#include "UART.h"

// ********************UART Init********************
// Initialise UART for 115200 Baud Rate, PLL must be at 80Mhz
// 8 bit word length, no parity bits, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void)
{
//	1. Enable the UART module using the RCGCUART register (see page 344).
	SYSCTL->RCGCUART |= 0x01;
	while((SYSCTL->PRUART & 0x01)==0);	// Wait for UART to be Ready, Stabilise
	
//	2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 340).
//	To find out which GPIO port to enable, refer to Table 23-5 on page 1351.
	SYSCTL->RCGCGPIO |= 0x01;						// Use PortA
	while((SYSCTL->PRGPIO & 0x01)==0);	// Wait for GPIO Port A to be Ready, Stabilise

//	3. Set the GPIO AFSEL bits for the appropriate pins (see page 671). To determine which GPIOs to
//	configure, see Table 23-4 on page 1344.
	GPIOA->AFSEL	|=	0x03;		// Use PA1-PA0;
	GPIOA->DEN		|=	0x03;		// Enable Digital on PA1-PA0
	GPIOA->AMSEL	&=	~0x03;	// Disable Analog on PA1-PA0

//	4. Configure the GPIO current level and/or slew rate as specified for the mode selected (see
//	page 673 and page 681).
	//GPIOA->DR8R |= 0x03;	// Enable 8mA
	//GPIOA->SLR	|= 0x03;	// Enable Slew Rate, will only work if 8mA is enabled
	
//	5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate
//	pins (see page 688 and Table 23-5 on page 1351).
	GPIOA->PCTL = (GPIOA->PCTL & 0xFFFFFF00) | 0x11;
	
//	With the BRD values in hand, the UART configuration is written to the module in the following order:
//	1. Disable the UART by clearing the UARTEN bit in the UARTCTL register.
	UART0->CTL &= ~0x00000001; 
	
//	2. Write the integer portion of the BRD to the UARTIBRD register.
	// IBRD = 80Mhz / (16 * 115200) = 43.402778, assuming HSE in CTL is 1
	UART0->IBRD = 43;
	
//	3. Write the fractional portion of the BRD to the UARTFBRD register.
	// FBRD = integer(0.402778 * 64 + 0.5) = 26
	UART0->FBRD = 26;

//	4. Write the desired serial parameters to the UARTLCRH register (in this case, a value of
//	0x0000.0060).
	UART0->LCRH = (UART0->LCRH & 0xFFFFFF00) | 0x00000070;

//	5. Configure the UART clock source by writing to the UARTCC register.
	UART0->CC = 0x00;

//	6. Optionally, configure the µDMA channel (see “Micro Direct Memory Access (µDMA)” on page 585)
//	and enable the DMA option(s) in the UARTDMACTL register.

//	7. Enable the UART by setting the UARTEN bit in the UARTCTL register.
	UART0->CTL |= 0x00000001;
}
