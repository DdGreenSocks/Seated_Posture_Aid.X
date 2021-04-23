
#include <xc.h>
#define _XTAL_FREQ 16000000

/******************************************************************************/
/* Initialize EUSART                                                          */
/******************************************************************************/
void Init_EUSART(void){
    
  OSCCONbits.IRCF0=1;       //Internal OSC Frequency set to 16MHZ
  OSCCONbits.IRCF1=1;
  OSCCONbits.IRCF2=1;
  
  TRISCbits.RC7=1;          // Set RC7 as receive pin   
  TRISCbits.RC6=1;          // Set RC6 as transmit pin
  
  TXSTAbits.TXEN=1;         // Enables transmitter circuitry 
  TXSTAbits.SYNC=0;         // Asynchronous operation
  RCSTAbits.SPEN=1;         // Enables EUSART 
  TXSTAbits.TX9=0;          // Sets 8 bit transmission
 
  BAUDCONbits.BRG16=1;      // Determines multiplier of baud rate
  
  SPBRG= 0x67;              // Register value to achieve approx 9600 baud rate
  
  RCSTAbits.CREN=1;         // Enables receiver circuitry 
  RCSTAbits.RX9=0;          // Sets 8 bit reception
  
  PEIE=1;                   //Peripheral Interrupts Enabled
  
  PIE1bits.RCIE=1;          // Enables Receive Interrupt
  PIE1bits.TXIE=1;         // Enables Transmit Interrupt 
  

}
/******************************************************************************/
/* Function to send one byte of date to EUSART                                                        */
/******************************************************************************/
void BT_load_char(char bt)  
{
   TXREG = bt;          //Load the transmitter buffer with the received value
   while(!TXIF);        // hold the program till TX buffer is free
   while(!TRMT);
 }
/******************************************************************************/
/* Function to broadcast data from RX. buffer                                                        */
/******************************************************************************/
void broadcast_BT()
{
  TXREG = 13;     //ASCII for carriage return
  __delay_ms(500);
}
/******************************************************************************/
/* Function to Load Bluetooth RX. buffer with string                                                    */
/******************************************************************************/
void BT_load_string(char* string)
{
    while(*string)
    BT_load_char(*string++);
}
