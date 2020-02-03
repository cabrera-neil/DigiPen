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
#define GPIO_MODE_INPUT 	0x00U
#define GPIO_MODE_OUTPUT 	0x01U
#define GPIO_MODE_AF		0x02U
#define GPIO_MODE_ANALOGUE	0x03U

#define GPIO_PULL_DIS		0x00U
#define GPIO_PULL_UP		0x01U
#define GPIO_PULL_DWN		0x02U

#define GPIO_SPEED_MIN		0x00U
#define GPIO_SPEED_MEDIUM	0x01U
#define GPIO_SPEED_HIGH 	0x02U
#define GPIO_SPEED_MAX 		0x03U

#define GPIO_PWM_AF1		0x01U
#define GPIO_PWM_AF2		0x02U
#define GPIO_I2C1_AF4		0x04U
#define GPIO_SPI1_AF5		0x05U
#define GPIO_SPI2_AF5		0x05U
#define GPIO_SPI3_AF6       0x06U
#define GPIO_USART2_AF7		0x07U
#define GPIO_UART7_AF8		0x08U


/*****************************************************************************
 Define - Pins
******************************************************************************/
#define PB_LED_LD1			0U
#define PB_LED_LD2			7U
#define PB_LED_LD3			14U

/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Macro
******************************************************************************/
#define BIT( x )					(1U<<(x))

/* LEDs */
#define LED_LD1_ON()			    (GPIOB->BSRR = BIT(PB_LED_LD1))
#define LED_LD1_OFF()			    (GPIOB->BSRR = (BIT(PB_LED_LD1)<<16U))
#define LED_LD1_SET( x )		    ((x)? LED_LD1_ON() : LED_LD1_OFF())

#define LED_LD2_ON()			    (GPIOB->BSRR = BIT(PB_LED_LD2))
#define LED_LD2_OFF()			    (GPIOB->BSRR = (BIT(PB_LED_LD2)<<16U))
#define LED_LD2_SET( x )		    ((x)? LED_LD2_ON() : LED_LD2_OFF())

#define LED_LD3_ON()			    (GPIOB->BSRR = BIT(PB_LED_LD3))
#define LED_LD3_OFF()			    (GPIOB->BSRR = (BIT(PB_LED_LD3)<<16U))
#define LED_LD3_SET( x )		    ((x)? LED_LD3_ON() : LED_LD3_OFF())
/******************************************************************************
 Global functions
******************************************************************************/


/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void PortInit( void );



#endif /* __HAL_DOT_H__ */









