/*****************************************************************************
 @Project	: 
 @File 		: 
 @Details  	: All Ports and peripherals configuration                    
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/

#ifndef __HAL_DOT_H__
#define __HAL_DOT_H__

/*****************************************************************************
 Define
******************************************************************************/
#define GPIO_MODE_OUTPUT 	0x01U
#define GPIO_PULL_DIS		0x00U
#define GPIO_SPEED_MAX 		0x03U

/*****************************************************************************
 Define - Pins
******************************************************************************/
#define PB_LED_BLUE			7U
#define PB_LED_RED			14U

/*****************************************************************************
 Macro
******************************************************************************/
#define BIT( x )					(1U<<(x))

/* LEDs */
#define LED_RED_ON()		(GPIOB->BSRR = BIT(PB_LED_RED))
#define LED_RED_OFF()		(GPIOB->BSRR = (BIT(PB_LED_RED)<<16U))
#define LED_RED_SET( x )	((x)? LED_RED_ON() : LED_RED_OFF())

#define LED_BLUE_ON()		(GPIOB->BSRR = BIT(PB_LED_BLUE))
#define LED_BLUE_OFF()		(GPIOB->BSRR = (BIT(PB_LED_BLUE)<<16U))
#define LED_BLUE_SET( x )	((x)? LED_BLUE_ON() : LED_BLUE_OFF())

#endif /* __HAL_DOT_H__ */









