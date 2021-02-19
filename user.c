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

    TRISD = 0x00; // Makes all 8 bits in PORTD register as outputs 

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
    
    
    GIE = 1; // enables global interrupts
    PEIE= 1; // enables all unmasked peripheral interrupts
    
    ADIE = 1; //enables A/D converter interrupt
    
    
     
}

/******************************************************************************/
/* Function to get Initial Flex Reading                                                             */
/******************************************************************************/


unsigned int Neutral_Init(){
  unsigned int neutral_pos;  
  
  PORTD=0xFF; 
  //__delay_ms(2); //Acquisition time to charge hold capacitor
  GO = 1; //Initializes A/D Conversion
  neutral_pos = ADRESL;
  return (neutral_pos +(ADRESH<<8)); //Returns Result
    
  
}


/******************************************************************************/
/* Function to get Continuous Flex Reading                                                               */
/******************************************************************************/

unsigned int Continous_Read(){
   
    unsigned int real_pos;
 // __delay_ms(2); //Acquisition time to charge hold capacitor
  GO = 1; //Initializes A/D Conversion
  //ADRESH = real_pos;
  return (ADRESH); //Returns Result 
 
}