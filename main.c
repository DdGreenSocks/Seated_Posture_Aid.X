/******************************************************************************/
/* Name: Seated_Posture_Aid
 * Last Updated: 12/02/2021
 * Author: Deirdre Kelly                                                    */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "ADC_Read.h"
#define _XTAL_FREQ 8000000

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

unsigned int max_pos;
unsigned int min_pos;
unsigned int duty_cycle; 
unsigned int temp;

/******************************************************************************/
/* Function to set PWM Duty Cycle                                                           */
/******************************************************************************/

void PWMSetDutyCycle(unsigned int percentage) {

    long output;

    if (percentage > 100) {
        return;
    }

    output = ((long) (PR2 + 1)) << 2;
    output=  output * ((long) percentage);
    output = output / 100;

    CCPR1L = output >> 2; // 10-bit value 8 MSBs
    DC1B1 = (output & 2) >> 1; // 10-bit value bit 1
    DC1B0 = (output & 1); // 10-bit value bit 0

}

/******************************************************************************/
/* Function to operate Vibration Motor                                                              */
/******************************************************************************/

void Vibration_ON(unsigned int percentage){
    
    
        
   PWMSetDutyCycle(percentage);
  
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp(); // calls user.c code
    Init_ADC();
    
    
    neutral_pos = 0x00;
    real_pos =0x00;
    PORTDbits.RD7=0;
    Vibration_ON(0);
    
  
 
    neutral_pos = ADCRead_Pos();
    
    PORTDbits.RD0=0xFF;
    __delay_ms(200);
    PORTDbits.RD0=0x00; 
   __delay_ms(200);
    PORTDbits.RD0=0xFF;
   __delay_ms(200);
    PORTDbits.RD0=0x00; 
    //LED Blinks once to show it has initialized
    
    
   
    
    
    while(1)
   {
     
    min_pos = neutral_pos - (neutral_pos*0.30); // gets lower tolerance (-30%)
    max_pos = neutral_pos + (neutral_pos*0.30); // gets higher tolerance (+30%)    
        
    real_pos = ADCRead_Pos(); //Continuously reads Flex sensor value
        
     if ((real_pos>=min_pos)&&(real_pos<=max_pos)){
            
      PORTDbits.RD0=0; //Lights turn OFF if Sensor is within 30% of initial value 
     
      Vibration_ON(0);
      
     }
     
     else{
         
         unsigned int percentage ; 
         
         
         PORTDbits.RD0=1; //Lights turn ON if Sensor is NOT within 30% of initial value 
        __delay_ms(100);
        
        Vibration_ON(40);
      
     }
        
}
    

}