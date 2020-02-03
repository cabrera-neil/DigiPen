// SysTick Parameters
#define NVIC_ST_CTRL_R 			(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R 		(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R 	(*((volatile unsigned long *)0xE000E018))
#define NVIC_SYS_PRI3_R 		(*((volatile unsigned long *)0xE000ED20))

extern const unsigned long Frequency_Period[4];

// ********************PLL 80Mhz Init********************
// Set PLL to 8-Mhz
// Input: none
// Output: none
void PLL_Init80(void);

// ********************Sound Init********************
// Call the PLL, DAC and SysTick Initalisation
// Input: none
// Output: none
void Sound_Init(void);

// ********************Sound Tone********************
// Call the PLL, DAC and SysTick Initalisation
// Input: Period which will be the reload value for SysTick
// Output: none
void Sound_Tone(unsigned long period);

// ********************Sound Off********************
// Forces 0 Output to the DAC when no key is pressed to avoid noise
// Input: none
// Output: none
void Sound_Off(void);
