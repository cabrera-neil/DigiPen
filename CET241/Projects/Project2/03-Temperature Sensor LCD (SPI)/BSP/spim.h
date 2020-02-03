/*****************************************************************************
 @Project	: STM32F7XX SPI Master driver
 @File 		: spim.h
 @Details : SPI Master hardware layer                    
 @Author	: 
 @Hardware: 
   
******************************************************************************/
#include <stdint.h>

#ifndef __SPIM_DOT_H__
#define __SPIM_DOT_H__

/*****************************************************************************
 Define
******************************************************************************/
#define SPIM_STS_OK					0
#define SPIM_E_INVALID_PORT			-1
#define SPIM_E_INVALID_CLK_POLARITY	-2
#define SPIM_E_INVALID_CLK_EDGE		-3
#define SPIM_E_INVALID_DATASIZE		-4
#define SPIM_E_INVALID_SPEED		-5


/*****************************************************************************
 Type definition
******************************************************************************/
typedef enum _SPIM_CFG
{
	SPI_CLK_INACT_HIGH,		/* Clock polarity selection */
	SPI_CLK_INACT_LOW,
	
	SPI_CLK_RISING_EDGE,		/* Clock sampling edge selection */
	SPI_CLK_FALLING_EDGE,
	
	SPI_DATA_SIZE_4,
	SPI_DATA_SIZE_5,
	SPI_DATA_SIZE_6,
	SPI_DATA_SIZE_7,
	SPI_DATA_SIZE_8,
	SPI_DATA_SIZE_9,
	SPI_DATA_SIZE_10,
	SPI_DATA_SIZE_11,
	SPI_DATA_SIZE_12,
	SPI_DATA_SIZE_13,
	SPI_DATA_SIZE_14,
	SPI_DATA_SIZE_15,
	SPI_DATA_SIZE_16
}SPIM_CFG;

/* SPI Driver typedef */
typedef void SPIM_CB_TRFR_DONE( void );


/*SPI Instance handle */
typedef struct _tagSpim_handle
{
	void 	*pSpi;
	int		Irq;
	int		Apb;
	int		Datasize;
	
	volatile int				nTxCount;
	volatile int				nRxCount;
	volatile char 			*pTxBuf;
	volatile char 			*pRxBuf;
	volatile uint16_t 	*pTxWordBuf;
	volatile uint16_t 	*pRxWordBuf;
	int 				nSize;
	
	uint8_t				bTransferWord :1;
	uint8_t				Reseved :7;
	
	SPIM_CB_TRFR_DONE	*pfDone;
}SPIM_HANDLE, *PSPIM_HANDLE;


/******************************************************************************
 Global functions
******************************************************************************/

int SpimInit(
		void 				*pHandle,
		char 				nPort,
		int 				nSpeed,
		SPIM_CFG			ClkInactive,
		SPIM_CFG			ClkEdge,
		SPIM_CFG			DATA_SIZE );


int SpimSetSpeed( void *pHandle, int nSpeed );

int SpimSetDataSize( void *pHandle, SPIM_CFG DATA_SIZE );

void SpimAddCallbackTransferDone(void *pHandle,	SPIM_CB_TRFR_DONE 	*pfDone);

void SpimTransfer(void *pHandle, void const *pTxBuf, void *pRxBuf, int nSize);	

#endif /* __SPIM_DOT_H__ */

