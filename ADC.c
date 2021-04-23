
#include <xc.h>

#define _XTAL_FREQ 16000000
/******************************************************************************/
/* Initialize ADC                                                            */
/******************************************************************************/
    
    void Init_ADC(void)
{
    TRISAbits.RA0 = 1;         // ADC input on  A0

    ANSELbits.ANS0 = 1;        // disabling digital buffer to make analog input
    ADCON2bits.ADFM = 0;       // Left justified, result format
    
    ADCON2bits.ACQT2 = 1;      // sets acquisition time to 12Tad
    ADCON2bits.ACQT1 = 0;
    ADCON2bits.ACQT0 = 1;
    
    ADCON2bits.ADCS2 = 0;      // sets conversion clock to Frc 
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS0 = 1;
    
    ADCON1bits.VCFG1 = 0;       //Neg volt reference supplied internally by Vss
    ADCON1bits.VCFG0 = 0;      // Pos volt reference supplied internally by Vdd
    
    ADCON0bits.CHS3=0;         // Analog channel select bits
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS0=0;
    
    ADCON0bits.ADON = 1;       // ADC is enabled
    
   
}

/******************************************************************************/
/* Function to get Reading of Flex Reading                                    *                      */
/******************************************************************************/

 double ADCRead_Pos(){ 
  __delay_ms(2);                   //Acquisition time to charge hold capacitor
  GO = 1;                          //Initializes A/D Conversion

  for(int i = 0; i < 8; i++){         //Delay to stop erratic readings
    if (i == 7) {                              
        double temp;                    //Temporary variable to get ADC value

        temp = ADRESL;                //Set reading of ADRESL (low byte) to temp
        temp = temp + (ADRESH << 8);  //Add ADRESH (high bytes) to temp
        return temp;                  //Return calculated ADC value
  
    }
  }
  return -1;
}