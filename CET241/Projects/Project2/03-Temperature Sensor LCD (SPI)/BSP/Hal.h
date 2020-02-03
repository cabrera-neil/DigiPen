/*****************************************************************************
 @Project	: 
 @File 		: 
 @Details : All Ports and peripherals configuration                    
 @Author	: 
 @Hardware: 

   
******************************************************************************/

#ifndef __HAL_DOT_H__
#define __HAL_DOT_H__

/*****************************************************************************
 Define
******************************************************************************/
#define PF_LED_RED			1U
#define PF_LED_BLUE			2U
#define PF_LED_GREEN		3U

#define PA_LCD_SSI0_SCK		2U
#define PA_LCD_SSI0_MOSI 	5U

#define PA_LCD_SSI0_CS		3U
#define PA_LCD_BL					4U
#define PA_LCD_DC					6U
#define PA_LCD_RESET			7U

/*****************************************************************************
 Macro
******************************************************************************/
#define BIT( x )						(1U<<(x))

/* LEDs */
#define LED_RED_ON()				(GPIOF->DATA |= BIT(PF_LED_RED))
#define LED_RED_OFF()				(GPIOF->DATA &= ~BIT(PF_LED_RED))
#define LED_RED_SET( x )		((x)? LED_RED_ON() : LED_RED_OFF())

#define LED_BLUE_ON()				(GPIOF->DATA |= BIT(PF_LED_BLUE))
#define LED_BLUE_OFF()			(GPIOF->DATA &= ~BIT(PF_LED_BLUE))
#define LED_BLUE_SET( x )		((x)? LED_BLUE_ON() : LED_BLUE_OFF())

#define LED_GREEN_ON()			(GPIOF->DATA |= BIT(PF_LED_GREEN))
#define LED_GREEN_OFF()			(GPIOF->DATA &= ~BIT(PF_LED_GREEN))
#define LED_GREEN_SET( x )	((x)? LED_GREEN_ON() : LED_GREEN_OFF())

/* LCD */
#define LCD_CS_HIGH()				(GPIOA->DATA |= BIT(PA_LCD_SSI0_CS))
#define LCD_CS_LOW()				(GPIOA->DATA &= ~BIT(PA_LCD_SSI0_CS))
#define LCD_CS_SET( x )			((x)? LCD_CS_ON() : LCD_CS_OFF())


#define LCD_DC_HIGH()				(GPIOA->DATA |= BIT(PA_LCD_DC))
#define LCD_DC_LOW()				(GPIOA->DATA &= ~BIT(PA_LCD_DC))
#define LCD_DC_SET( x )			((x)? LCD_DC_ON() : LCD_DC_OFF())

#define LCD_RESET_HIGH()		(GPIOA->DATA |= BIT(PA_LCD_RESET))
#define LCD_RESET_LOW()			(GPIOA->DATA &= ~BIT(PA_LCD_RESET))
#define LCD_RESET_SET( x )	((x)? LCD_RESET_LOW() : LCD_RESET_HIGH())

#define LCD_BL_ON()					(GPIOA->DATA |= BIT(PA_LCD_BL))
#define LCD_BL_OFF()				(GPIOA->DATA &= ~BIT(PA_LCD_BL))
#define LCD_BL_SET( x )			((x)? LCD_BL_ON() : LCD_BL_OFF())


/******************************************************************************
 Global functions
******************************************************************************/

void PortInit( void );
#endif /* __HAL_DOT_H__ */









