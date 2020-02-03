/*****************************************************************************
 @Project	: 
 @File 		: dma.c
 @Details  	: STM32F103XX rtc driver               
 @Author	: 
 @Hardware	: STM32
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  lcgan     XXXX-XX-X X  		Initial Release
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "dma.h"


/*****************************************************************************
 Define
******************************************************************************/
#define TOTAL_DMA		2U
#define TOTAL_STREAM	7U


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Constant Variables
******************************************************************************/
static const DMA_Stream_TypeDef *DMA1_STREAM_TABLE[] = 
{
	DMA1_Stream0,
	DMA1_Stream1,
	DMA1_Stream2,
	DMA1_Stream3,
	DMA1_Stream4,
	DMA1_Stream5,
	DMA1_Stream6,
	DMA1_Stream7
};


static const DMA_Stream_TypeDef *DMA2_STREAM_TABLE[] = 
{
	DMA2_Stream0,
	DMA2_Stream1,
	DMA2_Stream2,
	DMA2_Stream3,
	DMA2_Stream4,
	DMA2_Stream5,
	DMA2_Stream6,
	DMA2_Stream7
};


static const uint32_t DMA_ISR_HCIF[] = 
{
	DMA_LISR_HTIF0,
	DMA_LISR_HTIF1,
	DMA_LISR_HTIF2,
	DMA_LISR_HTIF3,
	DMA_HISR_HTIF4,
	DMA_HISR_HTIF5,
	DMA_HISR_HTIF6,
	DMA_HISR_HTIF7
};


static const uint32_t DMA_ISR_TCIF[] = 
{
	DMA_LISR_TCIF0,
	DMA_LISR_TCIF1,
	DMA_LISR_TCIF2,
	DMA_LISR_TCIF3,
	DMA_HISR_TCIF4,
	DMA_HISR_TCIF5,
	DMA_HISR_TCIF6,
	DMA_HISR_TCIF7
};


static const uint32_t DMA_ISR_TEIF[] = 
{
	DMA_LISR_TEIF0,
	DMA_LISR_TEIF1,
	DMA_LISR_TEIF2,
	DMA_LISR_TEIF3,
	DMA_HISR_TEIF4,
	DMA_HISR_TEIF5,
	DMA_HISR_TEIF6,
	DMA_HISR_TEIF7
};


static const IRQn_Type DMA1_IRQN[] = 
{
	DMA1_Stream0_IRQn,
	DMA1_Stream1_IRQn,
	DMA1_Stream2_IRQn,
	DMA1_Stream3_IRQn,
	DMA1_Stream4_IRQn,
	DMA1_Stream5_IRQn,
	DMA1_Stream5_IRQn,
	DMA1_Stream7_IRQn
};

static const IRQn_Type DMA2_IRQN[] = 
{
	DMA2_Stream0_IRQn,
	DMA2_Stream1_IRQn,
	DMA2_Stream2_IRQn,
	DMA2_Stream3_IRQn,
	DMA2_Stream4_IRQn,
	DMA2_Stream5_IRQn,
	DMA2_Stream5_IRQn,
	DMA2_Stream7_IRQn
};


/*****************************************************************************
 Local Variables
******************************************************************************/
static  DMA_HANDLE *g_pDma1IrqHandles[8];
static  DMA_HANDLE *g_pDma2IrqHandles[8];


/*****************************************************************************
 Local Functions
******************************************************************************/


/*****************************************************************************
 Implementation
******************************************************************************/
int 
DmaInit(
	DMA_HANDLE	*hHandle,
	int			nDMA,
	uint8_t		nStream,
	uint8_t		nCh,
	DMA_CONFIG	Direction,
	DMA_CONFIG	MemIncrement,
    DMA_CONFIG	MemDataSize,
	DMA_CONFIG	PeriIncrement,
	DMA_CONFIG	PeriphDataSize
	)
{
	DMA_TypeDef *dma;
    DMA_Stream_TypeDef *stream;
    IRQn_Type irq;
	uint32_t tmp;


	ASSERT( 0 != hHandle );
	ASSERT( 0 != nDMA );
    ASSERT( nStream<=TOTAL_STREAM );

	switch( nDMA )
	{
		case 1:
			dma = DMA1;
            stream = (DMA_Stream_TypeDef *)DMA1_STREAM_TABLE[nStream];
			irq = DMA1_IRQN[nStream];
            g_pDma1IrqHandles[nStream] = hHandle;
		break;

		case 2:
			dma = DMA2;
            stream = (DMA_Stream_TypeDef *)DMA2_STREAM_TABLE[nStream];
			irq = DMA2_IRQN[nStream];
            g_pDma2IrqHandles[nStream] = hHandle;
		break;

		default:
			return DMA_INVALID_PARAM;
	}

	hHandle->pDma = dma;
	hHandle->nStream = nStream;
	hHandle->pStream = stream;
	hHandle->Direction = Direction;

	/* Disable DMA during configuration */
    stream->CR &= ~DMA_SxCR_EN;
// stream->FCR |= DMA_SxFCR_DMDIS;
	tmp = stream->CR;

	/* Clear PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
	tmp &= ~(DMA_SxCR_CIRC
			| DMA_SxCR_MSIZE
			| DMA_SxCR_PSIZE
			| DMA_SxCR_MINC  
			| DMA_SxCR_PINC   
			| DMA_SxCR_CIRC   
			| DMA_SxCR_DIR
			| DMA_SxCR_CHSEL);

	tmp |= nCh<<DMA_SxCR_CHSEL_Pos;

	/* Configure direction */
	switch( Direction )
	{
		case DMA_DIR_MEM_TO_PERI:
			tmp |= DMA_SxCR_DIR_0;
		break;

		case DMA_DIR_PERI_TO_MEM:
			tmp &= ~DMA_SxCR_DIR;
		break;

		case DMA_DIR_MEM_TO_MEM:
			tmp |= DMA_SxCR_DIR_1;
		break;

		default:
			return DMA_INVALID_PARAM;
	}

	/* Configure data alignment */
	switch( PeriphDataSize )
	{
    	case DMA_DATA_ALIGN_BYTE:
			tmp &= ~(DMA_SxCR_PSIZE_0 | DMA_SxCR_PSIZE_1);
		break;

    	case DMA_DATA_ALIGN_HALF_WORD:
			tmp |= DMA_SxCR_PSIZE_0;
		break;

    	case DMA_DATA_ALIGN_WORD:
			tmp |= DMA_SxCR_PSIZE_1;
		break;

		default:
			return DMA_INVALID_PARAM;
	}

	switch( MemDataSize )
	{
    	case DMA_DATA_ALIGN_BYTE:
			tmp &= ~(DMA_SxCR_MSIZE_0 | DMA_SxCR_MSIZE_1);
		break;

    	case DMA_DATA_ALIGN_HALF_WORD:
			tmp |= DMA_SxCR_MSIZE_0;
		break;

    	case DMA_DATA_ALIGN_WORD:
			tmp |= DMA_SxCR_MSIZE_1;
		break;

		default:
			return DMA_INVALID_PARAM;
	}

	/* configure data auto increment */
	switch( MemIncrement )
	{
		case DMA_MEM_INC_EN:
			tmp |= DMA_SxCR_MINC;
		break;

		case DMA_MEM_INC_DIS:
			tmp &= ~DMA_SxCR_MINC;
		break;

		default:
			return DMA_INVALID_PARAM;
	}

	switch( PeriIncrement )
	{
		case DMA_PERI_INC_EN:
			tmp |= DMA_SxCR_PINC;
		break;

		case DMA_PERI_INC_DIS:
			tmp &= ~DMA_SxCR_PINC;
		break;

		default:
			return DMA_INVALID_PARAM;
	}

	stream->CR = tmp;
    NVIC_EnableIRQ( irq );

	return DMA_OK;
}


void
DmaAddCallback(
	DMA_HANDLE	*hHandle,
	DMA_CB_HALF *pfcbHalf,
	DMA_CB_COMP *pfcbComp,
	DMA_CB_ERROR *pfcbError
	)
{
	ASSERT( 0 != hHandle );

	hHandle->pfHalf = pfcbHalf;
	hHandle->pfComp = pfcbComp;
	hHandle->pfError = pfcbError;
}


void
DmaStart(
	DMA_HANDLE	*hHandle,
	uint32_t	SrcAddr,
	uint32_t	DestAddr,
	uint32_t	nSize
	)
{
	DMA_TypeDef *dma;
	DMA_Stream_TypeDef *stream;

	ASSERT( 0 != hHandle );
	ASSERT( 0 != SrcAddr );
	ASSERT( 0 != DestAddr );
	ASSERT( 0 != nSize );

	dma = (DMA_TypeDef *)hHandle->pDma;
	stream = (DMA_Stream_TypeDef *)hHandle->pStream;

	/* Disable DMA during configuration */
    stream->CR &= ~DMA_SxCR_EN;

	if( hHandle->nStream<4U )
	{
		/* Clear pending interrupts */
		dma->LIFCR = 0x3fU<<hHandle->nStream;
	}
	else
	{
		/* Clear pending interrupts */
		dma->HIFCR = 0x3fU<<hHandle->nStream;
	}

	/* Configure DMA Channel data length */
	stream->NDTR = nSize;

	/* Memory to Peripheral */

	switch( hHandle->Direction )
	{
		case DMA_DIR_MEM_TO_PERI:
			/* Configure DMA Channel destination address */
			stream->PAR = DestAddr;

			/* Configure DMA Channel source address */
			stream->M0AR = SrcAddr;
            stream->M1AR = 0;
		break;

		case DMA_DIR_PERI_TO_MEM:
			/* Configure DMA Channel source address */
			stream->PAR = SrcAddr;

			/* Configure DMA Channel destination address */
			stream->M0AR = DestAddr;
			stream->M1AR = 0;
		break;

		default:
		break;
	}

    /* Enable the transfer complete interrupt */
    /* Enable the transfer Error interrupt */
    /* Enable the Peripheral */
    stream->CR |=  DMA_SxCR_TCIE 
					//| DMA_SxCR_HTIE 
					| DMA_SxCR_TEIE
					| DMA_SxCR_EN;
}


void 
DmaStop(
	DMA_HANDLE	*hHandle
	)
{
	DMA_Stream_TypeDef *stream;

	ASSERT( 0 != hHandle );

	stream = hHandle->pStream;

	/* Disable DMA during configuration */
    stream->CR &= ~DMA_SxCR_EN;
}


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Local functions
******************************************************************************/
/**
  * @brief  Handles DMA interrupt request.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Channel.  
  * @retval None
  */

void dma_IRQHandler( DMA_HANDLE	*hHandle )
{
	uint32_t			isr;
	uint32_t			cr;
	DMA_TypeDef			*dma = (DMA_TypeDef *)hHandle->pDma;

	DMA_Stream_TypeDef *stream = (DMA_Stream_TypeDef *)hHandle->pStream;

	ASSERT( 0 != hHandle );

    /* NOTE: channel more than 4 consider High byte */
	if( hHandle->nStream<4 )
	{
		isr = dma->LISR;
	}
	else
	{
		isr = dma->HISR;
	}
	
	cr = stream->CR;
  
	/* Half Transfer Complete Interrupt management ******************************/
	if(0 != (isr&DMA_ISR_HCIF[hHandle->nStream]) && (0 != (cr&DMA_SxCR_HTIE)))
	{
		/* Disable the half transfer interrupt if the DMA mode is not CIRCULAR */
		if( 0 == (cr & DMA_SxCR_CIRC) )
		{
			/* Disable the half transfer interrupt */
			stream->CR &= ~DMA_SxCR_HTIE;
		}

		if( hHandle->nStream<4 )
		{
        	/* Clear the half transfer complete flag */
			dma->LIFCR = DMA_ISR_HCIF[hHandle->nStream];
		}
		else
		{
            /* Clear the half transfer complete flag */
			dma->HIFCR = DMA_ISR_HCIF[hHandle->nStream];
		}


		/* DMA peripheral state is not updated in Half Transfer */
		/* but in Transfer Complete case */

		if( 0 != hHandle->pfHalf )
		{
		  /* Half transfer callback */
			hHandle->pfHalf( hHandle->pLinkContext );
		}
	}

	/* Transfer Complete Interrupt management ***********************************/
	else if( (0 != (isr&DMA_ISR_TCIF[hHandle->nStream])) && (0 != (cr & DMA_SxCR_TCIE)) )
	{
		if( 0 == (cr & DMA_SxCR_CIRC) )
		{
			/* Disable the transfer complete and error interrupt */
            stream->CR &= ~(DMA_SxCR_TEIE | DMA_SxCR_TCIE);
		}

		if( hHandle->nStream<4 )
		{
        	/* Clear the half transfer complete flag */
			dma->LIFCR = DMA_ISR_TCIF[hHandle->nStream];
		}
		else
		{
            /* Clear the half transfer complete flag */
			dma->HIFCR = DMA_ISR_TCIF[hHandle->nStream];
		}


		if( 0 != hHandle->pfComp )
		{
			/* transfer done callback */
			hHandle->pfComp( hHandle->pLinkContext );
		}
	}

  /* Transfer Error Interrupt management **************************************/
  if ((0 != (isr&DMA_ISR_TEIF[hHandle->nStream])) && (0 != (cr & DMA_SxCR_TEIE)))
  {
    /* When a DMA transfer error occurs */
    /* A hardware clear of its EN bits is performed */
    /* Disable ALL DMA IT */
    stream->CR &= ~(DMA_SxCR_TEIE | DMA_SxCR_TCIE | DMA_SxCR_HTIE);

	if( hHandle->nStream<4 )
	{
		/* Clear all flags */
		dma->LIFCR = DMA_ISR_TEIF[hHandle->nStream];
	}
	else
	{

    	/* Clear all flags */
		dma->HIFCR = DMA_ISR_TEIF[hHandle->nStream];
	}

	if( 0 != hHandle->pfError )
	{
		/* transfer done callback */
		hHandle->pfError( hHandle->pLinkContext );
	}
  }
  return;
}

/*****************************************************************************
 Interrupt handling
******************************************************************************/
void DMA1_Stream0_IRQHandler( void )
{
	dma_IRQHandler( g_pDma1IrqHandles[0] );
}


void DMA1_Stream1_IRQHandler( void )
{
	dma_IRQHandler( g_pDma1IrqHandles[1] );
}


void DMA1_Stream2_IRQHandler( void )
{
	dma_IRQHandler( g_pDma1IrqHandles[2] );
}


void DMA1_Stream3_IRQHandler( void )
{
	dma_IRQHandler( g_pDma1IrqHandles[3] );
}


void DMA1_Stream4_IRQHandler( void )
{
	dma_IRQHandler( g_pDma1IrqHandles[4] );
}


void DMA1_Stream5_IRQHandler( void )
{
	dma_IRQHandler( g_pDma1IrqHandles[5] );
}


void DMA1_Stream6_IRQHandler( void )
{
	dma_IRQHandler( g_pDma1IrqHandles[6] );
}


void DMA1_Stream7_IRQHandler( void )
{
	dma_IRQHandler( g_pDma1IrqHandles[7] );
}


void DMA2_Stream0_IRQHandler( void )
{
	dma_IRQHandler( g_pDma2IrqHandles[0] );
}


void DMA2_Stream1_IRQHandler( void )
{
	dma_IRQHandler( g_pDma2IrqHandles[1] );
}


void DMA2_Stream2_IRQHandler( void )
{
	dma_IRQHandler( g_pDma2IrqHandles[2] );
}


void DMA2_Stream3_IRQHandler( void )
{
	dma_IRQHandler( g_pDma2IrqHandles[3] );
}


void DMA2_Stream4_IRQHandler( void )
{
	dma_IRQHandler( g_pDma2IrqHandles[4] );
}


void DMA2_Stream5_IRQHandler( void )
{
	dma_IRQHandler( g_pDma2IrqHandles[5] );
}


void DMA2_Stream6_IRQHandler( void )
{
	dma_IRQHandler( g_pDma2IrqHandles[6] );
}


void DMA2_Stream7_IRQHandler( void )
{
	dma_IRQHandler( g_pDma2IrqHandles[7] );
}
























