/*
Title: Displaying the Temperature Sensor Readings in the LCD
			 with Simple Animation

Where:
	MCU will receive the measured temperature from the sensor
	and display the output to LCD

Date: 03-September 2019
Author: Neil Cabrera
*/

#include <stdio.h>
#include "TM4C123GH6PM.h"
#include "PLL.h"
#include "I2C.h"

#include "App/LCD/LCD_ST7735R.h"
#include "App/LCD/gui.h"
#include "BSP/Common.h"
#include "BSP/Hal.h"
#include "BSP/BSP.h"
#include "BSP/spim.h"

// For debug purposes, this program may peek at the I2C0 Master
// Control/Status Register to try to provide a more meaningful
// diagnostic message in the event of an error.  The rest of the
// interface with the I2C hardware occurs through the functions
// in I2C0.c.
#define I2C0_MASTER_MCS_R       (*((volatile unsigned long *)0x40020004))

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

/*****************************************************************************
 Define
******************************************************************************/
#define LCD_BUF_SIZE			4096*2
#define LCD_UPDATE_MS			10

/*****************************************************************************
 Global Variables
******************************************************************************/
extern const unsigned short temp[];
void GUI_AppDraw( BOOL bFrameStart );

/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int 	g_nBlink		= 1000;
static volatile int 	g_bSpiDone 	= FALSE;

static SPIM_HANDLE		g_SpimHandle;
static GUI_DATA				g_aBuf[LCD_BUF_SIZE];
static GUI_MEMDEV			g_MemDev;

static volatile BOOL 	g_bLCDUpdate 	= FALSE;
static volatile int 	g_nLCD 				= LCD_UPDATE_MS;
volatile BOOL 				g_bLcdFree  	= TRUE;
volatile BOOL					g_I2CStatus		= FALSE;

/*****************************************************************************
 Callback Functions
******************************************************************************/
static void main_cbGuiFrameEnd(void);
static void main_cbLcdTransferDone(void);

/*****************************************************************************
 Local Functions
******************************************************************************/
static void SsiInit( void );
static void main_LcdInit( void );

uint16_t I2C_Recv2(int8_t slave);
uint32_t I2C_Send1(int8_t slave, uint8_t data1);
void parseTemp(unsigned short rawData, int * tempInt, int * tempFra);

int main(void)
{
	PLL_Init();				/* PLL Initialization, 80Mhz */
	SysTick_Config(SystemCoreClock/1000);
	
	PortInit();				/* Port Initialization */
	SsiInit(); 				/* SPI Master Intialization */
	main_LcdInit(); 	/* LCD Intialization */
  I2C_Init();				/* I2C Initialization */
                                          
	// Write command to Slave Address 0x48 (ADDR to ground)
	// Use command 1 to set pointer to config
  I2C_Send1(0x48, 1);                     
                                          
	// Read from 0x48 to get data
	// Expected 0x60A0 as power-on default, page 17 of the TMP102 datasheet
  if(I2C_Recv2(0x48) == 0x60A0)	          
  {
		g_I2CStatus = TRUE;
		LED_GREEN_ON();	// Passed
	}
  else if(I2C0_MASTER_MCS_R&0x02)
		LED_RED_ON();		// No Acknowledgement
  else
		LED_RED_ON();		// Failed
                
	// Write commands to Slave Address 0x48 (ADDR to ground)
	// Use command 0 to set pointer to temperature
  I2C_Send1(0x48, 0);                     
  while(1)
	{
		if( FALSE != g_bLCDUpdate )
		{
			if( 0 != g_bLcdFree )
			{
				g_bLCDUpdate	= FALSE;
				g_bLcdFree		= FALSE;
				
			  /* Draw every block.Consume less time  */
				GUI_Draw_Exe(); 
			}
		}
  }
}

/*****************************************************************************
 Callback functions
******************************************************************************/
void GUI_AppDraw( BOOL bFrameStart )
{
	unsigned short rawData = 0;	// 16-bit data straight from thermometer
  int tempInt = 0;            // Integer value of Temperature (-128 to 127)
  int tempFra = 0;            // Fractional value of Temperature (0 to 9375)
	char buff[12];							// Storage for String Value of Temperature
	
	/* Set background to blue.Refer to gui.h for color code */
	GUI_Clear( ClrWhiteSmoke ); 
	
	rawData = I2C_Recv2(0x48);            	// Read from 0x48 to get temperature, temperature data stored in 12 or 13 MSBs
	parseTemp(rawData, &tempInt, &tempFra);	// Split Raw Data into Integer and Fractional Part
	
	// Print I2C Status
	GUI_SetFont(&g_sFontCalibri10);
	GUI_PrintString("Temp Sensor Status:", ClrBlueViolet, 60, 10);
	if(g_I2CStatus==TRUE)
		GUI_PrintString("Connected!", ClrDarkBlue, 60, 20);
	else
		GUI_PrintString("Disconnected!", ClrRed, 60, 20);
	
	// Print Label for Temp Display
	GUI_SetFont(&g_sFontCalibri10);
	GUI_PrintString("Current", ClrBlueViolet, 60, 70);
	GUI_PrintString("Temp. Reading (C):", ClrBlueViolet, 60, 80);
	
	// Print the Integer and Fraction Part of the Temperature
	sprintf(buff, "%d.%d", tempInt, tempFra);
	GUI_SetFont(&g_sFontCalibri24);
	GUI_PrintString(buff, ClrDarkBlue, 70, 100);	
	
	/* Draw bitmap */
	GUI_DrawBitmap(temp, 0, 0);
	
	// Update the Thermometer Band
	// Scale maybe a bit too high too see
	// Tested up to 55 Celsius
	// Need aircon for Lower Temp or something hot for Higher Temp
	if(tempInt>20)
	{
		GUI_SetColor(ClrGreen);
		GUI_DrawFilledRect(19,71,33,85);
	}
	
	if(tempInt>25)
	{
		GUI_SetColor(ClrYellow);
		GUI_DrawFilledRect(19,57,33,70);
	}
	
	if(tempInt>27)
	{
		GUI_SetColor(ClrOrange);
		GUI_DrawFilledRect(19,43,33,56);
	}
	
	if(tempInt>29)
	{
		GUI_SetColor(ClrOrangeRed);
		GUI_DrawFilledRect(19,29,33,42);
	}
	
	if(tempInt>31)
	{
		GUI_SetColor(ClrRed);
		GUI_DrawFilledRect(19,15,33,28);
	}
}


static void main_cbLcdTransferDone( void )
{
	g_bLcdFree = TRUE;
}


static void main_cbGuiFrameEnd( void )
{
	g_bLcdFree = TRUE;
}

/*****************************************************************************
 Initialization functions
******************************************************************************/
static void SsiInit( void )
{
	NVIC_SetPriority(SSI0_IRQn, 0);
	SpimInit(&g_SpimHandle,0U,20000000U,SPI_CLK_INACT_LOW,SPI_CLK_RISING_EDGE,SPI_DATA_SIZE_8);
}

static void main_LcdInit( void )
{
	int screenx;
	int screeny;
	
	/* g_SpimHandle shall be initialized before use */
	/* Choosing a landscape orientation */
	LcdInit(&g_SpimHandle, LCD_LANDSCAPE);
	
	/* Get physical LCD size in pixels */
	LCD_GetSize(&screenx, &screeny);
	
	/* Initialize GUI */
	GUI_Init(&g_MemDev,screenx,screeny,g_aBuf,sizeof(g_aBuf));
	
	/* Switch to transfer word for faster performance */
	SpimSetDataSize(&g_SpimHandle, SPI_DATA_SIZE_16);
	GUI_16BitPerPixel(TRUE);
			
	LCD_AddCallback(main_cbLcdTransferDone);
	GUI_AddCbFrameEnd(main_cbGuiFrameEnd);
	
	/* Backlight ON */
	LCD_BL_ON();
}

void SysTick_Handler( void )
{
	if(0!=g_nLCD)
	{
		g_nLCD--;
		if(0==g_nLCD)
		{
			g_nLCD = LCD_UPDATE_MS;
			g_bLCDUpdate = TRUE;
		}
	}
}

/*****************************************************************************
 Local functions
******************************************************************************/

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
  if(rawData&0x0001)	// 13-bit mode
	{  
    *tempInt = rawData>>7;
    if(rawData&0x8000)
		{
			// negative value
      *tempFra = (0x10 - ((rawData>>3)&0xF))*10000/16;
      *tempInt = (*tempInt) - 0x5E8;
    }
    else
      *tempFra = ((rawData>>3)&0xF)*10000/16;
  }
  else								// 12-bit mode
	{
    *tempInt = rawData>>8;
    if(rawData&0x8000)
		{
			// negative value
      *tempFra = (16 - ((rawData>>4)&0xF))*10000/16;
      *tempInt = (*tempInt) - 0x4E8;
    }
    else
      *tempFra = ((rawData>>4)&0xF)*10000/16;
  }
}
