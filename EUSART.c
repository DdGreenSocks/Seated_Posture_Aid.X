
#include <xc.h>
#define _XTAL_FREQ 16000000

void Init_EUSART(void){
    
  OSCCONbits.IRCF0=1;
  OSCCONbits.IRCF1=1;
  OSCCONbits.IRCF2=1;
  TRISDbits.RD0=0;
  TRISDbits.RD1=0;
  TRISCbits.RC7=1;           // Set RC7 as receive pin   
  TRISCbits.RC6=1;           // Set RC6 as transmit pin
  
  TXSTAbits.TXEN=1;         // Enables transmitter circuitry 
  TXSTAbits.SYNC=0;         // Asynchronous operation
  RCSTAbits.SPEN=1;         // Enables EUSART 
  TXSTAbits.TX9=0;          // Sets 8 bit transmission
 
  BAUDCONbits.BRG16=1;      // Determines multiplier of baud rate
  
  SPBRG= 0x67;                // Register value to achieve approx 9600 baud rate
  
  RCSTAbits.CREN=1;         // Enables receiver circuitry 
  RCSTAbits.RX9=0;          // Sets 8 bit reception
  
  //GIE=1;
  PEIE=1;
  
  PIE1bits.RCIE=1;    // Enables Receive Interrupt
  PIE1bits.TXIE=1;    // Enables Transmit Interrupt 
  

}

/**Function to send one byte of date to UART**/
void BT_load_char(char bt)  
{
   TXREG = bt; //Load the transmitter buffer with the received value
   while(!TXIF);  // hold the program till TX buffer is free
   while(!TRMT);
 }


//Function to broadcast data from RX. buffer//
void broadcast_BT()
{
  TXREG = 13;     //ASCII for carriage return
  __delay_ms(500);
}

//**Function to get one byte of date from UART**//
int BT_get_char()   
{
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    
    if(RCIF==1) //if the user has sent a char return the char (ASCII value)
    {
        while(!RCIF);  
        return RCREG;
    }
    else //if user has sent no message return 0
        return 0;
}

//Function to Load Bluetooth Rx. buffer with string//
void BT_load_string(char* string)
{
    while(*string)
    BT_load_char(*string++);
}
//End of function/