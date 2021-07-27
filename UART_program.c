/*********************************************************/
/* Author      : Mesbah Abdullah                         */
/* Date        : 25 JAN 2021                             */
/* Version     : V01                                     */
/*********************************************************/
#include <avr/io.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_private.h"
#include "UART_interface.h"
#include "GPIO_interface.h"

#define  F_CPU 16000000UL

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

u8 Copy_DataString[20] ={0};
void UART_VidInit()
{
    UCSRA = (1<<U2X);
    UCSRB = (1<<RXEN) | (1<<TXEN);
    UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
    UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;    
}

void UART_VidSentByte(u8 Copy_u8Data)
{  
   /* Put data into buffer, sends the data */
   while(BIT_IS_CLEAR(UCSRA,UDRE)){}
   UDR = Copy_u8Data;   
}
u8   UART_VidReceveByte()
{
    /* Wait for data to be received */
    while(GET_BIT(UART_UCSRA , 7) == 0);
    /* Get and return received data from buffer */
    return UDR;
}

void UART_VidSendString( u8 * Copy_ptrString ){

	u8 LOC_u8Iterator = 0 ;

	while ( Copy_ptrString[ LOC_u8Iterator ] != '\0' )
    {

		UART_VidSentByte( Copy_ptrString[ LOC_u8Iterator ] );
		LOC_u8Iterator++ ;
	}

}
u8* UART_u8ReceveString(){

	u8 LOC_u8Iterator = 0 ;

    Copy_DataString[LOC_u8Iterator] =UART_VidReceveByte();
    while ( Copy_DataString[LOC_u8Iterator] != '#' )
    {
    	LOC_u8Iterator++ ;
		Copy_DataString[ LOC_u8Iterator ] =UART_VidReceveByte();

    }    
    return Copy_DataString;
}
