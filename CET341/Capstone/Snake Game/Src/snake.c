/*****************************************************************************
 @Project	: 
 @File 		: snake.c
 @Details  	:
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/

#include "snake.h"

/*****************************************************************************
 Functions
******************************************************************************/
void RNG_Init(void) {
  /* Enable RNG clock source */
  RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;

  /* RNG Peripheral enable */
  RNG->CR |= RNG_CR_RNGEN;
}

uint32_t RNG_Get(void) {
  /* Wait until the Random Number is Generated */
  while ( RNG->SR & 0x0001 == 0 ){}

  /* Get a 32bit Random number */
  return RNG->DR;
}