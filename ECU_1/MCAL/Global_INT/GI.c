#include "Bit_Math.h"
#include "Mcu_HW.h"
#include "GI.h"


void GI_Enable (void)
{
	sei();
	//SET_BIT(SREG,GI);
}

void GI_Disable (void)
{
	cli();
	//CLEAR_BIT(SREG,GI);
}
