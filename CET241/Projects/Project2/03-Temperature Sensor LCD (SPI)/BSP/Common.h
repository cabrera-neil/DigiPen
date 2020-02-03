/*****************************************************************************
 @Project	: Common include header for embbeded system
 @File 		: Common.h
 @Details : Common share macro, type         
 @Hardware:    
******************************************************************************/

#ifndef __COMMON_DOT_H__
#define __COMMON_DOT_H__
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "TM4C123GH6PM.h"


/*****************************************************************************
 Define
******************************************************************************/
#define TRUE		1
#define FALSE		0

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
	
#endif /* __COMMON_DOT_H__ */

