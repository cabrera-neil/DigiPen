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

#include "GUI.h"



#define GUI_BLOCKSIZE 1024
#define NBYTE   1024*48

static U32 aLcdMem[NBYTE/4];


//GUI_X_Config
void GUI_X_Config(void) {

	GUI_ALLOC_AssignMemory( aLcdMem, NBYTE );
	GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);

}
