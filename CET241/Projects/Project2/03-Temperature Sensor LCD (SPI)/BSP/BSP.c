/*****************************************************************************
 @Project	: 
 @File 		: BSP.c
 @Details :
 @Author	: 
 @Hardware: 
   
******************************************************************************/
#include "Common.h"
#include "Hal.h"
#include "BSP.h"


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






















