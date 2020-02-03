/**
 * @file     main.c
 * @author   Phi Luu
 * @date     May 07, 2016
 *
 * @brief    UTAustinX: UT.6.03x Embedded Systems - Shape the World
 *           Lab 14: Analog-Digital Conversion
 *
 * @section  DESCRIPTION
 *
 * Captures analog signals of the slide potentiometer and convert to digital
 * signals, whose values are displayed on the Nokia5110 LCD.
 */

/**
 * Required hardware I/O connections
 *
 * Slide pot pin 1 connected to GND
 * Slide pot pin 2 connected to PE2/AIN1
 * Slide pot pin 3 connected to +3.3V
 * Switch connected to PF4
 * Red LED built in PF2
 */

#include "adc.h"
#include "tm4c123gh6pm.h"
#include "nokia5110.h"
#include "TExaS.h"

// Function prototypes
void InitSystick(void);
void InitPortF(void);
void ConvertSampleToDistance(void);
void EnableInterrupts(void);

// Global variables
unsigned char out_str[10];   // null-terminated ASCII string
unsigned long distance;      // unit of 0.001 cm
unsigned long adc_data;      // 12-bit 0 to 4095 sample
unsigned long distance_flag; // 1 = valid distance, 0 = empty distance

int main(void) {
    // Setup
    TExaS_Init(ADC0_AIN1_PIN_PE2, SSI0_Real_Nokia5110_Scope);
    // initialize ADC0, channel 1, sequencer 3
    InitAdcChannel0();
    Nokia5110_Init();
    // initialize SysTick for 40 Hz interrupts
    InitSystick();
    InitPortF();
    EnableInterrupts();

    // Loop
    while (1) {
        distance_flag = 0;              // read mailbox

        while (distance_flag != 1) {}  // wait for the flag to be set
        Nokia5110_OutString(out_str);   // output to Nokia5110 LCD
        UartDistanceToString(distance); // convert distance to a proper format
        Nokia5110_SetCursor(0, 0);      // set the initial cursor position
    }
}

/**
 * Converts a 12-bit binary ADC sample into a 32-bit unsigned
 * fixed-point distance (resolution 0.001 cm).  Calibration
 * data is gathered using known distances and reading the
 * ADC value measured on PE2.
 *
 * @param   sample  12-bit ADC sample
 *
 * @return          32-bit distance (resolution 0.001cm)
 */
unsigned long ConvertSampleToDistance(unsigned long sample) {
    // Truth        adc_data
    // 500              471
    // 1000            1220
    // 1500            1976

    // slope_1 = (1000 - 500) / (1220 - 471) = 0.668
    // slope_2 = (1500 - 1000) / (1976 - 1220) = 0.661
    // slope_average = (0.668 + 0.661) / 2 = 0.6645

    // offset_1 = 500 - 0.6645 * 471 = 187.0205
    // offset_2 = 1000 - 0.6645 * 1220 = 189.31
    // offset_3 = 1500 - 0.6645 * 1976 = 186.948

    // offset_average = (187.0205 + 189.31 + 186.948) / 3 = 188

    // B = 188
    // A = 0.6645 * 1024 = 680

    unsigned long result;

    // distance = ((A * adc_data) >> 10) + B
    result = ((680 * sample) >> 10) + 188;
    return result;
}

/**
 * Initializes SysTick interrupts to trigger at 40 Hz, 25 ms.
 *
 * @assumption    80-MHz clock
 */
void InitSystick() {
    NVIC_ST_CTRL_R = 0;         // disable SysTick during startup
    NVIC_ST_RELOAD_R = 1999999; // trigger every 25ms
    // period = 1/(40Hz) * (80,000,000Hz) = 2,000,000
    // period - 1 = 1,999,999
    NVIC_ST_CURRENT_R = 0;      // any write to CURRENT clear it
    NVIC_ST_CTRL_R |= 0x05;     // set bits CLK_SRC and ENABLE of SysTick
    // priority 1
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
    NVIC_ST_CTRL_R |= 0x07;     // set bits CLK_SRC, INTEN, and ENABLE
}

/**
 * Executes every 25 ms, collects a sample, converts and stores in mailbox
 *
 * @assumption    80-MHz clock
 */
void SysTick_Handler(void) {
    GPIO_PORTF_DATA_R ^= 0x04;                    // toggle PF2
    GPIO_PORTF_DATA_R ^= 0x04;                    // toggle PF2 again
    adc_data = AdcChannel0In();                   // sample the ADC
    distance = ConvertSampleToDistance(adc_data); // convert to distance
    distance_flag = 1;                            // set the flag - new data is ready
    GPIO_PORTF_DATA_R ^= 0x04;                    // toggle PF2 the third time
}

/**
 * Converts a 32-bit distance into an ASCII string
 * and stores the conversion in global variable out_str[10]
 *
 * @param  n  32-bit unsigned number to be converted (resolution 0.001cm)
 *
 * @notes     Fixed format 1 digit, point, 3 digits, space, units, null termination
 *
 * @examples
 *   4 to "0.004 cm"
 *   31 to "0.031 cm"
 *   102 to "0.102 cm"
 *   2210 to "2.210 cm"
 *   10000 to "*.*** cm"  any value larger than 9999 converted to "*.*** cm"
 */
void UartDistanceToString(unsigned long n) {
    // first, put m into out_str[10]
    short i = 0, j = 0;
    unsigned short str_len;
    unsigned char reverse_str[15];
    unsigned long m = n; // keep n the same value after converting

    // special case
    if (m == 0) {
        str_len = 1;       // the length of out_str[10] is only 1
        out_str[0] = 0x30; // out_str[10] only contains only one '0'
        return;            // then exit immediately
    }

    // otherwise
    while (m != 0) {
        // using 10-division to get every single digit of m until m = 0
        reverse_str[j] = m % 10 + 0x30; // get the last digit of n
        m /= 10;                        // after get a digit, decrease n for the next time
        // eventually, n will equal 0 and the loop will be terminated
        j++;                            // increase the index
    }
    // the result string is reversed because of this method
    // change to the right order
    str_len = j;

    for (j = str_len - 1; j >= 0; j--) {
        out_str[i] = reverse_str[j];
        // the last digit in reverse_str[10] is the first one in out_str[10]
        i++; // increase the index of out_str[10]
    }

    // second, go over each case
    // n has 1 digits
    if (n <= 9) {
        out_str[4] = out_str[0];
        out_str[0] = 0x30;
        out_str[1] = '.';
        out_str[2] = 0x30;
        out_str[3] = 0x30;
        out_str[5] = 0x20;
        out_str[6] = 'c';
        out_str[7] = 'm';
    }
    // n has 2 digits
    else if ((n >= 10) && (n <= 99)) {
        out_str[4] = out_str[1];
        out_str[3] = out_str[0];
        out_str[0] = 0x30;
        out_str[1] = '.';
        out_str[2] = 0x30;
        out_str[5] = 0x20;
        out_str[6] = 'c';
        out_str[7] = 'm';
    }
    // n has 3 digits
    else if ((n >= 100) && (n <= 999)) {
        out_str[4] = out_str[2];
        out_str[3] = out_str[1];
        out_str[2] = out_str[0];
        out_str[0] = 0x30;
        out_str[1] = '.';
        out_str[5] = 0x20;
        out_str[6] = 'c';
        out_str[7] = 'm';
    }
    // n has 4 digits
    else if ((n >= 1000) && (n <= 9999)) {
        out_str[4] = out_str[3];
        out_str[3] = out_str[2];
        out_str[2] = out_str[1];
        out_str[1] = '.';
        out_str[5] = 0x20;
        out_str[6] = 'c';
        out_str[7] = 'm';
    }
    // n has more than 4 digits (Overflow)
    else {
        out_str[0] = '*';
        out_str[1] = '.';
        out_str[2] = '*';
        out_str[3] = '*';
        out_str[4] = '*';
        out_str[5] = 0x20;
        out_str[6] = 'c';
        out_str[7] = 'm';
    }
}

/**
 * Initializes port F for the blue LED and SW1
 */
void InitPortF(void) {
    volatile unsigned long delay;

    SYSCTL_RCGC2_R |= 0x20;          // enable port F clock
    delay = SYSCTL_RCGC2_R;          // allow time for clock to start
    GPIO_PORTF_LOCK_R |= 0x4C4F434B; // unlock GPIO port F
    GPIO_PORTF_CR_R |= 0x14;         // allow change to PF4, PF2
    GPIO_PORTF_DIR_R |= 0x04;        // PF4 input, PF2 output
    GPIO_PORTF_AFSEL_R &= ~0x14;     // disable alternate function on PF4, PF2
    GPIO_PORTF_PCTL_R = 0;           // disable PCTL
    GPIO_PORTF_DEN_R |= 0x14;        // enable digital I/O on PF4, PF2
    GPIO_PORTF_PUR_R |= 0x10;        // enable pull-up resistor on PF4
    GPIO_PORTF_AMSEL_R &= ~0x14;     // disable analog function on PF4, PF2
}
