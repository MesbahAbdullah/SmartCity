/*********************************************************/
/* Author      : Mosbah Abdallah                         */
/* Date        : 15 JUL 2021                             */
/* Version     : V01                                     */
/*********************************************************/
#include "BIT_MATH.h"

#include "WDT_config.h"
#include "WDT_interface.h"
#include <avr/io.h>


void WDT_VidON(void)
{
	#if    WDT_TIME == 2
	SET_BIT(WDTCR,WDE );
	SET_BIT(WDTCR,WDP2);
	SET_BIT(WDTCR,WDP1);
	SET_BIT(WDTCR,WDP0);

	#elif  WDT_TIME == 1
	SET_BIT(WDTCR,WDE );
	SET_BIT(WDTCR,WDP2);
	SET_BIT(WDTCR,WDP1);
	CLR_BIT(WDTCR,WDP0);	

	#elif  WDT_TIME == 52
	SET_BIT(WDTCR,WDE );
	SET_BIT(WDTCR,WDP2);
	CLR_BIT(WDTCR,WDP1);
	SET_BIT(WDTCR,WDP0);	

	#elif  WDT_TIME == 26
	SET_BIT(WDTCR,WDE );
	SET_BIT(WDTCR,WDP2);
	CLR_BIT(WDTCR,WDP1);
	CLR_BIT(WDTCR,WDP0);	

	#elif  WDT_TIME == 13
	SET_BIT(WDTCR,WDE );
	CLR_BIT(WDTCR,WDP2);
	SET_BIT(WDTCR,WDP1);
	SET_BIT(WDTCR,WDP0);	

	#elif  WDT_TIME == 65
	SET_BIT(WDTCR,WDE );
	CLR_BIT(WDTCR,WDP2);
	SET_BIT(WDTCR,WDP1);
	CLR_BIT(WDTCR,WDP0);

	#elif  WDT_TIME == 32
	SET_BIT(WDTCR,WDE );
	CLR_BIT(WDTCR,WDP2);
	CLR_BIT(WDTCR,WDP1);
	SET_BIT(WDTCR,WDP0);	

	#elif  WDT_TIME == 16
	SET_BIT(WDTCR,WDE );
	CLR_BIT(WDTCR,WDP2);
	CLR_BIT(WDTCR,WDP1);
	CLR_BIT(WDTCR,WDP0);
	#endif
	 
}


void WDT_VidOFF(void)
{
	WDTCR = (1<<WDTOE)|(1<<WDE);
	WDTCR = 0x00;
}
