/*****************************************************************************
 @Project	: 
 @File 		: Clock.c
 @Details  	: All Ports and peripherals configuration                    
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/
#include <Common.h>
#include "Clock.h"


/*****************************************************************************
 Define
******************************************************************************/
#define RCC_HSICALIBRATION_DEFAULT     ((uint32_t)0x10U)         /* Default HSI calibration trimming value */


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
void
ClockInit(
	uint32_t nPllm,
	uint32_t nPlln,
	uint32_t nPllp,
	uint32_t nPllq
	)
{
	int32_t tmp;

	/* HSE ON */
	RCC->CR = RCC_CR_HSION;
	while( 0 == (RCC->CR&RCC_CR_HSIRDY) ){}
	
    /* Set Internal RC default Calibartion trim */
    tmp = RCC->CR;
	tmp &= ~RCC_CR_HSITRIM;
	tmp |= RCC_HSICALIBRATION_DEFAULT<<RCC_CR_HSITRIM_Pos;
	RCC->CR = tmp;

	RCC->CR &= ~RCC_CR_PLLON;
	while( 0 != (RCC->CR&RCC_CR_PLLRDY) );
	
	ClockSetWaitStates( 216000000 );
	
	tmp = 0x20000000;
	tmp |= RCC_PLLCFGR_PLLSRC_HSI 
		| (nPllm<<RCC_PLLCFGR_PLLM_Pos) 
		| (nPlln<<RCC_PLLCFGR_PLLN_Pos)
		| (((nPllp>>1)-1)<<RCC_PLLCFGR_PLLP_Pos)
		| (nPllq<<RCC_PLLCFGR_PLLQ_Pos);
	RCC->PLLCFGR = tmp;
	
	RCC->CR |= RCC_CR_PLLON;
	while( 0 == (RCC->CR&RCC_CR_PLLRDY) ){}	
	
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	
	/* Activate the OverDrive to reach the 216 Mhz Frequency */
	/* Enable the Over-drive to extend the clock frequency to 216 MHz */
	PWR->CR1 |= PWR_CR1_ODEN;
	while( 0 == (PWR->CSR1&PWR_CSR1_ODRDY) );
	
	PWR->CR1 |= PWR_CR1_ODSWEN;
	while( 0 == (PWR->CSR1&PWR_CSR1_ODSWRDY) );
	
	tmp = RCC->CFGR;
	tmp &= ~RCC_CFGR_HPRE;
	tmp |= RCC_CFGR_HPRE_DIV1;
	RCC->CFGR  = tmp;
	while( 0 == (RCC->CR&RCC_CR_HSIRDY) ){}
	
	tmp = RCC->CFGR;
	tmp &= ~(RCC_CFGR_PPRE1 
			| RCC_CFGR_PPRE2);
	tmp |= RCC_CFGR_PPRE1_DIV4 
			| RCC_CFGR_PPRE2_DIV2;
	RCC->CFGR = tmp;
	
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while( 0 == (RCC->CFGR&RCC_CFGR_SWS_PLL) );	
}


void ClockSetWaitStates( uint32_t nSysClock )
{
	if( nSysClock <= 30000000U )
	{
		FLASH->ACR |= FLASH_ACR_LATENCY_0WS;
	}
	else if( nSysClock <= 60000000U )
	{
		FLASH->ACR |= FLASH_ACR_LATENCY_1WS;
	}
	else if( nSysClock <= 90000000U )
	{
		FLASH->ACR |= FLASH_ACR_LATENCY_2WS;
	}
	else if( nSysClock <= 120000000U )
	{
		FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
	}
	else if( nSysClock <= 150000000U )
	{
		FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
	}
	else if( nSysClock <= 180000000U )
	{
		FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
	}
	else if( nSysClock <= 210000000U )
	{
		FLASH->ACR |= FLASH_ACR_LATENCY_6WS;
	}
	else if( nSysClock <= 216000000U )
	{
		FLASH->ACR |= FLASH_ACR_LATENCY_7WS;
	}
}





















