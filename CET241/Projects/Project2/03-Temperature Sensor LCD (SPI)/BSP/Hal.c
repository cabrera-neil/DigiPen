/*****************************************************************************
 @Project	: 
 @File 		: Hal.c
 @Details : All Ports and peripherals configuration                    
 @Author	: 
 @Hardware: 
 
******************************************************************************/
#include "Common.h"
#include "Hal.h"

/*****************************************************************************
 Define
******************************************************************************/
#define LCD_PINS_BIT (BIT(PA_LCD_SSI0_CS)  	\
						| BIT(PA_LCD_DC) 	\
						| BIT(PA_LCD_RESET) \
						| BIT(PA_LCD_BL))

#define SYSCTL_RCGCGPIO_R5      0x00000020  // GPIO Port F Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R1      0x00000002  // GPIO Port B Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R0      0x00000001  // GPIO Port A Run Mode Clock
                                            // Gating Control

//*****************************************************************************
// The following are defines for the bit fields in the SYSCTL_PRGPIO register.
//*****************************************************************************
#define SYSCTL_PRGPIO_R5        0x00000020  // GPIO Port F Peripheral Ready
#define SYSCTL_PRGPIO_R1        0x00000002  // GPIO Port B Peripheral Ready
#define SYSCTL_PRGPIO_R0        0x00000001  // GPIO Port A Peripheral Ready

//*****************************************************************************
// The following are defines for the bit fields in the SYSCTL_RCGCSSI register.
//*****************************************************************************
#define SYSCTL_RCGCSSI_R0       0x00000001  // SSI Module 0 Run Mode Clock
                                            // Gating Control

#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register

//*****************************************************************************
// The following are defines for the bit fields in the GPIO_PCTL register for
// port A.
//*****************************************************************************
#define GPIO_PCTL_PA7_M         0xF0000000  // PA7 mask
#define GPIO_PCTL_PA7_I2C1SDA   0x30000000  // I2C1SDA on PA7
#define GPIO_PCTL_PA7_M1PWM3    0x50000000  // M1PWM3 on PA7
#define GPIO_PCTL_PA6_M         0x0F000000  // PA6 mask
#define GPIO_PCTL_PA6_I2C1SCL   0x03000000  // I2C1SCL on PA6
#define GPIO_PCTL_PA6_M1PWM2    0x05000000  // M1PWM2 on PA6
#define GPIO_PCTL_PA5_M         0x00F00000  // PA5 mask
#define GPIO_PCTL_PA5_SSI0TX    0x00200000  // SSI0TX on PA5
#define GPIO_PCTL_PA4_M         0x000F0000  // PA4 mask
#define GPIO_PCTL_PA4_SSI0RX    0x00020000  // SSI0RX on PA4
#define GPIO_PCTL_PA3_M         0x0000F000  // PA3 mask
#define GPIO_PCTL_PA3_SSI0FSS   0x00002000  // SSI0FSS on PA3
#define GPIO_PCTL_PA2_M         0x00000F00  // PA2 mask
#define GPIO_PCTL_PA2_SSI0CLK   0x00000200  // SSI0CLK on PA2
#define GPIO_PCTL_PA1_M         0x000000F0  // PA1 mask
#define GPIO_PCTL_PA1_U0TX      0x00000010  // U0TX on PA1
#define GPIO_PCTL_PA1_CAN1TX    0x00000080  // CAN1TX on PA1
#define GPIO_PCTL_PA0_M         0x0000000F  // PA0 mask
#define GPIO_PCTL_PA0_U0RX      0x00000001  // U0RX on PA0
#define GPIO_PCTL_PA0_CAN1RX    0x00000008  // CAN1RX on PA0

//*****************************************************************************
// The following are defines for the bit fields in the SYSCTL_PRSSI register.
//*****************************************************************************
#define SYSCTL_PRSSI_R0         0x00000001  // SSI Module 0 Peripheral Ready


/*****************************************************************************
 Implementation
******************************************************************************/
void PortInit( void )
{
	/************************
	 Enable GPIO Clock Gates
	*************************/
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R0 | SYSCTL_RCGCGPIO_R1 | SYSCTL_RCGCGPIO_R5;
	
	/* Waiting clocks ready */
	while( 0 == (SYSCTL->PRGPIO & SYSCTL_PRGPIO_R0) ){}
	while( 0 == (SYSCTL->PRGPIO & SYSCTL_PRGPIO_R1) ){}
	while( 0 == (SYSCTL->PRGPIO & SYSCTL_PRGPIO_R5) ){}		
	
	/************************
	 Enable SSIs Clock Gates
	*************************/		
	SYSCTL->RCGCSSI |= SYSCTL_RCGCSSI_R0;
	while( 0 == (SYSCTL->PRSSI & SYSCTL_PRSSI_R0) ){}
		
	/* LED */
	GPIOF->DIR 	|= BIT(PF_LED_RED) | BIT(PF_LED_BLUE) | BIT(PF_LED_GREEN);
	GPIOF->DEN 	|= BIT(PF_LED_RED) | BIT(PF_LED_BLUE) | BIT(PF_LED_GREEN);
		
	/************************
	 SSI0 for TFT LCD
	*************************/	
	GPIOA->LOCK = GPIO_LOCK_KEY;
	GPIOA->DIR |= LCD_PINS_BIT;
	GPIOA->DEN |= LCD_PINS_BIT;
	GPIOA->AFSEL &= ~LCD_PINS_BIT;
	GPIOA->PCTL &= ~(GPIO_PCTL_PA3_M 
					| GPIO_PCTL_PA4_M 
					| GPIO_PCTL_PA6_M 
					| GPIO_PCTL_PA7_M);
	
	GPIOA->DEN 		|= BIT(PA_LCD_SSI0_SCK) | BIT(PA_LCD_SSI0_MOSI);
	GPIOA->AFSEL 	|= (BIT(PA_LCD_SSI0_SCK) | BIT(PA_LCD_SSI0_MOSI) );
	GPIOA->PCTL 	&= ~(GPIO_PCTL_PA2_M | GPIO_PCTL_PA5_M);
	GPIOA->PCTL 	|= (GPIO_PCTL_PA2_SSI0CLK | GPIO_PCTL_PA5_SSI0TX);
}

