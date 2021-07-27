/*
 * ATmega16_DHT11_Project_File.c
 * Author      : Mesbah Abdullah                         
 * helpful resources : http://www.electronicwings.com
 * https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "DHT11_interface.h"
#include "UART_interface.h"
#include "WDT_interface.h"

#include <util/delay.h>
#define DHT11_PIN 4

u8 c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void Request()				/* Microcontroller send start pulse/request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(18);			/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);	/* set to high pin */
}

void Response()				/* receive response from DHT11 */
{
	WDT_VidON();
	DDRD &= ~(1<<DHT11_PIN);
	while( PIND & (1<<DHT11_PIN    ));
	while((PIND & (1<<DHT11_PIN))==0);
	while( PIND & (1<<DHT11_PIN    ));
	WDT_VidOFF();
}

u8 Receive_data()			/* receive data */
{	
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		  c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

void DHT11_VidStart(void)
{	
	char data[5];
	UART_VidSendString("Humidity =");
	UART_VidSendString("Temp = ");
	
		Request();		/* send start pulse */
		Response();		/* receive response */
        GPIO_VidSetPinValue(GPIO_PORTC,PIN7,LOW);

		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */

		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			UART_VidSendString("Error");
		}
		
		else
		{	
			itoa(I_RH,data,10);
			UART_VidSendString(data);
			UART_VidSendString(".");
			
			itoa(D_RH,data,10);
			UART_VidSendString(data);
			UART_VidSendString("%");

			itoa(I_Temp,data,10);
			UART_VidSendString(data);
			UART_VidSendString(".");
			
			itoa(D_Temp,data,10);
			UART_VidSendString(data);
			UART_VidSendString("C ");
			
			itoa(CheckSum,data,10);
			UART_VidSendString(data);
			UART_VidSendString(" ");
		}
				
	_delay_ms(10);	
}