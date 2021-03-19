/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */

    TRISD0 = 0; // LED output
    TRISD7 = 0;  // PWM output is on PORTD.7.

    TRISA0=1; // Makes bit A0 in PORTA register as input 
    
    ANS0= 1; // disabling digital buffer to make analog input
    
    ADFM = 0; // Left justified, result format
    
    ACQT2 = 1; // sets acquisition time to 12Tad
    ACQT1 = 0;
    ACQT0 = 1;
    
    ADCS2 = 0; // sets conversion clock to Frc 
    ADCS1 = 1;
    ADCS0 = 1;
    
    VCFG1 = 0; // Negative voltage reference supplied internally by Vss
    VCFG0 = 0; // Positive voltage reference supplied internally by Vdd
    
    CHS3=0; // Analog channel select bits
    CHS2=0;
    CHS1=0;
    CHS0=0;
    
    ADON = 1; // ADC is enabled
    
    ADIF = 0; // clear ADC interrupt flag
   
    /* Configure timer 2. */
    T2CKPS1 = 1; // set timer 2 prescaler to 1:16.
    TMR2ON = 1; // turn on timer 2
    PR2 = 194; // timer 2 will count for 195 steps
    
    CCP1CONbits.CCP1M = 0x0c; // PWM mode; 

    /* Output PWM to PORTD.7. */
    P1M1 = 0;
    P1M0 = 1;
    
    
    CCPR1L = 0x61; // 8 MSBs of 0111 1101 00
    DC1B1 = 1; // bit 1 of 0110 0001 10
    DC1B0 = 0; // bit 0 of 0110 0001 10

}
