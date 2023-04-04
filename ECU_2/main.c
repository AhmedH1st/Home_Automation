#include "STD_TYPES.h"
#include <util/delay.h>
#include "PORT_Interface.h"
#include "DIO_Interface.h"
#include "Timer0_interface.h"
#include "Timer1_interface.h"
#include "Timer2_interface.h"
#include "GI.h"
#include "UART_interface.h"
#include "PowerSaving_interface.h"
#include "WIFI_interface.h"
#include "LCD_interface.h"
#include "ADC_interface.h"
#include "RGB_interface.h"
#include "DC_Motor.h"
#include "LDR_interface.h"
#include "Call_Back_functions.h"
#include "ECU2App_interface.h"






int main(){


	 ECU2_Init();

	while(1)
	{

		if (EX_INTERRUPT_FLAG == 1)
		{
		EX_INTERRUPT_FLAG=0;
		//GI_Disable();
		First_Home_Step();
		ECU2_Runnable();
		//GI_Enable();
		}
	}
}
