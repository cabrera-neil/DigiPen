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
                                         Answer for Question 8 and 9
  1.2     Neil Cabrera  2019-09-26       Updated for Assignment 03
                                         Implementation for Task Switching
******************************************************************************/

#include <stdint.h>
#include "Common.h"
#include "MyOSConfig.h"
#include "proj_def.h"
#include "myos.h"
#include "my_task.h"
#include "my_mem.h"
#include "Hal.h"

/*****************************************************************************
 Define
******************************************************************************/
#define PSP_OFFSET_WORD        16
#define PSP_IDLE_OFFSET_WORD   19

/* Comment to Disable the TRACE */
//#define DEBUG_MODE

/* Comment to Disable the 8a and Enable 8b */
//#define EightA   

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

static BOOL g_bLedLd3 = FALSE;
static BOOL g_bScope = FALSE;


/******************************************************************************
 @Description : MyOS initialization
 @param       : Nill
******************************************************************************/
uint32_t myOsInit()
{
  uint32_t ret_IdleTask;
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
  timer_freq = OS_TIME_SLICE_HZ; //Unit: Hz
  systick_ticks = (uint32_t) SystemCoreClock / timer_freq;
  SysTick_Config(systick_ticks);

  xTaskCreate(IdleTask, "T0", IDLE_STACK_SIZE, 0);
  return TRUE;
}


/******************************************************************************
 @Description : Free Allocated Memory
 @param       : pNewTCB: TCB
                pStack:  Stack
                TaskListNext: Task List Node
******************************************************************************/
void xTaskFree(TCB_t *pNewTCB, uint32_t *pStack, TaskList_t *TaskListNext)
{
  if( NULL != pNewTCB)
  {
    MyFree((void*)pNewTCB);
    pNewTCB = NULL;
  }
  
  if(NULL != pStack)
  {
    MyFree((void *)pStack);
    pStack = NULL;
  }
    
  if(NULL != TaskListNext)
  {
    MyFree((void *)TaskListNext);
    TaskListNext = NULL;
  }
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
  TCB_t *pNewTCB = NULL;
  TaskList_t *TaskListNext = NULL;
  uint32_t *pStack = NULL;
  uint32_t psp;
  uint32_t offset;
  uint32_t xReturn;

  pStack        = pMyMalloc(TaskStackDepth * sizeof(uint32_t));
  pNewTCB       = (TCB_t *) pMyMalloc( sizeof(TCB_t));
  TaskListNext  = (TaskList_t *)pMyMalloc( sizeof(TaskList_t));

  if( pStack != NULL && pNewTCB != NULL && TaskListNext != NULL)
  {   
    psp = pStack;
    psp = psp + TaskStackDepth*4 - PSP_OFFSET_WORD*4;

    offset = PSP_OFFSET_WORD - 2;
    offset = offset<<2;
    HW32_REG((psp+offset)) = (unsigned long) pTaskCode;

    offset = PSP_OFFSET_WORD - 1;
    offset = offset<<2;
    HW32_REG((psp+offset)) = 0x01000000;

    pNewTCB->PSP        = (uint32_t)psp;
    pNewTCB->pTaskCode  = (TaskFunction_t *) pTaskCode;
    pNewTCB->priority   = TaskPriority;
    strcpy(pNewTCB->pcTaskName,pTaskName);
    
    pNewTCB->StackDepth = TaskStackDepth;
    pNewTCB->TimeWakeup = 0;
    pNewTCB->bFloat     = FALSE;
    pNewTCB->bWakeUp    = TRUE;
    pNewTCB->state      = TASK_STATE_READY;
    pNewTCB->id         = ++gTaskIDGen;
   
    TaskListNext->pTCB = (TaskHandle_t)pNewTCB;
    TaskListNext->pNext = NULL;
    
    if(NULL == TaskListHead)
      TaskListHead = TaskListNext;
    else
    {
      TaskList_t* pCurrTaskList = (TaskList_t*)TaskListHead;

      while(pCurrTaskList->pNext!=NULL)
        pCurrTaskList = pCurrTaskList->pNext;

      pCurrTaskList->pNext = TaskListNext;
    }

    ++gSchedStatus.numTaskTotal;
    return pdPASS;
  }
  else
  {
    if(pNewTCB==NULL)
      free(pNewTCB);
   
    if(pStack==NULL)
      free(pStack);

    if(TaskListNext==NULL)
      free(TaskListNext);

    return pdFAIL;
  }
}

/******************************************************************************
@Description : Create the idle task
@param       : Nill
******************************************************************************/
uint32_t xTaskCreateIdle(void)
{
  TCB_t *pNewTCB;
  TaskList_t *TaskListNext = NULL;
  uint32_t *pStack = NULL;
  uint32_t psp;

  uint32_t offset;
  uint32_t xReturn;

  pNewTCB       = (TCB_t*)      malloc(sizeof(TCB_t));
  pStack        = (uint32_t*)   malloc(sizeof(uint32_t)*IDLE_STACK_SIZE);
  TaskListNext  = (TaskList_t*) malloc(sizeof(TaskList_t));  

  if(pNewTCB!=NULL && pStack!=NULL && TaskListNext!=NULL)
  {
    psp = pStack;
    psp = psp + IDLE_STACK_SIZE*4 - PSP_OFFSET_WORD*4;

    offset = PSP_OFFSET_WORD - 2;
    offset = offset<<2;
    HW32_REG((psp+offset)) = (unsigned long) IdleTask;

    offset = PSP_OFFSET_WORD - 1;
    offset = offset<<2;
    HW32_REG((psp+offset)) = 0x01000000;

    pNewTCB->PSP        = (uint32_t)psp;
    pNewTCB->bFloat     = FALSE;
    pNewTCB->id         = gTaskIDGen;
    pNewTCB->pTaskCode  = (TaskFunction_t *)IdleTask;   
    strcpy(pNewTCB->pcTaskName, "Idle");

    pNewTCB->StackDepth = IDLE_STACK_SIZE;
    pNewTCB->priority   = 0;
    pNewTCB->state      = TASK_STATE_READY;
    pNewTCB->TimeWakeup = 0;
    pNewTCB->bWakeUp    = TRUE;

    TaskListNext->pTCB  = (TaskHandle_t) pNewTCB;
    TaskListNext->pNext = NULL;

    if(TaskListHead==NULL)
    {
      TaskListHead = TaskListNext;
      TaskListCurr = TaskListHead;
    }
    else
    {
      TaskList_t* pCurrTaskList = (TaskList_t*)TaskListHead;

      while(pCurrTaskList->pNext!=NULL)
        pCurrTaskList = pCurrTaskList->pNext;

      pCurrTaskList->pNext = TaskListNext;
    }

    ++gSchedStatus.numTaskTotal;
    return pdPASS;
  }
  else
  {
    if(pNewTCB==NULL)
      free(pNewTCB);
   
    if(pStack==NULL)
      free(pStack);

    if(TaskListNext==NULL)
      free(TaskListNext);

    return pdFAIL;
  }
}


/******************************************************************************
 @Description : Task delay (or sleep)
 @param       : DelayTime: delay time, unit: ms
******************************************************************************/
uint32_t vTaskDelay(uint32_t DelayTime)
{
  uint32_t DelayInterval;
  DelayInterval = DelayTime * OS_TIME_SLICE_HZ;
  DelayInterval = (uint32_t) DelayInterval/1000;

  __ASM volatile ("SVC #0x01");
}


/******************************************************************************
 @Description : Trigger the schedule running
 @param       : Nil
******************************************************************************/
void SchedulerStart(void)
{
  TaskListCurr = TaskListHead;

  NVIC_SetPriority(PendSV_IRQn, 0xFF);
  __set_CONTROL(0x3);
  __ISB();

  gSchedStatus.flgSchedRun = TRUE;

  ((TCB_t*)TaskListCurr->pTCB)->state = TASK_STATE_RUN;
  ((TCB_t*)TaskListCurr->pTCB)->pTaskCode(NULL);
}


/******************************************************************************
 @Description : The scheduler kernel, triggered by the SysTick
 @param       : Nill
******************************************************************************/
void SchedulerCore(void)
{
  /************************************************
  * To do: 
  * Step 1: Scheduling algorithm: decide which task 
  * is the next task
  * The switching-out task TCB is stored at:
  *   gSchedStatus.pTcbCurr;
  * The switching-in task TCB is stored at:
  *   gSchedStatus.pTcbNext;
  ************************************************/
  
  TCB_t *TcbCurr;
  TCB_t *TcbSelect;
  uint32_t TaskIdCurr;
  BOOL bFindNext;
  BOOL bIdleOnly;
  uint8_t i;

  TcbCurr = (TCB_t *)TaskListCurr->pTCB;
  TaskIdCurr = TcbCurr->id;
  bFindNext = FALSE;
  bIdleOnly = FALSE;

  for(i = 0; i< gSchedStatus.numTaskTotal; ++i)
  {
    /* Check if End of the Task List */
    if(TaskListCurr->pNext!=NULL)
      TaskListCurr = TaskListCurr->pNext;
    else
      TaskListCurr = TaskListHead;

    TcbSelect = (TCB_t *)TaskListCurr->pTCB;
    switch(TcbSelect->state)
    {      
      /* if task is in READY */         
      case TASK_STATE_READY:  
        bFindNext = TRUE;
        break;

      /* if task is in RUN */         
      case TASK_STATE_RUN:  
        if((TASK_ID_IDLE == TcbSelect->id) && (TASK_ID_IDLE == TcbCurr->id))
        {
          bFindNext = TRUE;
          bIdleOnly = TRUE;
        }
        break;        

      /* if task is in BLOCK */         
      case TASK_STATE_BLOCK:  
        if(myOsTime.time_ms >= TcbSelect->TimeWakeup)
            bFindNext = TRUE;
        break;
                             
      /* if task is in SUSPEND */         
      case TASK_STATE_SUSPEND:  
        break;
      
    }// end of switch

    if(bFindNext)
        break;
  }
  
  /* Check if it is Idle Task */
  if(TcbCurr->state != TASK_STATE_BLOCK)
    TcbCurr->state = TASK_STATE_READY;
  
  TcbSelect->state = TASK_STATE_RUN;

  gSchedStatus.pTcbCurr = TcbCurr;
  gSchedStatus.pTcbNext = TcbSelect;

  // Trigger the Switch using PendSV
  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

/******************************************************************************
 @Description : The idle task implementation
 @param       : pvParameters: the possible parameters to a task;
                              usually not used.
******************************************************************************/
static void IdleTask(void *pvParameters)
{
  for(;;)
  {
    #ifdef DEBUG_MODE
    TRACE( "Idle\r\n" );
    #endif
    __ASM volatile ("WFI");   // Sleep, until the next interrupt.
  }
}


/*****************************************************************************
 Interrupt functions
******************************************************************************/

/******************************************************************************
 @Description : pendSV, triggered by the ScheduleCore to set PENDSV Flag
 @param       : Nil
******************************************************************************/
void PendSV_Handler(void)
{
  #ifndef  EightA
  LED_LD1_SET(g_bScope=!g_bScope);
  #endif

  __ASM volatile ("MRS R0, PSP");         // get current process stack MRS: load from core processor register
  __ASM volatile ("STMDB R0!, {R4-R11}"); //save R4 to R11

  __ASM volatile ("LDR R1, =gSchedStatus");
  __ASM volatile ("LDR R2, [R1]");

  __ASM volatile ("TST LR, #0x10");       //test EXC_RETURN bit 4
  __ASM volatile ("ITTE EQ");             //if zero (which mean
  __ASM volatile ("SUBEQ R0, #0");
  __ASM volatile ("MOVEQ R3, #1");
  __ASM volatile ("MOVNE R3, #0");
  __ASM volatile ("STR R0, [R2]");        // save task stack value TCB->PSP
  __ASM volatile ("STR R3, [R2, #4]");    //save float flag in TCB->bFloat

  __ASM volatile ("Ldr r2, [r1, 4]");     // get gSchedStatus 2st element data, the next TCB address
  __ASM volatile ("Ldr r0, [r2]");
  __ASM volatile ("LDR R3, [R2, #4]");    

  __ASM volatile ("MVN R1, #0X10");
  __ASM volatile ("TST R3, #0X01");
  __ASM volatile ("ITE EQ");
  __ASM volatile ("ORREQ LR, #0X10");
  __ASM volatile ("ANDNE LR, R1");

  __ASM volatile ("LDMIA R0!, {R4-R11}"); //load r4 to r11 from task stack (8 register)
  __ASM volatile ("MSR PSP, R0");         //Set PSP to next task

  #ifdef  EightA
  if(g_bScope)
  {
    LED_LD1_OFF();
    g_bScope = FALSE;
  }
  #endif

  __ASM volatile ("BX LR");
}

/******************************************************************************
 @Description : SVC handler
 @param       : Nil
******************************************************************************/
void SVC_Handler(void)
{
  __ASM volatile ("TST LR, #4");
  __ASM volatile ("ITE EQ");
  __ASM volatile ("MRSEQ R0, MSP");
  __ASM volatile ("MRSNE R0, PSP");
  __ASM volatile ("B SVC_Handler_C");
}

void SVC_Handler_C(unsigned int * svc_args)
{
  uint8_t svc_number;
  uint32_t stacked_r0, stacked_r1, stacked_r2, stacked_r3;
  TCB_t *TCBCurr;

  svc_number = ((char*) svc_args[6])[-2];
  stacked_r0 =  svc_args[0];
  stacked_r1 =  svc_args[1];
  stacked_r2 =  svc_args[2];
  stacked_r3 =  svc_args[3];

  if(SVC_OS_DELAY==svc_number)
  {
    TCBCurr = TaskListCurr->pTCB;
    TCBCurr->state = TASK_STATE_BLOCK;
    TCBCurr->TimeWakeup = myOsTime.time_ms + stacked_r0;
  }
  else if(SVC_OS_SUSPEND==svc_number)
  {
    TCBCurr = TaskListCurr->pTCB;
    TCBCurr->state = TASK_STATE_SUSPEND;
    TCBCurr->bWakeUp = FALSE;
  }
  else { }
  
  /* Call the SchedulerCore to trigger Switching of Task */
  SchedulerCore();
}

/******************************************************************************
 @Description : SysTick handler
 @param       : Nil
******************************************************************************/
void SysTick_Handler( void )
{
    #ifdef  EightA
    if(!g_bScope)
    {
      LED_LD1_ON();
      g_bScope = TRUE;
    }
    #endif

    myOsTime.time_ms ++;
    if( 0 != g_nSysTick )
    {
        g_nSysTick--;

        if( 0 == g_nSysTick )
        {
            g_nSysTick = SYS_TICK_MS;
            myOsTime.time_slice ++;

            if (FALSE != gSchedStatus.flgSchedRun)
              SchedulerCore();
        }
    }
}
