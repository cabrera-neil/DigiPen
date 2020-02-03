/*
Title: Analog to Digital Conversion

Where:
	Please Run in Debug Mode to See the Captured Values
	in Raw Distance and Distance in String Format

Date: 26-August 2019
Author: Neil Cabrera
*/

#include "PLL.h"
#include "ADC.h"
#include "TM4C123GH6PM.h"

// SysTick Parameters
#define NVIC_ST_CTRL_R 			(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R 		(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R 	(*((volatile unsigned long *)0xE000E018))
#define NVIC_SYS_PRI3_R 		(*((volatile unsigned long *)0xE000ED20))

//Global Variables
volatile unsigned long Size = 6;
volatile unsigned long Distance;
volatile unsigned char DistanceString[10];
volatile unsigned long ADCData;
volatile unsigned long Flag;

// Function Prototypes
void SysTick_Init(unsigned long delay);
volatile unsigned long Convert(unsigned long value);
void ConvertToString(unsigned long value);

int main(void)
{
	ADC_Init();										// Initialise ADC
	SysTick_Init(2000000);				// Initialise SysTick and PLL
	__enable_irq();								// Enable Interrupts
	
	while(1)
	{
		Flag = 0;										// Clear the Flag and Wait for a New Input
		while(Flag!=1);							// Wait until Flag is 1, means Data has been captured
		ConvertToString(Distance);	// Converts the Captured Distance to String 
	}
}

// ********************SysTick Init********************
// Call the PLL and SysTick Initalisation
// Input: Time Delay
// Output: none
void SysTick_Init(unsigned long delay)
{   
	// PLL Initialisation - 80 Mhz
	PLL_Init80();

	// SysTick Initialization
	NVIC_ST_CTRL_R 		= 0;          // Disable SysTick during setup
	NVIC_ST_RELOAD_R 	= delay;			// Set the Maximum Reload Value to 16777215
	NVIC_ST_CURRENT_R = 0;         	// Set Current Count to 0
	
	// Set Priority 1
	NVIC_SYS_PRI3_R 	= (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
	NVIC_ST_CTRL_R 		= 0x0007;     // Enable the Clock Source, Interrupt and Systick
}

// ********************SysTick_Handler********************
// Convert Implement SysTick Handler, capture value during interrupt
// Input: None
// Output: None
void SysTick_Handler(void) 
{
	ADCData	= ADC_In();					// Read New Input from ADC
	Distance= Convert(ADCData);	// Convert to distance
	Flag 		= 1;                // Set the flag (New Data is available)
}

// ********************Convert********************
// Convert Input Value into Centimeters
// Input: Value from ADC
// Output: Distance in CM
volatile unsigned long Convert(unsigned long value)
{
	return (long) value/4095.0 * Size * 1000;
}

// ********************ConvertToString********************
// Convert Input Value into Centimeters and Store in Array
// Input: Value from ADC
// Output: None
void ConvertToString(unsigned long value)
{
	// Clear the Distance String
	int count;
	for(count=0; count<10; count++)
		DistanceString[count]='\0';
	
	// If Value is 0, No Need to Process
	if(value==0)
	{
		DistanceString[0]='0';

	}
	else
	{
		// Value is Greater than 0
		
		int StringLength;
		int DistanceDiv10;
		char DistanceStringTemp[10];
		
		// Clear the Temp String
		for(count=0; count<10; count++)
			DistanceStringTemp[count]='\0';
		
		// Extract the Digits one by one
		// Value is Stored in Reverse
		StringLength = 0;
		DistanceDiv10 = Distance;
		for(count=0; DistanceDiv10>0; count++)
		{
			DistanceStringTemp[count] = '0' + DistanceDiv10%10;
			DistanceDiv10 /= 10;
			
			StringLength++;
		}
		
		// Reverse the Value and Store in the DistanceString Variable
		for(count=0;count<StringLength;count++)
			DistanceString[count] = DistanceStringTemp[StringLength-1-count];
		
		
	}
}
