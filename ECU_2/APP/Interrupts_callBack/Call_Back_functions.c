#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"
#include "DIO_Interface.h"
#include "Ex_interface.h"
#include "LED_interface.h"
#include "LCD_interface.h"
#include "Lm35_interface.h"
#include "util/delay.h"
#include "Timer1_interface.h"
#include "UART_interface.h"
#include "UART_services.h"


/********VARIABLES RELATED TO UART RECIEVE PROCESS PROJECTT**********/

volatile u8 UART_RECIEVED_WORD;
volatile u8 UART_RECIEVED_STR [100];
volatile u8 Rec_Com_flag=0;

/***********************************************************/

volatile u8 EX_INTERRUPT_FLAG;


void UART_ReceiveWord (void)
{
	UART_RECIEVED_WORD=M_UART_receiveWord_ASynch();
	H_LCD_WriteChar(UART_RECIEVED_WORD);
}

void UART_Receive_Wifi (void)
{

	UART_Recieve_WIFI_String_Synch_TRIAL3(UART_RECIEVED_STR);
	H_LCD_ClearDisplay();

	u8 row_digit_counter=1;

	if (Rec_Com_flag == 0)
	{
		for (u8 i=0; i<100; i++)
		{
			if (UART_RECIEVED_STR[i] !='\r'  && UART_RECIEVED_STR[i] !='\n'  && UART_RECIEVED_STR[i] != 0)
			{
				if ((i+1) % 20 == 0)
				{
					H_LCD_GoTOAddress_UsingLine_Col(++row_digit_counter, DIgit_1);
				}
				H_LCD_WriteChar(UART_RECIEVED_STR[i]);
			}
			UART_RECIEVED_STR[i]=0;
		}
		Rec_Com_flag=1;
	}

	else if (Rec_Com_flag == 2)
	{
		//H_LCD_ClearDisplay();
		Rec_Com_flag=3;
	}
}

/****************EX_INT ROUTINES************************/


// Write Down Each Scenario You waana Implement During Each Interrupt Event ** then pass these functions
//to the function EXT_Int_SetCallBack to assign each function to be applied as a result to the interrupt causing


void EXT_INT1_FUNC(void)
{
	EX_INTERRUPT_FLAG=1;
}



