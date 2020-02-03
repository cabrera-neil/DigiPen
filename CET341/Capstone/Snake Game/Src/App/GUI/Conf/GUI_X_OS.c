/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2017  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.44 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_X_OS.C
Purpose     : This file provides emWin Interface with FreeRTOS
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license SLA0044,
  * the "License"; You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <Common.h>

#include "RTOS.h"

#include "GUI.h"
	
/*********************************************************************
*
* Global data
*/
static SemaphoreHandle_t xMutex = NULL;
static StaticSemaphore_t xMutexBuf;
  

static SemaphoreHandle_t  xSemaphore;
static StaticSemaphore_t xSemaphoreBuf;
//static volatile int g_nLockcnt = 0;


/*********************************************************************
*
* Timing:
* GUI_X_GetTime()
* GUI_X_Delay(int)

Some timing dependent routines require a GetTime
and delay function. Default time unit (tick), normally is
1 ms.
*/

GUI_TIMER_TIME GUI_X_GetTime(void)
{
    if( __get_IPSR() )
    {
        return xTaskGetTickCountFromISR();
    }
    else 
    {
        return xTaskGetTickCount();
    }
}

void GUI_X_Delay(int ms)
{
  vTaskDelay( ms );
}

/*********************************************************************
*
* GUI_X_Init()
*
* Note:
* GUI_X_Init() is called from GUI_Init is a possibility to init
* some hardware which needs to be up and running before the GUI.
* If not required, leave this routine blank.
*/

void GUI_X_Init(void) {
}


/*********************************************************************
*
* GUI_X_ExecIdle
*
* Note:
* Called if WM is in idle state
*/

void GUI_X_ExecIdle(void) 
{
	vTaskDelay(2);
}

/*********************************************************************
*
* Multitasking:
*
* GUI_X_InitOS()
* GUI_X_GetTaskId()
* GUI_X_Lock()
* GUI_X_Unlock()
*
* Note:
* The following routines are required only if emWin is used in a
* true multi task environment, which means you have more than one
* thread using the emWin API.
* In this case the
* #define GUI_OS 1
* needs to be in GUIConf.h
*/

/* Init OS */
void GUI_X_InitOS(void)
{ 
	/* Create Mutex lock */
	xMutex = xSemaphoreCreateMutexStatic( &xMutexBuf );

	/* Create Semaphore lock */
    /* Create the Semaphore used by the two threads */
	xSemaphore = xSemaphoreCreateCountingStatic( 1, 1, &xSemaphoreBuf );



}

void GUI_X_Unlock(void)
{ 
	portBASE_TYPE taskWoken = pdFALSE;

	if( __get_IPSR() )
	{
		if(xSemaphoreGiveFromISR( xMutex, &taskWoken) == pdTRUE)
		{
			portEND_SWITCHING_ISR(taskWoken);
		}
	}
	else
	{
		xSemaphoreGive( xMutex );
	}
}

void GUI_X_Lock(void)
{
  portBASE_TYPE taskWoken = pdFALSE;

// g_nLockcnt++;
// printf("Lock %d\r\n", g_nLockcnt );

 if( __get_IPSR() )
 {
    if (xSemaphoreTakeFromISR(xMutex, &taskWoken) != pdTRUE)
	{
		portEND_SWITCHING_ISR(taskWoken);
    }
	
  } 
  else 
  {
    xSemaphoreTake(xMutex, portMAX_DELAY/portTICK_PERIOD_MS);
  }

}

/* Get Task handle */
U32 GUI_X_GetTaskId(void) 
{ 
  return ((U32) xTaskGetCurrentTaskHandle());
}


void GUI_X_WaitEvent (void) 
{
	portBASE_TYPE taskWoken = pdFALSE;

	if( __get_IPSR() )
	{
		if (xSemaphoreTakeFromISR(xSemaphore, &taskWoken) == pdTRUE)
		{
			portEND_SWITCHING_ISR(taskWoken);
		}
	}  
	else
	{
		xSemaphoreTake(xSemaphore, portMAX_DELAY/portTICK_PERIOD_MS);
	}

}


void GUI_X_SignalEvent (void) 
{
	portBASE_TYPE taskWoken = pdFALSE;

	if( __get_IPSR() )
	{
		if(xSemaphoreGiveFromISR( xSemaphore, &taskWoken) == pdTRUE)
		{
			portEND_SWITCHING_ISR(taskWoken);
		}
	}
	else
	{
		xSemaphoreGive( xSemaphore );
	}
}

/*********************************************************************
*
* Logging: OS dependent

Note:
Logging is used in higher debug levels only. The typical target
build does not use logging and does therefor not require any of
the logging routines below. For a release build without logging
the routines below may be eliminated to save some space.
(If the linker is not function aware and eliminates unreferenced
functions automatically)

*/

void GUI_X_Log (const char *s) { }
void GUI_X_Warn (const char *s) { }
void GUI_X_ErrorOut(const char *s) { }

/*************************** End of file ****************************/
