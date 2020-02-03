/*
Title: Digital to Analog Conversion

Where:
Input Notes: C5, D5, E5, F5, G5, A5, B5, C6
Input Functionality: Additional Button for Demo Mode

Output: 4 bit Audio Resolution

Date: 26-August 2019
Author: Neil Cabrera
*/

#include "Sound.h"
#include "Piano.h"
#include "TM4C123GH6PM.h"

// Refer to the Values in the DAC Excel File for the Calculation of the Period
const unsigned long FREQ_TO_PERIOD[9] = {C_NOTE, D_NOTE, E_NOTE, F_NOTE, G_NOTE, A_NOTE, B_NOTE, C6_NOTE, O_NOTE}; 

// Hard Coded Demo Songs
// Mary had a Little Lamb
const unsigned long FREQ_TO_PERIOD_DEMO1[30]	=	{E_NOTE,D_NOTE,C_NOTE,D_NOTE,E_NOTE,E_NOTE,E_NOTE,
																								O_NOTE,
																								D_NOTE,D_NOTE,D_NOTE,E_NOTE,G_NOTE,G_NOTE,
																								O_NOTE,
																								E_NOTE,D_NOTE,C_NOTE,D_NOTE,E_NOTE,E_NOTE,E_NOTE,
																								O_NOTE,
																								C_NOTE,D_NOTE,D_NOTE,E_NOTE,D_NOTE,C_NOTE,
																								O_NOTE};

// Wheels on the Bus
const unsigned long FREQ_TO_PERIOD_DEMO2[29]	=	{C_NOTE,F_NOTE,F_NOTE,F_NOTE,A_NOTE,C_NOTE, A_NOTE, F_NOTE,
																								O_NOTE,
																								G_NOTE,E_NOTE,C_NOTE,C_NOTE,A_NOTE,F_NOTE,
																								O_NOTE,
																								C_NOTE,F_NOTE,F_NOTE,F_NOTE,A_NOTE,C_NOTE, A_NOTE, F_NOTE,
																								O_NOTE,
																								G_NOTE,C_NOTE,F_NOTE,
																								O_NOTE};

// Happy Birthday
const unsigned long FREQ_TO_PERIOD_DEMO3[30]	=	{G_NOTE,G_NOTE,A_NOTE,G_NOTE,C_NOTE,B_NOTE,
																								O_NOTE,
																								G_NOTE,G_NOTE,A_NOTE,G_NOTE,D_NOTE,C_NOTE,
																								O_NOTE,
																								G_NOTE,G_NOTE,A_NOTE,G_NOTE,G_NOTE,G_NOTE,A_NOTE,G_NOTE,
																								O_NOTE,
																								F_NOTE,F_NOTE,E_NOTE,C_NOTE,D_NOTE,C_NOTE,
																								O_NOTE};

// Row Row Row your Boat
const unsigned long FREQ_TO_PERIOD_DEMO4[30]	=	{C_NOTE,C_NOTE,C_NOTE,D_NOTE,E_NOTE,E_NOTE,D_NOTE,E_NOTE,F_NOTE,G_NOTE,
																								O_NOTE,
																								C_NOTE,C_NOTE,C_NOTE,G_NOTE,G_NOTE,G_NOTE,E_NOTE,E_NOTE,E_NOTE,C_NOTE,C_NOTE,C_NOTE,
																								O_NOTE,
																								G_NOTE,F_NOTE,E_NOTE,D_NOTE,C_NOTE,
																								O_NOTE};

// Software Delay and Demo
void delay(unsigned long msec);
void PlayDemo(void);
																								
// Current Demo Number
volatile unsigned long demonumber;

int main(void)
{
    Sound_Init();   // Initialize SysTick and DAC
    Piano_Init();   // Initialize Piano Keys (CDEG)
    __enable_irq(); // Enable interrupts

		// Initialise Demo Number Song
		demonumber = 0;
	
    while (1)
		{
				Piano_In();																// Read Keyboard Input

				if (freq_index == 8)
					Sound_Off();														// Turn Off Sound if Frequency Index is O_NOTE
				else if (freq_index == 9)
					PlayDemo();															// Play DEMO
				else
					Sound_Tone(FREQ_TO_PERIOD[freq_index]);	// Adjust the frequency similarly to C, D, E, F, G, A, B, C6
    }
}

// Plays Random Songs based on Current SysTick Value
void PlayDemo(void)
{
		unsigned char notesCount;
		unsigned long delay;
		
		if((demonumber%4)==0)
		{
			/********** Mary had a Little Lamb ***********/
			for(notesCount=0; notesCount<30; notesCount++)
			{
				// Insert Space between each note
				for(delay=0; delay<800000; delay++)
					Sound_Tone(O_NOTE);
				
				for(delay=0; delay<800000; delay++)
					Sound_Tone(FREQ_TO_PERIOD_DEMO1[notesCount]);
			}
			
			// Insert Silence After Demo
			for(delay=0; delay<1600000; delay++)
				Sound_Tone(O_NOTE);
		}

		if((demonumber%4)==1)
		{
			/********** Wheels on the Bus ***********/
			for(notesCount=0; notesCount<29; notesCount++)
			{
				// Insert Space between each note
				for(delay=0; delay<800000; delay++)
					Sound_Tone(O_NOTE);
				
				for(delay=0; delay<800000; delay++)
					Sound_Tone(FREQ_TO_PERIOD_DEMO2[notesCount]);
			}
			
			// Insert Silence After Demo
			for(delay=0; delay<1600000; delay++)
				Sound_Tone(O_NOTE);
		}
		
		if((demonumber%4)==2)
		{
			/********** Happy Birthday ***********/
			for(notesCount=0; notesCount<30; notesCount++)
			{
				// Insert Space between each note
				for(delay=0; delay<800000; delay++)
					Sound_Tone(O_NOTE);
				
				for(delay=0; delay<800000; delay++)
					Sound_Tone(FREQ_TO_PERIOD_DEMO3[notesCount]);
			}
			
			// Insert Silence After Demo
			for(delay=0; delay<1600000; delay++)
				Sound_Tone(O_NOTE);
		}
		
		if((demonumber%4)==3)
		{
			/********** Row Row Row Your Boat ***********/
			for(notesCount=0; notesCount<30; notesCount++)
			{
				// Insert Space between each note
				for(delay=0; delay<800000; delay++)
					Sound_Tone(O_NOTE);
				
				for(delay=0; delay<800000; delay++)
					Sound_Tone(FREQ_TO_PERIOD_DEMO4[notesCount]);
			}
			
			// Insert Silence After Demo
			for(delay=0; delay<1600000; delay++)
				Sound_Tone(O_NOTE);
		}
		
		demonumber++;
		
		// Reset Current Demo Number
		if(demonumber==4)
			demonumber = 0;

}
