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
static BOOL g_bLED1 = FALSE;
static BOOL g_bLED2 = FALSE;
static BOOL g_bLED3 = FALSE;

static StaticTask_t         xTCB1;
static StackType_t          xStack1[TASK_STACK_SIZE];

static StaticTask_t         xTCB2;
static StackType_t          xStack2[TASK_STACK_SIZE];

static StaticTask_t         xTCB3;
static StackType_t          xStack3[TASK_STACK_SIZE];

/* Define an enumerated type used to identify the source of the data. */
typedef enum
{
  eSender1,
  eSender2
} DataSource_t;

/* Define the structure type that will be passed on the queue. */
typedef struct
{
  uint8_t ucValue;
  DataSource_t eDataSource;
} Data_t;

/* Declare two variables of type Data_t that will be passed on the queue. */
static Data_t xStructsToSend[ 2 ] =
{
  { 100, eSender1 }, /* Used by Sender1. */
  { 200, eSender2 } /* Used by Sender2. */
};

static QueueHandle_t xQueue;

/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Callback functions
******************************************************************************/



/*****************************************************************************
 RTOS Tasks
******************************************************************************/
static void vProducerTask( void *pvParameters );
static void vConsumerTask( void *pvParameters );

/*****************************************************************************
 Implementation
******************************************************************************/
int main( void )
{
    BSPInit();

    TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock 216 MHz\r\n" );

    /* OS Tasks Creation */
    // Not Needed as the vTaskStartScheduler will create the Idle Task

    /* The queue is created to hold a maximum of 3 structures of type Data_t. */
    xQueue = xQueueCreate( 3, sizeof( Data_t ) );
    if( xQueue != NULL )
    {
      /* Create two instances of the task that will write to the queue. The
      parameter is used to pass the structure that the task will write to the
      queue, so one task will continuously send xStructsToSend[ 0 ] to the queue
      while the other task will continuously send xStructsToSend[ 1 ]. Both
      tasks are created at priority 2, which is above the priority of the receiver. */
      xTaskCreateStatic( vProducerTask, "Producer1", 1000, &( xStructsToSend[ 0 ] ), 2, xStack1, &xTCB1 );
      xTaskCreateStatic( vProducerTask, "Producer2", 1000, &( xStructsToSend[ 1 ] ), 2, xStack2, &xTCB2 );

      /* Create the task that will read from the queue. The task is created with
      priority 1, so below the priority of the sender tasks. */
      xTaskCreateStatic( vConsumerTask, "Consumer", 1000, NULL, 1, xStack3, &xTCB3 );

      /* Start the scheduler so the created tasks start executing. */
      vTaskStartScheduler();
    }
    else
    {
      /* The queue could not be created. */
    }
    
    /* If all is well then main() will never reach here as the scheduler will
    now be running the tasks. If main() does reach here then it is likely that
    there was insufficient heap memory available for the idle task to be created.
    Chapter 2 provides more information on heap memory management. */
    for( ;; );
}


static void vProducerTask( void *pvParameters )
{
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 );
  /* As per most tasks, this task is implemented within an infinite loop. */
  for( ;; )
  {
    /* Send to the queue.
    The second parameter is the address of the structure being sent. The
    address is passed in as the task parameter so pvParameters is used
    directly.
    The third parameter is the Block time - the time the task should be kept
    in the Blocked state to wait for space to become available on the queue
    if the queue is already full. A block time is specified because the
    sending tasks have a higher priority than the receiving task so the queue
    is expected to become full. The receiving task will remove items from
    the queue when both sending tasks are in the Blocked state. */
    xStatus = xQueueSendToBack( xQueue, pvParameters, xTicksToWait );
    //vTaskDelay(200);

    if( xStatus != pdPASS )
    {
      /* The send operation could not complete, even after waiting for 100ms.
      This must be an error as the receiving task should make space in the
      queue as soon as both sending tasks are in the Blocked state. */
      TRACE( "Could not send to the queue.\r\n" );
    }
  }
}

static void vConsumerTask( void *pvParameters )
{
  /* Declare the structure that will hold the values received from the queue. */
  Data_t xReceivedStructure;
  BaseType_t xStatus;
  /* This task is also defined within an infinite loop. */
  for( ;; )
  {
    /* Because it has the lowest priority this task will only run when the
    sending tasks are in the Blocked state. The sending tasks will only enter
    the Blocked state when the queue is full so this task always expects the
    number of items in the queue to be equal to the queue length, which is 3 in
    this case. */
    if( uxQueueMessagesWaiting( xQueue ) != 3 )
    {
      TRACE( "Queue should have been full!\r\n" );
    }
    /* Receive from the queue.
    The second parameter is the buffer into which the received data will be
    placed. In this case the buffer is simply the address of a variable that
    has the required size to hold the received structure.
    The last parameter is the block time - the maximum amount of time that the
    task will remain in the Blocked state to wait for data to be available
    if the queue is already empty. In this case a block time is not necessary
    because this task will only run when the queue is full. */
    xStatus = xQueueReceive( xQueue, &xReceivedStructure, 0 );
    if( xStatus == pdPASS )
    {
      char buffer[50] = {0};

      /* Data was successfully received from the queue, print out the received
      value and the source of the value. */
      if( xReceivedStructure.eDataSource == eSender1 )
      {
        TRACE( "From Producer 1...\r\n" );
        xStructsToSend[0].ucValue++;
      }
      else
      {
        TRACE( "From Producer 2...\r\n" );
        xStructsToSend[1].ucValue++;
      }
      
      //vTaskDelay(200);

    }
    else
    {
      /* Nothing was received from the queue. This must be an error as this
      task should only run when the queue is full. */
      TRACE( "Could not receive from the queue.\r\n" );
    }
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