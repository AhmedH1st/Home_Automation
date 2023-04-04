#include "STD_TYPES.h"
#include "Timer2_interface.h"
#include "Timer1_interface.h"
#include "RGB_interface.h"
#include "util/delay.h"




void H_void_Set_RGB_Color (RGB_User_Colors_t Color_ID)
{
	M_void_Timer2_FastPWM_OCR_Direct_input(RGB_Colors_arr[Color_ID].Red);
	M_void_Timer1_FastPWM_OCR_Direct_input(OCR_1A,RGB_Colors_arr[Color_ID].Green);
	M_void_Timer1_FastPWM_OCR_Direct_input(OCR_1B,RGB_Colors_arr[Color_ID].Blue);
}

void H_void_Set_RGB_Values (u8 red, u8 green, u8 blue)
{
	M_void_Timer2_FastPWM_OCR_Direct_input(red);
	M_void_Timer1_FastPWM_OCR_Direct_input(OCR_1A,green);
	M_void_Timer1_FastPWM_OCR_Direct_input(OCR_1B,blue);
}


void H_void_RGB_ShowRoom (void)
{
	u8 i,j,k;

	while(1)
	{
		H_void_Set_RGB_Values(0,0,0);
		for (i=0; i<255; i++)
		{
			H_void_Set_RGB_Values(i,0,0);
			_delay_ms(5);
		}

		for (j=0; j<255; j++)
		{
			H_void_Set_RGB_Values(i,j,0);
			_delay_ms(5);
		}
		for (k=0; k<255; k++)
		{
			H_void_Set_RGB_Values(i,j,k);
			_delay_ms(5);
		}
		for (; i>0; i--)
		{
			H_void_Set_RGB_Values(i,j,k);
			_delay_ms(5);
		}
		for (; j>0; j--)
		{
			H_void_Set_RGB_Values(i,j,k);
			_delay_ms(5);
		}
		for (; k>0; k--)
		{
			H_void_Set_RGB_Values(i,j,k);
			_delay_ms(5);
		}
		for (j=0; j<255; j++)
		{
			H_void_Set_RGB_Values(255,j,k);
			_delay_ms(5);
		}
		for (k=0; k<255; k++)
		{
			H_void_Set_RGB_Values(0,255,k);
			_delay_ms(5);
		}
	}
}
