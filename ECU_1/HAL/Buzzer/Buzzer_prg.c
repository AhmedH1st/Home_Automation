#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "Buzzer_interface.h"







void Buzzer_On (void)
{
	M_DIO_void_setPinValue(BUZZER,DIO_HIGH);
}



void Buzzer_Off (void)
{
	M_DIO_void_setPinValue(BUZZER,DIO_LOW);
}
