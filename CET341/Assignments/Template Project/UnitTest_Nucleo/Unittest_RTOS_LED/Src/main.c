/*****************************************************************************
 @Project	:
 @File 		: main.c
 @Details  	: Main entry
 @Author	: lcgan
 @Hardware	: STM32
 

 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   

******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "BSP.h"

#include "RTOS.h"

/* NOTE: Please follows code style provided. All tabs is 4 space */

/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS 500 /* Software Timer with 500 ms */

#define LED1_TASK_STACK_SIZE    120
#define LED2_TASK_STACK_SIZE    120


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Const Local Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int g_nSysTick = SYS_TICK_MS;
static volatile BOOL g_bSysTickReady = FALSE;
static int g_nCount = 0;


static StaticTask_t         xLed1TCB;
static StackType_t          xLed1Stack[LED1_TASK_STACK_SIZE];

static StaticTask_t         xLed2TCB;
static StackType_t          xLed2Stack[LED2_TASK_STACK_SIZE];


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Callback functions
******************************************************************************/



/*****************************************************************************
 RTOS Tasks
******************************************************************************/
static void Led1Task( void *pvParameters );
static void Led2Task( void *pvParameters );


/*****************************************************************************
 Implementation
******************************************************************************/
int main( void )
{
    BSPInit();

    TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock %dHz\r\n", SystemCoreClock );

    /* OS Tasks Creation */

    /* Led blinking task */
	xTaskCreateStatic(
		Led1Task,
		"Led1Task",
		LED1_TASK_STACK_SIZE,
		NULL,
		2,
		xLed1Stack,
        &xLed1TCB );	

	xTaskCreateStatic(
		Led2Task,
		"Led2Task",
		LED2_TASK_STACK_SIZE,
		NULL,
		3,
		xLed2Stack,
        &xLed2TCB );	


   /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* OS failed will reached here */
    while( 1 ){}	
}


static void Led1Task( void *pvParameters )
{
	BOOL toggle = FALSE;
    for(;;)
    {
		TRACE( "LED 1 task is running\r\n" );
        toggle = !toggle;
        LED_LD1_SET(toggle);
        vTaskDelay( 200 );
    }
}


static void Led2Task( void *pvParameters )
{
	BOOL toggle = FALSE;
    for(;;)
    {
		TRACE( "LED 2 task is running\r\n" );
        toggle = !toggle;
        LED_LD2_SET(toggle);
        vTaskDelay( 300 );
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
/* WARNING: 
 This function is called from RTOS.c from RTOS Application tick.
 DO NOT perform any heavy processing here, because it will blocking
 RTOS from running!
*/
void OS_SysTickHandler( void )
{
    /* NOTE:
    It is more efficient to compare to 0 for Cortex M
    */

    /* Provide system tick with a specified period
    decided by macro SYS_TICK_MS */
    if( 0 != g_nSysTick )
    {
        g_nSysTick--;

        if( 0 == g_nSysTick )
        {
            g_nSysTick = SYS_TICK_MS;
            g_bSysTickReady = TRUE;
        }
    }
}