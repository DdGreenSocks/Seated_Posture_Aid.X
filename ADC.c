/*
 * File:   ADC.c
 * 
 */
#include <xc.h>

    
    void Init_ADC(void)
{
    TRISAbits.RA0 = 1;          // ADC input on  A0

    ANSELbits.ANS0 = 1;        // disabling digital buffer to make analog input
    ADCON2bits.ADFM = 0;       // Left justified, result format
    
    ADCON2bits.ACQT2 = 1;      // sets acquisition time to 12Tad
    ADCON2bits.ACQT1 = 0;
    ADCON2bits.ACQT0 = 1;
    
    ADCON2bits.ADCS2 = 0;      // sets conversion clock to Frc 
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS0 = 1;
    
    ADCON1bits.VCFG1 = 0;      // Negative voltage reference supplied internally by Vss
    ADCON1bits.VCFG0 = 0;      // Positive voltage reference supplied internally by Vdd
    
    ADCON0bits.CHS3=0;         // Analog channel select bits
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS0=0;
    
    ADCON0bits.ADON = 1;       // ADC is enabled
    
    //PIR1bits.ADIF = 0;       // clear ADC interrupt flag

}

/******************************************************************************/
/* Function to get Initial Flex Reading & Change in Flex Reading                                                           */
/******************************************************************************/

 unsigned int ADCRead_Pos(){ 
  
 //__delay_ms(2); //Acquisition time to charge hold capacitor
  GO = 1; //Initializes A/D Conversion
  unsigned int temp;
  
  temp = ADRESL;
  temp = temp + (ADRESH << 8);
  return temp;
 
}