/*****************************************************************************
 @Project    : CET341 Assignment
 @File       : main.c
 @Details    : Main entry
 @Author     : Liang Tang
 @Hardware   : STM32
 

 --------------------------------------------------------------------------
 @Revision   :
  Ver      Author       Date             Changes
 --------------------------------------------------------------------------
  1.0     Liang Tang    2019-09-12       Initial Release
  1.1     Neil Cabrera  2019-09-13       Update to make changes for Assignment 02
******************************************************************************/
#include "Common.h"
#include <string.h>
#include "Hal.h"
#include "BSP.h"


/*****************************************************************************
 Define
******************************************************************************/
/* Software Timer with 10 ms 
   Increase the Value in order to see the blinking */
#define SYS_TICK_MS 10 

/*****************************************************************************
 Static Global Variables
******************************************************************************/
static volatile int g_nSysTick = SYS_TICK_MS;
static BOOL g_toggle = FALSE;

/*****************************************************************************
 Implementation
******************************************************************************/
int main( void )
{
  uint32_t systick_ticks;

  BSPInit();

/************************************************
* To do: 
* Refer to the definition of SysTick_Config,
* prepare the input argument: systick_ticks
************************************************/
  systick_ticks = SystemCoreClock / 1000;
  
  SysTick_Config(systick_ticks);

  while( 1 )
  {
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
  }    
}


/*****************************************************************************
 Exception handler
******************************************************************************/
void SysTick_Handler( void )
{
  /************************************************
  * Toggles Both Red and Blue LED
  * SysTick exception handler implementation
  ************************************************/
  if( 0 != g_nSysTick )
  {
      g_nSysTick--;

      if( 0 == g_nSysTick )
      {
          g_nSysTick = SYS_TICK_MS;

          if(!g_toggle)
          {
            LED_BLUE_ON();
            LED_RED_ON();
            g_toggle = TRUE;
          }
          else
          {
            LED_BLUE_OFF();
            LED_RED_OFF();
            g_toggle = FALSE;
          }
      }
  }
}

