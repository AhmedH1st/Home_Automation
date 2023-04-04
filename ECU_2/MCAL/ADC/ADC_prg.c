#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"
#include "ADC_interface.h"
#include "ADC_types.h"
#include "ADC_cfg.h"
#include "ADC_private.h"
#include "avr/delay.h"
#include "avr/interrupt.h"


static void (*P_CallBackFunc)(void)=NULL;
static u8 flag=0;           //flag to ensure no calling of function stop the other

void M_ADC_void_Init (void)
{
	/*******cfg Refernce Voltage*******/

	ADMUX=ADMUX&(0x3f);
	ADMUX=ADMUX|(ADC_configurion.ADC_REF_VOL<<6);

	/*******cfg Prescaler Mode*******/

	ADCSRA=ADCSRA&(0xf8);
	ADCSRA=ADCSRA|(ADC_configurion.mode);

	/*******SET or CLEAR to cfg Right data storage or left*******/
	ADMUX=ADMUX&(0xdf);
	ADMUX=ADMUX|(ADC_configurion.adjust<<5);

	/*******Turn On or OFF ADC Auto Trigger  //disable-->0 to turn off ^^ enable-->1 TO turn ON *******/
	ADCSRA=ADCSRA&(0xdf);
	ADCSRA=ADCSRA|(ADC_configurion.trigger_mode<<5);

	/*******Turn On ADC*******/
	SET_BIT(ADCSRA,ADEN);
}





u16 M_ADC_GetRead (ADC_Channel_ID_t ch)
{
	u16 reading=0;

	ADMUX=ADMUX&(0xe0);
	ADMUX=ADMUX | (ch);


	SET_BIT(ADCSRA,ADSC);

	while (GET_BIT(ADCSRA,ADSC) == 1 );
	//_delay_ms(1);

	reading=ADCL;
	reading=((u32)ADCH<<8)|reading;

	return reading;
}


void M_ADC_getDigitalValueAsynchCallBack(ADC_Channel_ID_t ch, void (*P_localToFunc)(void))
{
	if (flag==0)
	{
		SET_BIT(ADCSRA,ADIE);    //Enabling Interrupt
		ADMUX=ADMUX&(0xe0);
		ADMUX=ADMUX | (ch);
		P_CallBackFunc=P_localToFunc;
		SET_BIT(ADCSRA,ADSC);
		flag=1;
	}
}


ISR(ADC_vect)
{
	if (P_CallBackFunc!=NULL)
	{
		flag=0;
		P_CallBackFunc();

	}
}







