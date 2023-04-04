#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "ADC_interface.h"
#include "Lm35_interface.h"


void LM35_Init (void)
{

}


u16 LM35_GetRead (void)
{
	u16 reading;

	reading=M_ADC_GetRead(Temp_ch);
	reading=(((u32)reading * 5000)/1024)+5;

	return reading;
}
