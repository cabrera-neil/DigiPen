/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 2003 - 2019  SEGGER Microcontroller GmbH                 *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************/

#include <Common.h>
#include <stdio.h>
#include <stdlib.h>
#include "GUI.h"
#include "GUIDRV_X.h"
#include "GUIDRV_FlexColor.h"
#include "LCD_ST7735R.h"



/* LCD physical size in pixel */
#define XSIZE_PHYS  128
#define YSIZE_PHYS  160
#define VXSIZE_PHYS	128 
#define VYSIZE_PHYS 160


#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

  


void LCD_X_Config(void) {
	int hort;
    int vert;

    GUI_DEVICE_CreateAndLink(&GUIDRV_Template_API, GUICC_M565, 0, 0);
    LCD_GetSize( &hort, &vert );
   // TRACE( "Screen size: H:%d V:%d\r\n",hort, vert );
    
    LCD_SetSizeEx( 0, hort, vert );
    LCD_SetVSizeEx( 0, hort, vert );

}


int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: 
  {
	/* Initialize LCD controller here if no other place do this */
    return 0;
  }
		default:
    r = -1;
	}
  return r;
}
