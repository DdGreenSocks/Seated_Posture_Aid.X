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
#include "PWM.h"
#include "EUSART.h"

#define _XTAL_FREQ 16000000

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

unsigned int max_pos;
unsigned int min_pos;
int send_bad_posture_msg_counter;
int send_good_posture_msg_counter;
int get_value;

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
    real_pos =0;
    send_bad_posture_msg_counter = 0;
    send_good_posture_msg_counter = 0;
    PORTD =0x00;
    PORTAbits.RA0 =0;
    Vibration_ON(0);
    
    /* Reads in initial position of flex sensor*/
    neutral_pos = ADCRead_Pos();
    
//    PORTDbits.RD1=0xFF;
//    __delay_ms(200);
//    PORTDbits.RD1=0x00; 
//    __delay_ms(200);
//    PORTDbits.RD1=0xFF;
//    __delay_ms(200);
//    PORTDbits.RD1=0x00; 
    //LED on RD1 blinks twice to show it has initialized
    
    while(1)
   {
       
    min_pos = neutral_pos - (neutral_pos*0.10); // gets lower tolerance (-30%)
    max_pos = neutral_pos + (neutral_pos*0.10); // gets higher tolerance (+30%)    
        
    real_pos = ADCRead_Pos(); //Continuously reads Flex sensor value
        
        if ((real_pos>=min_pos)&&(real_pos<=max_pos)){
            
            PORTDbits.RD0=0;    //Light turns OFF if in 30% range 
     
            Vibration_ON(0);    //Vibration turns OFF if in 30% range 
            send_bad_posture_msg_counter = 0;
            if(send_good_posture_msg_counter == 0){
                BT_load_string("1");
                __delay_ms(100);   //Delay before vibration to prevent
                broadcast_BT();
            }
            send_good_posture_msg_counter++;
        }
     
        else{
         
            PORTDbits.RD0=1;    //Light turns ON if NOT in 30 % range 
            
            __delay_ms(100);   //Delay before vibration to prevent 
                               //vibration for small movement
            
            Vibration_ON(50);  //Vibration turns ON if NOT in 30 % range
            send_good_posture_msg_counter = 0;
            if (send_bad_posture_msg_counter == 0){
                BT_load_string("0");
                __delay_ms(100);   //Delay before vibration to prevent
                broadcast_BT();
                
            }
            send_bad_posture_msg_counter++;
             
        }   
        
    if (RCIF == 1){ 
            
            if(RCREG=='1'){
                
                PORTDbits.RD1=1; //Turn on LED
                __delay_ms(200);
                neutral_pos = ADCRead_Pos();
                //PORTDbits.RD1=0;
            }
            
        }
    
    }
    

}