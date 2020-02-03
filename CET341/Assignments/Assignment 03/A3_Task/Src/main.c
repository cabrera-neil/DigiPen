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
  1.2     Neil Cabrera  2019-09-26       Updated for Assignment 03
                                         Implementation for Task Switching
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

static BOOL g_bLedLd1 = FALSE;
static BOOL g_bLedLd2 = FALSE;
static BOOL g_bLedLd3 = FALSE;

/*****************************************************************************
 Local functions
******************************************************************************/
/**********************************************************
 Callback functions
**********************************************************/
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
  uint32_t ret_Task03;

  BSPInit();

  ret_OsInit = myOsInit();
  ASSERT(TRUE==ret_OsInit);

  ret_Task01 = xTaskCreate(Task01, "T01", TASK01_STACK_SIZE, TASK_PRIORITY_LEVEL_4); ASSERT(TRUE==ret_Task01);
  ret_Task02 = xTaskCreate(Task02, "T02", TASK02_STACK_SIZE, TASK_PRIORITY_LEVEL_4); ASSERT(TRUE==ret_Task02);

  SchedulerStart();

  for(;;)
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
    TRACE( "T1 Producer \r\n" );
    #endif

    LED_LD3_SET(g_bLedLd3 = !g_bLedLd3);

    WaitTime = 1000;
    vTaskDelay( WaitTime );
  }
}

static void Task02( void *pvParameters )
{
  BOOL bToggle = FALSE;
  uint32_t WaitTime;

  for(;;)
  {
    #ifdef DEBUG_MODE
    TRACE( "T2 Consumer \r\n" );
    #endif

    LED_LD2_SET(g_bLedLd2=!g_bLedLd2);

    WaitTime = 2000;
    vTaskDelay( WaitTime );
  }
}


/*****************************************************************************
 Callback functions
******************************************************************************/


