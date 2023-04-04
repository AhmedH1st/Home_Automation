#include "STD_TYPES.h"
#include <util/delay.h>
#include "PORT_Interface.h"
#include "DIO_Interface.h"
#include "I2C_interface.h"
#include "GI.h"
#include "UART_interface.h"
#include "UART_services.h"
#include "Call_Back_functions.h"
#include "Buzzer_interface.h"
#include "LCD_interface.h"
#include "EEPROM_interface.h"
#include "Keypad_interface.h"
#include "LED_interface.h"
#include "Relay_interface.h"
#include "RTC_interface.h"
#include "FP_interface.h"
#include "ECU1App_interface.h"
#include "ECU1App_private.h"


u8 Entry_Flag;




void ECU1_Intro (void)
{
	//Welcome messages & team represent
	H_LCD_ClearDisplay();
	H_LCD_Writestr("Welcome To");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
	H_LCD_Writestr("Home Automation");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_3, DIgit_1);
	H_LCD_Writestr("Project");

	_delay_ms(3000);
	H_LCD_ClearDisplay();
	H_LCD_Writestr("Developed By");
	_delay_ms(2000);
	H_LCD_ClearDisplay();
	H_LCD_Writestr("1-Ahmed Hesham");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
	H_LCD_Writestr("2-Shady Taha");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_3, DIgit_1);
	H_LCD_Writestr("3-Mohanad Rabea");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_4, DIgit_1);
	H_LCD_Writestr("4-Mahmoud Salah");
	_delay_ms(6000);
	H_LCD_ClearDisplay();

	/*********************************/
	H_LCD_Writestr("First Config Mode");
	_delay_ms(2000);
	H_LCD_ClearDisplay();
	/**********************************/
}

void ECU1_Init (void)
{
	Port_Init(PORT_Config_Arr);
	H_LCD_Init();
	EEPROM_Init();
	GI_Enable();
	M_void_UART_Receive_Complete_INT_Enable();
	M_void_UART_Receive_INT_SetCallBack(FB_Recieve_Trial);
	//M_void_UART_Init();
	FP_Init();
}

void EUC1_FirstConfig (void)
{
	EUC1_FirstConfig_PIN();
	EUC1_FirstConfig_FP();
	_delay_ms(100);
	EEPROM_WriteByte(1,FIRST_CFG_FLAG_ADDRESS);     //flag for first initialization
	_delay_ms(250);
	EEPROM_WriteByte(2,FP_LAST_PAGE_ID_ADDRESS);     //flag for first initialization

	H_LCD_ClearDisplay();
	H_LCD_Writestr("Setup Complete");
	_delay_ms(2000);
	H_LCD_ClearDisplay();
}



void ECU1_Add_FP (void)
{
	FP_Error_t Response;
	FP_PageID_t local_page_ID;


	EEPROM_ReadByte(&local_page_ID,FP_LAST_PAGE_ID_ADDRESS);

	while (1)
	{
		H_LCD_ClearDisplay();
		H_LCD_Writestr("Put Your Finger On");
		_delay_ms(5000);
		H_LCD_ClearDisplay();

		Response=FP_New_Scan(local_page_ID);

		if (Response == CMD_EXCUTION_COMPLETE)
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("F.P Added Successfully");
			_delay_ms(3000);
			H_LCD_ClearDisplay();
			break;
		}
		else
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("Fault in adding FP");
			H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
			H_LCD_Writestr("Repeat Steps Again");
			_delay_ms(3000);
		}
	}

	EEPROM_WriteByte((local_page_ID+1),FP_LAST_PAGE_ID_ADDRESS);
}


void EUC1_FirstConfig_PIN(void)
{
	u8 local_cfg_flag=0;
	u8 digits_counter=0;
	u8 PB=NO_PRESSED_KEY;
	u16 local_PIN_1=0;
	u16 local_PIN_2=0;

	while (local_cfg_flag == 0)
	{
		local_cfg_flag=0;
		digits_counter=0;
		PB=NO_PRESSED_KEY;
		local_PIN_1=0;
		local_PIN_2=0;

		H_LCD_ClearDisplay();
		H_LCD_Writestr("To setup Your PIN:");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		H_LCD_Writestr("PIN 4 chars only");            //user interface
		H_LCD_GoTOAddress_UsingLine_Col(LINE_3, DIgit_1);
		H_LCD_Writestr("PIN is Numbers only");
		_delay_ms(4000);
		H_LCD_ClearDisplay();
		H_LCD_Writestr("Please Enter PIN");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);


		while(digits_counter < PIN_DIGITS)
		{
			PB=H_KEYPAD_u8_getPressedKey();

			if (PB != NO_PRESSED_KEY)
			{
				if (PB>='0'  && PB<='9')
				{
					local_PIN_1=(local_PIN_1*10) + (PB - '0');
					H_LCD_WriteNum((local_PIN_1%10));
					digits_counter++;
				}
			}
			PB=NO_PRESSED_KEY;
		}

		H_LCD_ClearDisplay();
		H_LCD_Writestr("Please Re-Enter PIN");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);

		digits_counter=0;

		while(digits_counter < PIN_DIGITS)
		{
			PB=H_KEYPAD_u8_getPressedKey();

			if (PB != NO_PRESSED_KEY)
			{
				if (PB>='0'  && PB<='9')
				{
					local_PIN_2=(local_PIN_2*10) + (PB - '0');
					H_LCD_WriteNum((local_PIN_2%10));
					digits_counter++;
				}
			}
			PB=NO_PRESSED_KEY;
		}


		if (local_PIN_1 == local_PIN_2)
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("PIN Saved");
			H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
			H_LCD_Writestr("Successfully");
			_delay_ms(3000);
			H_LCD_ClearDisplay();

			local_cfg_flag=1;

			EEPROM_WriteByte((u8)(local_PIN_1%100),(u16) PIN_1ST_BYTE);
			_delay_ms(200);
			EEPROM_WriteByte((u8)(local_PIN_1/100),(u16) PIN_2ND_BYTE);
		}
		else
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("Wrong Matching!");
			H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
			H_LCD_Writestr("Please Follow Steps");
			H_LCD_GoTOAddress_UsingLine_Col(LINE_3, DIgit_1);
			H_LCD_Writestr("Again");
			_delay_ms(3000);
		}
	}

}

void EUC1_FirstConfig_FP (void)
{
	FP_Error_t Response;

	while (1)
	{
		H_LCD_ClearDisplay();
		H_LCD_Writestr("Finger Print Setup");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		H_LCD_Writestr("Put Your Finger On");
		_delay_ms(5000);
		H_LCD_ClearDisplay();

		Response=FP_New_Scan(FP_Page_1);

		if (Response == CMD_EXCUTION_COMPLETE)
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("F.P Setup Done");
			_delay_ms(3000);
			break;
		}
		else
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("Fault in Setup");
			H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
			H_LCD_Writestr("Repeat Steps Again");
			_delay_ms(3000);
		}
	}
}


void ECU1_StandBy(void)
{
	u8 PB=NO_PRESSED_KEY;

	while(PB == NO_PRESSED_KEY)
	{
		PB=H_KEYPAD_u8_getPressedKey();
	}
}

void ECU1_Runnable (void)
{
	ECU1_StandBy();

	ECU1_PIN_Verification();
	if (Entry_Flag != BLOCK)
	ECU1_FP_Verification();

	if (Entry_Flag == ENTER)
	{
		Entry_Flag=0;
		RTC_Init();
		ECU1_Entry();
		ECU1_InHome();
	}

	else if (Entry_Flag == BLOCK)
	{
		ECU1_Block();
	}
	else if (Entry_Flag == RESET)
	{
		ECU1_Reset_PIN();
		if (Entry_Flag == BLOCK)
		{
			ECU1_Block();
		}
	}
	else if (Entry_Flag == ADD_FP)
	{
		ECU1_Add_FP();
	}
}

void ECU1_PIN_Verification (void)
{
	ECU_PIN_t matching_status;
	u16 Entered_PIN=0;
	u8 digit_counter=0;
	u8 trial_counter=0;
	u8 PB=NO_PRESSED_KEY;

	H_LED_ON(LED_BLUE);
	H_LCD_ClearDisplay();

	EEPROM_Init();             //Test added

	while (trial_counter<MAX_NUM_FAULT_PIN)
	{
		H_LCD_Writestr("Enter PIN");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		H_LCD_Writestr("0000 to reset PIN");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_3, DIgit_1);
		H_LCD_Writestr("0001 to Add FP");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_4, DIgit_1);
		while (digit_counter < PIN_DIGITS)
		{
			PB=H_KEYPAD_u8_getPressedKey();

			if (PB != NO_PRESSED_KEY)
			{
				H_LCD_WriteChar('*');
				Entered_PIN=(Entered_PIN*10) + (PB - '0');
				digit_counter++;
			}
		}

		if (Entered_PIN == 0)
		{
			Entry_Flag=RESET;
			break;
		}
		else if (Entered_PIN == 1)
		{
			Entry_Flag=ADD_FP;
			break;
		}

		matching_status=ECU1_CheckPIN(Entered_PIN);

		if (matching_status == RIGHT_PIN)
		{
			Entry_Flag=ENTER;
			break;
		}
		else
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("Wrong Entry");
			_delay_ms(3000);
			H_LCD_ClearDisplay();
			trial_counter++;
		}
		if (trial_counter == MAX_NUM_FAULT_PIN)
		{
			Entry_Flag=BLOCK;
		}
		Entered_PIN=0;
		digit_counter=0;
	}

}


void ECU1_FP_Verification (void)
{
	FP_Error_t Response=CMD_EXCUTION_COMPLETE;

	while(1)
	{
		H_LCD_ClearDisplay();
		H_LCD_Writestr("Put Your Finger");
		_delay_ms(5000);

		Response=FP_Check();

		if (Response == CMD_EXCUTION_COMPLETE)
		{
			break;
		}
		else
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("No Match");
			_delay_ms(3000);
		}
	}

}



void ECU1_Reset_PIN (void)
{
	ECU_PIN_t matching_status;
	u16 Entered_PIN=0;
	u8 digit_counter=0;
	u8 trial_counter=0;
	u8 PB=NO_PRESSED_KEY;

	H_LCD_ClearDisplay();

	while (trial_counter<MAX_NUM_FAULT_PIN)
	{
		H_LCD_Writestr("Enter Old PIN");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		while (digit_counter < PIN_DIGITS)
		{
			PB=H_KEYPAD_u8_getPressedKey();

			if (PB != NO_PRESSED_KEY)
			{
				H_LCD_WriteChar('*');
				Entered_PIN=(Entered_PIN*10) + (PB - '0');
				digit_counter++;
			}
		}

		matching_status=ECU1_CheckPIN(Entered_PIN);

		if (matching_status == RIGHT_PIN)
		{
			break;
		}
		else
		{
			H_LCD_ClearDisplay();
			H_LCD_Writestr("Wrong Entry");
			_delay_ms(3000);
			H_LCD_ClearDisplay();
			trial_counter++;
		}
		if (trial_counter == MAX_NUM_FAULT_PIN)
		{
			Entry_Flag=BLOCK;
		}
		Entered_PIN=0;
		digit_counter=0;
	}

	if (Entry_Flag != BLOCK)
	{
		EUC1_FirstConfig();
	}
}



void ECU1_Entry (void)
{
	u8 Hours,Mins,Secs, Day,date,month,year;
	RTC_Hours_t Hours_zone;

	H_LED_Off(LED_BLUE);
	H_LED_ON(LED_GREEN);
	Relay_On();
	H_LCD_ClearDisplay();
	H_LCD_Writestr("Welcome Home Sir");
	_delay_ms(5000);
	H_LCD_ClearDisplay();
	H_LCD_Writestr("Last Login Time");

	RTC_Init();
	_delay_ms(200);
	RTC_LCD_Print();
	/*****save login time data*******   (new)
	 *
	 */
	_delay_ms(250);

	/*RTC_Get_Date(&Day, &date, &month, &year);

	_delay_ms(250);

	RTC_Get_Time(&Hours, &Mins, &Secs, &Hours_zone);

	_delay_ms(250);

	EEPROM_Init();           //SET For EEPROM I2C Setting
//Saving
	_delay_ms(250);
	EEPROM_WriteByte(Day,DAY_EEPROM_BYTE);
	_delay_ms(250);
	EEPROM_WriteByte(date,DATE_EEPROM_BYTE);
	_delay_ms(250);
	EEPROM_WriteByte(month,MONTH_EEPROM_BYTE);
	_delay_ms(250);
	EEPROM_WriteByte(year,YEAR_EEPROM_BYTE);
	_delay_ms(250);

	EEPROM_WriteByte(Secs,SEC_EEPROM_BYTE);
	_delay_ms(250);
	EEPROM_WriteByte(Mins,Mins);
	_delay_ms(250);
	EEPROM_WriteByte(Hours,HOUR_EEPROM_BYTE);
	_delay_ms(250);
	EEPROM_WriteByte(Hours_zone,HOURMODE_EEPROM_BYTE);
	_delay_ms(250);*/

	_delay_ms(9000);
	H_LCD_ClearDisplay();
	H_LED_Off(LED_GREEN);
	Relay_Off();


	M_DIO_void_setPinValue(SIGNAL_TO_MCU2_PIN,DIO_LOW);                         //send signal to wake up mcu2
	_delay_ms(1000);
	M_DIO_void_setPinValue(SIGNAL_TO_MCU2_PIN,DIO_HIGH);
}

void ECU1_Block (void)
{
	H_LED_Off(LED_BLUE);
	H_LED_ON(LED_RED);
	Buzzer_On();
	H_LCD_ClearDisplay();
	H_LCD_Writestr("ACCESS DENIED");
	for (u8 i=0; i<255; i++)
		{
			_delay_ms(5000);
		}
}

void ECU1_InHome (void)
{
	RTC_Init();       //set for RTC Setting   (new)

	while(M_DIO_getPinValue(SIGNAL_From_MCU2_PIN) == DIO_HIGH)                     //MCU2 should Make it read low to get signal that user left house
	{
		H_LCD_ClearDisplay();

		RTC_LCD_Print();
		_delay_ms(800);
	}

	H_LCD_ClearDisplay();
	H_LCD_Writestr("SEE YOU SOON SIR");
	_delay_ms(10000);
	H_LCD_ClearDisplay();

}

ECU_PIN_t ECU1_CheckPIN (u16 EnteredPin)
{
	ECU_PIN_t result;
	u16 Saved_PIN=0;
	u8 rest_of_pin=0;

	EEPROM_ReadByte(&Saved_PIN,PIN_2ND_BYTE);
	Saved_PIN*=100;
	_delay_ms(200);
	EEPROM_ReadByte(&rest_of_pin,PIN_1ST_BYTE);

	Saved_PIN+=rest_of_pin;

	if (Saved_PIN == EnteredPin)
	{
		result=RIGHT_PIN;
	}
	else
	{
		result=WRONG_PIN;
	}

	return result;
}
