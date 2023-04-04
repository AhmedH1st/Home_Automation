#include "STD_TYPES.h"
#include <util/delay.h>
#include "PORT_Interface.h"
#include "DIO_Interface.h"
#include "ADC_interface.h"
#include "GI.h"
#include "Ex_interface.h"
#include "Timer0_interface.h"
#include "Timer1_interface.h"
#include "Timer2_interface.h"
#include "UART_interface.h"
#include "LCD_interface.h"
#include "RGB_interface.h"
#include "DC_Motor.h"
#include "Lm35_interface.h"
#include "UART_services.h"
#include "PowerSaving_interface.h"
#include "WIFI_interface.h"
#include "LDR_interface.h"
#include "Call_Back_functions.h"
#include "ECU2App_interface.h"
#include "ECU2App_private.h"


const u8 WIFI_ACTIVITIES [HOME_NO_OF_FUNCTIONS][15] = {{"start fan"},{"stop fan"},{"fan high"},{"fan low"},{"red"},{"blue"},{"yellow"},{"white"},{"light off"},
														{"read temp"},{"logout"}};

void (*PTOWIFIFUNCTIONS[HOME_NO_OF_FUNCTIONS])(void)={Start_Fan,Stop_Fan,Fan_High,Fan_Low,RGB_Red,RGB_Blue,RGB_Yellow,RGB_White,RGB_Off,Temp_Read,LogOut};


volatile u8 FunctionToDoIndex;

static u8 shift=0;

volatile u8 Last_Fan_Speed=30;

volatile u8 LAST_SET_RED;
volatile u8 LAST_SET_GREEN;
volatile u8 LAST_SET_BLUE;

volatile u8 Logout_Flag;
volatile u8 Read_Temp_flag;
volatile u16 Temp_read;


void ECU2_Init (void)
{
	Port_Init(PORT_Config_Arr);
	H_LCD_Init();
	M_void_UART_Init();
	GI_Enable();

	M_EXTInerrupt_void_SetCallBack(INT_0,EXT_INT1_FUNC);
	//M_EXTInerrupt_void_SetCallBack(INT_2,EXT_INT1_FUNC);
	M_EXTInerrupt_void_Enable(INT_0, FALLING_EDGE);              //TEST
	//M_EXTInerrupt_void_Enable(INT_2,FALLING_EDGE);              //TEST



	M_void_UART_Receive_Complete_INT_Enable();
	M_void_UART_Receive_INT_SetCallBack(UART_Receive_Wifi);

	WIFI_Init();

	M_void_Timer0_Init();
	M_void_Timer0_Start(PRESCALER_256);
	M_void_Timer1_Init();
	M_void_Timer2_Init();

	M_ADC_void_Init();
}

void First_Home_Step (void)
{
	H_void_Set_RGB_Color(WHITE);
	H_void_Motor_Stop();
	H_LCD_ClearDisplay();
	H_LCD_Writestr("Welcome Home Boss");
	_delay_ms(5000);
}

void ECU2_Runnable (void)
{
	u8 i;

	Logout_Flag = 0;

	while (1)
	{
		if (Rec_Com_flag == 3)
		{
			H_LCD_ClearDisplay();
			if (String_Compare() == SIMILAR)
			{
				PTOWIFIFUNCTIONS[FunctionToDoIndex]();

				for (i=0; i<40; i++)
				{
					if (UART_RECIEVED_STR[i] != 0 && i>shift)
					{
						if (FunctionToDoIndex != READ_TEMP_FUNC_INDEX)
						{
							H_LCD_WriteChar(UART_RECIEVED_STR[i]);
						}
						//UART_RECIEVED_STR[i]=0;
					}
					UART_RECIEVED_STR[i]=0;
				}
			}
			else
			{
				H_LCD_Writestr("Wrong Instruction!");
				for (i=0; i<20; i++)
				{
					UART_RECIEVED_STR[i]=0;
				}
			}
			Rec_Com_flag=2;
		}

		Set_RGBLuminaire();


		if (Logout_Flag == 1)
		{
			_delay_ms(2000);
			H_LCD_ClearDisplay();
			H_LCD_Writestr("BYE BYE ^_^");
			Stop_Fan();
			RGB_Off();
			_delay_ms(5000);
			H_LCD_ClearDisplay();
			break;
		}

		if (Read_Temp_flag == 1)
		{
			H_LCD_Writestr("Temp is: ");
			H_LCD_WriteNum((u32)Temp_read);
			H_LCD_WriteChar('C');
			Read_Temp_flag=0;
		}
	}
}



String_cmp_t String_Compare (void)
{
	u8 i;

	String_cmp_t cmp_res;

	for (i=0; UART_RECIEVED_STR[i] != ':'; i++);

	shift=i;

	for (u8 Function_no=0; Function_no<HOME_NO_OF_FUNCTIONS; Function_no++)
	{
		 cmp_res=SIMILAR;
		for (i=0; UART_RECIEVED_STR[i+shift+1] || WIFI_ACTIVITIES[Function_no][i] ; i++)
		{
			if (UART_RECIEVED_STR[i+shift+1] != WIFI_ACTIVITIES[Function_no][i])
			{
				cmp_res=NO_SIMILAR;
				break;
			}
		}
		if (cmp_res==SIMILAR)
		{
			FunctionToDoIndex=Function_no;
			break;
		}
	}

	return cmp_res;
}

void Start_Fan (void)
{
	H_void_Motor_SetSpeed(Last_Fan_Speed);
}
void Stop_Fan (void)
{
	H_void_Motor_Stop();
}
void Fan_High (void)
{
	H_void_Motor_SetSpeed(70);
	Last_Fan_Speed=70;
}
void Fan_Low (void)
{
	H_void_Motor_SetSpeed(30);
	Last_Fan_Speed=30;
}
void RGB_Red (void)
{
	LAST_SET_RED=255;
	LAST_SET_GREEN=0;
	LAST_SET_BLUE=0;
	H_void_Set_RGB_Color(RED);
}
void RGB_Blue (void)
{
	LAST_SET_RED=0;
	LAST_SET_GREEN=0;
	LAST_SET_BLUE=255;
	H_void_Set_RGB_Color(BLUE);
}
void RGB_Yellow (void)
{
	LAST_SET_RED=255;
	LAST_SET_GREEN=255;
	LAST_SET_BLUE=0;
	H_void_Set_RGB_Color(YELLOW);
}
void RGB_White (void)
{
	LAST_SET_RED=255;
	LAST_SET_GREEN=255;
	LAST_SET_BLUE=255;
	H_void_Set_RGB_Color(WHITE);
}
void RGB_Off (void)
{
	LAST_SET_RED=0;
	LAST_SET_GREEN=0;
	LAST_SET_BLUE=0;
	H_void_Set_RGB_Values(NULL, NULL, NULL);
}

void Temp_Read (void)
{
	Read_Temp_flag=1;

	Temp_read=LM35_GetRead();
	Temp_read/=10;

	Wifi_SendData(Temp_read);
}

void LogOut (void)
{
	Logout_Flag = 1;

	M_DIO_void_setPinValue(MCU2_Signal_To_MCU1,DIO_LOW);
	_delay_ms(2500);
	M_DIO_void_setPinValue(MCU2_Signal_To_MCU1,DIO_HIGH);
}






void Set_RGBLuminaire (void)
{
	u16 Lux_reading;



	u8 local_red;
	u8 local_green;
	u8 local_blue;

	Lux_reading=LDR_GetRead();

	if (Lux_reading>=900)
	{
		if (LAST_SET_RED == NULL)
		{
			local_red=NULL;
		}
		else
		{
			local_red=LAST_SET_RED;
		}
		if (LAST_SET_GREEN == NULL)
		{
			local_green=NULL;
		}
		else
		{
			local_green=LAST_SET_GREEN;
		}
		if (LAST_SET_BLUE == NULL)
		{
			local_blue=NULL;
		}
		else
		{
			local_blue=LAST_SET_BLUE;
		}
	}
	else if (Lux_reading>=600 && Lux_reading<900)
	{
		if (LAST_SET_RED == NULL)
		{
			local_red=NULL;
		}
		else
		{
			local_red=LAST_SET_RED-RGB_EVINING;
		}
		if (LAST_SET_GREEN == NULL)
		{
			local_green=NULL;
		}
		else
		{
			local_green=LAST_SET_GREEN-RGB_EVINING;
		}
		if (LAST_SET_BLUE == NULL)
		{
			local_blue=NULL;
		}
		else
		{
			local_blue=LAST_SET_BLUE-RGB_EVINING;
		}
	}
	else if (Lux_reading>=300 && Lux_reading<600)
	{
		if (LAST_SET_RED == NULL)
		{
			local_red=NULL;
		}
		else
		{
			local_red=LAST_SET_RED-RGB_AFTERNOON;
		}
		if (LAST_SET_GREEN == NULL)
		{
			local_green=NULL;
		}
		else
		{
			local_green=LAST_SET_GREEN-RGB_AFTERNOON;
		}
		if (LAST_SET_BLUE == NULL)
		{
			local_blue=NULL;
		}
		else
		{
			local_blue=LAST_SET_BLUE-RGB_AFTERNOON;
		}
	}
	else if (Lux_reading>=0 && Lux_reading<300)
	{
		if (LAST_SET_RED == NULL)
		{
			local_red=NULL;
		}
		else
		{
			local_red=LAST_SET_RED-RGB_MORNING;
		}
		if (LAST_SET_GREEN == NULL)
		{
			local_green=NULL;
		}
		else
		{
			local_green=LAST_SET_GREEN-RGB_MORNING;
		}
		if (LAST_SET_BLUE == NULL)
		{
			local_blue=NULL;
		}
		else
		{
			local_blue=LAST_SET_BLUE-RGB_MORNING;
		}

	}

	H_void_Set_RGB_Values(local_red,local_green,local_blue);
}
