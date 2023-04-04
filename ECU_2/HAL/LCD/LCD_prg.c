#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "LCD_Types.h"
#include "LCD_cfg.h"
#include "LCD_interface.h"
#include "util/delay.h"
#include "Bit_Math.h"
#include "Call_Back_functions.h"



void H_LCD_Init(void)
{
	#if (LCD_TYPE == LCD_4_bit)
	_delay_ms(50);
	M_DIO_void_setPinValue(DB4,LOW);
	M_DIO_void_setPinValue(DB5,HIGH);
	M_DIO_void_setPinValue(DB6,LOW);
	M_DIO_void_setPinValue(DB7,LOW);
	M_DIO_void_setPinValue(EN,HIGH);
	_delay_ms(1);
	M_DIO_void_setPinValue(EN,LOW);
	_delay_ms(1);
	M_DIO_void_setPinValue(DB4,LOW);
	M_DIO_void_setPinValue(DB5,HIGH);
	M_DIO_void_setPinValue(DB6,LOW);
	M_DIO_void_setPinValue(DB7,LOW);
	M_DIO_void_setPinValue(EN,HIGH);
	_delay_ms(1);
	M_DIO_void_setPinValue(EN,LOW);
	_delay_ms(1);
	M_DIO_void_setPinValue(DB4,LOW);
	M_DIO_void_setPinValue(DB5,LOW);
	M_DIO_void_setPinValue(DB6,LOW);
	M_DIO_void_setPinValue(DB7,HIGH);
	M_DIO_void_setPinValue(EN,HIGH);
	_delay_ms(1);
	M_DIO_void_setPinValue(EN,LOW);
	_delay_ms(1);


	/****************************************************************/
	_delay_ms(1);
	H_LCD_SendIns(0x80);
	_delay_ms(1);
	H_LCD_SendIns(0x0C);   // the one that controls the cursor (0x0E)-->if wanna show the cursor .. (0x0F) if wanna make the cursor blinks
	_delay_ms(1);
	H_LCD_ClearDisplay();
	_delay_ms(1);
	H_LCD_SendIns(0x06);  //the one that responsible of shifting and increasing or decreasing order

#elif (LCD_TYPE == LCD_8_bit)

	_delay_ms(50);
		LCD_SendIns(0x38);
		_delay_ms(1);
		LCD_SendIns(0x0C);   // the one that controls the cursor (0x0E)-->if wanna show the cursor .. (0x0F) if wanna make the cursor blinks
		_delay_ms(1);
		LCD_ClearDisplay();
		_delay_ms(1);
		LCD_SendIns(0x06);  //the one that responsible of shifting and increasing or decreasing order
	#endif
}

void H_LCD_ClearDisplay ()
{
	H_LCD_SendIns(0x01);
}


void H_LCD_SendData (u8 data)
{
	M_DIO_void_setPinValue(RS,HIGH);
	H_LCD_Latch(data);
}


void H_LCD_SendIns(u8 inst)
{
	M_DIO_void_setPinValue(RS,LOW);
	H_LCD_Latch(inst);
}


void H_LCD_Latch(u8 message)
{
	#if (LCD_TYPE == LCD_4_bit)
	M_DIO_void_setPinValue(DB4,(GET_BIT(message,4)));
	M_DIO_void_setPinValue(DB5,(GET_BIT(message,5)));
	M_DIO_void_setPinValue(DB6,(GET_BIT(message,6)));
	M_DIO_void_setPinValue(DB7,(GET_BIT(message,7)));
	M_DIO_void_setPinValue(EN,HIGH);
	_delay_ms(1);
	M_DIO_void_setPinValue(EN,LOW);
	_delay_ms(1);
	M_DIO_void_setPinValue(DB4,(GET_BIT(message,0)));
	M_DIO_void_setPinValue(DB5,(GET_BIT(message,1)));
	M_DIO_void_setPinValue(DB6,(GET_BIT(message,2)));
	M_DIO_void_setPinValue(DB7,(GET_BIT(message,3)));
	M_DIO_void_setPinValue(EN,HIGH);
	_delay_ms(1);
	M_DIO_void_setPinValue(EN,LOW);
	_delay_ms(1);


	#elif (LCD_TYPE == LCD_8_bit)
	M_DIO_void_setPinValue(DB0,(GET_BIT(message,0)));
	M_DIO_void_setPinValue(DB1,(GET_BIT(message,1)));
	M_DIO_void_setPinValue(DB2,(GET_BIT(message,2)));
	M_DIO_void_setPinValue(DB3,(GET_BIT(message,3)));
	M_DIO_void_setPinValue(DB4,(GET_BIT(message,4)));
	M_DIO_void_setPinValue(DB5,(GET_BIT(message,5)));
	M_DIO_void_setPinValue(DB6,(GET_BIT(message,6)));
	M_DIO_void_setPinValue(DB7,(GET_BIT(message,7)));
	M_DIO_void_setPinValue(EN,HIGH);
	_delay_ms(1);
	M_DIO_void_setPinValue(EN,LOW);
	_delay_ms(1);




	#endif
}

void H_LCD_WriteChar (u8 ch)
{
	H_LCD_SendData(ch);
}

void H_LCD_WriteNum (u32 num)
{
	u8 numArr[16]={0};
	u8 i=0;
	s8 j;
	if (num==0)
	{
		H_LCD_SendData('0');
		return;
	}
	if (num<0)
	{
		H_LCD_SendData('-');
		num*=-1;
	}
	while(num)
	{
		numArr[i++]='0'+(num%10);
		num=num/10;
	}

	for (j=i-1; j>=0; j--)
	{
		H_LCD_SendData(numArr[j]);
	}
}

void H_LCD_Writestr (u8* str)
{
	u8 index;

	for (index=0; str[index]; index++)
	{
		H_LCD_SendData(str[index]);
	}
}

void H_LCD_ReturnHome (void)
{
	H_LCD_SendIns(0x02);
}


void H_LCD_WriteBinary (s16 num)
{
	u8 numArr[16]={0};
	u8 i=0;
	s8 j;
	if (num==0)
	{
		H_LCD_SendData('0');
		return;
	}
	while(num)
	{
		numArr[i++]='0'+(num&1);
		num=num>>1;
	}
	for(j=i-1; j>=0; j--)
	{
		H_LCD_SendData(numArr[j]);
	}
}


void H_LCD_GoTOAddress_UsingLine_Col(LCD_Line_t Line, LCD_Digit_t digit)
{
	#if (LCD_SIZE == 4*20)
	switch(Line)
	{
		case LINE_1:
		H_LCD_SET_Address((DDRAM_START_ADDRESS+digit));break;
		case LINE_2:
		H_LCD_SET_Address((0xC0+digit));break;
		case LINE_3:
		H_LCD_SET_Address((148+digit));break;
		case LINE_4:
		H_LCD_SET_Address((0xD4+digit));break;
	}

	#elif (LCD_SIZE == 2*16)
	{
		switch(Line)
		{
			case LINE_1:
			H_LCD_SET_Address((DDRAM_START_ADDRESS+digit));break;
			case LINE_2:
			H_LCD_SET_Address((0xC0+digit));break;
		}
	}

	#endif
}

void H_LCD_SET_Address (u8 address)
{
	M_DIO_void_setPinValue(RS,LOW);
	H_LCD_Latch(address);
}


void H_LCD_CreateCustomChar (u8* customArr)
{
	u8 i;

	H_LCD_SET_Address(CGRAM_START_ADDRESS);

	for (i=0; i<NUMBER_OF_DIGIT_ROWS; i++)
	{
		H_LCD_WriteChar(customArr[i]);
	}
}
