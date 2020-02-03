#include "TM4C123GH6PM.h"

// ********************UART Init********************
// Initialise UART for 115200 Baud Rate, PLL must be at 80Mhz
// 8 bit word length, no parity bits, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void);
