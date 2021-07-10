/*********************************************************/
/* Author      : Mesbah Abdullah                         */
/* Date        : 28 JAN 2021                             */
/* Version     : V01                                     */
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ESP_interface.h"
#include "UART_interface.h"
#include "GPIO_interface.h"
#include <util/delay.h>

void ESP8266_VidInit()
{
    u8 Local_u8Result=0;    
    while (Local_u8Result==0)
    {
        /* stop ECHO*/
        UART_VidSendString((u8*)"ATE0\r\n");
        Local_u8Result=ESP8266_u8ValidateCmd();
    }


    /*set station mode*/
    Local_u8Result=0;
    while (Local_u8Result==0)
    {
        UART_VidSendString((u8 *)"AT+CWMODE=1\r\n");
        Local_u8Result=ESP8266_u8ValidateCmd();
    }

}

u8 ESP8266_u8ValidateCmd()
{
    u8 Local_u8Response[100]={0};    
    u8 Counter=0;
    u8 TrueFlag=0;

    while (Local_u8Response[Counter-1] != '\n' )/*timer*/
    {
    	Local_u8Response [Counter] = UART_VidReceveByte();
    	Counter++;
    }

    if (Local_u8Response [0] == 'O' && Local_u8Response [1] == 'K')
    	{
    	TrueFlag =1;
    	}

    	return TrueFlag;

}
void ESP8266_VidConnectToWiFi ( u8* SSID , u8* Password )
{

	UART_VidSendString((u8 *)  "AT+CWJAP=\"" );
	UART_VidSendString((u8 *)  SSID );
	UART_VidSendString((u8 *) "\",\"" );
	UART_VidSendString((u8 *)  Password);
	UART_VidSendString((u8 *) "\"\r\n");
	_delay_ms( 8000 );
}
