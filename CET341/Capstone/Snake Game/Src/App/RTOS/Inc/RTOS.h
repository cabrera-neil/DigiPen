/*****************************************************************************
 @Project	: 
 @File 		: RTOS.h
 @Details  	:                 
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/

#ifndef __RTOS_DOT_H__
#define __RTOS_DOT_H__

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "queue.h"
#include "stream_buffer.h"


/*****************************************************************************
 Define
******************************************************************************/
														 

/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Macro
******************************************************************************/
#define OS_TASK_EVENT		EventGroupHandle_t
#define OS_EVENT_WAIT( a, b ) xEventGroupWaitBits( (a), (b), pdTRUE, pdFALSE, portMAX_DELAY )
#define OS_EVENT_WAIT_TIMEOUT( a, b, c ) xEventGroupWaitBits( (a), (b), pdTRUE, pdFALSE, (c) )

void FREERTOS_EVENT_SET( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet );

#define OS_EVENT_SET( a, b )    FREERTOS_EVENT_SET( (a), (b) )
#define OS_EVENT_RESET( a, b )  xEventGroupClearBits( (a), (b) );
#define OS_EVENT_CREATE( p )    ((p) = xEventGroupCreate())


/******************************************************************************
 Global functions
******************************************************************************/


/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/


#endif /* __RTOS_DOT_H__ */









