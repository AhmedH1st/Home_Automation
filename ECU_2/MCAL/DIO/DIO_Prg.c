#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "DIO_types.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"

void M_DIO_void_setPinValue (Dio_Pin_Type Pin_ID,Dio_LevelType level)
{
		u8 Pin_OrderinPort;
		Dio_PortType Port_No;

		Pin_OrderinPort=Pin_ID%10;
		Port_No=Pin_ID/10;

		switch(level)
		{

		case DIO_LOW:
			switch (Port_No)
			{
			case DIO_PORTA:
				CLR_BIT(PORTA_REG,Pin_OrderinPort);
				break;
			case DIO_PORTB:
				CLR_BIT(PORTB_REG,Pin_OrderinPort);
				break;
			case DIO_PORTC:
				CLR_BIT(PORTC_REG,Pin_OrderinPort);
				break;
			case DIO_PORTD:
				CLR_BIT(PORTD_REG,Pin_OrderinPort);
				break;
			}
			break;
			case DIO_HIGH:
				switch (Port_No)
				{
				case DIO_PORTA:
					SET_BIT(PORTA_REG,Pin_OrderinPort);
					break;
				case DIO_PORTB:
					SET_BIT(PORTB_REG,Pin_OrderinPort);
					break;
				case DIO_PORTC:
					SET_BIT(PORTC_REG,Pin_OrderinPort);
					break;
				case DIO_PORTD:
					SET_BIT(PORTD_REG,Pin_OrderinPort);
					break;
				}
				break;
		}
}


Dio_LevelType M_DIO_getPinValue (Dio_Pin_Type pin_ID)
{

	u8 Pin_OrderinPort;
	Dio_PortType Port_No;
	Dio_LevelType Bit_Val;

	Pin_OrderinPort=pin_ID%10;
	Port_No=pin_ID/10;

	switch (Port_No) {
		case DIO_PORTA:Bit_Val=GET_BIT(PINA_REG,Pin_OrderinPort);break;
		case DIO_PORTB:Bit_Val=GET_BIT(PINB_REG,Pin_OrderinPort);break;
		case DIO_PORTC:Bit_Val=GET_BIT(PINC_REG,Pin_OrderinPort);break;
		case DIO_PORTD:Bit_Val=GET_BIT(PIND_REG,Pin_OrderinPort);break;
	}
	return Bit_Val;

}


void M_DIO_TogglePin (Dio_Pin_Type pin_ID)
{
	u8 Pin_OrderinPort;
	Dio_PortType Port_No;

	Pin_OrderinPort=pin_ID%10;
	Port_No=pin_ID/10;

	switch (Port_No) {
			case DIO_PORTA:TOG_BIT(PORTA_REG,Pin_OrderinPort);break;
			case DIO_PORTB:TOG_BIT(PORTB_REG,Pin_OrderinPort);break;
			case DIO_PORTC:TOG_BIT(PORTC_REG,Pin_OrderinPort);break;
			case DIO_PORTD:TOG_BIT(PORTD_REG,Pin_OrderinPort);break;
		}
}


void M_Dio_void_setPortValue (Dio_PortType port,Dio_PortLevelType level)
{
	switch(port)
	{
		case DIO_PORTA: PORTA_REG=level;break;
		case DIO_PORTB: PORTB_REG=level;break;
		case DIO_PORTC: PORTC_REG=level;break;
		case DIO_PORTD: PORTD_REG=level;break;
	}
}

Dio_PortLevelType M_Dio_void_getPort (Dio_PortType port)
{
	Dio_PortLevelType val;
	switch(port)
	{
		case DIO_PORTA: val=PINA_REG;break;
		case DIO_PORTB: val=PINB_REG;break;
		case DIO_PORTC: val=PINC_REG;break;
		case DIO_PORTD: val=PIND_REG;break;
	}

	return val;
}





