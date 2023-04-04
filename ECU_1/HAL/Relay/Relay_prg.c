#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "Relay_interface.h"










void Relay_On (void)
{
	M_DIO_void_setPinValue(RELAY,DIO_HIGH);
}




void Relay_Off (void)
{
	M_DIO_void_setPinValue(RELAY,DIO_LOW);
}
