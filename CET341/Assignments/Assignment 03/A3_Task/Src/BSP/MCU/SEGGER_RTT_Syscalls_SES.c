/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2019 SEGGER Microcontroller GmbH                  *
*                                                                    *
*       Internet: segger.com  Support: support_embos@segger.com      *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS * Real time operating system for microcontrollers      *
*                                                                    *
*       Please note:                                                 *
*                                                                    *
*       Knowledge of this file may under no circumstances            *
*       be used to write a similar product or a real-time            *
*       operating system for in-house use.                           *
*                                                                    *
*       Thank you for your fairness !                                *
*                                                                    *
**********************************************************************
*                                                                    *
*       OS version: 5.06                                             *
*                                                                    *
**********************************************************************

---------------------------END-OF-HEADER------------------------------
File    : SEGGER_RTT_Syscalls_SES.c
Purpose : Reimplementation of printf, puts and __getchar using RTT
          in SEGGER Embedded Studio.
          To use RTT for printf output, include this file in your
          application.
Revision: $Rev: 9599 $
----------------------------------------------------------------------
*/
#if (defined __SES_ARM) || (defined __CROSSWORKS_ARM)

#include "SEGGER_RTT.h"
#include <stdarg.h>
#include <stdio.h>
#include "limits.h"
#include "__libc.h"
#include "__vfprintf.h"
#include "MyOS_MCU.h"

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
//
// Select string formatting implementation.
//
// RTT printf formatting
//  - Configurable stack usage. (SEGGER_RTT_PRINTF_BUFFER_SIZE in SEGGER_RTT_Conf.h)
//  - No maximum string length.
//  - Limited conversion specifiers and flags. (See SEGGER_RTT_printf.c)
// Standard library printf formatting
//  - Configurable formatting capabilities.
//  - Full conversion specifier and flag support.
//  - Maximum string length has to be known or (slightly) slower character-wise output.
//
// #define PRINTF_USE_SEGGER_RTT_FORMATTING    0 // Use standard library formatting
// #define PRINTF_USE_SEGGER_RTT_FORMATTING    1 // Use RTT formatting
//
#ifndef   PRINTF_USE_SEGGER_RTT_FORMATTING
  #define PRINTF_USE_SEGGER_RTT_FORMATTING    0
#endif
//
// If using standard library formatting,
// select maximum output string buffer size or character-wise output.
//
// #define PRINTF_BUFFER_SIZE                  0 // Use character-wise output
// #define PRINTF_BUFFER_SIZE                128 // Default maximum string length
//
#ifndef   PRINTF_BUFFER_SIZE
  #define PRINTF_BUFFER_SIZE                128
#endif

#if PRINTF_USE_SEGGER_RTT_FORMATTING  // Use SEGGER RTT formatting implementation
/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/
int SEGGER_RTT_vprintf(unsigned BufferIndex, const char * sFormat, va_list * pParamList);

/*********************************************************************
*
*       Global functions, printf
*
**********************************************************************
*/
/*********************************************************************
*
*       printf()
*
*  Function description
*    print a formatted string using RTT and SEGGER RTT formatting.
*/
int printf(const char *fmt,...) {
  int     n;
  va_list args;

  va_start (args, fmt);
  n = SEGGER_RTT_vprintf(0, fmt, &args);
  va_end(args);
  return n;
}

#elif PRINTF_BUFFER_SIZE == 0 // Use standard library formatting with character-wise output

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
static int _putchar(int x, __printf_tag_ptr ctx) {
  (void)ctx;
  SEGGER_RTT_Write(0, (char *)&x, 1);
  return x;
}

/*********************************************************************
*
*       Global functions, printf
*
**********************************************************************
*/
/*********************************************************************
*
*       printf()
*
*  Function description
*    print a formatted string character-wise, using RTT and standard
*    library formatting.
*/
int printf(const char *fmt, ...) {
  int         n;
  va_list     args;
  __printf_t  iod;

  va_start(args, fmt);
  iod.string    = 0;
  iod.maxchars  = INT_MAX;
  iod.output_fn = _putchar;
  SEGGER_RTT_LOCK();
  n = __vfprintf(&iod, fmt, args);
  SEGGER_RTT_UNLOCK();
  va_end(args);
  return n;
}

#else // Use standard library formatting with static buffer

/*********************************************************************
*
*       Global functions, printf
*
**********************************************************************
*/
/*********************************************************************
*
*       printf()
*
*  Function description
*    print a formatted string using RTT and standard library formatting.
*/
int printf(const char *fmt,...) {
  int     n;
  char    aBuffer[PRINTF_BUFFER_SIZE];
  va_list args;

  va_start (args, fmt);
#ifdef __MYOS_PRINTF_NO_INT
  /////////////////////////////////////////////////////////
  // MyOS special implementation:
  // The vsnprintf system call causes the MyOS context
  // switching hard fault.
  // Thus, this system call is disabled and a loop is used
  // to copy the printf string.
  // Liang
  /////////////////////////////////////////////////////////
  for (n=0; n<PRINTF_BUFFER_SIZE; n++){
    aBuffer[n] = fmt[n];
    if (aBuffer[n]==NULL){
      break;
    }
  }
  SEGGER_RTT_Write(0, aBuffer, n);

#else
  n = vsnprintf(aBuffer, sizeof(aBuffer), fmt, args);
  if (n > (int)sizeof(aBuffer)) {
    SEGGER_RTT_Write(0, aBuffer, sizeof(aBuffer));
  } else if (n > 0) {
    SEGGER_RTT_Write(0, aBuffer, n);
  }
#endif
  va_end(args);
  return n;
}
#endif

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/
/*********************************************************************
*
*       puts()
*
*  Function description
*    print a string using RTT.
*/
int puts(const char *s) {
  return SEGGER_RTT_WriteString(0, s);
}

/*********************************************************************
*
*       __putchar()
*
*  Function description
*    Write one character via RTT.
*/
int __putchar(int x, __printf_tag_ptr ctx) {
  (void)ctx;
  SEGGER_RTT_Write(0, (char *)&x, 1);
  return x;
}

/*********************************************************************
*
*       __getchar()
*
*  Function description
*    Wait for and get a character via RTT.
*/
int __getchar() {
  return SEGGER_RTT_WaitKey();
}

#endif
/****** End Of File *************************************************/
