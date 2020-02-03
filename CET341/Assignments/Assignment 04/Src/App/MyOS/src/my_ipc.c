/*****************************************************************************
 @Project    :
 @File       : my_ipc.c
 @Details    :  
 @Author     :  
 @Hardware   :  
 

 --------------------------------------------------------------------------
 @Revision   :
  Ver      Author        Date            Changes
 --------------------------------------------------------------------------
  1.0      Name        XXXX-XX-XX        Initial Release
   

******************************************************************************/

#include <stdint.h>
#include "Common.h"
#include "MyOSConfig.h"
#include "proj_def.h"
#include "myos.h"
#include "my_task.h"
#include "my_ipc.h"

/*****************************************************************************
 Define
******************************************************************************/


/*****************************************************************************
 Static Variables
******************************************************************************/


///////////////////////////////////////////////////////////////////////////////
// Function: xSemaphoreCreate
// Augument:
///////////////////////////////////////////////////////////////////////////////
uint32_t xSemaphoreCreate(SEMAPHORE_t *xSemaphore, uint32_t value)
{

  xSemaphore->value = value;
  xSemaphore->AddrWr = 0;
  xSemaphore->AddrRd = 0;

  return (MYOS_MSG_OK);

}



///////////////////////////////////////////////////////////////////////////////
// Function: xSemaphoreDown
// Augument: *xMutex:
//             xMutex pointer pointed address is stored in R0
//           max_delay:
//             max_delay is stored in R1
// Descript: Semaphore WAIT
///////////////////////////////////////////////////////////////////////////////
uint32_t xSemaphoreDown(SEMAPHORE_t *xSemaphore, TCB_t *pTCB)
{
  uint32_t RetCode;

  /////////////////////////////////////////////////////////////////
  // -- The original C implementation:                           //
  //[Lock--                                                      //
  //xSemaphore->value--;            // Atomic!                   //
  //if (xSemaphore->value <0 )                                   //
  //{                                                            //
  //  add the current task to xSemaphore->pTCB                   //
  //  block/suspend;                                             //
  //}                                                            //
  //--Unlock]                                                    //
  /////////////////////////////////////////////////////////////////
  /************************************************
  * To do: 
  * Implement the above algorithm in ASM,
  * LDREX/STREX instructions should be used to 
  * ensure the atomic operation.
  ************************************************/
//  if(xSemaphore->value <= 0)
//  {
//    RetCode = MYOS_MSG_ERR_UNKNOWN;
//    return (RetCode);
//  }

  __ASM volatile ("PUSH {R4-R7}");

  __ASM volatile ("__checking_sem_down:");
  __ASM volatile ("LDREX R4, [R0]");

//  __ASM volatile ("CMP R4, #0");
//  __ASM volatile ("BEQ __suspend_at_down");
  
  __ASM volatile ("SUB R4, #1");
  __ASM volatile ("STREX R5, R4, [R0]");
  __ASM volatile ("CMP R5, #0");
  __ASM volatile ("BNE __checking_sem_down");
//  __ASM volatile ("B __sem_down_end");

  __ASM volatile ("CMP R4, #0");
  __ASM volatile ("BGE __sem_down_end");
  
  __ASM volatile ("__suspend_at_down:");
  __ASM volatile ("LDR R4, [R0, #4]");
  __ASM volatile ("LSL R4, #2");
  __ASM volatile ("ADD R4, #0X0C");
  __ASM volatile ("ADD R4, R0");
  __ASM volatile ("STR R1, [R4]");

  __ASM volatile ("SVC #0x02");

  __ASM volatile ("__sem_down_end:  ");
  __ASM volatile ("POP {R4-R7}");
  
  RetCode = MYOS_MSG_OK;

  return (RetCode);
}



///////////////////////////////////////////////////////////////////////////////
// Function: xSemaphoreUp
// Augument: *xMutex:
//             xMutex pointer pointed address is stored in R0
//           max_delay:
//             max_delay is stored in R1
///////////////////////////////////////////////////////////////////////////////
uint32_t xSemaphoreUp(SEMAPHORE_t *xSemaphore, TCB_t *pTCB)
{
  uint32_t RetCode;

  /////////////////////////////////////////////////////////////////
  // -- The original C implementation:                           //
  //[Lock--                                                      //
  //xSemaphore->value++;                                         //
  //if (xSemaphore->value <=0 )                                  //
  //{                                                            //
  //  remove the registered task from xSemaphore                 //
  //  wakeup the task;                                           //
  //}                                                            //
  //--Unlock]                                                    //
  /////////////////////////////////////////////////////////////////
  /************************************************
  * To do: 
  * Implement the above algorithm in ASM,
  * LDREX/STREX instructions should be used to 
  * ensure the atomic operation.
  ************************************************/
  __ASM volatile ("PUSH {R4-R7}");

  __ASM volatile ("__checking_sem_up:");
  __ASM volatile ("LDREX R4, [R0]");
  __ASM volatile ("ADD R4, #1");
  __ASM volatile ("STREX R5, R4, [R0]");
  __ASM volatile ("CMP R5, #0");
  __ASM volatile ("BNE __checking_sem_up");

  __ASM volatile ("CMP R4, #0");
  __ASM volatile ("BGT __sem_up_end");

  __ASM volatile ("LDR R4, [R0, #8]");
  __ASM volatile ("LSL R4, #2");
  __ASM volatile ("ADD R4, #0X0C");
  __ASM volatile ("ADD R4, R0");
  __ASM volatile ("LDR R0, [R4]");

  __ASM volatile ("MOV R3, #1");
  __ASM volatile ("STR R3, [R0, #0X08]");

  __ASM volatile ("__sem_up_end:");
  __ASM volatile ("POP {R4-R7}");

  RetCode = MYOS_MSG_OK;

  return (RetCode);
}