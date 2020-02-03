/******************************************************************************
 @filename		Serial.h

 @project		UART logical layer	
 
 @description		
 
 @version		1.0.0

 @revision		
******************************************************************************/

#ifndef	__SERIAL_DOT_H__
#define	__SERIAL_DOT_H__


/******************************************************************************
 Defines 
******************************************************************************/

/* Uart status */
#define	UART_STS_OK					0				/* Success */
#define	UART_STS_FAULT				-1				/* Failed */
#define	UART_STS_NO_PORT			-2				/* Invalid port */
#define	UART_STS_NO_CFG				-3				/* Invalid Configuration */
#define	UART_STS_BUF_OVER			-4				/* Buffer Overflow */
#define	UART_STS_MISMATCH_MODE		-5				/*  not in the match mode */
#define	UART_STS_INVALID_PARAM		-6				/*  not in the param */

/* Error status */
#define	UART_ERR_CLEAR				0x00000000U		/* No error */
#define	UART_ERR_OVERFLOW			0x00000001U		/* Rx overflow */
#define	UART_ERR_PARITY				0x00000002U		/* Parity error */
#define	UART_ERR_FRAME				0x00000004U		/* Framing error */


/******************************************************************************
 typedef
******************************************************************************/

/* UART Callbacks */
typedef	void UART_CB_ONRX( void );
typedef	void UART_CB_ONTX( void );

/* UART configuration cater for all features */
typedef enum _tagUart_Cfg
{
	UART_DEFAULT = 0,						/* No change */
	
	UART_BITS_5,							/* data bits options */
	UART_BITS_6,
	UART_BITS_7,
	UART_BITS_8,
	UART_BITS_9,
	UART_BITS_10,
	
	UART_NONE,								/* No parity */
	UART_ODD,								/* Odd parity */
	UART_EVEN,								/* Even parity */
	UART_SPACE,								/* Space parity */
	UART_MARK,								/* Mark parity */
	
	UART_ONE,								/* 1 stop bit */
	UART_ONE_HALF,							/* 1.5 stop bits */
	UART_TWO								/* 2 stop bits */
}UART_CFG;


/* Uart Hardware driver function typedef */
typedef	int 	UART_INIT( void *pHandle, uint8_t nPort, uint32_t nBaud );
typedef	int 	UART_SET_BAUD( void const *pHandle, uint32_t nBaud );
typedef	int 	UART_SET_CFG(
					void const 	*pHandle,
					UART_CFG 	Databit,
					UART_CFG 	Parity,
					UART_CFG 	Stopbit );
typedef void 	UART_SET_IRQLEVEL( void const *pHandle, uint32_t nLevel );
typedef	int 	UART_LOOPBACK( void const *pHandle,int bEnable );
typedef	void	UART_WRITE( void const *pHandle, char Data );
typedef	void	UART_DMA_TX( void *pHandle, void const *pData, int nSize );
typedef char	UART_READ( void const *pHandle );
typedef	void	UART_DMA_RX( void *pHandle, void *pData, int nSize );
typedef int		UART_IS_TXEND( void const *pHandle );
typedef int		UART_IS_TXREADY( void const *pHandle );
typedef int		UART_IS_RXREADY( void const *pHandle );
typedef void 	UART_TXEND( void const *pHandle );
typedef void 	UART_RXEND( void const *pHandle );
typedef void 	UART_LOCK( void  *pHandle );
typedef void 	UART_UNLOCK( void *pHandle);


/* Uart Hardware driver functions */
typedef struct _tag_UART_DRIVER
{
	UART_INIT			*pfInit;
	UART_SET_BAUD		*pfBaudrate;
	UART_SET_CFG		*pfConfig;
	UART_SET_IRQLEVEL	*pfIrqLevel;
	UART_LOOPBACK		*pfLookback;
	UART_WRITE			*pfWrite;
    UART_DMA_TX			*pfDmaTx;
	UART_READ			*pfRead;
    UART_DMA_RX			*pfDmaRx;
	UART_IS_TXEND		*pfIsTxEnd;
	UART_IS_TXREADY		*pfIsTxReady;
	UART_IS_RXREADY		*pfIsRxReady;
	UART_TXEND			*pfTxEnd;
    UART_RXEND			*pfRxEnd;
	UART_LOCK			*pfLock;
	UART_UNLOCK			*pfUnlock;
}UART_DRIVER, *PUART_DRIVER;


typedef struct _tagUart_Fifo
{
	int		 		nSize;
	volatile int 	nHead;
	volatile int 	nTail;
	char 			*pBuf;
}UART_FIFO, *PUART_FIFO;


/* UART Handle */
typedef struct _tagUart_Handle
{
	UART_DRIVER const	*pDriver;		/* H/W driver */

	volatile uint32_t	nError;			/* Error state */
	
	void				*pUART;			/* H/W UART */
	uint32_t			Irq;			/* Uart interrupt ID */
	int					nPort;

    int32_t             lparam;

    char                *pReadBuf;
    volatile int        nReadbyte;

    void				*pDmaTx;		/* DMA support */
	void				*pDmaRx;

	UART_FIFO			TxFifo;			/* Ring buffer */
	UART_FIFO			RxFifo;
	
	UART_CB_ONTX		*pfOnTx;		/* every character Tx complete callback */
	UART_CB_ONRX		*pfOnRx;		/* receive callback */
}UART_HANDLE, *PUART_HANDLE;


/******************************************************************************
 Global functions
******************************************************************************/

/******************************************************************************
 @Description 	: Serial interface intialization

 @param			: pHandle 	- Serial handle/ instance
				  pDriver 	- UART hardware driver pointer
				  nPort		- UART Port number
				  nBaud		- UART baudrate
				  pTxBuf	- Transmit software buffer pointer
				  nTxSize	- Transmit software buffer size
				  pRxBuf	- Receive software buffer pointer
				  nRxSize	- Receive software buffer size
 
 @revision		: 1.0.0
 
******************************************************************************/
int
SerialInit(
	PUART_HANDLE		pHandle,
	UART_DRIVER const 	*pDriver,
	uint8_t 			nPort,
	uint32_t 			nBaud );


void
SerialBuffer(
	PUART_HANDLE		pHandle,
	char 				*pTxBuf,
	uint32_t 			nTxSize,
	char 				*pRxBuf,
	uint32_t 			nRxSize );


void
SerialLinkDMA(
	PUART_HANDLE	pHandle,
	void			*pDmaTxHandle,
	void			*pDmaRxHandle );


/******************************************************************************
 @Description 	: Serial interface add callback

 @param			: pHandle 	- Serial handle/instance
				  pfOnTx	- Transmit done callback function pointer
				  pfOnRx	- Receive done callback function pointer
 
 @revision		: 1.0.0

******************************************************************************/
void
SerialAddCallback(
	PUART_HANDLE	pHandle,
	UART_CB_ONTX	*pfOnTx,
	UART_CB_ONRX	*pfOnRx );


/******************************************************************************
 @Description 	: Serial interface set baudrate

 @param			: pHandle 	- Serial handle/instance
				  nBaud		- Desired baudrate
 
 @revision		: 1.0.0

******************************************************************************/
int SerialBaudrate( PUART_HANDLE pHandle, uint32_t nBaud );


/******************************************************************************
 @Description 	: Serial interface configuration

 @param			: pHandle - Serial handle/instance
				  Databit - Data bit size selection
				  Parity  - Parity selection
				  Stopbit - Stop bit selection
				  
 @revision		: 1.0.0
 
******************************************************************************/
int
SerialConfig(
	UART_HANDLE const	*pHandle, 
	UART_CFG 			Databit, 
	UART_CFG 			Parity,
	UART_CFG 			Stopbit );

	
/******************************************************************************
 @Description 	: Serial interface write

 @param			: pHandle - Serial handle/ instance		
 
 @revision		: 1.0.0

******************************************************************************/
int SerialWrite( PUART_HANDLE pHandle, char Data );
int SerialWriteEx(
	PUART_HANDLE 	pHandle,
	void const		*pData,
    int             nSize );


/******************************************************************************
 @Description 	: Serial interface read a char

 @param			: pHandle - Serial handle/ instance		
 
 @return		: successfully read character
	
 @revision		: 1.0.0
 
******************************************************************************/
char SerialRead( PUART_HANDLE pHandle );
int SerialReadEx( PUART_HANDLE pHandle, char *pBuf, int nSize );

/******************************************************************************
 @Description 	: Serial interface check number of bytes

 @param			: pHandle - Serial handle/ instance		
 
 @return		: remaining bytes
	
 @revision		: 1.0.0
 
******************************************************************************/
int SerialRxBytes( UART_HANDLE const *pHandle );



/******************************************************************************
 @Description 	: Check serial interface is transmit empty

 @param			: pHandle - Serial handle/ instance	
 
 @revision		:
******************************************************************************/
BOOL SerialIsTxEmpty( UART_HANDLE *pHandle );


/******************************************************************************
 @Description 	: Clear transmit buffer to empty

 @param			: pHandle - Serial handle/ instance	
 
 @revision		:
******************************************************************************/
void SerialTxEmpty( UART_HANDLE *pHandle );


/******************************************************************************
 @Description 	: Clear Received buffer to empty

 @param			: pHandle - Serial handle/ instance	
 
 @revision		:
******************************************************************************/
void SerialRxEmpty( UART_HANDLE *pHandle );


/******************************************************************************
 @Description 	: Check serial interface is ready to transmit

 @param			: pHandle - Serial handle/ instance
 
 @return		: TRUE/FALSE
 
 @revision		:
******************************************************************************/
BOOL SerialIsTxReady( UART_HANDLE *pHandle );


/******************************************************************************
 @Description 	: Check serial interface received data ready to read

 @param			: pHandle - Serial handle/ instance
 
 @return		: TRUE/FALSE
 
 @revision		:
******************************************************************************/
BOOL SerialIsRxReady( UART_HANDLE const *pHandle );


/******************************************************************************
 @Description 	: UART hardware driver callback functions

 @param			: pHandle - Serial handle/ instance
 
 @revision		: 1.0.0
 
******************************************************************************/
void UartIsrTx( PUART_HANDLE pHandle );
void UartIsrRx( PUART_HANDLE pHandle );


#endif	/* __SERIAL_DOT_H__ */















