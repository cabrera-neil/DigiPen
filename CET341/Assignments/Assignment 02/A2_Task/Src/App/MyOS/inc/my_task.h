/*****************************************************************************
 @Project    :
 @File       : task.h
 @Details    :  
 @Author     :  
 @Hardware   :  
 

 --------------------------------------------------------------------------
 @Revision   :
  Ver      Author        Date            Changes
 --------------------------------------------------------------------------
  1.0      Name         XXXX-XX-XX       Initial Release

******************************************************************************/


#ifndef MY_TASK_H
#define MY_TASK_H


/*****************************************************************************
 Define
******************************************************************************/

#define TASK_STATE_READY                0 //Task is in a wating queue to be run
#define TASK_STATE_RUN                  1 //Task is running
#define TASK_STATE_BLOCK                2 //Task is not in the waiting queue, 
                                          //it will move to READY after timeout
#define TASK_STATE_SUSPEND              3 //Task is not in the waiting queue,
                                          //it will move to READY after calling


#define TASK_ID_IDLE                    0 //Only the Idle task's ID is 0

#define OS_TIME_SLICE_HZ                1000//Scheduler time slice frequency (Hz)

// SVC exception immediate code
#define SVC_OS_DELAY                    0x01
#define SVC_OS_SUSPEND                  0x02

/*****************************************************************************
 Data types
******************************************************************************/
typedef struct
{
  uint32_t           time_ms;     /*Time, in the unit of systick resolution */
  uint32_t           time_slice;  /*Time, in the unit of OS time sclie*/
} myOsTime_t;



/*
 * Task control block.  A task control block (TCB) is allocated for each task,
 * and stores task state information, including a pointer to the task's context
 * (the task's run time environment, including register values)
 */
typedef struct
{
  ///////////////////////////////////////////////
  // PSP must be the first element of this struct.
  // This element is access in the PendSV context
  // switching assembly.
  ///////////////////////////////////////////////
  volatile uint32_t  PSP;//Process address

  ///////////////////////////////////////////////
  // bFloat must be the second element of this
  // struct.
  // This element is access in the PendSV context
  // switching assembly.
  // TRUE: floating point active;
  // FALSE: floating point inactive;
  ///////////////////////////////////////////////
  volatile uint32_t  bFloat;

  ///////////////////////////////////////////////
  // uint32_t must be the third element of this
  // struct.
  // This element is access in the xSemaphoreUp
  // assembly.
  // TRUE: wakeup: expect: SUSPEND ==> READY;
  // FALSE: still in SUSPEND;
  ///////////////////////////////////////////////
  uint32_t           bWakeUp;

  uint32_t           id;        /*Unique task ID*/
  TaskFunction_t     pTaskCode;/*Pointer to the task implementation code/function*/
  char               pcTaskName[configMAX_TASK_NAME_LEN];/*Descriptive name*/
  uint32_t           StackDepth;/*Max stack depth, used to check stack overflow*/
  uint32_t           priority;  /*Task priority*/
  uint32_t           state;     /*Task state*/
  uint32_t           TimeWakeup;/*Planned task wake up time*/
} TCB_t;

typedef struct TCB_t* TaskHandle_t;


typedef struct TaskList
{
  /* pNext MUST BE THE FIRST MEMBER OF THIS STRUCT.
     It is access in the inline assembly code. */
  struct TaskList      *pNext;//Pointer to the next task list node
  TaskHandle_t         pTCB  ;//Pointer to the TCB
} TaskList_t;



typedef struct
{
  ///////////////////////////////////////////////////////////////////
  // The positions of the pTcbCurr and pTcbNext elements are fixed,
  // which are accessed by the PendSV exception handler assembly.
  ///////////////////////////////////////////////////////////////////
  volatile TCB_t  *pTcbCurr;//Current TCB pointer
  volatile TCB_t  *pTcbNext;//Next TCB pointer
  BOOL       flgSchedRun   ;//TRUE: the scheduler is running
  uint32_t   numTaskReady  ; //Total number of Tasks in Ready
  uint32_t   numTaskRun    ; //Total number of Tasks in Run
  uint32_t   numTaskBlock  ; //Total number of Tasks in Block
  uint32_t   numTaskSuspend; //Total number of Tasks in Ready
  uint32_t   numTaskTotal  ; //Total number of Tasks, in all states
  TaskHandle_t    pTaskRun       ;//Point the the run task's TCB. Only one task in Run state
  TaskHandle_t    pTaskReadyTop  ;//Point to the TCB of the top task in Ready queue
  TaskHandle_t    pTaskBlockTop  ;//Point to the TCB of the top task in Ready queue
  TaskHandle_t    pTaskSuspendTop;//Point to the TCB of the top task in Ready queue
} SchedStatus_t;



/*****************************************************************************
 Function prototypes
******************************************************************************/
uint32_t myOsInit();
uint32_t xTaskCreate( TaskFunction_t pTaskCode,
                      const char * const pTaskName,
                      const uint32_t TaskStackDepth,
                      uint32_t TaskPriority);
uint32_t xTaskCreateIdle(void);
uint32_t vTaskDelay(uint32_t DelayTime);

void SchedulerStart(void);
void SchedulerCore(void);
static void IdleTask(void *pvParameters);

void SVC_Handler_C(unsigned int * svc_args);
void PendSV_Handler(void);
void SysTick_Handler( void );

#endif /* MY_TASK_H */



