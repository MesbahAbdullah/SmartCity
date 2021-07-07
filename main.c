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
//#include "lcd.h"
//#include "ADC_interface.h"
#include <util/delay.h>//it has delay function
#define GAS_PIN                   0
#define TEMP_PIN                  1
u16 adc_result0;
s16 temp;
s16 far;
u8 buffer[10];

/*This function is to read an analogue value from temp sensor lm-35 and send the data using uart */
// void TEMP_VidReadValue()
// {


// 		adc_result0 = ADC_u16ReadChannel(TEMP_PIN);      // read adc value 
		
// 		temp=adc_result0/2.01;   // finding the temperature
// 		lcd_gotoxy(0,0);
// 		itoa(temp,buffer,10);
// 		lcd_puts("Temp=");   //display temperature
// 		lcd_puts(buffer);
// 		lcd_gotoxy(7,0);
// 		lcd_puts("C"); 		
// 		_delay_ms(1000);

// }
// u8 *x;
        /*This function is to read an analogue value from gas sensor MQ-135 and send the data using uart */
void GAS_VidReadValue()
{
   u16 adc_result1=0;
   s16 temp=0;
   adc_result0 = ADC_u16ReadChannel(GAS_PIN);
}
int main(void)
{

	//lcd_init(LCD_DISP_ON_CURSOR); //CURSOR
	// LCD_GOTO(0,0);
	// LCD_WRITESTRING((u8 *)"LCD Initialized");
	// _delay_ms(1000);
	UART_VidInt();
	// LCD_CLear();
	// LCD_GOTO(0,0);
	// LCD_WRITESTRING((u8 *)"UART Initialized");
	//ADC_VidInit();
	// LCD_CLear();
	// LCD_GOTO(0,0);
	// LCD_WRITESTRING((u8 *)"ADC Initialized");
	// _delay_ms(1000);
	// LCD_CLear();
	// LCD_GOTO(0,0);
	
	// _delay_ms(1000);
    //lcd_init(LCD_DISP_ON_CURSOR); //CURSOR
	
		 
    UART_VidSendString((u8*)"HI HOW ARE U ");
	//ESP8266_VidInit();
	
	// LCD_WRITESTRING((u8 *)"ESP Initialized");
	// _delay_ms(2000);

    _delay_ms(4000);
	//ESP8266_VidConnectToWiFi((u8 *)"Not-For-U" , (u8 *)"1qaz2wsx3edc!@#");
	//LCD_GOTO(1,0);
	//LCD_WRITESTRING((u8 *)"WIFI Connected");



   
    GPIO_VidSetPinDirection(GPIO_PORTC,PIN7,OUTPUT);
	GPIO_VidSetPinValue(GPIO_PORTC,PIN7,HIGH);


    while (1) 
    {
	  DHT11_VidStart();
      //TEMP_VidReadValue_VidReadValue() ;
	//   UART_VidSendString((u8*)"HI HOW ARE U \n");
	//   UART_VidSendString((u8*)"\n");      
	//   UART_VidSendString((u8*)"temp is  ");
	//   UART_VidSendString((u8*)buffer);
	  //GPIO_VidSetPinValue(GPIO_PORTC,PIN7,LOW);
	  _delay_ms(2000); //to call the DHT11_VidStart() again  
	  //UART_VidSendString((u8* )"is  it working ");
    }
}

