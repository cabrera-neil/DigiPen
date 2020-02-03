/*****************************************************************************
 @Project	:
 @File 		: main.c
 @Details  	: Main entry
 @Author	: lcgan
 @Hardware	: STM32
 

 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   

******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "IRQ.h"
#include "BSP.h"
#include "Dma.h"
#include "Spim.h"

#include "RTOS.h"

#include "LCD_ST7735R.h"
#include "GUI.h"
#include "WM.h"

/* NOTE: Please follows code style provided. All tabs is 4 space */
/* NOTE: For Graphic emWin Library API, please get manual from 
https://www.segger.com/downloads/emwin/ */

/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS 500 /* Software Timer with 500 ms */

#define SYSINIT_TASK_STACK_SIZE 800
#define LED_TASK_STACK_SIZE 500
#define LED2_TASK_STACK_SIZE 300


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/
extern GUI_CONST_STORAGE GUI_BITMAP bmCE;


/*****************************************************************************
 Const Local Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int g_nSysTick = SYS_TICK_MS;
static volatile BOOL g_bSysTickReady = FALSE;

static TaskHandle_t xsysInitHandle = 0;
static StaticTask_t xSysInitTCB;
static StackType_t xSysInitStack[SYSINIT_TASK_STACK_SIZE];

static StaticTask_t xLed1TCB;
static StackType_t xLed1Stack[LED_TASK_STACK_SIZE];

static StaticTask_t xLed2TCB;
static StackType_t xLed2Stack[LED2_TASK_STACK_SIZE];

static SPIM_HANDLE g_SpimLcdHandle;
static DMA_HANDLE g_Dma1Spi2TxHandle;
static DMA_HANDLE g_Dma1Spi2RxHandle;


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_SpimInit( void );
static void main_LcdInit( void );


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 RTOS Tasks
******************************************************************************/
static void SystemInitTask( void* pvParameters );
static void Led1Task( void* pvParameters );
static void Led2Task( void* pvParameters );


/*****************************************************************************
 Implementation
******************************************************************************/
int main( void )
{
    /* Board support package initialization */
    BSPInit( );

    /* System info */
    TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock %dHz\r\n", SystemCoreClock );

    /* SPI master initialization for LCD */
    main_SpimInit();


    /* LCS driver Initialization */
    main_LcdInit();

    /* OS Tasks Creation */

    /* System module initialization task */
    xsysInitHandle = xTaskCreateStatic( SystemInitTask, "SystemInitTask",
                       SYSINIT_TASK_STACK_SIZE, NULL, 1, xSysInitStack,
                       &xSysInitTCB );

    /* Start the tasks and timer running. */
    vTaskStartScheduler( );

    /* OS failed will reached here */
    while( 1 ) {}
}


static void SystemInitTask( void* pvParameters )
{
    char buf[128];
    int nCount = 0;

    /* NOTE: If using emWin library with OS, GUI_Init() must called in a Task, 
    because Os delay is in use in the GUI initialization */
    GUI_Init( );

    GUI_SetBkColor( GUI_GREEN );

    GUI_SetColor( GUI_BLUE );
    GUI_Clear( );

    GUI_SetFont( &GUI_Font8x16 );

    GUI_SetColor( GUI_BLACK );
    GUI_DispStringAt( "Test", 0, 0 );

    IRQInit( );

    GUI_DrawBitmap( &bmCE, 0, 0 );

    vTaskDelay( 3000 );

    GUI_Clear();
    

    /* Led blinking task */
    xTaskCreateStatic( Led1Task, "Led1Task", LED_TASK_STACK_SIZE, NULL, 2,
                       xLed1Stack, &xLed1TCB );

    xTaskCreateStatic( Led2Task, "Led2Task", LED2_TASK_STACK_SIZE, NULL, 3,
                       xLed2Stack, &xLed2TCB );

    MainTask();

    vTaskDelete ( xsysInitHandle );
}


static void Led1Task( void* pvParameters )
{
    BOOL toggle = FALSE;

    for( ;; )
    {
        TRACE( "LED1 task is running\r\n" );
        toggle = !toggle;
        LED_ZIO_OB1_SET( toggle );

        vTaskDelay( 200 );
    }
}


static void Led2Task( void* pvParameters )
{
    BOOL toggle = FALSE;
    for( ;; )
    {
        TRACE( "LED2 task is running\r\n" );
        toggle = !toggle;
        LED_ZIO_OB2_SET( toggle );
        vTaskDelay( 300 );
    }
}

/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_SpimInit( void )
{
    int res;

    res = DmaInit( &g_Dma1Spi2TxHandle, 1, DMA1_SPI2_TX_CH, 0,
                   DMA_DIR_MEM_TO_PERI, DMA_MEM_INC_EN, DMA_DATA_ALIGN_BYTE,
                   DMA_PERI_INC_DIS, DMA_DATA_ALIGN_BYTE );
    ASSERT( DMA_OK == res );

    res = DmaInit( &g_Dma1Spi2RxHandle, 1, DMA1_SPI2_RX_CH, 0,
                   DMA_DIR_PERI_TO_MEM, DMA_MEM_INC_DIS, DMA_DATA_ALIGN_BYTE,
                   DMA_PERI_INC_DIS, DMA_DATA_ALIGN_BYTE );
    ASSERT( DMA_OK == res );

    /* LCD SPI */
    SpimInit( &g_SpimLcdHandle, 2, 15000000, SPI_CLK_INACT_LOW,
              SPI_CLK_RISING_EDGE, SPI_DATA_SIZE_8 );
}


static void main_LcdInit( void )
{
    int screenx;
    int screeny;
    int res;

    /* g_SpimLcdHandle shall be initialized before use */

    /* Choosing a landscape orientation */
    LcdInit( &g_SpimLcdHandle, LCD_LANDSCAPE );
}


/*****************************************************************************
 Interrupt functions
******************************************************************************/
void OS_SysTickHandler( void )
{
    /* NOTE:
    It is more efficient to compare to 0 for Cortex M
    */

    /* Provide system tick with a specified period
    decided by macro SYS_TICK_MS */
    if( 0 != g_nSysTick )
    {
        g_nSysTick--;

        if( 0 == g_nSysTick )
        {
            g_nSysTick = SYS_TICK_MS;
            g_bSysTickReady = TRUE;
        }
    }
}