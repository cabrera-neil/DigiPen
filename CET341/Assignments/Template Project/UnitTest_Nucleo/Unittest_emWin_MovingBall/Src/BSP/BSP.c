/*****************************************************************************
 @Project	: 
 @File 		: BSP.c
 @Details  	:
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "BSP.h"
#include "Clock.h"


/*****************************************************************************
 Define
******************************************************************************/


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/


/*****************************************************************************
 Local Functions
******************************************************************************/


/*****************************************************************************
 Implementation
******************************************************************************/
void BSPInit( void )
{
	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
	
	/* Configure Flash prefetch and Instruction cache through ART accelerator */ 
	FLASH->ACR |= FLASH_ACR_ARTEN;

    /* Configure clock to maximum = 200MHz */
	ClockInit( 16U, 432U, 2U, 2U );
	
	/* Update SystemCoreClock */
	SystemCoreClockUpdate();
	
	/* Hardware abstraction layer initialization */
	PortInit();

#ifdef _DEBUG
    SEGGER_SYSVIEW_Conf();
#endif

}


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Local functions
******************************************************************************/
#ifdef _UART_TRACE
	static void DebugUartInit( void )
	{
		/* This USART2 is assigned for Command interpreter(shell) use */
		int res;

		NVIC_SetPriority( USART2_IRQn, 0x09 );

		res = SerialInit(
				&g_DebugSerialHandle,
				&STM32F722X_USART_DRV,
				2U,
				460800 );
		ASSERT( res == UART_STS_OK );

		SerialBuffer(
				&g_DebugSerialHandle,
				g_aUsart2TxBuf,
				sizeof(g_aUsart2TxBuf),
				g_aUsart2RxBuf,
				sizeof(g_aUsart2RxBuf) );

		res = SerialConfig(
				&g_DebugSerialHandle, 
				UART_BITS_8, 
				UART_NONE,
				UART_ONE );
		ASSERT( res == UART_STS_OK );
	}
#endif


/*****************************************************************************
 Interrupt functions
******************************************************************************/
void HardFault_Handler( void )
{
	/* Hardware errors, wrong configuration on hardware,
	clock failure will stop here */
	TRACE( "Hard fault\n" );
	ASSERT( FALSE );
	
#ifndef _DEBUG
	NVIC_SystemReset();
#endif
}






















