/*****************************************************************************
 @Project	: 
 @File 		: spim.c
 @Details : SPI Master hardware layer                    
 @Author	:
 @Hardware: 

******************************************************************************/
#include "Common.h"
#include "math.h"
#include "Hal.h"
#include "spim.h"

/*****************************************************************************
 Define
******************************************************************************/
#define TOTAL_SPI			4U

//*****************************************************************************
// The following are defines for the bit fields in the SSI_O_CC register.
//*****************************************************************************
#define SSI_CC_CS_M             0x0000000F  // SSI Baud Clock Source
#define SSI_CC_CS_SYSPLL        0x00000000  // Either the system clock (if the
                                            // PLL bypass is in effect) or the
                                            // PLL output (default)
#define SSI_CC_CS_PIOSC         0x00000005  // PIOSC

//*****************************************************************************
// The following are defines for the bit fields in the SSI_O_CR0 register.
//*****************************************************************************
#define SSI_CR0_SCR_M           0x0000FF00  // SSI Serial Clock Rate
#define SSI_CR0_SPH             0x00000080  // SSI Serial Clock Phase
#define SSI_CR0_SPO             0x00000040  // SSI Serial Clock Polarity
#define SSI_CR0_FRF_M           0x00000030  // SSI Frame Format Select
#define SSI_CR0_FRF_MOTO        0x00000000  // Freescale SPI Frame Format
#define SSI_CR0_FRF_TI          0x00000010  // Texas Instruments Synchronous
                                            // Serial Frame Format
#define SSI_CR0_FRF_NMW         0x00000020  // MICROWIRE Frame Format
#define SSI_CR0_DSS_M           0x0000000F  // SSI Data Size Select
#define SSI_CR0_DSS_4           0x00000003  // 4-bit data
#define SSI_CR0_DSS_5           0x00000004  // 5-bit data
#define SSI_CR0_DSS_6           0x00000005  // 6-bit data
#define SSI_CR0_DSS_7           0x00000006  // 7-bit data
#define SSI_CR0_DSS_8           0x00000007  // 8-bit data
#define SSI_CR0_DSS_9           0x00000008  // 9-bit data
#define SSI_CR0_DSS_10          0x00000009  // 10-bit data
#define SSI_CR0_DSS_11          0x0000000A  // 11-bit data
#define SSI_CR0_DSS_12          0x0000000B  // 12-bit data
#define SSI_CR0_DSS_13          0x0000000C  // 13-bit data
#define SSI_CR0_DSS_14          0x0000000D  // 14-bit data
#define SSI_CR0_DSS_15          0x0000000E  // 15-bit data
#define SSI_CR0_DSS_16          0x0000000F  // 16-bit data
#define SSI_CR0_SCR_S           8

//*****************************************************************************
// The following are defines for the bit fields in the SSI_O_SR register.
//*****************************************************************************
#define SSI_SR_BSY              0x00000010  // SSI Busy Bit
#define SSI_SR_RFF              0x00000008  // SSI Receive FIFO Full
#define SSI_SR_RNE              0x00000004  // SSI Receive FIFO Not Empty
#define SSI_SR_TNF              0x00000002  // SSI Transmit FIFO Not Full
#define SSI_SR_TFE              0x00000001  // SSI Transmit FIFO Empty

//*****************************************************************************
// The following are defines for the bit fields in the SSI_O_IM register.
//*****************************************************************************
#define SSI_IM_TXIM             0x00000008  // SSI Transmit FIFO Interrupt Mask
#define SSI_IM_RXIM             0x00000004  // SSI Receive FIFO Interrupt Mask
#define SSI_IM_RTIM             0x00000002  // SSI Receive Time-Out Interrupt
                                            // Mask
#define SSI_IM_RORIM            0x00000001  // SSI Receive Overrun Interrupt
                                            // Mask
																						
//*****************************************************************************
// The following are defines for the bit fields in the SSI_O_CR1 register.
//*****************************************************************************
#define SSI_CR1_EOT             0x00000010  // End of Transmission
#define SSI_CR1_SOD             0x00000008  // SSI Slave Mode Output Disable
#define SSI_CR1_MS              0x00000004  // SSI Master/Slave Select
#define SSI_CR1_SSE             0x00000002  // SSI Synchronous Serial Port
                                            // Enable
#define SSI_CR1_LBM             0x00000001  // SSI Loopback Mode

/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile PSPIM_HANDLE g_pSpiIrqhandles[TOTAL_SPI] = { 0, 0, 0, 0 };


/*****************************************************************************
 Local Helpers
******************************************************************************/
static void SPI_Handler( PSPIM_HANDLE pHandle );


/*****************************************************************************
 Export functions
******************************************************************************/;


/*****************************************************************************
 Implementation
******************************************************************************/
int
SpimInit(
	void 		*pHandle,
	char 		nPort,
	int		 	nSpeed,
	SPIM_CFG	ClkInactive,
	SPIM_CFG	ClkEdge,
	SPIM_CFG	DATA_SIZE )
{
	IRQn_Type		irq;
	SSI0_Type 		*spi;
	int				clock;
    int				scr;
	int				prescale;
	int				preDiv;
	__IO uint32_t	cr0;
	PSPIM_HANDLE 	handle = (PSPIM_HANDLE)pHandle;
	
	ASSERT( 0 != pHandle );
	ASSERT( 0 != nSpeed );
	
	/* Check port */
	switch( nPort )
	{
		case 0:
			spi = SSI0;
			irq = SSI0_IRQn;
		break;
		
		case 1:
			spi = SSI1;
			irq = SSI1_IRQn;
		break;

		case 2:
			spi = SSI2;
			irq = SSI2_IRQn;
		break;

		case 3:
			spi = SSI3;
			irq = SSI3_IRQn;
		break;
		
		default:
			return SPIM_E_INVALID_PORT;
	}
	
	handle->pSpi = spi;
	handle->Irq = irq;
	
	g_pSpiIrqhandles[nPort] = handle;		/* keep the handle for interrupt use */
	
	spi->CR1 &= ~SSI_CR1_SSE;
	spi->CR1 &= ~SSI_CR1_MS;		/* Master mode */
	
	
	cr0 = spi->CR0;
	cr0 &= ~SSI_CR0_FRF_M;
	cr0 |= SSI_CR0_FRF_MOTO;
	
	/* Set clock polarity */
	switch( ClkInactive )
	{
		case SPI_CLK_INACT_LOW:
			cr0 &= ~SSI_CR0_SPO;
		break;
		
		case SPI_CLK_INACT_HIGH:
			cr0 |= SSI_CR0_SPO;
		break;
		
		default:
			return SPIM_E_INVALID_CLK_POLARITY;
	}
	
	/* Set clock edge */
	switch( ClkEdge )
	{
		case SPI_CLK_RISING_EDGE:
			cr0 &= ~SSI_CR0_SPH;
		break;
		
		case SPI_CLK_FALLING_EDGE:
			cr0 |= SSI_CR0_SPH;
		break;
		
		default:
			return SPIM_E_INVALID_CLK_EDGE;
	}

	spi->CR0 = cr0;
	
	
	/* Speed - Use system core clock */
	spi->CC &= ~SSI_CC_CS_M;
	spi->CC |= SSI_CC_CS_SYSPLL;
	
    clock = SystemCoreClock;

	prescale = clock / nSpeed;
	
	if( nSpeed>20000000 )
	{
		return SPIM_E_INVALID_SPEED;
	}
	
	if( prescale < 2 )
	{
		return SPIM_E_INVALID_SPEED;
	}
	
	preDiv = 0;
    do
    {
        preDiv += 2;
        scr = (prescale / preDiv) - 1;
    }
    while(scr > 255);
	
	spi->CPSR = preDiv;
	
	cr0 = spi->CR0;
	cr0 &= ~SSI_CR0_SCR_M;
	cr0 |= (scr<<SSI_CR0_SCR_S);
	cr0 &= ~SSI_CR0_DSS_M;
	
	handle->bTransferWord = FALSE;
	
	switch( DATA_SIZE )
	{
		case SPI_DATA_SIZE_4:
			cr0 |= SSI_CR0_DSS_4;
			handle->Datasize = 4;
		break;
		
		case SPI_DATA_SIZE_5:
			cr0 |= SSI_CR0_DSS_5;
			handle->Datasize = 5;
		break;
		
		case SPI_DATA_SIZE_6:
			cr0 |= SSI_CR0_DSS_6;
			handle->Datasize = 6;
		break;
		
		case SPI_DATA_SIZE_7:
			cr0 |= SSI_CR0_DSS_7;
			handle->Datasize = 7;
		break;
		
		case SPI_DATA_SIZE_8:
			cr0 |= SSI_CR0_DSS_8;
			handle->Datasize = 8;
		break;
		
		case SPI_DATA_SIZE_9:
			cr0 |= SSI_CR0_DSS_9;
			handle->Datasize = 9;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_10:
			cr0 |= SSI_CR0_DSS_10;
			handle->Datasize = 10;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_11:
			cr0 |= SSI_CR0_DSS_11;
			handle->Datasize = 11;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_12:
			cr0 |= SSI_CR0_DSS_12;
			handle->Datasize = 12;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_13:
			cr0 |= SSI_CR0_DSS_13;
			handle->Datasize = 13;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_14:
			cr0 |= SSI_CR0_DSS_14;
			handle->Datasize = 14;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_15:
			cr0 |= SSI_CR0_DSS_15;
			handle->Datasize = 15;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_16:
			cr0 |= SSI_CR0_DSS_16;
			handle->Datasize = 16;
			handle->bTransferWord = TRUE;
		break;
		
		default:
			return SPIM_E_INVALID_DATASIZE;
	}
	
	spi->CR0 = cr0;
	spi->CR1 |= SSI_CR1_EOT | SSI_CR1_SSE;
	
	NVIC_EnableIRQ( irq );
	
	return SPIM_STS_OK;
}


int SpimSetSpeed( void *pHandle, int nSpeed )
{
	int				clock;
  int				scr;
	int				prescale;
	int				preDiv;
	
	__IO uint32_t	cr0;
    PSPIM_HANDLE 	handle = (PSPIM_HANDLE)pHandle;
    SSI0_Type 		*spi 	= handle->pSpi;

	ASSERT( 0 != pHandle );

	spi->CR1 &= ~SSI_CR1_SSE;
	
	/* Speed - Use system core clock */
	spi->CC &= ~SSI_CC_CS_M;
	spi->CC |= SSI_CC_CS_SYSPLL;
	
    clock = SystemCoreClock;

	prescale = clock / nSpeed;
	
	if( prescale < 2 )
	{
		return SPIM_E_INVALID_SPEED;
	}
	
	preDiv = 0;
    do
    {
        preDiv += 2;
        scr = (prescale / preDiv) - 1;
    }
    while(scr > 255);
	
	spi->CPSR = preDiv;
	
	cr0 = spi->CR0;
	cr0 &= ~SSI_CR0_SCR_M;
	cr0 |= (scr<<SSI_CR0_SCR_S);
	spi->CR0 = cr0;

	spi->CR1 |= SSI_CR1_SSE;
	
	return clock;
}


int SpimSetDataSize( void *pHandle, SPIM_CFG DATA_SIZE )
{
	PSPIM_HANDLE 	handle = (PSPIM_HANDLE)pHandle;
	SSI0_Type 		*spi	= handle->pSpi;
	
	spi->CR1 &= ~SSI_CR1_SSE;
	spi->CR0 &= ~SSI_CR0_DSS_M;
	
	handle->bTransferWord = FALSE;
	
	switch( DATA_SIZE )
	{
		case SPI_DATA_SIZE_4:
			spi->CR0 |= SSI_CR0_DSS_4;
			handle->Datasize = 4;
		break;
		
		case SPI_DATA_SIZE_5:
			spi->CR0 |= SSI_CR0_DSS_5;
			handle->Datasize = 5;
		break;
		
		case SPI_DATA_SIZE_6:
			spi->CR0 |= SSI_CR0_DSS_6;
			handle->Datasize = 6;
		break;
		
		case SPI_DATA_SIZE_7:
			spi->CR0 |= SSI_CR0_DSS_7;
			handle->Datasize = 7;
		break;
		
		case SPI_DATA_SIZE_8:
			spi->CR0 |= SSI_CR0_DSS_8;
			handle->Datasize = 8;
		break;
		
		case SPI_DATA_SIZE_9:
			spi->CR0 |= SSI_CR0_DSS_9;
			handle->Datasize = 9;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_10:
			spi->CR0 |= SSI_CR0_DSS_10;
			handle->Datasize = 10;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_11:
			spi->CR0 |= SSI_CR0_DSS_11;
			handle->Datasize = 11;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_12:
			spi->CR0 |= SSI_CR0_DSS_12;
			handle->Datasize = 12;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_13:
			spi->CR0 |= SSI_CR0_DSS_13;
			handle->Datasize = 13;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_14:
			spi->CR0 |= SSI_CR0_DSS_14;
			handle->Datasize = 14;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_15:
			spi->CR0 |= SSI_CR0_DSS_15;
			handle->Datasize = 15;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_16:
			spi->CR0 |= SSI_CR0_DSS_16;
			handle->Datasize = 16;
			handle->bTransferWord = TRUE;
		break;
		
		default:
			return SPIM_E_INVALID_DATASIZE;
	}
	
	spi->CR1 |= SSI_CR1_SSE;
	
	return SPIM_STS_OK;
}



void SpimAddCallbackTransferDone(void *phandle, SPIM_CB_TRFR_DONE 	*pfDone)
{
	PSPIM_HANDLE handle = (PSPIM_HANDLE)phandle;	
	
	ASSERT( 0 != phandle );
	ASSERT( 0 != pfDone );	
	
	handle->pfDone = pfDone;
}


void SpimTransfer(void *phandle, void const *pTxBuf, void *pRxBuf, int nSize)
{
	PSPIM_HANDLE handle 	= (PSPIM_HANDLE)phandle;
	SSI0_Type *spi 	= handle->pSpi;
	
	ASSERT( 0 != phandle );
	ASSERT( 0 != pTxBuf );
	ASSERT( 0 != pRxBuf );
	ASSERT( 0 != nSize );
	
	
	handle->nTxCount	= 0;
	handle->nRxCount	= 0;
	
	/* This driver need to modify if datasize more than 8 bits */
	if( FALSE == handle->bTransferWord )
	{
		handle->pRxBuf 	= (char *)pRxBuf;
		handle->pTxBuf 	= (char *)pTxBuf;
		handle->nSize	= nSize;
		spi->DR = handle->pTxBuf[0];
	}
	else
	{
		handle->pRxWordBuf 	= (uint16_t *)pRxBuf;
		handle->pTxWordBuf 	= (uint16_t *)pTxBuf;
		handle->nSize	= nSize>>1;
		spi->DR = handle->pTxWordBuf[0];
	}

	handle->nTxCount++;
	
	
	spi->IM = SSI_IM_TXIM | SSI_IM_RXIM;	/* Enable interrupts */
	spi->CR1 |= SSI_CR1_SSE;
}

/*****************************************************************************
 Local functions
******************************************************************************/
static void SPI_Handler( PSPIM_HANDLE pHandle )
{
	SSI0_Type *spi = pHandle->pSpi;
	int status = spi->SR;
	int isr = spi->RIS;
	uint16_t tmp;
	
	ASSERT( 0 != pHandle );
	
	if( 0 != (status & SSI_SR_RNE) )
	{
		tmp = spi->DR; 
		
		if( FALSE == pHandle->bTransferWord )
		{
			if( 0 != pHandle->pRxBuf )
			{
				pHandle->pRxBuf[pHandle->nRxCount] = tmp;
			}
		}
		else
		{
			if( 0 != pHandle->pRxWordBuf )
			{
				pHandle->pRxWordBuf[pHandle->nRxCount] = tmp;
			}
		}
		
		pHandle->nRxCount++;
		
		if( pHandle->nRxCount >= pHandle->nSize )
		{
			spi->IM &= ~SSI_IM_RXIM;	/* Disable interrupts */
			spi->CR1 &= ~SSI_CR1_SSE;
			
			/* Callback to application */
			if( 0 != pHandle->pfDone )	/* The pointer maybe 0 */
			{
				pHandle->pfDone();
			}
		}
	}

			
	if( (0 != (status & SSI_SR_TNF)) || (0 != (status & SSI_SR_TFE)) )
	{
		if( pHandle->nTxCount >= pHandle->nSize )
		{
			/* Transfer has completed */
			spi->IM &= ~SSI_IM_TXIM;
		}
		else
		{
			if( FALSE == pHandle->bTransferWord )
			{
				/* Write to data register to transfer */
				spi->DR = pHandle->pTxBuf[pHandle->nTxCount];
			}
			else
			{
				/* Write to data register to transfer */
				spi->DR = pHandle->pTxWordBuf[pHandle->nTxCount];
			}
			
			pHandle->nTxCount++;
		}
	}
}



/*****************************************************************************
 Interrupt
******************************************************************************/
void SSI0_Handler( void )
{
	ASSERT( 0 != g_pSpiIrqhandles[0] );
	
	SPI_Handler( g_pSpiIrqhandles[0] );
}

