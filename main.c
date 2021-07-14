/*
 * graduation project faculty of electronic engineering (smart city)
 * Created: 7/2/2021 10:24:12 PM
 * author Mesbah Abdullah 
 */ 

//#include <avr/io.h>
#define  F_CPU 16000000UL
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "DHT11_interface.h"
#include "ESP_interface.h"
#include "ADC_interface.h"
#include <util/delay.h>//it has delay function
/***********************************temperature sensor variables**********************************/
    #define TEMP_PIN                 1
	u16 adc_result1;
    s16 temp;
    s16 far;
    u8 buffer[10];           

/*This function is to read an analogue value from temp sensor lm-35 and send the data using UART */
void TEMP_VidReadValue()
{
	adc_result1 = ADC_u16ReadChannel(TEMP_PIN);      // read ADC value 		
	temp=adc_result1*4.88;   // finding the temperature
	temp=temp/10.0;
	itoa(temp,buffer,10);
	UART_VidSendString((u8*)"Temp=");   //display temperature
	UART_VidSendString(buffer);
	UART_VidSendString((u8*)"C\r\n"); 		
	_delay_ms(1000);
}
// u8 *x;
/***********************************GAS Sensor variables******************************************/
    #define GAS_PIN                   2
    u16 adc_result0=0;
    u8 tempBuffer[10];
/*This function is to read an analogue value from gas sensor MQ-135 and send the data using uart */
void GAS_VidReadValue()
{
    adc_result0 = ADC_u16ReadChannel(GAS_PIN);
    itoa(adc_result0,tempBuffer,10);
    UART_VidSendString((u8*)tempBuffer);
}

/******This function is to read an digital value from PIR sensor and send the data using uart*****/
void PIR_VidReadValue()
{
    //u8 localVariable=GPIO_u8GetPinValue(GPIO_PORTB,PIN0);	//test that line for ma
    if(GPIO_u8GetPinValue(GPIO_PORTB,PIN0)==1)
        UART_VidSendString((u8*)"there is someone moving around");
    else
        UART_VidSendString((u8*)"No one is moving");
}

/******This function is to read an digital value from IR sensor and send the data using uart*****/
void IR_VidReadValue()
{
	
}
int main(void)
{

    GPIO_VidSetPinDirection(GPIO_PORTB,PIN0,INPUT);  //This pin is for operating the PIR sensor
	UART_VidInt();	
	ADC_VidInit();	 
    UART_VidSendString((u8*)"HI HOW ARE U ");
    while (1) 
    {
	 /* DHT11 operating */	
	 DHT11_VidStart();    
	 _delay_ms(2000); //to call the DHT11_VidStart() again  

	 /* MQ-135 operating */
	   GAS_VidReadValue();
	  _delay_ms(2000);
     /*lm-35 operating */
	 TEMP_VidReadValue();
     _delay_ms(2000);

	 /*PIR operating */	  
	 PIR_VidReadValue();
	 _delay_ms(2000);
    }
}