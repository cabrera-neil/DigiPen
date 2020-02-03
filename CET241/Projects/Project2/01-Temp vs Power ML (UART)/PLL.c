#include "PLL.h"

// ********************PLL 80Mhz Init********************
// Set PLL to 80Mhz
// Input: none
// Output: none
void PLL_Init80(void)
{
		SYSCTL->RCC2	|=	0x80000000;
		SYSCTL->RCC2	|=	0x00000800;
		SYSCTL->RCC		=		(SYSCTL->RCC &~0x000007C0)+(0x15<<6);
		SYSCTL->RCC2	&=	~0x00000070;
		SYSCTL->RCC2	&= 	~0x00002000;
		
    SYSCTL->RCC2	|= 0x40000000;
		SYSCTL->RCC2 	= (SYSCTL->RCC2&~0x1FC00000)+(4<<22);

		while((SYSCTL->RIS&0x00000040)==0);

		SYSCTL->RCC2 &= ~0x00000800;
}
