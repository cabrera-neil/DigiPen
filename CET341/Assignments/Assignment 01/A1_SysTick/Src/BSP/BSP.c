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


}



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






















