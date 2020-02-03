/*****************************************************************************
 @Project	: 
 @File 		:
 @Details :                  
 @Author	: 
 @Hardware: This is hardware depend. Different LCD need to update this file.
						This driver purely use for 1.8 TFT LCD with ST7735R driver
  
******************************************************************************/
#include "../../BSP/Common.h"
#include "../../BSP/Hal.h"
#include "../../BSP/spim.h"
#include "LCD_ST7735R.h"
#include "gui.h"


/*****************************************************************************
 Define
******************************************************************************/
#define LCD_PHY_SIZE_X		128		/* Different LCD has different size in pixel */
#define LCD_PHY_SIZE_Y		160

/*****************************************************************************
 Local Variables
******************************************************************************/
static PSPIM_HANDLE	g_pSpimHandle;
static volatile int	g_bSpiDone = 0;
static int					g_nScreenX = LCD_PHY_SIZE_X;
static int					g_nScreenY = LCD_PHY_SIZE_Y;
static LCD_CB_DONE	*g_pLcdCbDone = 0;
static uint8_t			g_Cmd;
static uint8_t			g_Data;
static char data[64];

/*****************************************************************************
 Callback functions
******************************************************************************/
static void lcd_cbSpiDone( void );


/*****************************************************************************
 Local functions
******************************************************************************/
static void lcd_WriteCmd( uint8_t Cmd );
static void lcd_WriteData( uint8_t Data );
static void lcd_Delayms( uint32_t ms );
static void lcd_WriteMultipleByte( void const *pData, int nSize );;


/*****************************************************************************
 Implementation
******************************************************************************/
void LcdInit(PSPIM_HANDLE pSpimHAndle, LCD_ORIENTATION Orientation)
{
	ASSERT( 0 != pSpimHAndle );

	/* Keep SPI handle for later use */
	g_pSpimHandle = pSpimHAndle;
	
	/* Add a callback from SPI to notify SPI done */
	SpimAddCallbackTransferDone( pSpimHAndle, lcd_cbSpiDone );
	
	/* All the LCD intialization code normally come from LCD maker. 
	 Same ship might have different internal connection to LCD glass */

	/*******************
	 Hardware  Reset
	********************/
	LCD_CS_HIGH();
	LCD_RESET_HIGH();
	
	lcd_Delayms( 5U );
	
	LCD_RESET_LOW();
	
	lcd_Delayms( 5U );
	
	LCD_RESET_HIGH();
	
	lcd_Delayms( 5U );
	
  LCD_CS_HIGH();

	/*******************
	 Software Reset
	********************/
	lcd_WriteCmd(0x01);   /* Sofeware setting */
  lcd_Delayms(10);
  lcd_WriteCmd(0x01);   /* Sofeware setting */
	lcd_Delayms(10);
	lcd_WriteCmd(0x11);   /* sleep out */
	lcd_Delayms(120);
	
  lcd_WriteCmd(0x29);   /* display  on setting  */
	lcd_Delayms(120);
	lcd_WriteCmd(0x3A); 
	lcd_WriteData(0x05);  /* 16 bit  RGB color  format  select */
	lcd_Delayms(10);

	lcd_WriteCmd(0xB1);   /* Frame rate setting   95hz */
	
	data[0] = 0x00;
	data[1] = 0x06;
	data[2] = 0x03;
	lcd_WriteMultipleByte( data, 3 );

	lcd_Delayms(10);

	/*******************
	 LCD geometry setting
	********************/
	lcd_WriteCmd(0x36);  /* MV,MX,MY */
	
	if(LCD_POTRAIT == Orientation) /* Select potrait or landscape */
	{
		g_nScreenX = LCD_PHY_SIZE_X;
		g_nScreenY = LCD_PHY_SIZE_Y;		
		lcd_WriteData(0x10); 
	}
	else
	{
		g_nScreenX = LCD_PHY_SIZE_Y;
		g_nScreenY = LCD_PHY_SIZE_X;	
		lcd_WriteData(0xa0); 
	}

	lcd_WriteCmd(0xB4);  /* line inverion */
	lcd_WriteData(0x00); 

	/* POWER ON SETTING */
	lcd_WriteCmd(0xC0);  /* VCI1=2.65V */
	data[0] = 0x02;
	data[1] = 0x70;
	lcd_WriteMultipleByte( data, 2 );
	lcd_Delayms(10);
	
	lcd_WriteCmd(0xC1);   
	lcd_WriteData(0x05);  /* VGH,VGL */
	
	lcd_WriteCmd(0xC2);  

	data[0] = 0x0a;
	data[1] = 0x00;   	/* DC/DC SET */
	lcd_WriteMultipleByte( data, 2 );
	
	lcd_WriteCmd(0xC5); /* VCOMH=3.925V;VCOML=0.875V */
	
	data[0] = 0x3c;
	data[1] = 0x38;
	lcd_WriteMultipleByte( data, 2 );
	lcd_Delayms(10);

	/* GAMMA SETTING */
	lcd_WriteCmd(0xE0);	/* Positive */
	
	data[0] = 0x09;
	data[1] = 0x16;
	data[2] = 0x09;
	data[3] = 0x20;
	data[4] = 0x21;
	data[5] = 0x1B;
	data[6] = 0x13;
	data[7] = 0x19;
	data[8] = 0x17;
	data[9] = 0x15;
	data[10] = 0x1E;
	data[11] = 0x2B;
	data[12] = 0x04;
	data[13] = 0x05;
	data[14] = 0x02;
	data[15] = 0x0E;
	lcd_WriteMultipleByte( data, 16 );

	lcd_WriteCmd(0xE1); /* Negative */
	data[0] = 0x0B;
	data[1] = 0x14;
	data[2] = 0x08;
	data[3] = 0x1E;
	data[4] = 0x22;
	data[5] = 0x1D;
	data[6] = 0x18;
	data[7] = 0x1E;
	data[8] = 0x1B;
	data[9] = 0x1A;
	data[10] = 0x24;
	data[11] = 0x2B;
	data[12] = 0x06;
	data[13] = 0x06;
	data[14] = 0x02;
	data[15] = 0x0F;
	lcd_WriteMultipleByte( data, 16 );
	lcd_Delayms(10);

	/* window setting */
	lcd_WriteCmd(0x2A);
	
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = g_nScreenX - 1;
	lcd_WriteMultipleByte( data, 4 );

	lcd_WriteCmd(0x2B);
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = g_nScreenY - 1;
	lcd_WriteMultipleByte( data, 4 );

	lcd_WriteCmd(0x13);
	lcd_Delayms(10);
	lcd_WriteCmd(0x2C);
	lcd_Delayms(20);
	lcd_WriteCmd(0x29);  /* display on setting */ 
	lcd_Delayms(120);
	lcd_WriteCmd(0x2C);
}


void LCD_GetSize( int *pScreenX, int *pScreenY )
{
	*pScreenX = g_nScreenX;
	*pScreenY = g_nScreenY;	
}


void LCD_AddCallback( LCD_CB_DONE *pDone )
{
	g_pLcdCbDone = pDone;
}


void LCD_Reset( void )
{
	char data[4];
	
	lcd_WriteCmd(0x2A);
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = g_nScreenX - 1;
	lcd_WriteMultipleByte( data, 4 );

	lcd_WriteCmd(0x2B);
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = g_nScreenY - 1;
	lcd_WriteMultipleByte( data, 4 );

  lcd_WriteCmd(0x2C);
}

void LCD_WriteData8( uint8_t Data )
{
	g_Data = Data;
	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_HIGH();
	LCD_CS_LOW();
	
	SpimTransfer( g_pSpimHandle, &g_Data, 0, 1U );
	
	while( 0 == g_bSpiDone );
	g_bSpiDone = 0;

	LCD_CS_HIGH();  
}


void LCD_WriteDataPixel( void const *pData, int nSize )
{
	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_HIGH();
	LCD_CS_LOW();
	SpimTransfer( g_pSpimHandle, pData, 0, nSize );
	
	if( 0 == g_pLcdCbDone )
	{
		while( 0 == g_bSpiDone );
		g_bSpiDone = 0;
		LCD_CS_HIGH(); 
	}
}


/*****************************************************************************
 Callback functions
******************************************************************************/
static void lcd_cbSpiDone( void )
{
	if( 0 == g_pLcdCbDone )
	{
		g_bSpiDone = 1;
	}
	else
	{
		g_pLcdCbDone();
        LCD_CS_HIGH();
	}
}


/*****************************************************************************
 Local functions
******************************************************************************/
static void lcd_WriteCmd( uint8_t Cmd )
{
	g_Cmd = Cmd;

	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_LOW();
	LCD_CS_LOW();

	SpimTransfer( g_pSpimHandle, &g_Cmd, 0, 1U );
	
	while( 0 == g_bSpiDone );
	g_bSpiDone = 0;

	LCD_CS_HIGH();  
}


static void lcd_WriteData( uint8_t Data )
{
	g_Data = Data; 
	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_HIGH();
	LCD_CS_LOW();

	SpimTransfer( g_pSpimHandle, &g_Data, 0, 1U );
	while( 0 == g_bSpiDone );
	g_bSpiDone = 0;

	LCD_CS_HIGH();  
}


static void lcd_WriteMultipleByte( void const *pData, int nSize )
{
	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_HIGH();
	LCD_CS_LOW();
	SpimTransfer( g_pSpimHandle, pData, 0, nSize );
	while( 0 == g_bSpiDone );
	g_bSpiDone = 0;
	LCD_CS_HIGH(); 
}


static void lcd_Delayms(uint32_t ms)
{
	/* This not an accurate delay. */
	volatile int cnt = (SystemCoreClock*ms)/10000;
	
	while( cnt-- )
	{
		__NOP();
	}
}

