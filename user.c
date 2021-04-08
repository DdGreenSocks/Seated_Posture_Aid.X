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
    

/* Initialize I/O */                                                            

    TRISDbits.RD0 = 0;     // LED output on D0
    TRISDbits.RD1 = 0;     // LED output on RD1 
    TRISDbits.RD7 = 0;     // PWM output on D7
    TRISAbits.RA0 = 1;     // ADC input on  A0
    TRISBbits.RB0 = 1;     // Set RB0 button as input
    
 
   
    /* Initialize PWM */
    
    T2CONbits.T2CKPS1 = 1;    // set timer 2 prescaler to 1:16.
    T2CONbits.TMR2ON = 1;     // turn on timer 2
    PR2 = 194;                // timer 2 will count for 195 steps
    
    CCP1CONbits.CCP1M = 0x0c; // PWM mode; 

    CCP1CONbits.P1M1 = 0;           // PWM output on D7
    CCP1CONbits.P1M0 = 1;           // PWM output on D7
    
    CCPR1L = 0x61;      // 8 MSBs of 0111 1101 00
    CCP1CONbits.DC1B1 = 1;          // bit 1 of 0110 0001 10
    CCP1CONbits.DC1B0 = 0;          // bit 0 of 0110 0001 10

     /* Initialize Button Interrupt */
    
    ANSELHbits.ANS12 = 0;       // Set RB0 as digital input
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;         // Enables Global interrupts
    INTCONbits.INT0IE=1;
    INTCONbits.INT0IF=0;  // Clear External Interrupt Flag
    INTCON2bits.INTEDG0 = 1;    // Interrupt on falling edge
}

