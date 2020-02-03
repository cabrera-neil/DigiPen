/*****************************************************************************
 @Project    :
 @File       : my_ipc.h
 @Details    :  
 @Author     :  
 @Hardware   :  
 

 --------------------------------------------------------------------------
 @Revision   :
  Ver      Author        Date            Changes
 --------------------------------------------------------------------------
  1.0      Name         XXXX-XX-XX       Initial Release
   

******************************************************************************/


#ifndef MY_IPC_H
#define MY_IPC_H


/*****************************************************************************
 Define
******************************************************************************/



/*****************************************************************************
 Data types
******************************************************************************/
// Counting semaphore data structure
typedef struct
{
  // Semaphore counter/value.
  // This element must be the first element in this struct.
  // This element is access by the assembly code.
  volatile int32_t  value;

  volatile uint32_t  AddrWr;
  volatile uint32_t  AddrRd;
  volatile TCB_t    *pTCB[SEMAPHORE_MAX_TASK];//The requesting task's TCB address
  //volatile TaskList_t SemTask;
} SEMAPHORE_t;

/*****************************************************************************
 Function prototypes
******************************************************************************/
uint32_t xSemaphoreCreate(SEMAPHORE_t *xSemaphore, uint32_t value);
uint32_t xSemaphoreDown(SEMAPHORE_t *xSemaphore, TCB_t *pTCB);
uint32_t xSemaphoreUp(SEMAPHORE_t *xSemaphore, TCB_t *pTCB);

#endif /* MY_IPC_H */



