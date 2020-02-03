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
#define TASK_STACK_SIZE    1000

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


static StaticTask_t         xTCB1;
static StackType_t          xStack1[TASK_STACK_SIZE];

static StaticTask_t         xTCB2;
static StackType_t          xStack2[TASK_STACK_SIZE];


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Callback functions
******************************************************************************/



/*****************************************************************************
 RTOS Tasks
******************************************************************************/
static void Task1( void *pvParameters );
static void Task2( void *pvParameters );


/*****************************************************************************
 Implementation
******************************************************************************/
int main( void )
{
    BSPInit();

    TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock 216 MHz\r\n" );

    /* OS Tasks Creation */
        

    /* Led blinking task */
	xTaskCreateStatic(
		Task1,
		"Task1",
		TASK_STACK_SIZE,
		NULL,
		1,
		xStack1,
        &xTCB1 );	

	xTaskCreateStatic(
		Task2,
		"Task2",
		TASK_STACK_SIZE,
		NULL,
		1,
		xStack2,
        &xTCB2 );	


   /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* OS failed will reached here */
    while( 1 ){}	
}


static void Task1( void *pvParameters )
{
    for(;;)
    {
	TRACE( "Task 1 is running\r\n" );
        vTaskDelay( 200 );
    }
}


static void Task2( void *pvParameters )
{
    for(;;)
    {
	TRACE( "Task 2 is running\r\n" );
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