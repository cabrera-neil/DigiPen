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
#include "BSP.h"


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
void IRQInit( void )
{
    NVIC_SetPriority( EXTI4_IRQn, 0x09 );
    NVIC_SetPriority( EXTI15_10_IRQn, 0x09 );
    NVIC_EnableIRQ( EXTI4_IRQn );
    NVIC_EnableIRQ( EXTI15_10_IRQn );
}

/*****************************************************************************
 Implementation
******************************************************************************/
void EXTI0_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
}


void EXTI1_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
        UNUSE( irqStatus );
}


void EXTI2_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
        EXTI->PR = EXTI_PR_PR2;
}

void EXTI3_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
}

void EXTI4_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );

        /* Clear the Interrupt Bit */
        EXTI->PR = EXTI_PR_PR4;
        Navigation_SWitchIRQHandler( 4U );
}

void EXTI9_5_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
}

void EXTI15_10_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );

        /* Clear the Interrupt Bit */
        if( 0 != (irqStatus&EXTI_PR_PR12) )
        {
            EXTI->PR = EXTI_PR_PR12;
            Navigation_SWitchIRQHandler( 0U );
        }

        if( 0 != (irqStatus&EXTI_PR_PR13) )
        {
            EXTI->PR = EXTI_PR_PR13;
            Navigation_SWitchIRQHandler( 1U );
        }

        if( 0 != (irqStatus&EXTI_PR_PR14) )
        {
            EXTI->PR = EXTI_PR_PR14;
            Navigation_SWitchIRQHandler( 2U );
        }

        if( 0 != (irqStatus&EXTI_PR_PR15) )
        {
            EXTI->PR = EXTI_PR_PR15;
            Navigation_SWitchIRQHandler( 3U );
    }
}



/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Interrupt functions
******************************************************************************/






















