/*********************************************************/
/* Author      : Mosbah Abdallah                         */
/* Date        : 23 JAN 2021                             */
/* Version     : V01                                     */
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"


void GPIO_VidSetPinDirection( u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8DIR )
{
    switch(Copy_u8Port)
    {
    case GPIO_PORTA :
        if(Copy_u8DIR==INPUT)
             CLR_BIT(DDRA , Copy_u8Pin);
        else if (Copy_u8DIR==OUTPUT)     
            SET_BIT(DDRA,Copy_u8Pin);
        break;
    case GPIO_PORTB :
         if(Copy_u8DIR==INPUT)
             CLR_BIT(DDRB , Copy_u8Pin);
        else if (Copy_u8DIR==OUTPUT)     
            SET_BIT(DDRB,Copy_u8Pin);
        break;
    case GPIO_PORTC :
         if(Copy_u8DIR==INPUT)
             CLR_BIT(DDRC , Copy_u8Pin);
        else if (Copy_u8DIR==OUTPUT)     
            SET_BIT(DDRC,Copy_u8Pin);
        break;
    case GPIO_PORTD :
         if(Copy_u8DIR==INPUT)
             CLR_BIT(DDRD , Copy_u8Pin);
        else if (Copy_u8DIR==OUTPUT)     
            SET_BIT(DDRD,Copy_u8Pin);
        break;
    default:
        break;
    }

}

void GPIO_VidSetPinValue( u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value )
{
    switch(Copy_u8Port)
    {
    case GPIO_PORTA :
        if(Copy_u8Value==LOW)
             CLR_BIT(PORTA , Copy_u8Pin);
        else if (Copy_u8Value==HIGH)     
            SET_BIT(PORTA,Copy_u8Pin);
        break;
    case GPIO_PORTB :
         if(Copy_u8Value==LOW)
             CLR_BIT(PORTB , Copy_u8Pin);
        else if (Copy_u8Value==HIGH)     
            SET_BIT(PORTB,Copy_u8Pin);
        break;
    case GPIO_PORTC :
         if(Copy_u8Value==LOW)
             CLR_BIT(PORTC , Copy_u8Pin);
        else if (Copy_u8Value==HIGH)     
            SET_BIT(PORTC,Copy_u8Pin);
        break;
    case GPIO_PORTD :
         if(Copy_u8Value==LOW)
             CLR_BIT(PORTD , Copy_u8Pin);
        else if (Copy_u8Value==HIGH)     
            SET_BIT(PORTD,Copy_u8Pin);
        break;
    default:
        break;
    }
}
u8 GPIO_u8GetPinValue( u8 Copy_u8Port , u8 Copy_u8Pin )
{
    u8 LOC_u8Result = 0 ;
    switch(Copy_u8Port)
    {
    case GPIO_PORTA :
       LOC_u8Result= GET_BIT(PINA,Copy_u8Pin) ;
        break;
    case GPIO_PORTB :
       LOC_u8Result= GET_BIT(PINA,Copy_u8Pin) ;
        break;
    case GPIO_PORTC :
        LOC_u8Result= GET_BIT(PINA,Copy_u8Pin) ;
        break;
    case GPIO_PORTD :
        LOC_u8Result= GET_BIT(PINA,Copy_u8Pin) ;
        break;
    default:
        break;
    }
    return LOC_u8Result;
}

void GPIO_VidSetPullUps(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    switch (Copy_u8Port)
	{
		case GPIO_PORTA:
		SET_BIT(PORTA , Copy_u8Pin);
		break;
		
		case GPIO_PORTB:
		SET_BIT(PORTB , Copy_u8Pin);
		break;
		
		case GPIO_PORTC:
		SET_BIT(PORTC , Copy_u8Pin);
		break;
		
		case GPIO_PORTD:
		SET_BIT(PORTD , Copy_u8Pin);
		break;

		default:
		break;
	}
}


