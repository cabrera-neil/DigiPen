/*****************************************************************************
 @Project    : CET341 Assignment
 @File       : main.c
 @Details    : Main entry
 @Author     : Liang Tang
 @Hardware   : STM32F46 only
 --------------------------------------------------------------------------
 @Revision   :
  Ver      Author       Date             Changes
 --------------------------------------------------------------------------
  1.0     Liang Tang    2019-09-19       Initial Release
  1.1     Neil Cabrera  2019-09-22       Updated for Assignment 02
                                         Answer for Question 8 and 9
******************************************************************************/
#include "Common.h"
#include "proj_def.h"
#include "MyOSConfig.h"
#include <string.h>
#include "myos.h"
#include "my_task.h"
#include "Hal.h"
#include "BSP.h"
#include "Timer.h"

/*****************************************************************************
 Define
******************************************************************************/
#define TIMER1_ID              1    /*Timer 1 ID*/
#define TIMER1_FREQ            2    /*Timer 1 Frequency */
#define TIMER2_ID              2    /*Timer 2 ID*/
#define TIMER2_FREQ            5    /*Timer 2 Frequency */

#define DEBUG_MODE                  /* Comment to Disable the TRACE */

/**********************************************************
 Task stack size (unit: byte)
**********************************************************/
#define TASK01_STACK_SIZE       512
#define TASK02_STACK_SIZE       512


/*****************************************************************************
 Static Global Variables
******************************************************************************/
static volatile uint32_t g_nSysTick = SYS_TICK_MS; /* Tick count*/
BOOL                     g_toggle   = FALSE;       /* Toggle*/

static TIMER_HANDLE g_Timer1Handle; /* This is timer 1 handle */
static TIMER_HOOK   g_TImer1Hook1;  /* This is hook 1 to timer 1 */

static TIMER_HANDLE g_Timer2Handle; /* This is timer 2 handle */
static TIMER_HOOK   g_TImer2Hook1;  /* This is hook 1 to timer 2 */

static BOOL g_bLedLd1 = FALSE;
static BOOL g_bLedLd2 = FALSE;


/*****************************************************************************
 Local functions
******************************************************************************/
/**********************************************************
 Callback functions
**********************************************************/
static void main_cbTimer1Hook1( void );
static void main_cbTimer2Hook1( void );


/**********************************************************
 RTOS Tasks
**********************************************************/
static void Task01( void *pvParameters );
static void Task02( void *pvParameters );


/*****************************************************************************
 Implementation
******************************************************************************/
int main( void )
{
  uint32_t systick_ticks;
  uint32_t systick_freq;   /* SysTick Frequency, Unit: Hz*/
  uint32_t timer_id;
  uint32_t timer_freq;
  uint32_t ret_OsInit;
  uint32_t ret_Task01;
  uint32_t ret_Task02;

  BSPInit();

  timer_id   = TIMER1_ID;
  timer_freq = TIMER1_FREQ;
  TimerInit( &g_Timer1Handle, timer_id, timer_freq );

  /* LED1 toggle function hooks to Timer 1 */
  TimerAddHook( &g_Timer1Handle, &g_TImer1Hook1, main_cbTimer1Hook1 );
  TimerStart( &g_Timer1Handle );

  timer_id   = TIMER2_ID;
  timer_freq = TIMER2_FREQ;
  TimerInit( &g_Timer2Handle, timer_id, timer_freq );

  /* LED2 toggle function hooks to Timer 2 */
  TimerAddHook( &g_Timer2Handle, &g_TImer2Hook1, main_cbTimer2Hook1 );
  TimerStart( &g_Timer2Handle );

  ret_OsInit = myOsInit();
  ASSERT(TRUE==ret_OsInit);

  ret_Task01 = xTaskCreate(Task01, "T01_Producer", TASK01_STACK_SIZE, TASK_PRIORITY_LEVEL_4); ASSERT(TRUE==ret_Task01);
  ret_Task02 = xTaskCreate(Task02, "T02_Consumer", TASK02_STACK_SIZE, TASK_PRIORITY_LEVEL_4); ASSERT(TRUE==ret_Task02);

  /* This will call Task 01,
     SysTick will then call Task 02 */
  SchedulerStart();

  while( 1 )
  {
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
  }
}



/*****************************************************************************
 Task implementation functions
******************************************************************************/
static void Task01( void *pvParameters )
{
  BOOL bToggle = FALSE;
  uint32_t WaitTime;

  for(;;)
  {
    #ifdef DEBUG_MODE
    TRACE( "T01_Producer task is running\r\n" );
    #endif

    WaitTime = 400;
    vTaskDelay( WaitTime );

    /* Break the Loop for Now
       otherwise the SysTick Interrupt will be stuck forever */
    return;
  }
}

static void Task02( void *pvParameters )
{
  BOOL bToggle = FALSE;
  uint32_t WaitTime;

  for(;;)
  {
    #ifdef DEBUG_MODE
    TRACE( "T02_Consumer task is running\r\n" );
    #endif

    WaitTime = 600;
    vTaskDelay( WaitTime );

    /* Break the Loop for Now
       otherwise the SysTick Interrupt will be stuck forever */
    return;
  }
}


/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbTimer1Hook1( void )
{
/************************************************
* To do: 
* This function can be called by the Timer 1
* interrupt, if your setting is correct.
* Note:
* 1) this function is a Callback function, which
* is still in ISR, thus, its execution must be fast;
* 2) this function is provided to users, so that 
* users can use the interrupt and do something.
* The real raw-format of the ISR is not provided
* to users for safety reason;
************************************************/

  // set some flags here only
  // cannot be heavy logic
  // the update functions can be handle elsewhere
  LED_LD1_SET(g_bLedLd1=!g_bLedLd1);
}

static void main_cbTimer2Hook1( void )
{
/************************************************
* To do: 
* This function can be called by the Timer 1
* interrupt, if your setting is correct.
* Note:
* 1) this function is a Callback function, which
* is still in ISR, thus, its execution must be fast;
* 2) this function is provided to users, so that 
* users can use the interrupt and do something.
* The real raw-format of the ISR is not provided
* to users for safety reason;
************************************************/

  // set some flags here only
  // cannot be heavy logic
  // the update functions can be handle elsewhere
  LED_LD2_SET(g_bLedLd2=!g_bLedLd2);
}



