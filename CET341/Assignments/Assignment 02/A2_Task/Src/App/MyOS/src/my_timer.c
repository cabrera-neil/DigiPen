/*****************************************************************************
 @Project    : CET341 Assignment
 @File       : my_timer.c
 @Details    : Timer ISR
 @Author     : Liang Tang
 @Hardware   : STM32F46 only
 --------------------------------------------------------------------------
 @Revision   :
  Ver      Author       Date             Changes
 --------------------------------------------------------------------------
  1.0     Liang Tang    2019-09-19       Initial Release
******************************************************************************/

#include "Common.h"
#include "Hal.h"
#include "Timer.h"


/*****************************************************************************
 Define
******************************************************************************/
#define TOTAL_TIMER        14U


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile PTIMER_HANDLE g_aTimerIrqHandle[TOTAL_TIMER] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


/*****************************************************************************
 Local Functions
******************************************************************************/
static void timer_IRQHandler( PTIMER_HANDLE pHandle );


/*****************************************************************************
 Implementation
******************************************************************************/
/******************************************************************************
 @Description : Initialize the timer interrupt
 @param       : pHandle: the handler of the timer;
                nTimer: ID of the timer;
                nFreq: frequency of the timer (unit: Hz);
******************************************************************************/
int TimerInit( PTIMER_HANDLE pHandle, uint8_t nTimer, uint32_t nFreq )
{
  TIM_TypeDef *timer;
  IRQn_Type   irq;
  uint32_t   clock    = SystemCoreClock;
  uint32_t   count    = 0U;
  uint32_t   prescale = 0U;
  int        apb      = 0;
  
  ASSERT( 0 != pHandle );
  ASSERT( 0 != nTimer  );
  ASSERT( 0 != nFreq   );

  /* Timer selection base on user specified */
  switch( nTimer )
  {
    case 1U:
      timer = TIM1;
      irq = TIM1_UP_TIM10_IRQn;
      apb = 2;
    break;
    
    case 2U:
      timer = TIM2;
      irq = TIM2_IRQn;
            apb = 1;
    break;
    
    case 3U:
      timer = TIM3;
      irq = TIM3_IRQn;
      apb = 1;
    break;
    
    case 4U:
      timer = TIM4;
      irq = TIM4_IRQn;
      apb = 1;
    break;
    
    case 5U:
      timer = TIM5;
      irq = TIM5_IRQn;
      apb = 1;
    break;
    
    case 6U:
      timer = TIM6;
      irq = TIM6_DAC_IRQn;
      apb = 1;
    break;
    
    case 7U:
      timer = TIM7;
      irq = TIM7_IRQn;
      apb = 1;
    break;
    
    case 8U:
      timer = TIM8;
      irq = TIM8_UP_TIM13_IRQn;
      apb = 2;
    break;

    case 9U:
      timer = TIM9;
      irq = TIM1_BRK_TIM9_IRQn;
      apb = 2;
    break;

    case 10U:
      timer = TIM10;
      irq = TIM1_UP_TIM10_IRQn;
      apb = 2;
    break;

    case 11U:
      timer = TIM11;
      irq = TIM1_TRG_COM_TIM11_IRQn;
      apb = 2;
    break;
  
    case 12U:
      timer = TIM12;
      irq = TIM8_BRK_TIM12_IRQn;
      apb = 1;
    break;

       case 13U:
      timer = TIM13;
      irq = TIM8_UP_TIM13_IRQn;
      apb = 1;
    break;

    case 14U:
      timer = TIM14;
      irq = TIM8_TRG_COM_TIM14_IRQn;
      apb = 1;
    break;

    default:
      return TIMER_ERR_INVALID;    /* User specified an invalid timer, return error */
  }
  
  if( (0 != (timer->CR1&TIM_CR1_CEN)) || (0 != (timer->CR1&TIM_CR1_ARPE)) )
  {
    /* Timer has been used for others. overlap is not possible */
    return TIMER_ERR_USED;
  }

  /* Keep the timer pointer into handle for next use */
  pHandle->pTimer = timer;
  pHandle->Irq = irq;
  
  /* Keep the handle pointer into a local variable so that it can be accessed in ISR */
  g_aTimerIrqHandle[nTimer-1] = pHandle;

  timer->CR1 &= ~(TIM_CR1_DIR   /* Direction: up counter */
                | TIM_CR1_OPM   /* One pulse mode: Counter is not stopped at update event */
                | TIM_CR1_CKD   /* Clock division*/
                | TIM_CR1_CMS); /* Center align mode */
  
  /* Different timer has different APB bus */
  if( 1 == apb )
  {
    /* Re-calculate current bus clock. User may change it in Hal.c */
    switch( RCC->CFGR & RCC_CFGR_PPRE1 )
    {
      case RCC_CFGR_PPRE1_DIV1:
        clock = SystemCoreClock;
      break;
    
      case RCC_CFGR_PPRE1_DIV2:
        clock = SystemCoreClock>>1U;
      break;
    
      case RCC_CFGR_PPRE1_DIV4:
        clock = SystemCoreClock>>2U;
      break;
    
      case RCC_CFGR_PPRE1_DIV8:
        clock = SystemCoreClock>>3U;
      break;
    
      case RCC_CFGR_PPRE1_DIV16:
        clock = SystemCoreClock>>4U;
      break;

      default:
      break;
    }
  }
  
  if( 2 == apb )
  {
    /* Re-calculate current bus clock. User may change it in Hal.c */
    switch( RCC->CFGR & RCC_CFGR_PPRE2 )
    {
      case RCC_CFGR_PPRE2_DIV1:
        clock = SystemCoreClock;
      break;
    
      case RCC_CFGR_PPRE2_DIV2:
        clock = SystemCoreClock>>1U;
      break;
    
      case RCC_CFGR_PPRE2_DIV4:
        clock = SystemCoreClock>>2U;
      break;
    
      case RCC_CFGR_PPRE2_DIV8:
        clock = SystemCoreClock>>3U;
      break;
    
      case RCC_CFGR_PPRE1_DIV16:
        clock = SystemCoreClock>>4U;
      break;

      default:
      break;
    }
  }

    /* Refer to manual page 127 */
  if( 0 == (RCC->DCKCFGR1 & RCC_DCKCFGR1_TIMPRE) )
  {
    clock = 2 * clock;
  }

  /* Calculate auto reload counter and its prescaler */
  count = clock / nFreq;
  while( count >= 0xffffU )
  {
    /* Prescaler is needed since the count over 16 bits */
    count = clock / nFreq;
    
    /* try to increase presacaler */
    prescale++;

    /* divide again */
    count /= (prescale + 1);
  }

  if( 0 != prescale )
  {
    /* prescaler is applicable */
    timer->PSC = prescale;
  }
  
  /* the rest of the count store into auto reload counter register */
  timer->ARR = count;
  
  return TIMER_OK;
}


/******************************************************************************
 @Description : Start the configured timer;
 @param       : pHandle: the handler of the timer;
******************************************************************************/
void TimerStart( PTIMER_HANDLE pHandle )
{
  TIM_TypeDef *timer = pHandle->pTimer;

  ASSERT( 0 != pHandle );

  /* enable update generation interrupt */
  timer->EGR |= TIM_EGR_UG;
  
  /* Timer counting enable with auto reload */
  timer->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
  
  /* Enable Timer interrupt */
  timer->DIER |= TIM_DIER_UIE;
  
  /* Enable NVIC controller for this timer irq */
  NVIC_EnableIRQ( pHandle->Irq );
}


/******************************************************************************
 @Description : Stop the configured timer;
 @param       : pHandle: the handler of the timer;
******************************************************************************/
void TimerStop( PTIMER_HANDLE pHandle )
{
  TIM_TypeDef *timer = pHandle->pTimer;

  ASSERT( 0 != pHandle );

  /* Disable update generation interrupt */
  timer->EGR &= ~TIM_EGR_UG;
  
  /* Timer counting Disable with auto reload */
  timer->CR1 &= ~(TIM_CR1_CEN | TIM_CR1_ARPE);
  
  /* Disable Timer interrupt */
  timer->DIER &= ~TIM_DIER_UIE;
  
  /* Disable NVIC controller for this timer irq */
  NVIC_DisableIRQ( pHandle->Irq );
}


/******************************************************************************
 @Description : Attach hook function to the timer ISR;
 @param       : pHandle: the handler of the timer;
                pHook: the link list node which holds the callBack function;
                pfUpdate: the callback function;
******************************************************************************/
void 
TimerAddHook(
  PTIMER_HANDLE     pHandle,
  PTIMER_HOOK       pHook,
  TIMER_CB_UPDATE  *pfUpdate
  )
{
  ASSERT( 0 != pHandle );
  ASSERT( 0 != pHook );
  ASSERT( 0 != pfUpdate );
  
  /* Insert into link list */
  pHook->pfUpdate = pfUpdate;
  pHook->pNext = pHandle->pHeadHook;
  pHandle->pHeadHook = pHook;
}


/******************************************************************************
 @Description : The generic ISR for all timers;
 @param       : pHandle: the handler of the timer;
******************************************************************************/
static void timer_IRQHandler( PTIMER_HANDLE pHandle )
{
  TIM_TypeDef *timer = pHandle->pTimer;
  PTIMER_HOOK cur;
  int      status;

  ASSERT( 0 != pHandle );
  
  /* Read a copy of timer status */
  status = timer->SR;

  if( 0 != (status & TIM_SR_UIF) )
  {
    timer->SR &= ~TIM_SR_UIF;

    /* Timer interrupted due to timer update flag set */
    
    /* Make sure link list first object is not null */
    if( 0 != pHandle->pHeadHook )
    {
      /* Iterates a link list */
      for( cur=pHandle->pHeadHook; 0 != cur; cur=cur->pNext )
      {
        ASSERT( 0 != cur->pfUpdate );
        cur->pfUpdate();
      }
    }
  }
}


/*****************************************************************************
 Interrupt handling
******************************************************************************/
void TIM1_UP_TIM10_IRQHandler( void )
{
    /* Timer 1 and 10 shared the same IRQ */
  if( 0 != g_aTimerIrqHandle[0] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[0] );
  }

  if( 0 != g_aTimerIrqHandle[9] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[9] );
  }
}

void TIM2_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[1] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[1] );
  }
}


void TIM3_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[2] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[2] );
  }
}


void TIM4_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[3] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[3] );
  }
}


void TIM5_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[4] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[4] );
  }
}


void TIM6_DAC_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[5] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[5] );
  }
}


void TIM7_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[6] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[6] );
  }
}


void TIM8_UP_TIM13_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[7] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[7] );
  }

  if( 0 != g_aTimerIrqHandle[12] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[12] );
  }
}


void TIM1_BRK_TIM9_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[8] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[8] );
  }
}


void TIM1_TRG_COM_TIM11_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[10] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[10] );
  }
}


void TIM8_BRK_TIM12_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[11] )
  {
    timer_IRQHandler( g_aTimerIrqHandle[11] );
  }
}


void TIM8_TRG_COM_TIM14_IRQHandler( void )
{
  if( 0 != g_aTimerIrqHandle[13]  )
  {
    timer_IRQHandler( g_aTimerIrqHandle[13] );
  }
}


