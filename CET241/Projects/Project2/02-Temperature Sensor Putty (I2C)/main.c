/*
Title: Integrating a Temperature Sensor with the MCU using I2C

Where:
	MCU will receive the measured temperature from the sensor
	and display the output to Putty Terminal

Date: 03-September 2019
Author: Neil Cabrera
*/

#include <stdio.h>
#include "TM4C123GH6PM.h"
#include "PLL.h"
#include "UART.h"
#include "I2C.h"

// For debug purposes, this program may peek at the I2C0 Master
// Control/Status Register to try to provide a more meaningful
// diagnostic message in the event of an error.  The rest of the
// interface with the I2C hardware occurs through the functions
// in I2C0.c.
#define I2C0_MASTER_MCS_R       (*((volatile unsigned long *)0x40020004))

//*****************************************************************************
// The following are defines for the bit fields in the UART_O_FR register.
//*****************************************************************************
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty

//*****************************************************************************
// The following are defines for the bit fields in the I2C0.
//*****************************************************************************
#define I2C_MCS_ACK             0x00000008  // Data Acknowledge Enable
#define I2C_MCS_DATACK          0x00000008  // Acknowledge Data
#define I2C_MCS_ADRACK          0x00000004  // Acknowledge Address
#define I2C_MCS_STOP            0x00000004  // Generate STOP
#define I2C_MCS_START           0x00000002  // Generate START
#define I2C_MCS_ERROR           0x00000002  // Error
#define I2C_MCS_RUN             0x00000001  // I2C Master Enable
#define I2C_MCS_BUSY            0x00000001  // I2C Busy
#define I2C_MCR_MFE             0x00000010  // I2C Master Function Enable
#define MAXRETRIES 											 5 	// number of receive attempts before giving up

//*****************************************************************************
// Local Functions
//*****************************************************************************
uint16_t I2C_Recv2(int8_t slave);

void printChar(char c);
void printString(char* string);

uint16_t I2C_Recv2(int8_t slave);
uint32_t I2C_Send1(int8_t slave, uint8_t data1);

void parseTemp(unsigned short rawData, int * tempInt, int * tempFra);
void Delay(unsigned long count);

int main(void){
  unsigned short rawData = 0;	// 16-bit data straight from thermometer
  int tempInt = 0;            // Integer value of Temperature (-128 to 127)
  int tempFra = 0;            // Fractional value of Temperature (0 to 9375)
	char buff[12];							// Storage for String Value of Temperature
  
	PLL_Init();
  UART_Init();
  I2C_Init();
                                          // write commands to 0x48 (ADDR to ground)
  I2C_Send1(0x48, 1);                     // use command 1 to set pointer to config
                                          // read from 0x48 to get data
  if(I2C_Recv2(0x48) == 0x60A0)	          // expected 0x60A0 as power-on default, page 17 of the TMP102 datasheet
    printString("Test Passed\r\n");
  else if(I2C0_MASTER_MCS_R&0x02)
		printString("No Acknowledge\r\n");
  else
		printString("Test Failed\r\n");
                                          // write commands to 0x48 (ADDR to ground)
  I2C_Send1(0x48, 0);                     // use command 0 to set pointer to temperature
  while(1)
	{
    rawData = I2C_Recv2(0x48);            											// Read from 0x48 to get temperature, temperature data stored in 12 or 13 MSBs
    parseTemp(rawData, &tempInt, &tempFra);											// Split Raw Data into Integer and Fractional Part
		sprintf(buff, "Current Temp: %d.%d\r\n", tempInt, tempFra);	// Combine both as String and Print on Putty
    printString(buff);
    
		// Wait 250ms to sample at ~4 Hz the next temperature
		Delay(4166667);
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

// ********************I2C Receive********************
// Receive 2 bytes from I2C Slave
// Input: Slave Address, for this Project is 0x49
// Output: 2 bytes of data from the sensor
uint16_t I2C_Recv2(int8_t slave){
  uint8_t data1,data2;
  int retryCounter = 1;
  do{
    while(I2C0->MCS&I2C_MCS_BUSY){};				// wait for I2C ready
    I2C0->MSA = (slave<<1)&0xFE;    				// MSA[7:1] is slave address
    I2C0->MSA |= 0x01;              				// MSA[0] is 1 for receive
    I2C0->MCS = (0
                         | I2C_MCS_ACK      // positive data ack
                         | I2C_MCS_START    // generate start/restart
                         | I2C_MCS_RUN);    // master enable
    while(I2C0->MCS&I2C_MCS_BUSY){};				// wait for transmission done
    data1 = (I2C0->MDR&0xFF);       				// MSB data sent first
    I2C0->MCS = (0
                         | I2C_MCS_STOP     // generate stop
                         | I2C_MCS_RUN);    // master enable
    while(I2C0->MCS&I2C_MCS_BUSY){}					// wait for transmission done
    data2 = (I2C0->MDR&0xFF);       				// LSB data sent last
    retryCounter = retryCounter + 1;        // increment retry counter
  }                                         // repeat if error
  while(((I2C0->MCS&(I2C_MCS_ADRACK|I2C_MCS_ERROR)) != 0) && (retryCounter <= MAXRETRIES));
  return (data1<<8)+data2;                  // usually returns 0xFFFF on error
}

// ********************I2C Send********************
// Send 1 byte to I2C Slave
// Input: Slave Address, for this Project is 0x48
// Output: 0 if Successful, Non Zero if Error
uint32_t I2C_Send1(int8_t slave, uint8_t data1)
{
  while(I2C0->MCS&I2C_MCS_BUSY){};				// wait for I2C ready
  I2C0->MSA = (slave<<1)&0xFE;    				// MSA[7:1] is slave address
  I2C0->MSA &= ~0x01;             				// MSA[0] is 0 for send
  I2C0->MDR = data1&0xFF;         				// prepare first byte
  I2C0->MCS = (0
                       | I2C_MCS_STOP     // generate stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C0->MCS&I2C_MCS_BUSY){};				// wait for transmission done
                                          // return error bits
  return (I2C0->MCS&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR));
}

// ********************Parse Temp********************
// Split the Raw Data from I2C into Integer and Fraction
// Input: Raw Data, Integer Container, Fractional Container
// Output: None
// Refer to page 9 and 10 of tmp102 datasheet
void parseTemp(unsigned short rawData, int * tempInt, int * tempFra){
  if(rawData&0x0001){  // 13-bit mode
    *tempInt = rawData>>7;
    if(rawData&0x8000){// negative value
      *tempFra = (0x10 - ((rawData>>3)&0xF))*10000/16;
      *tempInt = (*tempInt) - 0x5E8;
      }
    else{
      *tempFra = ((rawData>>3)&0xF)*10000/16;
    }
  }
  else{
    *tempInt = rawData>>8;
    if(rawData&0x8000){// negative value
      *tempFra = (16 - ((rawData>>4)&0xF))*10000/16;
      *tempInt = (*tempInt) - 0x4E8;
    }
    else{
      *tempFra = ((rawData>>4)&0xF)*10000/16;
    }
  }
}

void Delay(unsigned long count)
{
	while(count--){}
}
