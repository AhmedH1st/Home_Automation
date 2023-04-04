#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "Mcu_HW.h"
#include "Ex_interface.h"
#include "Ex_cfg.h"
#include "Ex_types.h"
#include "LED_interface.h"
#include "avr/interrupt.h"




 void (*PISR_Arr_To_Functions [NO_OF_FUNCTIONS])(void)={0};



void M_EXTInerrupt_void_Enable (Inter_ID_t InT, Inter_Sense_Control_t sense)
{
		switch (InT)
		{
			case INT_0:
				SET_BIT(GICR,INT0);
				MCUCR=MCUCR&(0xfc);
				MCUCR=MCUCR|(sense);
				break;

			case INT_1:
				SET_BIT(GICR,INT1);
				MCUCR=MCUCR&(0xf3);
				MCUCR=MCUCR|(sense<<2);
				break;

			case INT_2:
				SET_BIT(GICR,INT2);
				CLR_BIT(MCUCSR,ISC2);
				MCUCSR=MCUCSR|((sense&1)<<6);
				break;
		}
}



void M_EXTInerrupt_void_Diable (Inter_ID_t InT)
{
	switch(InT)
	{
	case INT_0:
		CLR_BIT(GICR,INT0);
		break;
	case INT_1:
		CLR_BIT(GICR,INT1);
		break;
	case INT_2:
		CLR_BIT(GICR,INT2);
		break;
	}
}

void M_EXTInerrupt_void_Trigger (Inter_ID_t InT, Inter_Sense_Control_t sense)
{
	switch(InT)
	{
	case INT_0:
		MCUCR=MCUCR&(0xfc);
		MCUCR=MCUCR|(sense);
		break;
	case INT_1:
		MCUCR=MCUCR&(0xf3);
		MCUCR=MCUCR|(sense<<2);
		break;
	case INT_2:
		CLR_BIT(MCUCSR,ISC2);
		MCUCSR=MCUCSR|((sense&1)<<6);
		break;
	}
}

void M_EXTInerrupt_void_SetCallBack (Inter_ID_t InT,  void(*pf)(void))
{

switch(InT)
{
case INT_0:
	PISR_Arr_To_Functions[0]=pf;
	break;
case INT_1:
	PISR_Arr_To_Functions[1]=pf;
	break;
case INT_2:
	PISR_Arr_To_Functions[2]=pf;
	break;
}
}



ISR(INT0_vect)
{
	if(PISR_Arr_To_Functions[0]!=0)
	PISR_Arr_To_Functions[0]();
}


ISR(INT1_vect)
{
	PISR_Arr_To_Functions[1]();
}

ISR(INT2_vect)
{
	PISR_Arr_To_Functions[2]();
}
