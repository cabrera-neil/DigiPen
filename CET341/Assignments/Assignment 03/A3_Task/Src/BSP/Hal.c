/*****************************************************************************
 @Project	: 
 @File 		: Hal.c
 @Details  	: All Ports and peripherals configuration                    
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name          XXXX-XX-XX       Initial Release
   1.1  Neil Cabrera  2019-09-22       Updated for Assignment 02  
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "proj_def.h"


/*****************************************************************************
 Define
******************************************************************************/
#define __ASSIGN_TODO

/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/


/*****************************************************************************
 Implementation
******************************************************************************/
void PortInit( void )
{
	/* peripherals bus clocks enable */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN
					| RCC_AHB1ENR_GPIOFEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
#ifdef __ASSIGN_TODO
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
#endif

	/*******************************
	 LED control pins
	********************************/
#ifdef __ASSIGN_TODO
	GPIOB->MODER &= ~GPIO_MODER_MODER0;									/* PB_LED_LD1 */
	GPIOB->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER0_Pos);
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR0_Msk;
	GPIOB->PUPDR |= (GPIO_PULL_DIS<<GPIO_PUPDR_PUPDR0_Pos);
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR0;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR0_Pos);
	GPIOB->BSRR = GPIO_BSRR_BR_0;

	GPIOB->MODER &= ~GPIO_MODER_MODER7;									/* PB_LED_LD2 */
	GPIOB->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER7_Pos);
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7_Msk;
	GPIOB->PUPDR |= (GPIO_PULL_DIS<<GPIO_PUPDR_PUPDR7_Pos);
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR7;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR7_Pos);
	GPIOB->BSRR = GPIO_BSRR_BR_7;
	
	GPIOB->MODER &= ~GPIO_MODER_MODER14;								/* PB_LED_LD3 */
	GPIOB->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER14_Pos);
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR14_Msk;
	GPIOB->PUPDR |= (GPIO_PULL_DIS<<GPIO_PUPDR_PUPDR14_Pos);
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR14;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR14_Pos);
	GPIOB->BSRR = GPIO_BSRR_BR_14;
#endif
}


























