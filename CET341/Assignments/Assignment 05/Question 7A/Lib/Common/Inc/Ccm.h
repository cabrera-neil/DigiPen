/*****************************************************************************
 @Project	: SEP150 - Capsule
 @File 		: Ccm.h
 @Details  	: Ccm
 @Author	: lcgan
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release

******************************************************************************/

#ifndef __CCM_DOT_H__
#define __CCM_DOT_H__

/*****************************************************************************
 Define
******************************************************************************/

#define CCM_OK					0
#define CCM_ERR_TIM_INVALID		-1
#define CCM_ERR_TIM_USED		-2
#define CCM_ERR_INPUT			-3


/*****************************************************************************
 Typedef 
******************************************************************************/
typedef enum _tagCCM_ENC_INPUT
{
	CCM_ENC_INPUT_A,
	CCM_ENC_INPUT_B,
    CCM_ENC_INPUT_AB
}CCM_ENC_INPUT;

typedef struct _tagCcm_Handle
{
	void 		*pTimer;
	int			nClock;
}CCM_HANDLE, *PCCM_HANDLE;


/*****************************************************************************
 @Description 	: Initialize PWM with a full cycle of intended frequency
 
 @Param			: nFrequency - Requirend frequency in Hertz

 @Requirement	: The function does not take care Pin intialization. User shall
				  responsible to configure the pin as PWM. 
				  
 @Revision		:
******************************************************************************/
int CCMInit(
	PCCM_HANDLE	pHandle,
	uint8_t 	nTimer );


/*****************************************************************************
 @Description 	: 
 
 @Param			: 
				  
 
 @Revision		:
******************************************************************************/
int CCMEncoderMode( PCCM_HANDLE pHandle, CCM_ENC_INPUT Input );


/*****************************************************************************
 @Description 	: 
 
 @Param			: 
				  
 
 @Revision		:
******************************************************************************/
int CCMInputMode( PCCM_HANDLE pHandle );


/*****************************************************************************
 @Description 	: 
 
 @Param			: 
				  
 
 @Revision		:
******************************************************************************/
int16_t CCMReadCount( PCCM_HANDLE pHandle );

int16_t CCMReadCountAutoReset( PCCM_HANDLE pHandle );

void CCMResetCount( PCCM_HANDLE pHandle );


/*****************************************************************************
 @Description 	: 
 
 @Param			: 
				  
 
 @Revision		:
******************************************************************************/
void CCMEnable( PCCM_HANDLE	pHandle, uint32_t	nChannel );


/*****************************************************************************
 @Description 	: Enable PWM channel sperately. Duty cycle % must be specify
 
 @Param			: nChannel 			- PWM channel 1 to 6
				  nDutyCycPercent 	- Duty clycle %
 
 @Revision		:
******************************************************************************/
void CCMDisable( PCCM_HANDLE	pHandle, uint32_t	nChannel );


#endif /* __CCM_DOT_H__ */




















































