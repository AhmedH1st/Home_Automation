#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "UART_interface.h"
#include "UART_services.h"
#include "WIFI_interface.h"
#include "Call_Back_functions.h"
#include "util/delay.h"
#include <stdio.h>

/*******************TO BE REALLOCATE IN ANOTHER FILE*********************/



void WIFI_Init (void)
{
	UART_SendString_Synch("AT\r\n");

	while(Rec_Com_flag == 0);

	Rec_Com_flag=0;
	_delay_ms(250);

	UART_SendString_Synch("ATE0\r\n");

	while(Rec_Com_flag == 0);

	Rec_Com_flag=0;
	_delay_ms(250);

	UART_SendString_Synch("AT+GMR\r\n");

	while(Rec_Com_flag == 0);

	Rec_Com_flag=0;
	_delay_ms(350);

	UART_SendString_Synch("AT+CWMODE=3\r\n");

	while(Rec_Com_flag == 0);

	Rec_Com_flag=0;
	_delay_ms(800);


	UART_SendString_Synch("AT+CWJAP=");            //here
	UART_SendString_Synch(IP);
	UART_SendString_Synch(",");
	UART_SendString_Synch(Pass);
	UART_SendString_Synch("\r\n");

	while(Rec_Com_flag == 0);

	Rec_Com_flag=0;
	_delay_ms(800);

	UART_SendString_Synch("AT+CIFSR\r\n");

	while(Rec_Com_flag == 0);

	Rec_Com_flag=0;
	_delay_ms(800);

	UART_SendString_Synch("AT+CIPSTATUS\r\n");

	while(Rec_Com_flag == 0);

	Rec_Com_flag=0;
	_delay_ms(800);


	UART_SendString_Synch("AT+CIPSTART=");
	UART_SendString_Synch("\"TCP\"");
	UART_SendString_Synch(",");
	UART_SendString_Synch(SERVER_IP);
	UART_SendString_Synch(",");
	UART_SendString_Synch(SERVER_PORT);
	UART_SendString_Synch("\r\n");


	while(Rec_Com_flag == 0);

	Rec_Com_flag=0;
	_delay_ms(2000);
	Rec_Com_flag=2;
	_delay_ms(2000);
	H_LCD_ClearDisplay();

	H_LCD_Writestr("You Ready To Go!");
	_delay_ms(3000);
	H_LCD_ClearDisplay();

}

void Wifi_SendData (u8 Data)
{
	u8 firstDig;
	u8 secDig;
	u8 str [30]={"Temp="};

	firstDig=(Data%10) + '0';
	secDig=(Data/10) + '0';

	str[5]=secDig;
	str[6]=firstDig;
	str[7]=' ';
	str[8]='C';
	str[9]=0;

	UART_SendString_Synch("AT+CIPSEND=9\r\n");
	_delay_ms(500);

	UART_SendString_Synch(str);
	_delay_ms(300);

}







