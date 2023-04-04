#include "STD_TYPES.h"
#include <util/delay.h>
#include "PORT_Interface.h"
#include "DIO_Interface.h"
#include "I2C_interface.h"
#include "UART_interface.h"
#include "UART_services.h"
#include "Call_Back_functions.h"
#include "LCD_interface.h"
#include "EEPROM_interface.h"
#include "LED_interface.h"
#include "Relay_interface.h"
#include "Buzzer_interface.h"
#include "Keypad_interface.h"
#include "RTC_interface.h"
#include "ECU1App_interface.h"





int main (){

	u8 FirstConfigFlag;


	ECU1_Init();

	/*Port_Init(PORT_Config_Arr);
	H_LCD_Init();
	EEPROM_Init();*/

	//EEPROM_WriteByte(0,FIRST_CFG_FLAG_ADDRESS);
	//RTC_Set_Time(10, 40, 00, RTC_AM);


	EEPROM_ReadByte(&FirstConfigFlag, FIRST_CFG_FLAG_ADDRESS);

	if (FirstConfigFlag == 0)
	{
		ECU1_Intro();
		EUC1_FirstConfig();
	}
	else
	{
	}




	while (1)
	{
		ECU1_Runnable();
	}
}
