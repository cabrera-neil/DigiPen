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
******************************************************************************/
#include "Common.h"
#include "proj_def.h"
#include "MyOSConfig.h"
#include <string.h>
#include "myos.h"
#include "my_task.h"
#include "my_ipc.h"
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
#define TASK03_STACK_SIZE       512
#define TASK04_STACK_SIZE       512
#define TASK05_STACK_SIZE       512
#define TASK06_STACK_SIZE       512
#define TASK07_STACK_SIZE       512
#define TASK08_STACK_SIZE       512
#define TASK09_STACK_SIZE       512
#define TASK10_STACK_SIZE       512
#define TASK11_STACK_SIZE       512
#define TASK12_STACK_SIZE       512

/**********************************************************
 Each task's wait/sleep random boundaries: unit: ms
**********************************************************/
#define TASK01_WAIT_MAX         199
#define TASK01_WAIT_MIN         50
#define TASK02_WAIT_MAX         999
#define TASK02_WAIT_MIN         50
#define TASK03_WAIT_MAX         1999
#define TASK03_WAIT_MIN         50
#define TASK04_WAIT_MAX         9999
#define TASK04_WAIT_MIN         100
#define TASK05_WAIT_MAX         9999
#define TASK05_WAIT_MIN         100
#define TASK06_WAIT_MAX         9999
#define TASK06_WAIT_MIN         100
#define TASK07_WAIT_MAX         9999
#define TASK07_WAIT_MIN         100
#define TASK08_WAIT_MAX         9999
#define TASK08_WAIT_MIN         100
#define TASK09_WAIT_MAX         9999
#define TASK09_WAIT_MIN         100
#define TASK10_WAIT_MAX         9999
#define TASK10_WAIT_MIN         100

/**********************************************************
 IPC methods practice in assignments.
**********************************************************/
#define ASSIGN_IPC_NO_TEST      0
#define ASSIGN_IPC_NONE         1
#define ASSIGN_IPC_MUTEX        2
#define ASSIGN_IPC_SEMPH        3
#define ASSIGN_IPC_QUEUE        4
#define ASSIGN_IPC_SELEC        ASSIGN_IPC_QUEUE
//#define ASSIGN_IPC_SELEC        ASSIGN_IPC_NO_TEST
#define __DEBUG_IPC_1

// The number of the IPC buffer entries
#define IPC_BUF_ENTRY           60
// The depth of each IPC buffer entry
#define IPC_BUF_DEPTH           60

/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 External Global Variables
******************************************************************************/
extern volatile myOsTime_t myOsTime;

/*****************************************************************************
 Static Global Variables
******************************************************************************/
///////////////////////////////////////////////////////////
// IPC buffer and control variabls.
///////////////////////////////////////////////////////////
static volatile uint8_t g_IpcBuf[IPC_BUF_ENTRY][IPC_BUF_DEPTH];
static volatile uint32_t g_Buf1AddrWr = 0;
static volatile uint32_t g_Buf1AddrRd = 0;

static volatile uint32_t g_nSysTick = SYS_TICK_MS; /* Tick count*/

static BOOL g_bLedLd1 = FALSE;
static BOOL g_bLedLd2 = FALSE;
static BOOL g_bLedLd3 = FALSE;

/////////////////////////////////////////////////
// Three semaphores for Printf buffer IPC
/////////////////////////////////////////////////
static SEMAPHORE_t         xSemPrintFull;
static SEMAPHORE_t         xSemPrintEmpty;
static SEMAPHORE_t         xSemPrintMutex;

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
static void Task03( void *pvParameters );
static void Task04( void *pvParameters );
static void Task05( void *pvParameters );
static void Task06( void *pvParameters );
static void Task07( void *pvParameters );
static void Task08( void *pvParameters );
static void Task09( void *pvParameters );
static void Task10( void *pvParameters );
static void Task11( void *pvParameters );
static void Task12( void *pvParameters );

/*****************************************************************************
 Implementation
******************************************************************************/
int main( void )
{
  uint32_t ret_OsInit;
  uint32_t ret_Task01;
  uint32_t ret_Task02;
  uint32_t ret_Task03;
  uint32_t ret_Task04;
  uint32_t ret_Task05;
  uint32_t ret_Task06;
  uint32_t ret_Task07;
  uint32_t ret_Task08;
  uint32_t ret_Task09;
  uint32_t ret_Task10;
  uint32_t ret_Task11;
  uint32_t ret_Task12;
  uint32_t reg;
  uint32_t SemValue;

  BSPInit();

  ///////////////////////////////////////////////
  // Enable double word stack alignment
  // recommended in Cortex-M3 r1p1, default in 
  // Cortex-M3 r2px and Cortex-M4
  ///////////////////////////////////////////////
  SCB->CCR |= SCB_CCR_STKALIGN_Msk;
  
  __set_CONTROL(0);//Thread mode has privileged access; MSP

  TRACE( "System Boot up\r\n" );
  TRACE( "SystemCoreClock %dHz\r\n", SystemCoreClock );

  ret_OsInit = myOsInit();
  ASSERT(TRUE==ret_OsInit);

  ret_Task01 = xTaskCreate(Task01, "T01_Producer", TASK01_STACK_SIZE, TASK_PRIORITY_LEVEL_4); ASSERT(TRUE==ret_Task01);
  ret_Task02 = xTaskCreate(Task02, "T02_Producer", TASK02_STACK_SIZE, TASK_PRIORITY_LEVEL_3); ASSERT(TRUE==ret_Task02);
  //ret_Task03 = xTaskCreate(Task03, "T03_Producer", TASK03_STACK_SIZE, TASK_PRIORITY_LEVEL_2); ASSERT(TRUE==ret_Task03);
  ret_Task11 = xTaskCreate(Task11, "T11_PRINTF"  , TASK11_STACK_SIZE, TASK_PRIORITY_LEVEL_8); ASSERT(TRUE==ret_Task11);

  xSemaphoreCreate(&xSemPrintEmpty, IPC_BUF_ENTRY);
  xSemaphoreCreate(&xSemPrintFull, 0);
  xSemaphoreCreate(&xSemPrintMutex, 2);

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
static void IpcInsert(uint8_t *StrInsert, uint32_t WrAddr)
{
  uint32_t i;

  for (i=0; i<IPC_BUF_DEPTH; i++)
  {
    g_IpcBuf[WrAddr][i] = StrInsert[i];
    if (NULL==StrInsert[i])
    {
      break;
    }
  }
}
;
static void IpcRemove(uint8_t *StrRemove, uint32_t RdAddr)
{
  uint32_t i;

  for (i=0; i<IPC_BUF_DEPTH; i++)
  {
    StrRemove[i] = g_IpcBuf[RdAddr][i];
    if (NULL==g_IpcBuf[RdAddr][i])
    {
      break;
    }
  }
}

static void Task01( void *pvParameters )
{
  BOOL     bToggle = FALSE;
  uint32_t WaitTime;
  TCB_t    *pTCB;
  uint8_t  BufPrintf[IPC_BUF_DEPTH];
#ifdef __DEBUG_IPC_1
  uint32_t cnt;
  cnt = 0;
#endif

  TaskTcbEnq(&pTCB);

  for(;;)
  {
#ifdef __DEBUG_IPC_1
//    sprintf(BufPrintf, "T01: %d, %d, %d;\n", xSemPrintEmpty.value, xSemPrintFull.value, xSemPrintMutex);
//    TRACE(BufPrintf);
//    sprintf(BufPrintf, "T01: [%d];\n", cnt);
    cnt++;
#endif
  /************************************************
  * To do: 
  * Produce: store the BufPrintf string into the 
  * g_IpcBuf buffer.
  ************************************************/
    if(xSemPrintFull.value<IPC_BUF_ENTRY)
    {
      xSemaphoreDown(&xSemPrintEmpty, pTCB);
      xSemaphoreDown(&xSemPrintMutex, pTCB);

  
      sprintf(BufPrintf, "T01: Full:%d, Empty:%d, Mutex:%d;\n", xSemPrintFull.value, xSemPrintEmpty.value, xSemPrintMutex.value);

      IpcInsert(&BufPrintf, g_Buf1AddrWr);

      g_Buf1AddrWr++;
      if(IPC_BUF_ENTRY==g_Buf1AddrWr)
        g_Buf1AddrWr = 0;

      xSemaphoreUp(&xSemPrintMutex, pTCB);
      xSemaphoreUp(&xSemPrintFull, pTCB);
    }


    WaitTime = rand();
    WaitTime = WaitTime % (TASK01_WAIT_MAX + 1 - TASK01_WAIT_MIN);
    WaitTime = WaitTime + TASK01_WAIT_MIN;
    vTaskDelay( WaitTime );
  }
}

static void Task02( void *pvParameters )
{
  BOOL bToggle = FALSE;
  uint32_t WaitTime;
  TCB_t    *pTCB;
  uint8_t  BufPrintf[IPC_BUF_DEPTH];
#ifdef __DEBUG_IPC_1
  uint32_t cnt;
  cnt = 0;
#endif

  TaskTcbEnq(&pTCB);

  for(;;)
  {
#ifdef __DEBUG_IPC_1
//    sprintf(BufPrintf, "T02: %d, %d, %d;\n", xSemPrintEmpty.value, xSemPrintFull.value, xSemPrintMutex);
//    TRACE(BufPrintf);
//    sprintf(BufPrintf, "T02: [%d];\n", cnt); 
    cnt++;
#endif
  /************************************************
  * To do: 
  * Produce: store the BufPrintf string into the 
  * g_IpcBuf buffer.
  * It's up to you whether implement this second
  * producer.
  ************************************************/
    if(xSemPrintFull.value<IPC_BUF_ENTRY)
    {
  
      xSemaphoreDown(&xSemPrintEmpty, pTCB);
      xSemaphoreDown(&xSemPrintMutex, pTCB);

      sprintf(BufPrintf, "  T02: Full:%d, Empty:%d, Mutex:%d;\n", xSemPrintFull.value, xSemPrintEmpty.value, xSemPrintMutex.value);


      IpcInsert(&BufPrintf, g_Buf1AddrWr);

      g_Buf1AddrWr++;
      if(IPC_BUF_ENTRY==g_Buf1AddrWr)
        g_Buf1AddrWr = 0;


      xSemaphoreUp(&xSemPrintMutex, pTCB);
      xSemaphoreUp(&xSemPrintFull, pTCB);
    }

    WaitTime = rand();
    WaitTime = WaitTime % (TASK02_WAIT_MAX + 1 - TASK02_WAIT_MIN);
    WaitTime = WaitTime + TASK02_WAIT_MIN;
    vTaskDelay( WaitTime );
  }
}

//static void Task03( void *pvParameters )
//{
//  BOOL bToggle = FALSE;
//  uint32_t WaitTime;
//  TCB_t    *pTCB;
//  uint8_t  BufPrintf[IPC_BUF_DEPTH];
//#ifdef __DEBUG_IPC_1
//  uint32_t cnt;
//  cnt = 0;
//#endif
//
//  TaskTcbEnq(&pTCB);
//
//  for(;;)
//  {
//#ifdef __DEBUG_IPC_1
//    sprintf(BufPrintf, "T02: %d, %d, %d;\n", xSemPrintEmpty.value, xSemPrintFull.value, xSemPrintMutex);
//    TRACE(BufPrintf);
//    sprintf(BufPrintf, "T02: [%d];\n", cnt); 
//    cnt++;
//#endif
//  /************************************************
//  * To do: 
//  * Produce: store the BufPrintf string into the 
//  * g_IpcBuf buffer.
//  * It's up to you whether implement this second
//  * producer.
//  ************************************************/
//    xSemaphoreDown(&xSemPrintMutex, pTCB);
//
//    if(xSemPrintFull.value<IPC_BUF_ENTRY)
//    {
//      xSemaphoreDown(&xSemPrintEmpty, pTCB);
//  
//      sprintf(BufPrintf, "T03: %d, %d;\n", xSemPrintFull.value, xSemPrintMutex.value+1);
//
//      IpcInsert(&BufPrintf, g_Buf1AddrWr);
//
//      g_Buf1AddrWr++;
//      if(IPC_BUF_ENTRY==g_Buf1AddrWr)
//        g_Buf1AddrWr = 0;
//
//      xSemaphoreUp(&xSemPrintFull, pTCB);
//    }
//
//    xSemaphoreUp(&xSemPrintMutex, pTCB);
//
//    WaitTime = rand();
//    WaitTime = WaitTime % (TASK02_WAIT_MAX + 1 - TASK02_WAIT_MIN);
//    WaitTime = WaitTime + TASK02_WAIT_MIN;
//    vTaskDelay( WaitTime );
//  }
//}

static void Task11( void *pvParameters )
{
  uint32_t WaitTime;
  TCB_t    *pTCB;
  uint8_t  BufPrintf[IPC_BUF_DEPTH];

  TaskTcbEnq(&pTCB);

  for(;;)
  {
  /************************************************
  * To do: 
  * Consume (and TRACE display) the strings in 
  * the g_IpcBuf buffer.
  ************************************************/
    if(xSemPrintFull.value>IPC_BUF_ENTRY/2)
    {
    xSemaphoreDown(&xSemPrintFull, pTCB);
    xSemaphoreDown(&xSemPrintMutex, pTCB);

    
      IpcRemove(&BufPrintf, g_Buf1AddrRd);

      TRACE(BufPrintf);

      g_Buf1AddrRd++;
      if(IPC_BUF_ENTRY==g_Buf1AddrRd)
        g_Buf1AddrRd = 0;

    xSemaphoreUp(&xSemPrintMutex, pTCB);
    xSemaphoreUp(&xSemPrintEmpty, pTCB);
    }


//    WaitTime = rand();
//    WaitTime = WaitTime % (TASK01_WAIT_MAX + 1 - TASK01_WAIT_MIN);
//    WaitTime = WaitTime + TASK01_WAIT_MIN;
//    vTaskDelay( WaitTime );
  }
}

/*****************************************************************************
 Callback functions
******************************************************************************/


