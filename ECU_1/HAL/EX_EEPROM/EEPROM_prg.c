#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "I2C_interface.h"
#include "EEPROM_interface.h"
#include "util/delay.h"



void EEPROM_Init (void)
{
	I2C_Configuration_Bit_Rate.bit_rate=I2C_RATE_400KHZ;
	M_void_I2C_Init();
	_delay_ms(200);

}


EEPROM_status_t EEPROM_WriteByte (u8 byte, u16 address)
{
	EEPROM_status_t EE_state=EEPROM_OK;
	I2C_Error_t I2C_status;

	u8 Least_Half_Adress;
	u8 Most_Half_Address;
	u8 Adress_Byte_to_Send=0;

	Least_Half_Adress=(u8)address;
	Most_Half_Address=(u8)(address>>8);

	Adress_Byte_to_Send=(0xA << 4) | (Most_Half_Address<1);



	/***Start Sending Routine***/

	I2C_status=M_void_I2C_Start();                         //start condition

	if (I2C_status == I2C_NOK)
	{
		//H_LCD_WriteChar('1');   //Debug Purbose
		EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Adress_Byte_to_Send);  //sending first address packet

	if (I2C_status == I2C_NOK)
	{
		//H_LCD_WriteChar('2');
		EE_state=EEPROM_NOK;
	}


	I2C_status=M_void_I2C_SendByte(Least_Half_Adress);  //sending remain of address as a data

	if (I2C_status == I2C_NOK)
	{
		//H_LCD_WriteChar('3');
		EE_state=EEPROM_NOK;
	}


	I2C_status=M_void_I2C_SendByte(byte);                 //sending data

	if (I2C_status == I2C_NOK)
	{
		//H_LCD_WriteChar('4');
		EE_state=EEPROM_NOK;
	}


	M_void_I2C_Stop();                                //Stop Connection

	return EE_state;

}


EEPROM_status_t EEPROM_ReadByte (u8* byte, u16 address)
{
	EEPROM_status_t EE_state=EEPROM_OK;
	I2C_Error_t I2C_status;

	u8 Least_Half_Adress;
	u8 Most_Half_Address;
	u8 Adress_Byte_to_Send=0;

	Least_Half_Adress=(u8)address;
	Most_Half_Address=(u8)(address>>8);

	Adress_Byte_to_Send=(0xA << 4) | (Most_Half_Address<1);   //1010 0 (M_H_A"2bits") 0


	/***Start Sending Routine to send the address***/

	I2C_status=M_void_I2C_Start();                         //start condition

	if (I2C_status == I2C_NOK)
	{
		EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Adress_Byte_to_Send);  //sending first address packet

	if (I2C_status == I2C_NOK)
	{
		EE_state=EEPROM_NOK;
	}


	I2C_status=M_void_I2C_SendByte(Least_Half_Adress);  //sending remain of address as a data

	if (I2C_status == I2C_NOK)
	{
		EE_state=EEPROM_NOK;
	}


	/***Start again to recieve data***/

	Adress_Byte_to_Send=0;
	Adress_Byte_to_Send=(0xA << 4) | 1;  //1010 0001

	I2C_status=M_void_I2C_Start();                         //start condition

	if (I2C_status == I2C_NOK)
	{
		EE_state=EEPROM_NOK;
	}

	I2C_status=M_void_I2C_SendByte(Adress_Byte_to_Send);  //sending  address packet

	if (I2C_status == I2C_NOK)
	{
		EE_state=EEPROM_NOK;
	}


	if (EE_state==EEPROM_OK)
	{
		*byte=M_void_I2C_RecieveByte_NO_Ack();
	}

	M_void_I2C_Stop();

	return EE_state;

}

