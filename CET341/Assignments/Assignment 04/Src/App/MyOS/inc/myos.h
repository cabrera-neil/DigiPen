/*****************************************************************************
 @Project	:
 @File 		: myos.h
 @Details  	:  
 @Author	:  
 @Hardware	:  
 

 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   

******************************************************************************/


#ifndef MYOS_H
#define MYOS_H
                   
#include <stddef.h>
#include <stdint.h> /* READ COMMENT ABOVE. */


/* Application specific configuration options. */
#include "MyOSConfig.h"

/* Basic FreeRTOS definitions. */
#include "proj_def.h"

typedef void (*TaskFunction_t)( void * );
typedef long BaseType_t;


#define pdFALSE        ((BaseType_t) 0)
#define pdTRUE         ((BaseType_t) 1)
#define pdPASS         (pdTRUE )
#define pdFAIL         (pdFALSE)


/* Task priority*/
#define TASK_PRIORITY_LEVEL_0  0 /* The lowest priority */
#define TASK_PRIORITY_LEVEL_1  1
#define TASK_PRIORITY_LEVEL_2  2
#define TASK_PRIORITY_LEVEL_3  3
#define TASK_PRIORITY_LEVEL_4  4
#define TASK_PRIORITY_LEVEL_5  5
#define TASK_PRIORITY_LEVEL_6  6
#define TASK_PRIORITY_LEVEL_7  7
#define TASK_PRIORITY_LEVEL_8  8
#define TASK_PRIORITY_LEVEL_9  9

                     
#define OS_MAX_DELAY           0x7FFFFFFF

//Max. serving task for a semaphore
#define SEMAPHORE_MAX_TASK     16




#define IDLE_STACK_SIZE        64 //Idle task task size. Unit: word (4 bytes)
#define SYS_TICK_MS            50 //OS time slice = this value * SysTick period



///////////////////////////////////////////////////////////////////////////////
// From Josef Yiu's book: Chapter 10.5, page 339
///////////////////////////////////////////////////////////////////////////////
#define HW32_REG(ADDRESS)     (*((volatile unsigned long *)(ADDRESS)))
#define stop_cpu               __breakpoint(0)


#define ARM_CORE_CONTROL_NPRIV 0x01 //0: Thread mode has privileged access;
                                    //1: Thread mode has unprivileged access.
#define ARM_CORE_CONTROL_SPSEL 0x02 //0: MSP; 1: PSP;
#define ARM_CORE_CONTROL_FPCA  0x04 //0: FP extension not active; 1: active



///////////////////////////////////////////////////////////////////////////////
// MyOS message/error code
///////////////////////////////////////////////////////////////////////////////
#define MYOS_MSG_OK            0x00000001
#define MYOS_MSG_ERR_UNKNOWN   0x7FFFFFFF
#define MYOS_MSG_MALLOC_FAIL   0x7FFFFFFE


#endif /* MYOS_H */



