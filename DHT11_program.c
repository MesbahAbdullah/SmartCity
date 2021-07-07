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

//#include <avr/io.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include "lcd.h"
#define DHT11_PIN 0
u8 c=0;
u8 I_RH=0;
u8 D_RH=0;
u8 I_Temp=0;
u8 D_Temp=0;
u8 CheckSum=0;

void Request()				/* Microcontroller send start pulse/request */
{
	DDRC |= (1<<DHT11_PIN);
	PORTC &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(20);			    /* wait for 20ms */
	PORTC |= (1<<DHT11_PIN);	/* set to high pin */
	//_delay_us(35);
}

void Response()				/* receive response from DHT11 */
{
	DDRC &= ~(1<<DHT11_PIN);
	while( PINC & (1<<DHT11_PIN    ));
	while((PINC & (1<<DHT11_PIN))==0);
	while( PINC & (1<<DHT11_PIN    ));
}

uint8_t Receive_data()			/* receive data */
{	
	for (int q=0; q<8; q++)
	{
		while((PINC & (1<<DHT11_PIN)) == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(PINC & (1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(PINC & (1<<DHT11_PIN));
	}
	return c;
}

void DHT11_VidStart(void)
{	
	char data[5]={0};
	//lcd_init(LCD_DISP_ON_CURSOR); //CURSOR
		/* Initialize LCD */
	//lcd_gotoxy(0,0);		/* Enter column and row position */
	
	//lcd_gotoxy(0,1);
	
	
    
	
		Request();		/* send start pulse */
		//UART_VidSendString((u8 *)"is it requested");
			

		Response();		/* receive response */
		//GPIO_VidSetPinValue(GPIO_PORTC,PIN7,LOW);

		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
		
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			//lcd_gotoxy(0,0);
			UART_VidSendString((u8*)"Error");
		}
		
		else
		{	
			UART_VidSendString((u8*)"Humidity =");
			itoa(I_RH,data,10);
			//lcd_gotoxy(11,0);
			UART_VidSendString((u8*)data);
			UART_VidSendString((u8*)".");
			
			itoa(D_RH,data,10);
			UART_VidSendString((u8*)data);
			UART_VidSendString((u8*)"%");

			itoa(I_Temp,data,10);
			//lcd_gotoxy(6,1);
			UART_VidSendString((u8*)"   Temp = ");
			UART_VidSendString((u8*)data);
			UART_VidSendString((u8*)".");
			
			itoa(D_Temp,data,10);
			UART_VidSendString((u8*)data);
			//lcddata(0xDF);
			UART_VidSendString((u8*)"C ");
			UART_VidSendString((u8 *)"SUM=  ");
			itoa(CheckSum,data,10);
			UART_VidSendString((u8*)data);
			UART_VidSendString((u8*)" ");
			UART_VidSendString((u8*)"\r\n");

		}
				
	_delay_ms(10);

		
}