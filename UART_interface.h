/*********************************************************/
/* Author      : Mosbah Abdallah                         */
/* Date        : 25 JAN 2021                             */
/* Version     : V01                                     */
/*********************************************************/
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H


#define USART_BAUDRATE 115200









void UART_VidInt();
void UART_VidSentByte(u8 Copy_u8Data);
u8   UART_VidReceveByte();
void UART_VidSendString( u8 * Copy_ptrString );
u8* UART_u8ReceveString();


#endif // !UART_INTERFACE_H
