/*****************************************************************************
 @Project	:
 @File 		: Hal.c
 @Details  	: All Ports and peripherals configuration
 @Author	:
 @Hardware	:
 

 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   

******************************************************************************/
#include <Common.h>
#include "RTOS.h"


/*****************************************************************************
 Define
******************************************************************************/


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/
extern void OS_SysTickHandler( void ) __attribute__((weak));


/*****************************************************************************
 Local Variables
******************************************************************************/
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
    static StaticTask_t xTimerTCB;
    static StackType_t xTimerStack[200];
    static StaticTask_t xIdleTCB;
    static StackType_t xIldeStack[200];
#endif

/*****************************************************************************
 Implementation
******************************************************************************/
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
    void vApplicationGetTimerTaskMemory( StaticTask_t** ppxTimerTaskTCBBuffer,
                                         StackType_t** ppxTimerTaskStackBuffer,
                                         uint32_t* pulTimerTaskStackSize )
    {
        *ppxTimerTaskTCBBuffer = &xTimerTCB;
        *ppxTimerTaskStackBuffer = xTimerStack;
        *pulTimerTaskStackSize = 200;
    }


    void vApplicationGetIdleTaskMemory( StaticTask_t** ppxIdleTaskTCBBuffer,
                                        StackType_t** ppxIdleTaskStackBuffer,
                                        uint32_t* pulIdleTaskStackSize )
    {
        *ppxIdleTaskTCBBuffer = &xIdleTCB;
        *ppxIdleTaskStackBuffer = xIldeStack;
        *pulIdleTaskStackSize = 200;
    }
#endif

void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

    /* Force an assert. */
    configASSERT( (volatile void*)NULL );
}


void vApplicationStackOverflowHook( TaskHandle_t pxTask, char* pcTaskName )
{
    (void)pcTaskName;
    (void)pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */

    TRACE( "Stack overflow: %s\r\n", pcTaskName );
    /* Force an assert. */
    configASSERT( (volatile void*)NULL );
}


void vAssertCalled( uint32_t ulLine, const char* pcFile )
{
    volatile unsigned long ul = 0;

    (void)pcFile;
    (void)ulLine;

    TRACE( "Assert: %s %d\r\n", pcFile, ulLine );
    ASSERT( FALSE );
    taskENTER_CRITICAL( );
    {
        /* Set ul to a non-zero value using the debugger to step out of this
        function. */
        while( ul == 0 )
        {
            __NOP( );
        }
    }
    taskEXIT_CRITICAL( );
}


void vApplicationTickHook( void )
{
    OS_SysTickHandler( );
}


void vApplicationIdleHook( void )
{

}


/*-----------------------------------------------------------*/