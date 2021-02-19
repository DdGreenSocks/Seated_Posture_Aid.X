/******************************************************************************/
/* Name: Posture_Aid
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

#define _XTAL_FREQ 8000000

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned int neutral_pos;
unsigned int real_pos;
unsigned int max_pos;
unsigned int min_pos;
unsigned int duty_cycle; 
/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Function to get Initial Flex Reading                                                             */
/******************************************************************************/


unsigned int Neutral_Init(){
    
  PORTD=0xFF; 
  //__delay_ms(2); //Acquisition time to charge hold capacitor
  GO = 1; //Initializes A/D Conversion
  return (ADRESH); //Returns Result
    
  
}

/******************************************************************************/
/* Function to get Continuous Flex Reading                                                               */
/******************************************************************************/

unsigned int Continous_Read(){
    
 // __delay_ms(2); //Acquisition time to charge hold capacitor
  GO = 1; //Initializes A/D Conversion
  return (ADRESH); //Returns Result 
 
}

/******************************************************************************/
/* Function to operate Vibration Motor                                                              */
/******************************************************************************/
unsigned int Vibration_ON(){
    
  //__delay_ms(2); 
  
 
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    real_pos = 0x00;
    neutral_pos = 0x00;
    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp(); // calls user.c code

    /* TODO <INSERT USER APPLICATION CODE HERE> */
 
    neutral_pos = Neutral_Init();//Initializes Flex sensor & initial records value
    
    //__delay_ms(2);
    
    PORTD=0x00; 
    
  
    
    //LED Blinks once to show it has initialized
    
    
    min_pos = neutral_pos - (neutral_pos*0.20); // gets lower tolerance (-30%)
    max_pos = neutral_pos + (neutral_pos*0.20); // gets higher tolerance (+30%)
    
    
    while(1)
   {
     
    real_pos = Continous_Read(); //Continuously reads Flex sensor value
        
     if ((real_pos>=min_pos)&&(real_pos<=max_pos)){
            
          PORTD=0x00; //Lights turn OFF if Sensor is within 30% of initial value 
      //__delay_ms(10);
     }
     
     else{
           
     PORTD=0xFF; //Lights turn ON if Sensor is NOT within 30% of initial value 
        
     
     }
        
   

}
    

}