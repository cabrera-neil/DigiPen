/*****************************************************************************
 @Project	: SEP150 - Capsule
 @File 		: pwm.h
 @Details  	: pwm
 @Author	: lcgan
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   1.1  Liang    2017-03-01      Updated for Infrared (IrDA) transmission.
******************************************************************************/

#ifndef __PWM_DOT_H__
#define __PWM_DOT_H__

/*****************************************************************************
 Define
******************************************************************************/

#define PWM_OK					0
#define PWM_ERR_INVALID 		-1
#define PWM_ERR_USED			-2


/*****************************************************************************
 Typedef 
******************************************************************************/
typedef struct _tagPwm_Handle
{
	void 		*pTimer;
	int32_t		ReloadCounter;
	BOOL		bInverse;
}PWM_HANDLE, *PPWM_HANDLE;


/*****************************************************************************
 @Description 	: Initialize PWM with a full cycle of intended frequency
 
 @Param			: nFrequency - Requirend frequency in Hertz

 @Requirement	: The function does not take care Pin intialization. User shall
				  responsible to configure the pin as PWM. 
				  
 @Revision		:
******************************************************************************/
int PWMInit(
	PPWM_HANDLE	pHandle,
	uint8_t 	nTimer,
	uint32_t 	nFreq );


/*****************************************************************************
 @Description 	: 
 
 @Param			: 
				  
 
 @Revision		:
******************************************************************************/
void
PWMEnable(
	PPWM_HANDLE	pHandle,
	uint32_t	nChannel,
	double 		dDutyCycPercent,
	BOOL		bInverse );


/*****************************************************************************
 @Description 	: Enable PWM channel sperately. Duty cycle % must be specify
 
 @Param			: nChannel 			- PWM channel 1 to 6
				  nDutyCycPercent 	- Duty clycle %
 
 @Revision		:
******************************************************************************/
void
PWMDisable(
	PPWM_HANDLE	pHandle,
	uint32_t	nChannel );


/*****************************************************************************
 @Description 	: Set PWM inverse 
 
 @Param			: 
 
 @Revision		:
******************************************************************************/
void
PWMSetInverse(
	PPWM_HANDLE	pHandle,
	uint32_t	nChannel,
	BOOL		bInverse );

#endif /* __PWM_DOT_H__ */




















































