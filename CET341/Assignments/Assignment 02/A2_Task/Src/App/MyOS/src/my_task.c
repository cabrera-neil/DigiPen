/*****************************************************************************
 @Project    : CET341 Assignment
 @File       : my_task.c
 @Details    : Task management kernel
 @Author     : Liang Tang
 @Hardware   : STM32F46 only
 --------------------------------------------------------------------------
 @Revision   :
  Ver      Author       Date             Changes
 --------------------------------------------------------------------------
  1.0     Liang Tang    2019-09-19       Initial Release
  1.1     Neil Cabrera  2019-09-22       Updated for Assignment 02
******************************************************************************/

#include <stdint.h>
#include "Common.h"
#include "MyOSConfig.h"
#include "proj_def.h"
#include "myos.h"
#include "my_task.h"
#include "Hal.h"

/*****************************************************************************
 Define
******************************************************************************/

//#define PSP_OFFSET_WORD    19
#define PSP_OFFSET_WORD        16
#define PSP_IDLE_OFFSET_WORD   19
#define __ASSIGN_TODO


/*****************************************************************************
 Cross-file Global Variables
******************************************************************************/
volatile myOsTime_t myOsTime;

/*****************************************************************************
 Static Global Variables
******************************************************************************/
static volatile uint32_t      g_nSysTick = SYS_TICK_MS;
static volatile SchedStatus_t gSchedStatus;
static volatile TaskList_t   *TaskListHead = NULL;//Task list: head node
static volatile TaskList_t   *TaskListCurr = NULL;//Task list: current node

static uint32_t               gTaskIDGen = TASK_ID_IDLE;

#ifdef __ASSIGN_TODO
static BOOL g_bLedLd3 = FALSE;
#endif


/******************************************************************************
 @Description : MyOS initialization
 @param       : Nill
******************************************************************************/
uint32_t myOsInit()
{
  uint32_t  ;
  uint32_t timer_freq;
  uint32_t systick_ticks;

  gSchedStatus.flgSchedRun    = FALSE;
  gSchedStatus.numTaskReady   = 0;
  gSchedStatus.numTaskRun     = 0;
  gSchedStatus.numTaskBlock   = 0;
  gSchedStatus.numTaskSuspend = 0;
  gSchedStatus.numTaskTotal   = 0;

  gSchedStatus.pTaskRun        = NULL;
  gSchedStatus.pTaskReadyTop   = NULL;
  gSchedStatus.pTaskBlockTop   = NULL;
  gSchedStatus.pTaskSuspendTop = NULL;

  myOsTime.time_ms = 0;
  myOsTime.time_slice = 0;


  /* Generate interrupt each 1 ms as system tick */
  timer_freq = OS_TIME_SLICE_HZ;//Unit: Hz
  systick_ticks = (uint32_t) SystemCoreClock / timer_freq;
  SysTick_Config(systick_ticks);

  //return(ret_IdleTask); // Seems Pretty Useless
  return TRUE;
}


/******************************************************************************
 @Description : Create the user specified task
 @param       : pTaskCode     : the task execution function;
                pTaskName     : an ASCII string for the task name;
                TaskStackDepth: the stack size for this task;
                TaskPriority  : the priority for this task;
******************************************************************************/
uint32_t xTaskCreate( TaskFunction_t pTaskCode,
                      const char * const pTaskName,
                      const uint32_t TaskStackDepth,
                      uint32_t TaskPriority)
{
  TCB_t *pNewTCB;
  TaskList_t *TaskListNext = NULL;//Task list: next node
  uint32_t xReturn;

/************************************************
* To do: 
* This function create tasks:
* 1) Construct the content for pNewTCB;
* 2) Add the created TCB into the TaskListNext;
* 3) Insert TaskListNext to TaskListCurr link list;
************************************************/
  /* Step 1 */
  pNewTCB             = (TCB_t*) malloc(sizeof(TCB_t));
  pNewTCB->pTaskCode  = pTaskCode;
  pNewTCB->StackDepth = TaskStackDepth;
  pNewTCB->priority   = TaskPriority;
  strcpy(pNewTCB->pcTaskName, pTaskName);

  /* Step 2 */
  TaskListNext        = (TaskList_t*) malloc(sizeof(TaskList_t));
  TaskListNext->pTCB  = (TaskHandle_t) pNewTCB;
  TaskListNext->pNext = NULL;

  /* Step 3 */
  if(TaskListHead==NULL)
  {
    TaskListHead = TaskListNext;

    /* Set Current Task to First Task */
    TaskListCurr = TaskListHead;
  }
  else
  {
    TaskList_t* pCurrTaskList = TaskListHead;
    while(pCurrTaskList->pNext!=NULL)
      pCurrTaskList = pCurrTaskList->pNext;
    
    pCurrTaskList->pNext = TaskListNext;
  }
  
  return pdPASS;
}


/******************************************************************************
 @Description : Task delay (or sleep)
 @param       : DelayTime: delay time, unit: ms

******************************************************************************/
uint32_t vTaskDelay(uint32_t DelayTime)
{
/************************************************
* To do: 
* Tentatively, use the busy-waiting method to
* wait.
* This method is a blocking method. We will update
* it later.
************************************************/
  while(DelayTime--);
}


/******************************************************************************
 @Description : Trigger the schedule running
 @param       : Nill
******************************************************************************/
void SchedulerStart(void)
{
/************************************************
* To do: 
* Call the Task01() function here!
************************************************/
  if(!gSchedStatus.flgSchedRun)
    gSchedStatus.flgSchedRun = TRUE;

  (*((TCB_t*) TaskListCurr->pTCB)->pTaskCode)(NULL);
}


/******************************************************************************
 @Description : The scheduler kernel, triggered by the SysTick
 @param       : Nill
******************************************************************************/
void SchedulerCore(void)
{
/************************************************
* To do: 
* Call the Task02() function here!
************************************************/
  (*((TCB_t*) TaskListCurr->pTCB)->pTaskCode)(NULL);
}


/******************************************************************************
 @Description : The idle task implementation
 @param       : pvParameters: the possible parameters to a task;
                              usually not used.
******************************************************************************/
static void IdleTask(void *pvParameters)
{
  uint32_t i;

  for(;;)
  {
    __ASM volatile ("WFI");   // Sleep, until the next interrupt.
  }
}


/*****************************************************************************
 Interrupt functions
******************************************************************************/
/******************************************************************************
 @Description : SysTick handler
 @param       : Nil
******************************************************************************/
void SysTick_Handler( void )
{
    myOsTime.time_ms ++;
    if( 0 != g_nSysTick )
    {
        g_nSysTick--;

        if( 0 == g_nSysTick )
        {
            g_nSysTick = SYS_TICK_MS;
            myOsTime.time_slice ++;

            /* Toggle the LED3 */
            LED_LD3_SET(g_bLedLd3=!g_bLedLd3);

            /* Check if the Scheduler can set to Run */
            if (FALSE != gSchedStatus.flgSchedRun)
            {
              /* There are only 2 task list nodes available
                 keep switching back and forth between the 2 tasks */
              if(TaskListCurr->pNext!=NULL)
                TaskListCurr = TaskListCurr->pNext;
              else
                TaskListCurr = TaskListHead;
              
              /* This Function will call Task 2 */
              SchedulerCore();
            }
        }
    }
}
