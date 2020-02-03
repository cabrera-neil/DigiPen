/*****************************************************************************
 @Project	: CE
 @File 		:
 @Details  	:                  
 @Author	: lcgan
 @Hardware	: This is hardware depend. Different LCD need to update this file.
			  This driver purely use for 1.8 TFT LCD with ST7735R driver
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "Dma.h"
#include "Spim.h"
#include "LCD_ST7735R.h"
#include "gui.h"


/*****************************************************************************
 Define
******************************************************************************/
#define LCD_PHY_SIZE_X		128		/* Different LCD has different size in pixel */
#define LCD_PHY_SIZE_Y		160

#define COLOR_SWAP( x )		(((((x)>>8)&0x00ff) | (((x)<<8)&0xff00))&0xffff)

/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/
extern SPIM_HANDLE			g_SpimLcdHandle;


extern DMA_HANDLE			g_Dma1Spi2TxHandle;
extern DMA_HANDLE			g_Dma1Spi2RxHandle;

/*****************************************************************************
 Local Variables
******************************************************************************/
static PSPIM_HANDLE	g_pSpimHandle;
static volatile int	g_bSpiDone = 0;
static int			g_nScreenX = LCD_PHY_SIZE_X;
static int			g_nScreenY = LCD_PHY_SIZE_Y;
static LCD_CB_DONE	*g_pfLcdCbTransferDone = 0;
static char			g_aTxBuf[512];


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
void
LcdInit(
	void				*pSpimHAndle,
	LCD_ORIENTATION 	Orientation
	)
{
	ASSERT( 0 != pSpimHAndle );

	/* Keep SPI handle for later use */
	g_pSpimHandle = pSpimHAndle;
	
	/* Add a callback from SPI to notify SPI done */
	SpimAddCallbackTransferDone( pSpimHAndle, lcd_cbSpiDone );

    SpimSetDataSize( g_pSpimHandle, SPI_DATA_SIZE_8 );
	
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
	
	g_aTxBuf[0] = 0x00;
	g_aTxBuf[1] = 0x06;
	g_aTxBuf[2] = 0x03;
	lcd_WriteMultipleByte( g_aTxBuf, 3 );

	lcd_Delayms(10);

	/*******************
	 LCD geometry setting
	********************/
	lcd_WriteCmd(0x36);  /* MV,MX,MY */
	
	if( LCD_PORTRAIT == Orientation ) /* Select portrait or landscape */
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

	lcd_WriteCmd(0xB4);  /* line inversion */
	lcd_WriteData(0x00); 

	/* POWER ON SETTING */
	lcd_WriteCmd(0xC0);  /* VCI1=2.65V */
	g_aTxBuf[0] = 0x02;
	g_aTxBuf[1] = 0x70;
	lcd_WriteMultipleByte( g_aTxBuf, 2 );
	lcd_Delayms(10);
	
	lcd_WriteCmd(0xC1);   
	lcd_WriteData(0x05);  /* VGH,VGL */
	
	lcd_WriteCmd(0xC2);  

	g_aTxBuf[0] = 0x0a;
	g_aTxBuf[1] = 0x00;   	/* DC/DC SET */
	lcd_WriteMultipleByte( g_aTxBuf, 2 );
	
	lcd_WriteCmd(0xC5); /* VCOMH=3.925V;VCOML=0.875V */
	
	g_aTxBuf[0] = 0x3c;
	g_aTxBuf[1] = 0x38;
	lcd_WriteMultipleByte( g_aTxBuf, 2 );
	lcd_Delayms(10);

	/* GAMMA SETTING */

	lcd_WriteCmd(0xE0);	/* Positive */
	
	g_aTxBuf[0] = 0x09;
	g_aTxBuf[1] = 0x16;
	g_aTxBuf[2] = 0x09;
	g_aTxBuf[3] = 0x20;
	g_aTxBuf[4] = 0x21;
	g_aTxBuf[5] = 0x1B;
	g_aTxBuf[6] = 0x13;
	g_aTxBuf[7] = 0x19;
	g_aTxBuf[8] = 0x17;
	g_aTxBuf[9] = 0x15;
	g_aTxBuf[10] = 0x1E;
	g_aTxBuf[11] = 0x2B;
	g_aTxBuf[12] = 0x04;
	g_aTxBuf[13] = 0x05;
	g_aTxBuf[14] = 0x02;
	g_aTxBuf[15] = 0x0E;
	lcd_WriteMultipleByte( g_aTxBuf, 16 );


	lcd_WriteCmd(0xE1); /* Negative */
	g_aTxBuf[0] = 0x0B;
	g_aTxBuf[1] = 0x14;
	g_aTxBuf[2] = 0x08;
	g_aTxBuf[3] = 0x1E;
	g_aTxBuf[4] = 0x22;
	g_aTxBuf[5] = 0x1D;
	g_aTxBuf[6] = 0x18;
	g_aTxBuf[7] = 0x1E;
	g_aTxBuf[8] = 0x1B;
	g_aTxBuf[9] = 0x1A;
	g_aTxBuf[10] = 0x24;
	g_aTxBuf[11] = 0x2B;
	g_aTxBuf[12] = 0x06;
	g_aTxBuf[13] = 0x06;
	g_aTxBuf[14] = 0x02;
	g_aTxBuf[15] = 0x0F;
	lcd_WriteMultipleByte( g_aTxBuf, 16 );
	lcd_Delayms(10);

	/* window setting */
	lcd_WriteCmd(0x2A);
	
	g_aTxBuf[0] = 0x00;
	g_aTxBuf[1] = 0x00;
	g_aTxBuf[2] = 0x00;
	g_aTxBuf[3] = g_nScreenX - 1;
	lcd_WriteMultipleByte( g_aTxBuf, 4 );


	lcd_WriteCmd(0x2B);
	g_aTxBuf[0] = 0x00;
	g_aTxBuf[1] = 0x00;
	g_aTxBuf[2] = 0x00;
	g_aTxBuf[3] = g_nScreenY - 1;
	lcd_WriteMultipleByte( g_aTxBuf, 4 );

#if 0
	lcd_WriteCmd(0x26); /* default gamma setting */
	lcd_WriteCmd(0x30); /* partial area setting */
#endif

	lcd_WriteCmd(0x13);
	lcd_Delayms(10);

	lcd_WriteCmd(0x2C);

	lcd_Delayms(20);

	lcd_WriteCmd(0x29);  /* display on setting */ 

	lcd_Delayms(120);
	
	lcd_WriteCmd(0x2C);

	SpimSetDataSize( g_pSpimHandle, SPI_DATA_SIZE_16 );
}


void LCD_GetSize( int *pScreenX, int *pScreenY )
{
	*pScreenX = g_nScreenX;
	*pScreenY = g_nScreenY;	
}


void LCD_AddCallback( LCD_CB_DONE *pDone )
{
	g_pfLcdCbTransferDone = pDone;
}


void LCD_Reset( void )
{
	SpimSetDataSize( g_pSpimHandle, SPI_DATA_SIZE_8 );

	lcd_WriteCmd(0x2A);
	g_aTxBuf[0] = 0x00;
	g_aTxBuf[1] = 0x00;
	g_aTxBuf[2] = 0x00;
	g_aTxBuf[3] = g_nScreenX - 1;
	lcd_WriteMultipleByte( g_aTxBuf, 4 );

	lcd_WriteCmd(0x2B);
	g_aTxBuf[0] = 0x00;
	g_aTxBuf[1] = 0x00;
	g_aTxBuf[2] = 0x00;
	g_aTxBuf[3] = g_nScreenY - 1;
	lcd_WriteMultipleByte( g_aTxBuf, 4 );

    lcd_WriteCmd(0x2C);

    SpimSetDataSize( g_pSpimHandle, SPI_DATA_SIZE_16 );
}


void LCD_SetArea( int X0, int X1, int Y0, int Y1 )
{
	SpimSetDataSize( g_pSpimHandle, SPI_DATA_SIZE_8 );

	lcd_WriteCmd(0x2A);
	g_aTxBuf[0] = 0x00;
	g_aTxBuf[1] = X0;
	g_aTxBuf[2] = 0x00;
	g_aTxBuf[3] = X1;
	lcd_WriteMultipleByte( g_aTxBuf, 4 );

	lcd_WriteCmd(0x2B);
	g_aTxBuf[0] = 0x00;
	g_aTxBuf[1] = Y0;
	g_aTxBuf[2] = 0x00;
	g_aTxBuf[3] = Y1;
	lcd_WriteMultipleByte( g_aTxBuf, 4 );

    lcd_WriteCmd(0x2C);

    SpimSetDataSize( g_pSpimHandle, SPI_DATA_SIZE_16 );
}


void LCD_WriteData8( uint8_t Data )
{
	ASSERT( 0 != g_pSpimHandle );

	SpimSetDataSize( g_pSpimHandle, SPI_DATA_SIZE_8 );
	LCD_DC_HIGH();
	LCD_CS_LOW();
	
    g_aTxBuf[0] = Data;

	SpimTransfer( g_pSpimHandle, g_aTxBuf, 0, 1U );
	
	while( 0 == g_bSpiDone );
	g_bSpiDone = 0;

	LCD_CS_HIGH();  

    SpimSetDataSize( g_pSpimHandle, SPI_DATA_SIZE_16 );
}



void LCD_WriteDataPixelIndex( uint32_t Index, int nPixel )
{
    int cnt;
    int n;
    int acc = 0;
    int nblock = 0;
    int bsize = sizeof(g_aTxBuf)>>1; /*/2 due to 16bit per pixel */

    uint16_t *p = (uint16_t *)g_aTxBuf; /* use 16bit since 16bit/pixel */

    /* Please note that SPI now is in 16bit data size mode */
	for( cnt=0; cnt<bsize; cnt++ )
	{
		*p++ = Index;
	}

	/* NOTE:
	This function is purely for LCD has been set in graphic pixel memory.
	It will only transfer pixel data from GUI library */

	LCD_DC_HIGH();
	LCD_CS_LOW();

	/* Base on current available Txbuf size estimate number of block need to send */
	nblock = (nPixel / bsize) + 1;

	do
	{
		n = MIN( (nPixel - acc), bsize );

		if( n <= 0 )
		{
			break;
		}

        SpimTransfer( g_pSpimHandle, (uint8_t *)g_aTxBuf, 0, n<<1 );

		/* NOTE:
		SPI transfer can be blocking if wait until all data was sent.
		Or user specify a callback that it will not block the flow,
		it will callback to user when it is done
		*/
		if( 0 == g_pfLcdCbTransferDone )
		{
			/* There is no callback, user wish to use blocking wait */
			while( 0 == g_bSpiDone );
			g_bSpiDone = 0;
		}

		nblock--;
		acc += n;
	}while( 0 != nblock );

    LCD_CS_HIGH(); 
                
}


void LCD_WriteDataPixel( void const *pData, int nPixel )
{
	/* NOTE:
	This function is purely for LCD has been set in graphic pixel memory.
	It will only transfer pixel data from GUI library */

	LCD_DC_HIGH();
	LCD_CS_LOW();
	SpimTransfer( g_pSpimHandle, (uint8_t *)pData, 0, nPixel<<1 ); /* eache pixel is 16 bit, 2 bytes */

	/* NOTE:
	SPI transfer can be blocking if wait until all data was sent.
	Or user specify a callback that it will not block the flow,
	it will callback to user when it is done 
	*/
	if( 0 == g_pfLcdCbTransferDone )
	{
		/* There is no callback, user wish to use blocking wait */
		while( 0 == g_bSpiDone );
		g_bSpiDone = 0;
		LCD_CS_HIGH(); 
	}
}


void LCD_WriteSinglePixel( uint16_t Pixel )
{
	/* NOTE:
	This function is purely for LCD has been set in graphic pixel memory.
	It will only transfer pixel data from GUI library */
	uint16_t *p = (uint16_t *)g_aTxBuf;
	*p = Pixel;

	LCD_DC_HIGH();
	LCD_CS_LOW();
	SpimTransfer( g_pSpimHandle, g_aTxBuf, 0, 2 ); /* Send 1 pixel = 16bit */

	/* NOTE:
	SPI transfer can be blocking if wait until all data was sent.
	Or user specify a callback that it will not block the flow,
	it will callback to user when it is done
	*/
	if( 0 == g_pfLcdCbTransferDone )
	{
		/* There is no callback, user wish to use blocking wait */
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
	/* SPI transfer completed. Check user callback */
	if( 0 == g_pfLcdCbTransferDone )
	{
		/* Set polling flag */
		g_bSpiDone = 1;
	}
	else
	{
		/* Callback to user */
		g_pfLcdCbTransferDone();
        LCD_CS_HIGH();
	}
}


/*****************************************************************************
 Local functions
******************************************************************************/
static void lcd_WriteCmd( uint8_t Cmd )
{
	g_aTxBuf[0] = Cmd;

	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_LOW();
	LCD_CS_LOW();

	SpimTransfer( g_pSpimHandle, g_aTxBuf, 0, 1U );
	
	while( 0 == g_bSpiDone ){}
	g_bSpiDone = 0;

	LCD_CS_HIGH();  
}


static void lcd_WriteData( uint8_t Data )
{
	g_aTxBuf[0] = Data;

	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_HIGH();
	LCD_CS_LOW();

	SpimTransfer( g_pSpimHandle, g_aTxBuf, 0, 1U );
	while( 0 == g_bSpiDone ){}
	g_bSpiDone = 0;

	LCD_CS_HIGH();  
}


static void lcd_WriteMultipleByte( void const *pData, int nSize )
{
	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_HIGH();
	LCD_CS_LOW();
	SpimTransfer( g_pSpimHandle, pData, 0, nSize );
	while( 0 == g_bSpiDone ){}
	g_bSpiDone = 0;
	LCD_CS_HIGH(); 
}


#if 0
static void lcd_ReadData( uint8_t Cmd )
{
	/* Not supported by Adafruit TFT LCD */
	ASSERT( 0 != g_pSpimHandle );

	LCD_DC_LOW();
	LCD_CS_LOW();

	g_aTxBuf[0] = Cmd;
	SpimTransfer( g_pSpimHandle, g_aTxBuf, g_aRxBuf, 5U );
	
	while( 0 == g_bSpiDone ){}
	g_bSpiDone = 0;

	LCD_CS_HIGH(); 
}
#endif

static void lcd_Delayms( uint32_t ms )
{
	/* This not an accurate delay. */
	volatile int cnt = (SystemCoreClock*ms)/10000;
	
	while( cnt-- )
	{
		__NOP();
	}
}




















