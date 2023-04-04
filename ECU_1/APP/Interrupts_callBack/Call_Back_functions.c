#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"
#include "DIO_Interface.h"
#include "LED_interface.h"
#include "LCD_interface.h"
#include "util/delay.h"
#include "UART_interface.h"
#include "UART_services.h"
#include "FP_interface.h"






void FB_Recieve_Trial (void)
{
	Recieving_Buffer[Recieve_Index++]=M_UART_receiveWord_ASynch();
}







