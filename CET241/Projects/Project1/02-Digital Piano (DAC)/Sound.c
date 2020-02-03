#include "Sound.h"
#include "DAC.h"
#include "Piano.h"
#include "TM4C123GH6PM.h"

// Digital Values for the SINE WAVE
// 2 Versions: 16 and 32 (Sampling and Sampling*2)
//const unsigned char SINE_WAVE[16] = {8, 10, 13, 14, 15, 14, 13, 10, 
//																		 8, 5, 2, 1, 0, 1, 2, 5};
  const unsigned char SINE_WAVE[32] = {8,9,11,12,13,14,15,15,
																			 15,15,15,14,13,12,11,9,
																			 8,7,5,4,3,2,1,1,
																			 1,1,1,2,3,4,5,7};

// Stores the Current Position in the SINE WAVE
// Allowed Values from 0 to 15
volatile unsigned char position = 0;

// ********************PLL 80Mhz Init********************
// Set PLL to 80Mhz
// Input: none
// Output: none
void PLL_Init80(void)
{
		SYSCTL->RCC2	|=	0x80000000;
		SYSCTL->RCC2	|=	0x00000800;
		SYSCTL->RCC		=		(SYSCTL->RCC &~0x000007C0)+(0x15<<6);
		SYSCTL->RCC2	&=	~0x00000070;
		SYSCTL->RCC2	&= 	~0x00002000;
		
    SYSCTL->RCC2	|= 0x40000000;
		SYSCTL->RCC2 	= (SYSCTL->RCC2&~0x1FC00000)+(4<<22);

		while((SYSCTL->RIS&0x00000040)==0);

		SYSCTL->RCC2 &= ~0x00000800;
}

// ********************Sound Init********************
// Call the PLL, DAC and SysTick Initalisation
// Input: none
// Output: none
void Sound_Init(void) 
{
		// PLL Initialisation - 80 Mhz
		PLL_Init80();
	
    // DAC Initialization
    DAC_Init();                     // call the InitDac() function in DAC.c
    position = 0;                   // init value of index is 0
    
		// SysTick Initialization
    NVIC_ST_CTRL_R = 0;            // Disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF; // Set the Maximum Reload Value to 16777215
    NVIC_ST_CURRENT_R = 0;         // Set Current Count to 0
    
		// Set Priority 1
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
    NVIC_ST_CTRL_R = 0x0007;       // Enable the Clock Source, Interrupt and Systick
}

// ********************Sound Tone********************
// Call the PLL, DAC and SysTick Initalisation
// Input: Period which will be the reload value for SysTick
// Output: none
void Sound_Tone(unsigned long period) {
    // Reset the RELOAD value based on the Note that was pressed
		// Refer to the Excel File for the Values
    NVIC_ST_RELOAD_R = (period - 1) & 0x00FFFFFF;
}

// ********************Sound Off********************
// Forces 0 Output to the DAC when no key is pressed to avoid noise
// Input: none
// Output: none
void Sound_Off(void)
{
		GPIOB->DATA &= ~0x0F;	// Clear the DAC and Force Output to 0
}

// ********************SysTick Event Handler********************
// Event Handler for Systick
// Input: none
// Output: none
void SysTick_Handler(void) 
{
    if (freq_index != 8) 
		{
        position = (position + 1) & 0x3F; // Position in the SINEWAVE & with 0x3F to reset once it reaches the limit
        DAC_Out(SINE_WAVE[position]);   	// Send SINEWAVE Magnitude to DAC Out for Sound
    }
}
