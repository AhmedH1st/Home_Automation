#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"
#include "I2C_interface.h"
#include "LCD_interface.h"
#include "util/delay.h"


void M_void_I2C_Init (void)
{
	/********Ack enable************/
	SET_BIT(TWCR,TWEA);

	/********Set Bit rate************/
	//Set prescaler to to 0
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);

	switch (I2C_Configuration_Bit_Rate.bit_rate)
	{
	case I2C_RATE_400KHZ:
		TWBR=12;
		break;

	case I2C_RATE_100KHZ:
		//write to Bit Rate Reg
		TWBR=72;
		break;
	}

	/********Set Address************/
	TWAR=0x02;

	/********I2C enable************/
	SET_BIT(TWCR,TWEN);

}


I2C_Error_t M_void_I2C_Start(void)
{
	I2C_reply_t reply;

	TWCR = (1<<TWINT) | (1<<TWSTA)| (1<<TWEN);

	while(GET_BIT(TWCR,TWINT) == 0);

	reply=M_void_I2C_GetStatus();

	if (reply == START_TRANSMITTED || reply == REAPEATED_START_TRANSMITTED)
	{

		return I2C_OK;
	}
	else
	{
		return I2C_NOK;
	}
}


void M_void_I2C_Stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

I2C_Error_t M_void_I2C_SendByte (u8 Byte)
{
	I2C_reply_t reply;

	TWDR=Byte;

	TWCR = (1<<TWINT) | (1<<TWEN);

	while(GET_BIT(TWCR,TWINT) == 0);

	reply=M_void_I2C_GetStatus();

	//H_LCD_Writestr("Not Stuck");

	if (reply==ADRESS_TRANSMITTED_W_ACK_RECIEVED || reply==DATA_BYTE_TRANSMITTED_ACK_RECIEVED
			|| reply==ADRESS_TRANSMITTED_R_ACK_RECIEVED)
	{
		return I2C_OK;
	}
	else
	{
		H_LCD_WriteChar('n');     //Debug Purpose
		//H_LCD_WriteBinary(reply);
		_delay_ms(2000);

		return I2C_NOK;
	}

}

u8 M_void_I2C_RecieveByte_Ack (void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

	while(GET_BIT(TWCR,TWINT) == 0);

	return TWDR;
}

u8 M_void_I2C_RecieveByte_NO_Ack (void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);

	while(GET_BIT(TWCR,TWINT) == 0);

	return TWDR;
}

I2C_reply_t M_void_I2C_GetStatus (void)
{
	I2C_reply_t status;

	status=(TWSR & (0xF8));

	return status;

}


