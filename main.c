/*
 * 
 *
 * Created: 7/2/2021 10:24:12 PM
 * 
 */ 

//#include <avr/io.h>
#define  F_CPU 16000000UL
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "DHT11_interface.h"
//#include "ESP_interface.h"
#include "lcd.h"
#include "ADC_interface.h"
#include <util/delay.h>//it has delay function
#define GAS_PIN                   2
#define TEMP_PIN                  1


/*This function is to read an analogue value from temp sensor lm-35 and send the data using uart */
void TEMP_VidReadValue()
{
	u16 adc_result1;
    s16 temp;
    s16 far;
    u8 buffer[10];


		adc_result1 = ADC_u16ReadChannel(TEMP_PIN);      // read adc value 
		
		temp=adc_result1/2.01;   // finding the temperature
		itoa(temp,buffer,10);
		UART_VidSendString((u8*)"Temp=");   //display temperature
		UART_VidSendString(buffer);
		UART_VidSendString((u8*)"C"); 		
		_delay_ms(1000);
}
// u8 *x;

        /*This function is to read an analogue value from gas sensor MQ-135 and send the data using uart */
void GAS_VidReadValue()
{
   u16 adc_result0=0;
   u8 tempBuffer[10];
   adc_result0 = ADC_u16ReadChannel(GAS_PIN);
   itoa(adc_result0,tempBuffer,10);
   UART_VidSendString((u8*)tempBuffer);
}
int main(void)
{

	
	UART_VidInt();	
		 
    UART_VidSendString((u8*)"HI HOW ARE U ");
    while (1) 
    {
	    /* DHT11 operating */	
	  //DHT11_VidStart();    
	  //_delay_ms(2000); //to call the DHT11_VidStart() again  


	  /* MQ-135 operating */
	  //GAS_VidReadValue();
	 // _delay_ms(2000);

	 TEMP_VidReadValue();
	_delay_ms(2000);
	  
 }
}
