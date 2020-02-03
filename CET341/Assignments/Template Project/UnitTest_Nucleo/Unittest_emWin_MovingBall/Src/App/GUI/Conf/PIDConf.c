/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 2003 - 2019  SEGGER Microcontroller GmbH                 *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : PIDConf.c
Purpose     : Touch screen controller configuration
---------------------------END-OF-HEADER------------------------------
*/

#include <Common.h>
#include "GUI.h"
#include "PIDConf.h"

#include "RTOS.h"




/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */

#define TOUCH_STACK_SIZE	256
/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */
static U8 _IsInitialized;
static int _LayerIndex;

static StaticTask_t         xTouchTCB;
static StackType_t          xTouchStack[TOUCH_STACK_SIZE];

static void PID_X_Exec( void );
static void TouchTask( void *pvParameters );

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       HAL_Delay
 *
 *  Function description
 *    overwrite HAL_Delay from stm32f7xx_hal.c
 */
void HAL_Delay( __IO uint32_t Delay )
{
    int Cnt = 1000 * 100 * Delay;
    volatile int i = 0;
    for( ; i < Cnt; i++ ) {}
    // OS_Delay(Delay);
}

/*********************************************************************
 *
 *       TouchTask
 */
static void TouchTask( void *pvParameters )
{
	TickType_t xLastWakeTime;

    while( 1 )
    {
        PID_X_Exec( );
        vTaskDelayUntil( &xLastWakeTime, 50 );
    }
}
static GUI_MTOUCH_EVENT g_event;
static GUI_MTOUCH_INPUT g_aInput[5];
static int IsTouched = 0;
/*********************************************************************
 *
 *       PID_X_Exec
 */
static void PID_X_Exec( void )
{
    TS_StateTypeDef TS_State = {0};
    static GUI_PID_STATE StatePID;

    int IsMirrorX;
    int IsMirrorY;
    int xSize;
    int ySize;
    int i;

    if( _IsInitialized )
    {
        BSP_TS_GetState( &TS_State );// Read touch input
        StatePID.Layer = _LayerIndex;
        if( TS_State.touchDetected )
        {// If touch detected, set up pid statte structure
            // IsTouched = 1;                    // Remember that last even has
            // been touch down
            StatePID.Pressed = 5;// Pressed, "down event"
            //
            // Get some information about the display orientation and its size
            //
            IsMirrorX = LCD_GetMirrorX( );
            IsMirrorY = LCD_GetMirrorY( );
            xSize = LCD_GetXSize( );// Depending on the orientation these values
                                    // are swapped.
            ySize = LCD_GetYSize( );// Previous x size will y size vice versa

            g_event.NumPoints = TS_State.touchDetected;
            g_event.LayerIndex = _LayerIndex;

            for( i = 0; i < TS_State.touchDetected; i++ )
            {
                g_aInput[i].Id = i;
                g_aInput[i].x = TS_State.touchX[i];
                g_aInput[i].y = TS_State.touchY[i];
                if( IsTouched == 0 )
                {
                    IsTouched = 1;
                    g_aInput[i].Flags =
                    GUI_MTOUCH_FLAG_DOWN | GUI_MTOUCH_FLAG_MOVE;
                }
                //  else if(i==TS_State.touchDetected)
                // g_aInput[i].Flags = GUI_MTOUCH_FLAG_UP ;
                else
                {
                    g_aInput[i].Flags = GUI_MTOUCH_FLAG_MOVE;
                }
            }
            GUI_MTOUCH_StoreEvent( &g_event, g_aInput );

            if( LCD_GetSwapXYEx( _LayerIndex ) )
            {
                //
                // If an axis is mirrored we have to suptract the input from the
                // given axis, be aware that the axis values might be swapped.
                // That's why we use ySize for x and xSize for y...
                //
                StatePID.y =
                ( IsMirrorX )
                ? ySize - TS_State.touchX[0]
                : TS_State.touchX[0];// XY swapped, use x coordinates (ySize is
                                     // formaer xSize) for the y coordinate
                StatePID.x = ( IsMirrorY )
                             ? xSize - TS_State.touchY[0]
                             : TS_State.touchY[0];// Same as above but for y
            }
            else
            {
                StatePID.x =
                ( IsMirrorX )
                ? xSize - TS_State.touchX[0]
                : TS_State.touchX[0];// Nothings swapped but maybe mirrored
                StatePID.y =
                ( IsMirrorY ) ? ySize - TS_State.touchY[0] : TS_State.touchY[0];
            }
            GUI_TOUCH_StoreStateEx( &StatePID );// Pass information to emWin
        }
        else
        {
            if( IsTouched == 1 )
            {                 // No touch detected but last event was touch down
                IsTouched = 0;// Restore IsTouched variable
                StatePID.Pressed = 0;// Unpressed, "up event"
                GUI_TOUCH_StoreStateEx(
                &StatePID );// Since StatePID is declared as static we use the
                            // x/y coordinate
                //  g_event.NumPoints = TS_State.touchDetected;
                // g_event.LayerIndex = _LayerIndex;

                for( i = 0; i < 5; i++ )
                {
                    g_aInput[i].Id = i;
                    g_aInput[i].x = TS_State.touchX[i];
                    g_aInput[i].y = TS_State.touchY[i];


                    g_aInput[i].Flags = GUI_MTOUCH_FLAG_UP;
                }
                GUI_MTOUCH_StoreEvent(
                &g_event,
                g_aInput );// from the down event to create an up event.
            }
        }
    }
}

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */
/*********************************************************************
 *
 *       PID_X_SetLayerIndex
 */
void PID_X_SetLayerIndex( int LayerIndex )
{
    _LayerIndex = LayerIndex;
}

/*********************************************************************
 *
 *       PID_X_Init
 */
void PID_X_Init( void )
{
    int xSize, ySize;

    if( _IsInitialized == 0 )
    {
        xSize = LCD_GetXSize( );
        ySize = LCD_GetYSize( );
        BSP_TS_Init( xSize, ySize );
        xTaskCreateStatic(
            TouchTask,
            "TouchTask",
            TOUCH_STACK_SIZE,
            NULL,
            1,
            xTouchStack,
            &xTouchTCB );	

        _IsInitialized = 1;
    }
}

/*************************** End of file ****************************/