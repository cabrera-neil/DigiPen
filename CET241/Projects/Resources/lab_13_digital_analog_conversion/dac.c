/**
 * @file     dac.c
 * @author   Phi Luu
 * @date     April 22, 2016
 *
 * @brief    UTAustinX: UT.6.03x Embedded Systems - Shape the World
 *           Lab 13: Digital-Analog Conversion
 *
 * @section  DESCRIPTION
 *
 * Initializes DAC and writes data into a 4-bit DAC.
 * Note that 4-bit DAC connected to PB3-PB0.
 */

#include "dac.h"
#include "tm4c123gh6pm.h"

/**
 * Initializes 4-bit DAC.
 */
void InitDac(void) {
    volatile unsigned long delay;

    SYSCTL_RCGC2_R |= 0x02;          // unlock port B clock
    delay = SYSCTL_RCGC2_R;          // allow time for clock to start
    GPIO_PORTB_LOCK_R |= 0x4C4F434B; // unlock GPIO Port B
    GPIO_PORTB_CR_R |= 0x0F;         // allow change to PB3-PB0
    GPIO_PORTB_AMSEL_R &= ~0x0F;     // disable analog function on PB3-PB0
    GPIO_PORTB_PCTL_R = 0x00;        // clear PCTL register on PB3-PB0
    GPIO_PORTB_DIR_R |= 0x0F;        // PB3-PB0 outputs
    GPIO_PORTB_AFSEL_R &= ~0x0F;     // disable alternate function on PB3-PB0
    GPIO_PORTB_DEN_R |= 0x0F;        // enable digital pins on PB3-PB0
    GPIO_PORTB_DR8R_R |= 0x0F;       // enable 8-mA drive select on PB3-PB0
}

/**
 * Writes output to DAC.
 *
 * @param  data  4-bit data, 0 to 15
 */
void OutDac(unsigned long data) {
    // write every single value from the SineWave array
    GPIO_PORTB_DATA_R = data;
}
