/******************************************************************************/
/* Name: Seated_Posture_Aid
 * Last Updated: 23/04/2021
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
#include "PWM.h"
#include "EUSART.h"

#define _XTAL_FREQ 16000000

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

double max_pos;
double min_pos;
unsigned int send_bad_posture_msg_counter;
unsigned int send_good_posture_msg_counter;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    
    InitApp();          // calls user.c code
    Init_ADC();         // calls ADC.c code
    Init_PWM();         // calls PWM.c code
    Init_EUSART();      // calls EUSART.c code
    
    /* Clears existing memory associated with variables */
    neutral_pos = 0;
    real_pos = 0;
    send_bad_posture_msg_counter = 0;
    send_good_posture_msg_counter = 0;
    PORTD =0x00;
    PORTA =0x00;
    
    Vibration_ON(0);
    
    /* Reads in initial position of flex sensor*/
    neutral_pos = ADCRead_Pos();
    
    /*LED on RD1 blinks twice to show it has initialized on power start up*/
    PORTDbits.RD1=1;
    PORTDbits.RD0=0;
    __delay_ms(200);
    PORTDbits.RD1=0; 
    PORTDbits.RD0=1;
    __delay_ms(200);
    PORTDbits.RD1=1;
    PORTDbits.RD0=0;
    __delay_ms(200);
    PORTDbits.RD1=0; 
    PORTDbits.RD0=0;
    
    max_pos = neutral_pos + (neutral_pos*0.10);
    min_pos = neutral_pos - (neutral_pos*0.10);
    
   while(1)
   {
       /* Calculates range from neutral position and continuously reads flex 
         sensor value */
        
        real_pos = ADCRead_Pos(); 
        
        /*ADC value is within 15% neutral position LED & motor turns off & 
          bluetooth sends out '1' once until if statement is entered again*/
        if (real_pos>=min_pos && real_pos<=max_pos){
            
            PORTDbits.RD0=0;                        
            Vibration_ON(0);     
            
            send_bad_posture_msg_counter = 0;
            if(send_good_posture_msg_counter == 0){
                
                BT_load_string("1");
                __delay_ms(100);   
                broadcast_BT();
            }
            send_good_posture_msg_counter++;
        }
        
        /*ADC value is NOT within 15% neutral position LED & motor turns ON & 
          bluetooth sends out '0' once until if statement is entered again*/
        else if(real_pos<min_pos || real_pos>max_pos){
            
            __delay_ms(1000);  //Delay to allow for small movement
            PORTDbits.RD0=1;                    
            Vibration_ON(real_pos/256);  
            
            send_good_posture_msg_counter = 0;
            if (send_bad_posture_msg_counter == 0){
                
                BT_load_string("0");
                __delay_ms(100);   
                broadcast_BT();      
            }
            send_bad_posture_msg_counter++;   
        }   
        
        /*Bluetooth interrupt to allow for neutral position value to change 
          when a '1' is received and LED blinks */
        if (RCIF == 1){ 
            
            if(RCREG=='1'){
                
                PORTDbits.RD1=1; 
                __delay_ms(200);
                neutral_pos = ADCRead_Pos();
                PORTDbits.RD1=0;
                
                max_pos = neutral_pos + (neutral_pos*0.10);
                min_pos = neutral_pos - (neutral_pos*0.10);
            }
            
        }
    
    } 

}