#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"
#include "Timer2_interface.h"
#include "Timer2_private.h"
#include "avr/interrupt.h"



void M_void_Timer2_Init(void)
{
	/**initialize to work as non inverting .. fast pwm mode .. 256 prescaler***/

	TCCR2=0x6E;

}

void M_void_Timer2_FastPWM_OCR_Direct_input(u8 OCR_value)
{
	OCR2=OCR_value;
}
