/******************************************************************************
 * helpful rescources : Mohamed Tarek
 *******************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include <avr/io.h>

void ADC_VidInit(void)
{
    ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}

u16 ADC_u16ReadChannel(u8 channel_num)
{
	// select the corresponding channel 0~7	
	channel_num &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|channel_num;
	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);
	// wait for conversion to complete
	// ADSC becomes '0' again	
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}
