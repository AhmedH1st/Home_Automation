#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "RTC_interface.h"
#include "I2C_interface.h"
#include "LCD_interface.h"
#include "util/delay.h"




void RTC_Init (void)
{
	I2C_Configuration_Bit_Rate.bit_rate=I2C_RATE_100KHZ;
	M_void_I2C_Init();
}


void RTC_Set_Date (u8 Day, u8 Date, u8 Month, u8 Year)
{
	I2C_Error_t I2C_status;

	u8 local_Date_Right_Half;
	u8 local_Date_Left_Half;
	u8 Transmitted_Date_byte=0;

	u8 local_Month_Right_Half;
	u8 local_Month_Left_Half;
	u8 Transmitted_Month_byte=0;

	u8 local_Year_Right_Half;
	u8 local_Year_Left_Half;
	u8 Transmitted_Year_byte=0;

	/******Date calc to transmit*******/

	local_Date_Right_Half=Date%10;
	local_Date_Left_Half=Date/10;

	Transmitted_Date_byte=local_Date_Right_Half | (local_Date_Left_Half<<4);

	/******Month calc to transmit*******/

	local_Month_Right_Half=Month%10;
	local_Month_Left_Half=Month/10;

	Transmitted_Month_byte=local_Month_Right_Half | (local_Month_Left_Half<<4);

	/******Year calc to transmit*******/

	local_Year_Right_Half=Year%10;
	local_Year_Left_Half=Year/10;

	Transmitted_Year_byte=local_Year_Right_Half | (local_Year_Left_Half<<4);


	/*******Start Transmitting Sequence**********/

	I2C_status=M_void_I2C_Start();                         //start condition

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(RTC_ADDRESS_WRITE);  //sending first address packet

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(DAY_REG);  //sending Day register address

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Day);         //sending Day register address

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Transmitted_Date_byte);         //sending Date register address

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Transmitted_Month_byte);         //sending Month register address

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Transmitted_Year_byte);         //sending Year register address

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	M_void_I2C_Stop();                                //Stop Connection


}



void RTC_Set_Time (u8 Hours, u8 Mins, u8 Secs, RTC_Hours_t Hours_zone)
{
	I2C_Error_t I2C_status;

	u8 local_Hours_Right_Half;
	u8 local_Hours_Left_Half;
	u8 Transmitted_Hours_byte=0;

	u8 local_Mins_Right_Half;
	u8 local_Mins_Left_Half;
	u8 Transmitted_Mins_byte=0;

	u8 local_Secs_Right_Half;
	u8 local_Secs_Left_Half;
	u8 Transmitted_Secs_byte=0;

	/******Hours calc to transmit*******/

	local_Hours_Right_Half=Hours%10;
	local_Hours_Left_Half=Hours/10;

	Transmitted_Hours_byte=local_Hours_Right_Half | (local_Hours_Left_Half<<4) | (Hours_zone<<5) | (1<<HOUR_MODEBIT);


	/******Minutes calc to transmit*******/

	local_Mins_Right_Half=Mins%10;
	local_Mins_Left_Half=Mins/10;

	Transmitted_Mins_byte=local_Mins_Right_Half | (local_Mins_Left_Half<<4);

	/******Seconds calc to transmit*******/

	local_Secs_Right_Half=Secs%10;
	local_Secs_Left_Half=Secs/10;

	Transmitted_Secs_byte=local_Secs_Right_Half | (local_Secs_Left_Half<<4);


	/*******Start Transmitting Sequence**********/

	I2C_status=M_void_I2C_Start();                         //start condition

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}


	I2C_status=M_void_I2C_SendByte(RTC_ADDRESS_WRITE);  //sending first address packet

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(SECONDS_REG);  //sending Seconds register address

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Transmitted_Secs_byte);  //sending Seconds seeting

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}


	I2C_status=M_void_I2C_SendByte(Transmitted_Mins_byte);  //sending Minutes seeting

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Transmitted_Hours_byte);  //sending Hours seeting

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}


	M_void_I2C_Stop();                                //Stop Connection

}

void RTC_Get_Time (u8* Hours, u8* Mins, u8* Secs, RTC_Hours_t* Hours_zone)
{
	I2C_Error_t I2C_status;

	u8 Recieved_Hours;
	u8 Recieved_Mins;
	u8 Recieved_Secs;


	/*********Recieve data from RTC************/

	I2C_status=M_void_I2C_Start();                         //start condition

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(RTC_ADDRESS_WRITE);  //sending first address packet

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(SECONDS_REG);  //sending Seconds register address

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_Start();                         //Reapeted start condition

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(RTC_ADDRESS_READ);  //sending first address packet

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}


	Recieved_Secs=M_void_I2C_RecieveByte_Ack();

	Recieved_Mins=M_void_I2C_RecieveByte_Ack();

	Recieved_Hours=M_void_I2C_RecieveByte_NO_Ack();

	M_void_I2C_Stop();                                //Stop Connection


	/************calc to find equivalent values of recieved data************/

	*Secs=(Recieved_Secs & 0xF) + ((Recieved_Secs>>4)*10);

	*Mins=(Recieved_Mins & 0xF) + ((Recieved_Mins>>4)*10);

	*Hours=(Recieved_Hours & 0xF) + ((GET_BIT(Recieved_Hours,4))*10);

	if ((GET_BIT(Recieved_Hours,5)) == RTC_AM)
	{
		*Hours_zone=RTC_AM;
	}

	else
	{
		*Hours_zone=RTC_PM;
	}

}

void RTC_Get_Date (u8* Day, u8* Date, u8* Month, u8* Year)
{
	I2C_Error_t I2C_status;

	u8 Recieved_Date;
	u8 Recieved_Month;
	u8 Recieved_Year;


	/*********Recieve data from RTC************/

	I2C_status=M_void_I2C_Start();                         //start condition

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(RTC_ADDRESS_WRITE);  //sending first address packet

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(DAY_REG);  //sending Day register address

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_Start();                         //Reapeted start condition

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(RTC_ADDRESS_READ);  //sending first address packet

	if (I2C_status == I2C_NOK)
	{
		//EE_state=EEPROM_NOK;
	}


	*Day=M_void_I2C_RecieveByte_Ack();

	Recieved_Date=M_void_I2C_RecieveByte_Ack();

	Recieved_Month=M_void_I2C_RecieveByte_Ack();

	Recieved_Year=M_void_I2C_RecieveByte_NO_Ack();

	M_void_I2C_Stop();                                //Stop Connection


	/************calc to find equivalent values of recieved data************/

	*Date=(Recieved_Date & 0xF)   + ((Recieved_Date>>4)*10);

	*Month=(Recieved_Month & 0xF) + ((Recieved_Month>>4)*10);

	*Year=(Recieved_Year & 0xF)   + ((Recieved_Year >>4)*10);


}





void RTC_LCD_Print (void)
{
	u8 Hours,Mins,Secs, Day,date,month,year;
	RTC_Hours_t Hours_zone;

	//H_LCD_ClearDisplay();

	H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
	RTC_Get_Date(&Day, &date, &month, &year);

	_delay_ms(200);

	RTC_Get_Time(&Hours, &Mins, &Secs, &Hours_zone);

	switch (Day)
	{
	case 1:H_LCD_Writestr("SUNDAY ");break;
	case 2:H_LCD_Writestr("MONDAY ");break;
	case 3:H_LCD_Writestr("Tuesday ");break;
	case 4:H_LCD_Writestr("Wednesday ");break;
	case 5:H_LCD_Writestr("Thursday ");break;
	case 6:H_LCD_Writestr("Friday ");break;
	case 7:H_LCD_Writestr("Saturday ");break;
	}


	H_LCD_GoTOAddress_UsingLine_Col(LINE_3, DIgit_1);

	H_LCD_WriteNum(date);
	H_LCD_WriteChar(':');
	H_LCD_WriteNum(month);
	H_LCD_WriteChar(':');
	H_LCD_Writestr("20");
	H_LCD_WriteNum(year);


	H_LCD_GoTOAddress_UsingLine_Col(LINE_4, DIgit_1);

	H_LCD_WriteNum(Hours);
	H_LCD_WriteChar(':');
	H_LCD_WriteNum(Mins);
	H_LCD_WriteChar(':');
	H_LCD_WriteNum(Secs);
	H_LCD_WriteChar(' ');

	switch(Hours_zone)
	{
	case RTC_AM : H_LCD_Writestr("AM");break;
	case RTC_PM : H_LCD_Writestr("PM");break;
	}
}





