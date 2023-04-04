#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"
#include "PowerSaving_interface.h"






void SleepMode_Enable (void)
{
#if PW_SAVE_MODE == POWER_DOWN

	MCUCR &= 0x8F;
	MCUCR |= 0xA0;

	asm volatile("sleep");

	//SET_BIT(MCUCR,SE);

#elif 	PW_SAVE_MODE == IDLE


#endif

}


void SleepMode_Disable (void)
{
	CLR_BIT(MCUCR,SE);
}
