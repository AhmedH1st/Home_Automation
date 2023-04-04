#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "LDR_interface.h"











u16 LDR_GetRead (void)
{
	u16 LDR_read;

	LDR_read=M_ADC_GetRead(LDR_CH);

	return LDR_read;
}

