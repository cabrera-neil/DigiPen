/*****************************************************************************
 @Project	: STM32 Peripherals Lib
 @File 		: Timer.h
 @Details  	: STM32F722 Timer driver               
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/

#ifndef __TIMER_DOC_H__
#define __TIMER_DOC_H__

/*****************************************************************************
 Define
******************************************************************************/

#define TIMER_OK				0
#define TIMER_ERR_INVALID		-1
#define TIMER_ERR_USED			-2


/*****************************************************************************
 Type definition
******************************************************************************/
typedef void TIMER_CB_UPDATE( void );

typedef struct _tagTimer_Hook
{
	TIMER_CB_UPDATE 		*pfUpdate;
	struct _tagTimer_Hook 	*pNext;
}TIMER_HOOK, *PTIMER_HOOK;


typedef struct _tagTimer_Handle
{
	void 				*pTimer;
	int					Irq;
	PTIMER_HOOK			pHeadHook;
}TIMER_HANDLE, *PTIMER_HANDLE;


/******************************************************************************
 Global functions
******************************************************************************/


/******************************************************************************
 @Description 	:Initialize specified timer. This will not run the timer. Call
				 TimerStart() to run

 @param			: pHandle - To an empty handle pointer
				  nTimer - Timer index e.g: 1, 2, 3 ... 14
				  nFreq - Timer tick speed
 
 @revision		: 1.0.0
 
******************************************************************************/
int TimerInit( PTIMER_HANDLE pHandle, uint8_t nTimer, uint32_t nFreq );


/******************************************************************************
 @Description 	: Start specified timer

 @param			: pHandle - To an initialized handle pointer
 
 @revision		: 1.0.0
 
******************************************************************************/
void TimerStart( PTIMER_HANDLE pHandle );


/******************************************************************************
 @Description 	: Stop specified timer

 @param			: pHandle - To an initialized handle pointer
 
 @revision		: 1.0.0
 
******************************************************************************/
void TimerStop( PTIMER_HANDLE pHandle );


/******************************************************************************
 @Description 	: Add callback to a timer

 @param			: pHandle - To an initialized handle pointer
				  pHook   - To an empty hook pointer
				  pfUpdate - callback function pointer
				   
 @revision		: 1.0.0
 
******************************************************************************/
void 
TimerAddHook(
	PTIMER_HANDLE 		pHandle,
	PTIMER_HOOK 		pHook,
	TIMER_CB_UPDATE 	*pfUpdate );


#endif /* __TIMER_DOC_H__ */


