/*********************************************************/
/* Date        : 28 JAN 2021                             */
/* Version     : V01                                     */
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ESP_interface.h"
#include "UART_interface.h"
#include "GPIO_interface.h"
#include <util/delay.h>


u8 volatile DataCome[200] ;


void ESP8266_VidInit()
{
    u8 Local_u8Result=0;    
    while (Local_u8Result==0)
    {
        UART_VidSendString((u8*)"ATE0\r\n");
        Local_u8Result=ESP8266_u8ValidateCmd();
    }


    Local_u8Result=0;
    while (Local_u8Result==0)
    {
        UART_VidSendString((u8 *)"AT+CWMODE=3\r\n");
        Local_u8Result=ESP8266_u8ValidateCmd();
    }

    Local_u8Result=0;
    while (Local_u8Result==0)
    {
        UART_VidSendString((u8 *)"AT+CIPMODE=0\r\n");
        Local_u8Result=ESP8266_u8ValidateCmd();
    }
}

u8 ESP8266_u8ValidateCmd()
{
    u8 Local_u8Response[100]={0};    
    u8 Counter=0;
    u8 TrueFlag=0;

    while (Local_u8Response[Counter-1] != '\n' )
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



void ESP8266_VidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port )
{
	UART_VidSendString( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
	UART_VidSendString( (u8 *) Copy_u8Domain );
	UART_VidSendString( (u8 *) "\"," );
	UART_VidSendString( (u8 *) Copy_u8Port );
	UART_VidSendString( (u8 *) "\r\n" );
	_delay_ms( 2000 );
}

void ESP8266_VidSendHttpReq( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length )
{
	UART_VidSendString( (u8 *) "AT+CIPSEND=" );
	UART_VidSendString( (u8 *) Copy_u8Length );
	UART_VidSendString( (u8 *) "\r\n" );
	_delay_ms( 4000 );	

	UART_VidSendString( (u8 *) "GET /update?api_key=" );
	UART_VidSendString( (u8 *) Copy_u8Key );
	UART_VidSendString( (u8 *) "&field1=" );
	UART_VidSendString( (u8 *) Copy_u8Data );
	UART_VidSendString( (u8 *) "\r\n" );
	_delay_ms( 20000 );

}

u8   ESP8266_u8ReceiveHttpReq( u8 * Copy_u8ChannelID , u8 * Copy_u8Length )
{
	UART_VidSendString( (u8 *) "AT+CIPSEND=" );
	UART_VidSendString( (u8 *) Copy_u8Length );
	UART_VidSendString( (u8 *) "\r\n" );
	_delay_ms( 4000 );

	

	UART_VidSendString( (u8 *) "GET http://" );
	UART_VidSendString( (u8 *) Copy_u8ChannelID );
	UART_VidSendString( (u8 *) "/value.txt\r\n" );
	_delay_ms( 20000 );

	ESP8266_VidConnectToSrvTcp( (u8 *)"162.253.155.226" , (u8 *)"80" );

	return  DataCome[82] ;
}

