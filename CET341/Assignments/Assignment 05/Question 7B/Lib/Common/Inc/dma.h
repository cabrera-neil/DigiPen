/*****************************************************************************
 @Project	: 
 @File 		: dma.h
 @Details  	: dma
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
******************************************************************************/

#ifndef __DMA_DOT_H__
#define __DMA_DOT_H__

/*****************************************************************************
 Define
******************************************************************************/
#define DMA_OK						0
#define DMA_INVALID_PARAM			-1


/* NOTE:
 Refer to RM0431 document, page 218 */
#define DMA1_SPI2_RX_CH				3U
#define DMA1_SPI2_TX_CH				4U

#define DMA2_USART1_TX_STREAM		7U
#define DMA2_USART1_RX_STREAM		5U
#define DMA2_USART1_TX_CH			4U
#define DMA2_USART1_RX_CH			4U


/*****************************************************************************
 Typedef 
******************************************************************************/
typedef void DMA_CB_HALF( void *pContext );
typedef void DMA_CB_COMP( void *pContext );
typedef void DMA_CB_ERROR( void *pContext );

typedef enum _tagDma_Config
{
	DMA_DIR_MEM_TO_PERI,
	DMA_DIR_PERI_TO_MEM,
	DMA_DIR_MEM_TO_MEM,

	DMA_DATA_ALIGN_BYTE,
	DMA_DATA_ALIGN_HALF_WORD,
	DMA_DATA_ALIGN_WORD,

	DMA_MEM_INC_EN,
    DMA_MEM_INC_DIS,
	DMA_PERI_INC_EN,
	DMA_PERI_INC_DIS
}DMA_CONFIG;


typedef struct _tagDma_Handle
{
	void		*pDma;
    void		*pStream;
	uint32_t	nStream;

	void		*pLinkContext;

	DMA_CONFIG	Direction;

	DMA_CB_HALF  *pfHalf;
	DMA_CB_COMP  *pfComp;
	DMA_CB_ERROR *pfError;
}DMA_HANDLE, *PDMA_HANDLE;


/*****************************************************************************
 Implementation 
******************************************************************************/

/*****************************************************************************
 @Description 	: 
 
 @Param			: 

 @Requirement	:  
				  
 @Revision		:
******************************************************************************/
int DmaInit(
		DMA_HANDLE	*hHandle,
		int			nPort,
		uint8_t		nStream,
        uint8_t		nCh,
		DMA_CONFIG	Direction,
		DMA_CONFIG	MemIncrement,
		DMA_CONFIG	MemDataSize,
		DMA_CONFIG	PeriIncrement,
		DMA_CONFIG	PeriphDataSize );


/*****************************************************************************
 @Description 	: 
 
 @Param			: 

 @Requirement	:  
				  
 @Revision		:
******************************************************************************/
void DmaStart(
		DMA_HANDLE	*hHandle,
		uint32_t	SrcAddr,
		uint32_t	DestAddr,
		uint32_t	nSize );


/*****************************************************************************
 @Description 	: 
 
 @Param			: 

 @Requirement	:  
				  
 @Revision		:
******************************************************************************/
void DmaStop( DMA_HANDLE	*hHandle );


/*****************************************************************************
 @Description 	: 
 
 @Param			: 

 @Requirement	:  
				  
 @Revision		:
******************************************************************************/
void DmaAddCallback(
		DMA_HANDLE		*hHandle,
		DMA_CB_HALF		*pfcbHalf,
		DMA_CB_COMP		*pfcbComp,
		DMA_CB_ERROR	*pfcbError );

#endif /* __DMA_DOT_H__ */




















































