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
#include "Serial.h"
#include "Spim.h"

#include "RTOS.h"

#include "LCD_ST7735R.h"
#include "GUI.h"
#include "WM.h"

#include "snake.h"

/* NOTE: Please follows code style provided. All tabs is 4 space */
/* NOTE: For Graphic emWin Library API, please get manual from 
https://www.segger.com/downloads/emwin/ */

/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS 500 /* Software Timer with 500 ms */

#define SYSINIT_TASK_STACK_SIZE   800
#define LED1_TASK_STACK_SIZE      300
#define LED2_TASK_STACK_SIZE      300
#define NAVSW_TASK_STACK_SIZE     500
#define SNAKE_TASK_STACK_SIZE     500
#define SCORE_TASK_STACK_SIZE     500

/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/
extern GUI_CONST_STORAGE GUI_BITMAP bmsnakegame;


/*****************************************************************************
 Const Local Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int g_nSysTick       = SYS_TICK_MS;
static volatile BOOL g_bSysTickReady = FALSE;

static StaticTask_t xSysInitTCB;
static StaticTask_t xLed1TCB;
static StaticTask_t xLed2TCB;
static StaticTask_t xNavSwTCB;
static StaticTask_t xSnakeTCB;
static StaticTask_t xScoreTCB;

static StackType_t xSysInitStack  [SYSINIT_TASK_STACK_SIZE];
static StackType_t xLed1Stack     [LED1_TASK_STACK_SIZE];
static StackType_t xLed2Stack     [LED2_TASK_STACK_SIZE];
static StackType_t xNavSwStack    [NAVSW_TASK_STACK_SIZE];
static StackType_t xSnakeStack    [SNAKE_TASK_STACK_SIZE];
static StackType_t xScoreStack    [SCORE_TASK_STACK_SIZE];

// Peripheral Handles
static SPIM_HANDLE g_SpimLcdHandle;
static DMA_HANDLE g_Dma1Spi2TxHandle;
static DMA_HANDLE g_Dma1Spi2RxHandle;

// Task Handles
static TaskHandle_t xsysInitHandle    = (TaskHandle_t) 0;
static TaskHandle_t xNavSwHandle      = (TaskHandle_t) 1;
static TaskHandle_t xLed1TaskHandle   = (TaskHandle_t) 2;
static TaskHandle_t xLed2TaskHandle   = (TaskHandle_t) 3;
static TaskHandle_t xSnakeTaskHandle  = (TaskHandle_t) 4;
static TaskHandle_t xScoreTaskHandle  = (TaskHandle_t) 5;

static volatile int g_Xres = 0;
static volatile int g_Yres = 0;

static USB_HIDHOST_Result_t    USB_HIDHOST_INT_Result;
static USB_HIDHOST_Keyboard_t  USB_HIDHOST_INT_Keyboard;

USB_HIDHOST_Keyboard_t Keyboard;

volatile int8_t Random[2], Snake_Food[2];
volatile int8_t Snake_Head[2], Snake_Head_Last[2], Snake_Foot[2];

volatile uint8_t Snake_FirstTime = 1;
volatile uint8_t GameOver = 0, GameOverDisplay = 0;

char Buffer[50];

volatile BOOL g_GameStart = FALSE;
volatile SNAKE_t Snake, Snake1;
volatile SNAKE_Settings_t Settings, Settings1;

/*****************************************************************************
 Local functions
******************************************************************************/
static void main_SpimInit( void );
static void main_LcdInit( void );

void SNAKE_Start(void);

void SNAKE_DrawPixel(uint8_t x, uint8_t y, uint16_t value);
void SNAKE_PrepareDisplay(void);
void SNAKE_DrawArea(void);
void SNAKE_SetDefaultSnake(void);
void SNAKE_SetFirstOptions(void);

void SNAKE_DeleteFromArray(uint16_t index, int8_t* twobytesarray);
void SNAKE_AddToArray(int8_t* twobytesarray);
void SNAKE_ReplaceArray(uint16_t index, int8_t* twobytesarray); 

void SNAKE_SpeedUp(void);
void SNAKE_SpeedDown(void);

void SNAKE_Random(int8_t* twobytesarray);
void SNAKE_GenerateTarget(void);

/* Check if given X and Y location matches coordinates where snake is */
uint8_t SNAKE_MatchesSnakeLocations(int8_t* twobytesarray);

static USB_HIDHOST_Result_t USB_HIDHOST_ReadKeyboard(USB_HIDHOST_Keyboard_t* Keyboard);
/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 RTOS Tasks
******************************************************************************/
static void SystemInitTask( void* pvParameters );
static void Led1Task( void* pvParameters );
static void Led2Task( void* pvParameters );
static void SnakeTask( void* pvParameters );
static void ScoreTask( void* pvParameters );

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
    xsysInitHandle = xTaskCreateStatic( SystemInitTask, "SystemInitTask", SYSINIT_TASK_STACK_SIZE, NULL, 1, xSysInitStack, &xSysInitTCB );

    /* Start the tasks and timer running. */
    vTaskStartScheduler( );

    /* OS failed will reached here */
    for( ;; ) {}
}

static void SystemInitTask( void* pvParameters )
{
    /* NOTE: If using emWin library with OS, GUI_Init() must called in a Task, 
    because Os delay is in use in the GUI initialization */
    GUI_Init( );

    IRQInit( );

    /* Get Screen Resolution */
    LCD_GetSize( &g_Xres, &g_Yres );

    /* Display Starting Wallpaper */
    GUI_DrawBitmap( &bmsnakegame, 0, 0 );

    GUI_SetColor( ILI9341_COLOR_WHITE );
    GUI_SetFont( &GUI_Font8x8 );
    GUI_DispStringAt( "Press START to play!", 0, 120 );

    /* Play Start Game Music */
    LED_GREEN_SET(TRUE);
    MS_START_SET(TRUE);

    /* Wait for the Game to Start */
    LED_ZIO_OB1_OFF();
    LED_ZIO_OB2_OFF();

    while ( !g_GameStart ) {}

    /* Stop Start Game Music */
    LED_GREEN_SET(FALSE);
    MS_START_SET(FALSE);

    vTaskDelay( 1000 );
    GUI_Clear();

    /* LED Tasks, One for Game Running and the Other One for Game Over */
    xLed1TaskHandle = xTaskCreateStatic( Led1Task, "Led1Task", LED1_TASK_STACK_SIZE, NULL, 3, xLed1Stack, &xLed1TCB );
    xLed2TaskHandle = xTaskCreateStatic( Led2Task, "Led2Task", LED2_TASK_STACK_SIZE, NULL, 3, xLed2Stack, &xLed2TCB );

    /* Snake Moving Task */
    xSnakeTaskHandle = xTaskCreateStatic( SnakeTask, "SnakeTask", SNAKE_TASK_STACK_SIZE, NULL, 1, xSnakeStack, &xSnakeTCB );
  
    /* Score and Time Task */
    xScoreTaskHandle = xTaskCreateStatic( ScoreTask, "ScoreTask", SCORE_TASK_STACK_SIZE, NULL, 1, xScoreStack, &xScoreTCB );

    vTaskDelete ( xsysInitHandle );
}

static void Led1Task( void* pvParameters )
{
    for( ;; )
    {
        if ( !GameOver )
          TRACE( "Game is now running\r\n" );
        
        LED_ZIO_OB1_SET( !GameOver );

        vTaskDelay( 5 );
    }
}

static void Led2Task( void* pvParameters )
{
    for( ;; )
    {
        if ( GameOver )
          TRACE( "Game Over \r\n" );
        
        LED_ZIO_OB2_SET( GameOver );
        vTaskDelay( 5 );
    }
}

static void ScoreTask ( void* pvParameters )
{
    for( ;; )
    {
        /* Display Hit and Score */
        if (!GameOver)
        {
          sprintf(Buffer, "Hits:%d;  Score: %d;  ", Snake.Hits, (2 - Settings.Overflow) * Snake.Hits * Settings.Speed / 2);
          GUI_SetFont( &GUI_Font8x8 );
          GUI_DispStringAt( Buffer, 1, 1 );
        }

        vTaskDelay( 5 );
    }
}

static void SnakeTask( void* pvParameters )
{
    /* Initialize True random number generator */
    RNG_Init();

    /* Set default options */
    SNAKE_SetFirstOptions();

    /* Set default values */
    SNAKE_SetDefaultSnake();
    
    /* Prepare display */
    SNAKE_PrepareDisplay();
    
    /* Generate random target */
    SNAKE_GenerateTarget();

    /* Set Initial Direction */
    USB_HIDHOST_INT_Keyboard.Button = SNAKE_KEY_RIGHT;
    
    for (;;) 
    {
      /* Check for timeout, move snake here */
      if (!Settings.Pause && !GameOver) 
      {
          /* Get new direction value */
          Snake.Direction = Snake1.Direction;
          
          /* Get last x/y value from snake array = snake head */
          Snake_Head[0] = Snake.Snake[Snake.LastIndex][0];
          Snake_Head[1] = Snake.Snake[Snake.LastIndex][1];
          
          /* Store last value before update */
          Snake_Head_Last[0] = Snake_Head[0];
          Snake_Head_Last[1] = Snake_Head[1];
          
          if (!Snake_FirstTime) 
          {
            /* Move snake */
            switch (Snake.Direction) 
            {
              case SNAKE_DIRECTION_LEFT:
                      Snake_Head[0] -= 1;
                      break;
              case SNAKE_DIRECTION_RIGHT:
                      Snake_Head[0] += 1;
                      break;
              case SNAKE_DIRECTION_UP:
                      Snake_Head[1] -= 1;
                      break;
              case SNAKE_DIRECTION_DOWN:
                      Snake_Head[1] += 1;
                      break;
              default:
                      break;
            }
          }
              
          /* Overflow is activated */
          if (Settings.Overflow) 
          {
            /* Check X */
            if (Snake_Head[0] == -1) 
            {
              Snake_Head[0] = SNAKE_PIXELS - 1;
            } 
            else if (Snake_Head[0] == SNAKE_PIXELS) 
            {
              Snake_Head[0] = 0;
            }

            /* Check Y */
            if (Snake_Head[1] == -1) 
            {
              Snake_Head[1] = SNAKE_PIXELS_Y - 1;
            } 
            else if (Snake_Head[1] == SNAKE_PIXELS_Y) 
            {
              Snake_Head[1] = 0;
            }

            /* Draw border to Handle Overflow */
            GUI_SetColor(SNAKE_COLOR_BORDER);
            GUI_DrawRect( SNAKE_BACK_START_X,SNAKE_BACK_START_Y,
                          SNAKE_BACK_START_X + SNAKE_PIXELS * (SNAKE_PIXEL_SIZE + 1) + 1, SNAKE_BACK_START_Y + SNAKE_PIXELS_Y * (SNAKE_PIXEL_SIZE + 1) + 1 );
          } 
          else 
          {
            /* Check walls */
            if ( Snake_Head[0] == -1 || Snake_Head[0] == SNAKE_PIXELS ||
                 Snake_Head[1] == -1 || Snake_Head[1] == SNAKE_PIXELS_Y )
            {
              /* We hit the wall somewhere */
              GameOver = 1;
            }
          }
                              
          if (!Snake_FirstTime) 
          {
            /* Clear first value from array = snake foot */
            SNAKE_DeleteFromArray(0, Snake_Foot);
            
            /* Check if snake hit itself, set the Game Over Flag*/
            if ( SNAKE_MatchesSnakeLocations(Snake_Head) )
              GameOver = 1;
          }
              
          /* Check if target is reached */
          if ( !GameOver && Snake_Head[0] == Snake_Food[0] && Snake_Head[1] == Snake_Food[1] ) 
          {
            /* Add new value to the array, increase snake */
            SNAKE_AddToArray(Snake_Head);
            
            /* Increase counter for snake hits */
            Snake.Hits++;
            
            /* Generate new target */
            SNAKE_GenerateTarget();

            /* Speed Up */
            Settings.Speed -= 5;

            /* Trigger Sound */
            //MS_EAT_SET(TRUE);
          }
              
          if (!GameOver) 
          {
            if (!Snake_FirstTime) 
            {
              /* Add new value to the array = new snake head */
              SNAKE_AddToArray(Snake_Head);
            }
            
            /* Clear pixel on LCD for foot */
            /* First clear foot, maybe is new head on the same position */
            SNAKE_DrawPixel(Snake_Foot[0], Snake_Foot[1], 0);
            
            /* Draw pixel on LCD for new head position with head color */
            SNAKE_DrawPixel(Snake_Head[0], Snake_Head[1], 3);
            /* Draw new pixel for the second pixel after head with new color to delete head color */
            SNAKE_DrawPixel(Snake_Head_Last[0], Snake_Head_Last[1], 1);
          }
                            
          /* Clear flag if needed */
          if (Snake_FirstTime) 
          {
            Snake_FirstTime = 0;
          }
      }
            
      if (GameOver) 
      {
          /* Check flag */
          if (!GameOverDisplay) 
          {
              /* Set flag and Display Message */
              GameOverDisplay = 1;
              GUI_SetFont( &GUI_Font8x8 );
              GUI_DispStringAt( "Game Over!", 44, 60 );

              /* Turn On Game Over Sound */
              MS_END_SET(TRUE);
          }
      } 
      else 
      {
          /* Clear flag */
          GameOverDisplay = 0;
      }
              
      /* Read keyboard data */
      USB_HIDHOST_ReadKeyboard(&Keyboard);
              
      /* If any buttons active */
      if (Keyboard.ButtonStatus == USB_HIDHOST_Button_Pressed) 
      {
          /* Check pressed button and do actions */
          switch ((uint8_t)Keyboard.Button) 
          {
              case SNAKE_KEY_LEFT:
                /* Change direction if possible */
                if ( Snake.Direction == SNAKE_DIRECTION_UP || Snake.Direction == SNAKE_DIRECTION_DOWN || Snake.Direction == SNAKE_DIRECTION_LEFT )
                {
                  /* Disable pause mode */
                  Settings.Pause = 0;
                  /* Set direction */
                  Snake1.Direction = SNAKE_DIRECTION_LEFT;
                }
                break;
              case SNAKE_KEY_RIGHT:
                /* Change direction if possible */
                if ( Snake.Direction == SNAKE_DIRECTION_UP || Snake.Direction == SNAKE_DIRECTION_DOWN || Snake.Direction == SNAKE_DIRECTION_RIGHT )
                {
                  /* Disable pause mode */
                  Settings.Pause = 0;
                  /* Set direction */
                  Snake1.Direction = SNAKE_DIRECTION_RIGHT;
                }
                break;
              case SNAKE_KEY_UP:
                /* Change direction if possible */
                if ( Snake.Direction == SNAKE_DIRECTION_LEFT || Snake.Direction == SNAKE_DIRECTION_RIGHT || Snake.Direction == SNAKE_DIRECTION_UP )
                {
                  /* Disable pause mode */
                  Settings.Pause = 0;
                  /* Set direction */
                  Snake1.Direction = SNAKE_DIRECTION_UP;
                }
                break;
              case SNAKE_KEY_DOWN:
                /* Change direction if possible */
                if ( Snake.Direction == SNAKE_DIRECTION_LEFT || Snake.Direction == SNAKE_DIRECTION_RIGHT || Snake.Direction == SNAKE_DIRECTION_DOWN )
                {
                  /* Disable pause mode */
                  Settings.Pause = 0;
                  /* Set direction */
                  Snake1.Direction = SNAKE_DIRECTION_DOWN;
                }
                break;
              default:
                break;
          }
      }
            
      /* Update LCD with changed settings */
            
      /* Check overflow */
      if (Settings1.Overflow != Settings.Overflow) 
      {
        /* Save new */
        Settings1.Overflow = Settings.Overflow;
      }
            
      /* Check snake hits */
      if (Snake1.Hits != Snake.Hits) 
      {
        /* Save new */
        Snake1.Hits = Snake.Hits;
      }

      vTaskDelay( Settings.Speed );
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

void Navigation_SWitchIRQHandler( uint32_t State )
{
  /* Update the Coodinates based on the Direction Pressed */
  USB_HIDHOST_INT_Keyboard.ButtonStatus = USB_HIDHOST_Button_Pressed;
  USB_HIDHOST_INT_Keyboard.Button = State;

  if (1 == State && !g_GameStart)
  {
    g_GameStart = TRUE;
  }

  if (1 == State && GameOverDisplay)
  {
    GUI_Clear();

    /* Initialize True random number generator */
    RNG_Init();

    /* Set default options */
    SNAKE_SetFirstOptions();

    /* Set default values */
    SNAKE_SetDefaultSnake();
    
    /* Prepare display */
    SNAKE_PrepareDisplay();
    
    /* Generate random target */
    SNAKE_GenerateTarget();

    /* Set Initial Direction */
    USB_HIDHOST_INT_Keyboard.Button = SNAKE_KEY_RIGHT;

    /* Reset Game Over */
    GameOver = 0;
    GameOverDisplay = 0;

    /* Turn Off Game Over Sound */
    MS_END_SET(FALSE);
  }

  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  xTaskNotifyFromISR( xNavSwHandle,
                      BIT(State),
                      eSetBits,
                      &xHigherPriorityTaskWoken );

  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

static USB_HIDHOST_Result_t USB_HIDHOST_ReadKeyboard(USB_HIDHOST_Keyboard_t* Keyboard) 
{
  /* Fill data */
  Keyboard->Button = USB_HIDHOST_INT_Keyboard.Button;
  Keyboard->ButtonStatus = USB_HIDHOST_INT_Keyboard.ButtonStatus;

  /* Reset internal data */
  USB_HIDHOST_INT_Keyboard.ButtonStatus = USB_HIDHOST_Button_Released;
  USB_HIDHOST_INT_Keyboard.Button = 1;

  /* Return keyboard connected */
  return USB_HIDHOST_Result_KeyboardConnected;
}

/* Draw snake pixel */
void SNAKE_DrawPixel(uint8_t x, uint8_t y, uint16_t value)
{
  uint16_t color;
  
  /* Get pixel color */
  if (value == 0) {
          color = SNAKE_COLOR_GAME_BCK;	/* Clear pixel */
  } else if (value == 1) {
          color = SNAKE_COLOR_PIXEL;	/* Set snake pixel */
  } else if (value == 2) {
          color = SNAKE_COLOR_TARGET;	/* Set target pixel */
  } else if (value == 3) {
          color = SNAKE_COLOR_HEAD;	/* Set head pixel for snake */
  }
  
  /* Draw Filled rectangle */
  GUI_SetColor(color);
  GUI_FillRect(
          SNAKE_BACK_START_X + 2 + x * (SNAKE_PIXEL_SIZE + 1),
          SNAKE_BACK_START_Y + 2 + y * (SNAKE_PIXEL_SIZE + 1),
          SNAKE_BACK_START_X + 1 + x * (SNAKE_PIXEL_SIZE + 1) + SNAKE_PIXEL_SIZE,
          SNAKE_BACK_START_Y + 2 + y * (SNAKE_PIXEL_SIZE + 1) + SNAKE_PIXEL_SIZE);
}

void SNAKE_PrepareDisplay(void)
{
  /* Fill screen */
  GUI_SetBkColor(SNAKE_COLOR_MAIN_BCK);
  GUI_FillRect(0, 0, g_Xres, g_Yres);

  /* Draw snake area */
  SNAKE_DrawArea();
}

void SNAKE_SetFirstOptions(void)
{
  Settings.Speed    = SNAKE_SPEED_DEFAULT;
  Settings.Micros   = 1000000 / Settings.Speed;
  Settings.Pause    = 0;
  Settings.Overflow = 1;
}

void SNAKE_SetDefaultSnake() 
{
  uint16_t i;
  
  /* Set default options */
  Snake.Direction = Snake1.Direction = SNAKE_DIRECTION_RIGHT;
  Snake.LastIndex = 0;
  Snake.Length    = 0;
  Snake.Hits      = 0;
  
  /* Set default snake1 settings */
  Snake1.Hits = 255;
  
  /* Default X and Y values */
  /* Get random number */
  SNAKE_Random(Random);
  
  Random[0] = 3;
  Random[1] = 3;

  /* Add first to array, foot */
  SNAKE_AddToArray(Random);
  
  /* Store values */
  for (i = 0; i < SNAKE_DEFAULT_LENGTH - 1; i++) 
  {
    if (i == (SNAKE_DEFAULT_LENGTH - 2))
    {
      Random[0]++;
    }
    SNAKE_AddToArray(Random);
  }
}

void SNAKE_DeleteFromArray(uint16_t index, int8_t* twobytesarray) 
{
  if (index < Snake.Length) 
  {
    /* Store value that will be removed */
    twobytesarray[0] = Snake.Snake[index][0];
    twobytesarray[1] = Snake.Snake[index][1];
    
    /* Remove data from array at specific index */
    for (; index < Snake.LastIndex; index++) 
    {
      Snake.Snake[index][0] = Snake.Snake[index + 1][0];
      Snake.Snake[index][1] = Snake.Snake[index + 1][1];
    }
    
    /* Last index-- */
    Snake.LastIndex--;
    Snake.Length--;
  }
}

/* Add new position to the snake array */
void SNAKE_AddToArray(int8_t* twobytesarray) 
{
  /* Increase counters */
  if (Snake.Length == 0)
    Snake.Length++;
  else 
  {
    Snake.LastIndex++;
    Snake.Length++;
  }
  
  /* Add new values to array */
  Snake.Snake[Snake.LastIndex][0] = twobytesarray[0];
  Snake.Snake[Snake.LastIndex][1] = twobytesarray[1];
}

void SNAKE_ReplaceArray(uint16_t index, int8_t* twobytesarray)
{
  /* Replace array values */
  Snake.Snake[index][0] = twobytesarray[0];
  Snake.Snake[index][1] = twobytesarray[1];
}

void SNAKE_Random(int8_t* twobytesarray) 
{
  float temp;
  
  /* Generate first random number */
  temp = (float)RNG_Get() / (float)0xFFFFFFFF * (SNAKE_PIXELS - 1);
  twobytesarray[0] = (int8_t)temp;
  
  /* Generate second random number */
  temp = (float)RNG_Get() / (float)0xFFFFFFFF * (SNAKE_PIXELS_Y - 1);
  twobytesarray[1] = (int8_t)temp;
}

uint8_t SNAKE_MatchesSnakeLocations(int8_t* twobytesarray) 
{
  uint16_t i;
  
  for (i = 0; i < Snake.Length; i++)
  {
    if ( Snake.Snake[i][0] == twobytesarray[0] && Snake.Snake[i][1] == twobytesarray[1] )
      return 1; /* Snake hit itself */
  }

  /* Snake did not hit itself */
  return 0;
}

/* Generate 2 coordinates which are not on snake already */
void SNAKE_GenerateTarget(void)
{
  do {
    /* Generate random X and Y locations */
    SNAKE_Random(Snake_Food);
  } while (SNAKE_MatchesSnakeLocations(Snake_Food));

  /* Display target on LCD */
  SNAKE_DrawPixel(Snake_Food[0], Snake_Food[1], 2);
}

void SNAKE_DrawArea(void) 
{
  /* Draw filled rectangle */
  GUI_SetColor( SNAKE_COLOR_GAME_BCK );
  GUI_FillRect( SNAKE_BACK_START_X, SNAKE_BACK_START_Y,
                SNAKE_BACK_START_X + SNAKE_PIXELS * (SNAKE_PIXEL_SIZE + 1), SNAKE_BACK_START_Y + SNAKE_PIXELS_Y * (SNAKE_PIXEL_SIZE + 1));

  /* Draw border */
  GUI_SetColor( SNAKE_COLOR_BORDER );
  GUI_DrawRect( SNAKE_BACK_START_X, SNAKE_BACK_START_Y,
                SNAKE_BACK_START_X + SNAKE_PIXELS * (SNAKE_PIXEL_SIZE + 1) + 1,
                SNAKE_BACK_START_Y + SNAKE_PIXELS_Y * (SNAKE_PIXEL_SIZE + 1) + 1);
}
