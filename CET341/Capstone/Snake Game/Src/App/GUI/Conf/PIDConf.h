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
File        : PIDConf.h
Purpose     : Touch screen controller interface
---------------------------END-OF-HEADER------------------------------
*/

#ifndef PIDCONF_H
#define PIDCONF_H

void PID_X_Init(void);
void PID_X_SetLayerIndex(int LayerIndex);

#endif // PIDCONF_H
