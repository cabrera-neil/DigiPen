/*****************************************************************************
 @Project	: Common include header for embbeded system
 @File 		: Common.h
 @Details  	: Common share macro, type         
 @Author	: lcgan
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/

#ifndef __COMMON_DOT_H__
#define __COMMON_DOT_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


#if defined(_MBED_LPC1768)
	#include "LPC17xx.h"
#endif

#if defined(_STM32_NUCLEO_F103RB)
	#include "stm32f103xb.h"
#endif

#if defined(_STM32_OPEN_F407)
	#include "stm32f4xx.h"
#endif

#if defined(_MEGA2560)
	#include <avr/io.h>
	#include <avr/interrupt.h>
#define __INLINE __inline
#endif

#if defined(_STM32_NUCLEO_F722ZE)
	#include "stm32f7xx.h"
#endif

#if defined(_STM32_NUCLEO_F746NG)
	#include "stm32f7xx.h"
#endif

#if defined(_STM32_DISCO_F746NG)

	#include "stm32f7xx.h"
    #include "stm32f7xx_hal.h"
    #include "Global.h"
#endif

#if defined(_STM32_NUCLEO_F746NG)

	#include "stm32f7xx.h"
    #include "GLobal.h"
#endif




/*****************************************************************************
 Define
******************************************************************************/
#define TRUE		1
#define FALSE		0

#define PI			3.1415926535897932384626433832795
#define RAD_TO_DEG	57.295779513082320876798154814105
#define UNUSE( a )	(void)(a)
#define ABS( a )	(((a)<0)? -(a) : (a))
#define BIT( x )	(1U<<(x))
#define MIN( a, b )	(((a)<(b))? (a) : (b))
#define MAX( a, b )	(((a)<(b))? (b) : (a))

#define CONCAT (a,b) a ## b				/* concatenate  */

#define CI_TRACE   printf

#ifdef _DEBUG
	#define TRACE   printf
#else	
    inline  void 	PrintfEmpty( const char * string, ... ) __attribute__((always_inline));
	inline  void 	PrintfEmpty( const char * string, ... ){}
	#define TRACE	PrintfEmpty
#endif

#ifdef _DEBUG
#define ASSERT( e )													\
{																	\
	if (!(e))														\
	{																\
		TRACE( "Error! Halt at %s %d\r\n", __FILE__, __LINE__ ); 	\
		while( 1 );													\
	}																\
}
#else
	#define ASSERT( e )( (void)0 )		/* no effect in release */
#endif


/*****************************************************************************
 typedef
******************************************************************************/
typedef int BOOL;


/*****************************************************************************
 Retarget 
******************************************************************************/
extern BOOL IsKbHit( void );
extern char GetKey( void );


		
#endif /* __COMMON_DOT_H__ */














