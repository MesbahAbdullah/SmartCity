/*********************************************************/
/* Author      : Mosbah Abdallah                         */
/* Date        : 23 JAN 2021                             */
/* Version     : V01                                     */
/*********************************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H


#define HIGH    1
#define LOW     0

#define GPIO_PORTA   0
#define GPIO_PORTB   1
#define GPIO_PORTC   2
#define GPIO_PORTD   3


#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7
#define PIN8    8
#define PIN9    9
#define PIN10    10
#define PIN11    11
#define PIN12    12
#define PIN13    13
#define PIN14    14
#define PIN15    15

#define INPUT    0
#define OUTPUT   1


void GPIO_VidSetPinDirection  ( u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8DIR   );
void GPIO_VidSetPinValue      ( u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value );
void GPIO_VidSetPullUps       ( u8 Copy_u8Port , u8 Copy_u8Pin                   );
u8   GPIO_u8GetPinValue       ( u8 Copy_u8Port , u8 Copy_u8Pin                   );


#endif /*GPIO_INTERFACE_H*/