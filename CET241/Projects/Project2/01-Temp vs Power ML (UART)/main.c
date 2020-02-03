/*
Title: Interfacing with MCU using UART and Putty

Where:
	MCU is ML Trained with Linear Regression using Gradient Descent
	MCU is able to recognise errant power output based on input temperature
	If predicted power deviates by more than 2 Watts, set the alert with Red LED
	Otherwise, flash Green (Normal) or Blue (Slight Deviation)

Date: 03-September 2019
Author: Neil Cabrera
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "TM4C123GH6PM.h"
#include "PLL.h"
#include "UART.h"

//*****************************************************************************
// The following are defines for the bit fields in the UART_O_FR register.
//*****************************************************************************
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty

//#define DEMO															// Initiate DEMO Mode
#define MAX_INPUT								0xC8				// Max Length of Input String as Defined in the Heap

//*****************************************************************************
// Local Functions
//*****************************************************************************
char readChar(void);
void readString(char* string, int maxLength, char delimeter);
void printChar(char c);
void printString(char* string);

void PortF_Init(void);
void SwitchLED(double value);
void SwitchLEDOff(void);

int main(void)
{
	PLL_Init80();	// Set System Clock to 80Mhz
	UART_Init();	// Initialise UART
	PortF_Init();	// Initialise PortF
	
	while(1)
	{
		// Print Startup Message
		printString("Initialisation Success! Running MCU at 80Mhz.\n\r");
		
		#ifdef DEMO
		// Allocate Maximum Input String (based on the Heap)
		char* colour = (char*)calloc(MAX_INPUT, sizeof(char));
		
		// Check if Allocation Failed
		if(colour!=NULL)
		{						
			printString("Enter 'red', 'green', or 'blue' and press enter (anything else will turn the LED off):\n\r");
			readString(colour, MAX_INPUT, 13);
			
			if(strcmp(colour, "red")==0)
			{
				GPIOF->DATA  |= 0x02;
				GPIOF->DATA  &= ~0x0C;
			}
			else if(strcmp(colour, "blue")==0)
			{
				GPIOF->DATA  |= 0x04;
				GPIOF->DATA  &= ~0x0A;
			}
			else if(strcmp(colour, "green")==0)
			{
				GPIOF->DATA  |= 0x08;
				GPIOF->DATA  &= ~0x06;
			}
			else
			{
				GPIOF->DATA  &= ~0x0E;
				printString("\n\rInvalid Input - Turning the LED Off!");
			}
			
			printString("\n\r");	// Print a New Line
			free(colour);					// Free the Allocated String to Prevent Filling up the Heap
			
		}
		else
		{
			printString("Memory Allocation Failed! Try Restarting the MCU...\n\r");	// Print a New Line
			return 0x01;
		}
		#endif
		
		#ifndef DEMO
		printString("Loading Training Data (20 Data Points)...\n\r");
		char buffer[20];
		
		// Training and Test Data for Linear Regression using Gradient Descent
		// x is for Temperature, y for Power
		double x[20] = {27.00,28.00,28.50,29.50,30.00,31.00,31.50,32.50,33.00,34.00,34.50,35.50,36.00,37.00,37.50,38.50,39.00,40.00,40.50,41.50};
		double y[20] = {15.75,15.789375,14.32125,14.428125,16.025625,16.2225,14.784375,15.03375,16.77375,17.128125,15.675,16.066875,17.994375,18.50625,16.993125,17.5275,19.6875,20.356875,18.73875,19.415625};
		double xTest[11] = {27.50,29.00,30.50,32.00,54.50,35.00,36.50,38.00,39.50,41.00, 59.00};
		double yTest[11] = {14.261875, 15.88125, 14.5825, 16.471875, 32.5375, 17.535, 16.50625, 19.070625, 18.109375, 21.07875, 43.05};
			
		// Variables for Gradient Descent
		double b0 = 0;
		double b1 = 0;
		double alpha = 0.001;
		 
		printString("Training Model, Setting Alpha to 0.001 and Epochs to 4...\n\r");
		for (int i = 0; i < 80; i ++)
		{
			int idx 		= i % 20;
			double p 		= b0 + b1 * x[idx];
			double err	= p - y[idx];
			
			// Calculate B0 and B1
			b0 = b0 - alpha * err;
			b1 = b1 - alpha * err * x[idx];
			
			// Print Calculated Values of B0, B1 and Error
			sprintf(buffer, "B0=%0.4f\t", b0);
			printString(buffer);
		
			sprintf(buffer, "B1=%0.4f\t", b1);
			printString(buffer);
			
			sprintf(buffer, "error=%0.4f\t\n\r", err);
			printString(buffer);
		}
		printString("Done!\n\r");
		
		printString("Press Enter to proceed to Testing...\n\r");
		while(readChar()!=13){}
		
		printString("Loading Test Data (11 Data Points)...\n\r");
		for (int i = 0; i < 11; i ++)
		{
			double p 		= b0 + b1 * xTest[i];
			double err	= p - yTest[i];
			SwitchLED(err);
			
			// Print Temp, True Power, Predicted Power & Error
			sprintf(buffer, "Temp=%0.2f(C)\t", xTest[i]);
			printString(buffer);
			
			sprintf(buffer, "True Power=%0.4f(W)\t", yTest[i]);
			printString(buffer);
			
			sprintf(buffer, "Pred. Power=%0.4f(W)\t", p);
			printString(buffer);
			
			sprintf(buffer, "error=%0.4f\t", err);
			printString(buffer);
			
			printString("Press Enter to Continue...\n\r");
			while(readChar()!=13){}
		}
		printString("Done!\n\r");
		printString("Press Enter to Restart...\n\r");
		while(readChar()!=13){}
		
		// Testing Completed, Turn Off the LED
		SwitchLEDOff();
		#endif
	}
}

// ********************Read Char********************
// Read Input Character from Putty Terminal
// Input: none
// Output: char
char readChar(void)
{
	while((UART0->FR & UART_FR_RXFE) != 0){}
  return((unsigned char)(UART0->DR & 0xFF));
}

// ********************Read String********************
// Read Input from Putty Terminal and store once delimeter is encountered
// Input: pointer to store the string, allocated length for string, delimiter
// Output: none
void readString(char* string, int maxLength, char delimeter)
{
	int stringSize = 0;
	char c;
	
	while((c=readChar())!=delimeter && stringSize<=maxLength)
	{
		*(string + stringSize) = c;
		stringSize++;
	}
}

// ********************Print Char********************
// Print Input Character in Putty Terminal
// Input: single char
// Output: None
void printChar(char c)
{
	while ((UART0->FR & UART_FR_TXFF) != 0) {}
  UART0->DR = c;
}

// ********************Print String********************
// Print Input String in Putty Terminal
// Input: char* to string
// Output: None
void printString(char* string)
{
	int position=0;
	while(*(string+position)!='\0')
	{
		printChar(*(string+position));
		position++;
	}
}

// ********************PortF Init********************
// Initialise PF3-PF1 LEDs for Output
// Input: none
// Output: none
void PortF_Init(void)
{
	SYSCTL->RCGCGPIO |= 0x20;						// Use PortF
	while((SYSCTL->PRGPIO & 0x20)==0);	// Wait for GPIO Port F to be Ready, Stabilise
	
	GPIOF->AMSEL	&= ~0x0E;							// Clear Analog for PF3-PF1
	GPIOF->PCTL		&= ~0xFFF0;						// Clear PCTL for PF3-PF1
	GPIOF->DIR		|= 0x0E;							// Set PF3-PF1 as Output
	GPIOF->AFSEL	&= ~0x0E;							// Clear Alternative Function for PF3-PF1
	GPIOF->DEN		|= 0x0E;							// Enable Digital for PF3-PF1
}

// ********************SwitchLED********************
// Turn On LED based on Input value
// Used for ML
// Input: Value
// Output: none
void SwitchLED(double value)
{
		double roundValue = fabs(value);
	
		if(roundValue>=2.00)
		{
			// Error is Greater than 2.00
			// Turn LED to RED
			GPIOF->DATA  |= 0x02;
			GPIOF->DATA  &= ~0x0C;
		}
		else if(roundValue>=1.00 && roundValue<2.00)
		{
			// Error is Greater than 1.00 and less than 2.00
			// Turn LED to BLUE
			GPIOF->DATA  |= 0x04;
			GPIOF->DATA  &= ~0x0A;
		}
		else if(roundValue>=0.00 && roundValue<1.00)
		{
			// Error is Greater than 0.00 and less than 1.00
			// Turn LED to BLUE
			GPIOF->DATA  |= 0x08;
			GPIOF->DATA  &= ~0x06;
		}
		else
		{
			// Invalid Input
			// Turn LED OFF
			SwitchLEDOff();
			printString("\n\rInvalid Input - Turning the LED Off!");
		}
}

// ********************SwitchLED Off********************
// Turn Off LED
// Input: Value
// Output: none
void SwitchLEDOff(void)
{
	GPIOF->DATA  &= ~0x0E;
}
