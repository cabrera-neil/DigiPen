/*****************************************************************************
 @Project	: 
 @File 		: i2c.h
 @Details  	:              
 @Author	: lcgan
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/


#ifndef __I2C_DOT_H__
#define __I2C_DOT_H__

/*****************************************************************************
 Define
******************************************************************************/
#define I2C_STS_OK					0
#define I2C_STS_PORT_INVALID		-1


/*****************************************************************************
 Type definition
******************************************************************************/
typedef void I2C_CB_DONE( void );

typedef struct _tagI2c_Hook
{
	I2C_CB_DONE 			*pfDone;
	struct _tagI2c_Hook 	*pNext;
}I2C_HOOK, *PI2C_HOOK;


typedef struct _tagI2C_Handle
{
	void 				*pI2c;
	uint8_t				nSlaveAddr;
	uint8_t				Register;
	volatile uint8_t	*pData;
	uint8_t				nByte;
	volatile int		nTxCount;
	volatile int		nRxCount;
    volatile int		nReadCount;
	int					nClock;
	
	uint8_t				bRepeatStart    :1;
    uint8_t				bRepeatStartReq	:1;
    uint8_t				bWrite          :1;
    uint8_t				bNotEmpty		:1;
	uint8_t                             :4;

	PI2C_HOOK			pHeadHook;
}I2C_HANDLE, *PI2C_HANDLE;


/******************************************************************************
 Global functions
******************************************************************************/


/******************************************************************************
 @Description 	: Initialize I2c with parameters and callback

 @param			: nPort - 1 to 3
 
 @revision		: 1.0.0
 
******************************************************************************/
int I2cInit(
		PI2C_HANDLE 	pHandle,
		uint8_t 		nPort,
		uint32_t 		nBusSpeed );


/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void I2cSetRiseTimeMax( PI2C_HANDLE pHandle, int nRiseNanoSec );


/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void I2cWrite(
	PI2C_HANDLE 	pHandle,
	uint8_t 		nSlaveAddr,
	uint8_t 		Register,
	void const 		*pData,
	uint8_t 		nByte );


/******************************************************************************
 @Description 	:

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void I2cRead( 
	PI2C_HANDLE pHandle,
	uint8_t 	nSlaveAddr,
	uint8_t 	Register,
	void 		*pData,
	uint8_t 	nByte );


/******************************************************************************
 @Description 	:

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void
I2cAddHook(
	PI2C_HANDLE 		pHandle,
	PI2C_HOOK 			pHook,
	I2C_CB_DONE 		*pfDone );


/******************************************************************************
 @Description 	:

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
BOOL I2cIsDone( PI2C_HANDLE pHandle );


#endif /* __I2C_DOT_H__ */

