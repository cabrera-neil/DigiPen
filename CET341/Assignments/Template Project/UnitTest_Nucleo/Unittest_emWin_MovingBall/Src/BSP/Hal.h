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
#define PB_LED_BLUE			7U
#define PB_LED_RED			14U
#define PF_LED_OB1			7U
#define PF_LED_OB2			9U


#define PB_LCD_RESET		1U
#define PE_LCD_DC			0U
#define PB_LCD_BL			2U
#define PB_LCD_SPI2_CS		2U
#define PD_LCD_SPI2_CLK		3U
#define PB_LCD_SPI2_MISO	14U
#define PB_LCD_SPI2_MOSI	15U

#define PE_NAV_SW1			0
#define PE_NAV_SW2			2


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Macro
******************************************************************************/
#define BIT( x )					(1U<<(x))

/* LEDs */
#define LED_RED_ON()				(GPIOB->BSRR = BIT(PB_LED_RED))
#define LED_RED_OFF()				(GPIOB->BSRR = (BIT(PB_LED_RED)<<16U))
#define LED_RED_SET( x )			((x)? LED_RED_ON() : LED_RED_OFF())

#define LED_BLUE_ON()				(GPIOB->BSRR = BIT(PB_LED_BLUE))
#define LED_BLUE_OFF()				(GPIOB->BSRR = (BIT(PB_LED_BLUE)<<16U))
#define LED_BLUE_SET( x )			((x)? LED_BLUE_ON() : LED_BLUE_OFF())

#define LED_ZIO_OB1_ON()			(GPIOF->BSRR = BIT(PF_LED_OB1))
#define LED_ZIO_OB1_OFF()			(GPIOF->BSRR = (BIT(PF_LED_OB1)<<16U))
#define LED_ZIO_OB1_SET( x )		((x)? LED_ZIO_OB1_ON() : LED_ZIO_OB1_OFF())

#define LED_ZIO_OB2_ON()			(GPIOF->BSRR = BIT(PF_LED_OB2))
#define LED_ZIO_OB2_OFF()			(GPIOF->BSRR = (BIT(PF_LED_OB2)<<16U))
#define LED_ZIO_OB2_SET( x )		((x)? LED_ZIO_OB2_ON() : LED_ZIO_OB2_OFF())



/* LCD */
#define LCD_RESET_LOW()				(GPIOB->BSRR = (BIT(PB_LCD_RESET)<<16U))
#define LCD_RESET_HIGH()			(GPIOB->BSRR = BIT(PB_LCD_RESET))
#define LCD_RESET_SET( x )			((x)? LCD_RESET_HIGH() : LCD_RESET_LOW())

#define LCD_DC_HIGH()				(GPIOE->BSRR = BIT(PE_LCD_DC))
#define LCD_DC_LOW()				(GPIOE->BSRR = (BIT(PE_LCD_DC)<<16U))
#define LCD_DC_SET( x )				((x)? LCD_DC_HIGH() : LCD_DC_LOW())

#define LCD_BL_ON()					(GPIOB->BSRR = BIT(PB_LCD_BL))
#define LCD_BL_OFF()				(GPIOB->BSRR = (BIT(PB_LCD_BL)<<16U))
#define LCD_BL_SET( x )				((x)? LCD_BL_ON() : LCD_BL_OFF())

#define LCD_CS_LOW()				(GPIOB->BSRR = (BIT(PB_LCD_SPI2_CS)<<16U))
#define LCD_CS_HIGH()			(GPIOB->BSRR = BIT(PB_LCD_SPI2_CS))


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









