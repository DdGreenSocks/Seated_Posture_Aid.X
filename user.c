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

void InitApp(void)
{
    

/* Initialize I/O */                                                            

    TRISDbits.RD0 = 0;     // LED output on D0
    TRISDbits.RD1 = 0;     // LED output on RD1 
    TRISDbits.RD7 = 0;     // PWM output on D7
    TRISAbits.RA0 = 1;     // ADC input on  A0
    TRISBbits.RB0 = 1;     // Set RB0 button as input
    
 
   
  /* Initialize Button Interrupt */
    
//    ANSELHbits.ANS12 = 0;       // Set RB0 as digital input
//    RCONbits.IPEN = 1;
//    INTCONbits.GIE = 1;         // Enables Global interrupts
//    INTCONbits.INT0IE=1;
//    INTCONbits.INT0IF=0;  // Clear External Interrupt Flag
//    INTCON2bits.INTEDG0 = 1;    // Interrupt on falling edge
   
}

