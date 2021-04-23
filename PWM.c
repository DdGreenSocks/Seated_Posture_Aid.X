#include <xc.h>

void Init_PWM(void) 
{
    T2CONbits.T2CKPS1 = 1;          // set timer 2 prescaler to 1:16.
    T2CONbits.TMR2ON = 1;           // turn on timer 2
    PR2 = 194;                      // timer 2 will count for 195 steps
    
    CCP1CONbits.CCP1M = 0x0c;       // PWM mode; 

    CCP1CONbits.P1M1 = 0;           // PWM output on D7
    CCP1CONbits.P1M0 = 1;           // PWM output on D7
    
    CCPR1L = 0x61;                  // 8 MSBs of 0111 1101 00
    CCP1CONbits.DC1B1 = 1;          // bit 1 of 0110 0001 10
    CCP1CONbits.DC1B0 = 0;          // bit 0 of 0110 0001 10
  
}
/******************************************************************************/
/* Function to set PWM Duty Cycle                                                           */
/******************************************************************************/

void Vibration_ON(double percentage) {

    long output;

    if (percentage > 100) {
        return;
    }

    output = ((long) (PR2 + 1)) << 2;
    output=  output * ((long) percentage);
    output = output / 100;
    //output = (unsigned char)output;
    
    CCPR1L = output >> 2;       // 10-bit value 8 MSBs
    DC1B1 = (output & 2) >> 1;  // 10-bit value bit 1
    DC1B0 = (output & 1);       // 10-bit value bit 0

}

