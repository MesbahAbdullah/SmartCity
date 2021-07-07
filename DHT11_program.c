/*
 * ATmega16_DHT11_Project_File.c
 *
 * source code from http://www.electronicwings.com
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "DHT11_interface.h"
#include "UART_interface.h"
#include <util/delay.h>//it has delay function
#define DHT11_PIN 4
//#include <avr/io.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include "lcd.h"
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void Request()				/* Microcontroller send start pulse/request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(20);			/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);	/* set to high pin */
}

void Response()				/* receive response from DHT11 */
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data()			/* receive data */
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
	//lcdinit();			/* Initialize LCD */
	//lcd_clear();			/* Clear LCD */
	//lcd_gotoxy(0,0);		/* Enter column and row position */
	UART_VidSendString("Humidity =");
	//lcd_gotoxy(0,1);
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
			//lcd_gotoxy(0,0);
			UART_VidSendString("Error");
		}
		
		else
		{	
			itoa(I_RH,data,10);
			//lcd_gotoxy(11,0);
			UART_VidSendString(data);
			UART_VidSendString(".");
			
			itoa(D_RH,data,10);
			UART_VidSendString(data);
			UART_VidSendString("%");

			itoa(I_Temp,data,10);
			//lcd_gotoxy(6,1);
			UART_VidSendString(data);
			UART_VidSendString(".");
			
			itoa(D_Temp,data,10);
			UART_VidSendString(data);
			//lcddata(0xDF);
			UART_VidSendString("C ");
			
			itoa(CheckSum,data,10);
			UART_VidSendString(data);
			UART_VidSendString(" ");
		}
				
	_delay_ms(10);
	
}