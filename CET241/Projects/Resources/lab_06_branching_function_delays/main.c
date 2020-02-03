/**
 * @file     main.c
 * @author   Phi Luu
 * @date     March 07, 2016
 *
 * @brief    UTAustinX: UT.6.03x Embedded Systems - Shape the World
 *           Lab 06: Branching Function Delays
 *
 * @section  DESCRIPTION
 *
 * Calculates the area of a rectangle.
 *     If 3 <= Lenght, Width <= 20, Area = Length * Width
 *     Otherwise, Area = 0
 */


#include "TExaS.h" // lab grader functions

// Constant declarations to access port registers
// using symbolic names instead of addresses
#define GPIO_PORTF_DATA_R     (*((volatile unsigned long*)0x400253FC))
#define GPIO_PORTF_DIR_R      (*((volatile unsigned long*)0x40025400))
#define GPIO_PORTF_AFSEL_R    (*((volatile unsigned long*)0x40025420))
#define GPIO_PORTF_PUR_R      (*((volatile unsigned long*)0x40025510))
#define GPIO_PORTF_DEN_R      (*((volatile unsigned long*)0x4002551C))
#define GPIO_PORTF_LOCK_R     (*((volatile unsigned long*)0x40025520))
#define GPIO_PORTF_CR_R       (*((volatile unsigned long*)0x40025524))
#define GPIO_PORTF_AMSEL_R    (*((volatile unsigned long*)0x40025528))
#define GPIO_PORTF_PCTL_R     (*((volatile unsigned long*)0x4002552C))
#define SYSCTL_RCGC2_R        (*((volatile unsigned long*)0x400FE108))
#define SYSCTL_RCGC2_GPIOF    0x00000020 // port F Clock Gating Control

// Global variables
unsigned long switch_input;              // input from PF4
// Function prototypes
void EnableInterrupts(void);             // enable interrupts
void Delay100ms(unsigned long time);     // delay function
void PortFInit(void);                    // port F initial function

int main(void) {
    // Setup
    // activate grader and set system clock to 80 MHz
    TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);
    PortFInit();        // port F initialization
    EnableInterrupts(); // enable interrupts for the grader

    // Loop
    while (1) {
        switch_input = GPIO_PORTF_DATA_R & 0x10; // read bit PF4 into SW1

        if (!switch_input) {                     // SW1 is pressed
            Delay100ms(1);                       // set delay of 0.1 second
            GPIO_PORTF_DATA_R ^= 0x04;           // toggle out
        } else {                                 // SW1 is not pressed
            GPIO_PORTF_DATA_R = 0x04;            // turn on the blue LED
        }
    }
}

/**
 * Initializes port F pins for input and output
 */
void PortFInit(void) {
    volatile unsigned long delay;

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // 1) F clock
    delay = SYSCTL_RCGC2_R;               // delay
    GPIO_PORTF_LOCK_R = 0x4C4F434B;       // 2) unlock PortF
    GPIO_PORTF_CR_R |= 0x14;              // allow changes to PF4 (SW1) and PF2 (Blue LED)
    GPIO_PORTF_AMSEL_R = 0x00;            // 3) disable analog function
    GPIO_PORTF_PCTL_R = 0x00;             // 4) GPIO clear bit PCTL
    GPIO_PORTF_DIR_R |= 0x04;             // 5) PF4 (SW1) is input,
                                          // PF2 (Blue LED) is output
    GPIO_PORTF_AFSEL_R = 0x00;            // 6) no alternate function
    GPIO_PORTF_PUR_R |= 0x10;             // enable pullup resistor on PF4
    GPIO_PORTF_DEN_R |= 0x14;             // 7) enable digital pins PF4, PF2
}

/**
 * Delays some hundreds of milliseconds
 *
 * @param  time  how many hundreds of milliseconds to delay
 *
 * @assumption   80-MHz clock
 */
void Delay100ms(unsigned long time) {
    unsigned long i;

    while (time) {
        i = 1333333; // this number means 100ms

        while (i) {
            i--;
        }
        time--; // decrements every 100 ms
    }
}
