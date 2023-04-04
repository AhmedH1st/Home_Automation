#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "Keypad_interface.h"
#include "Keypad_cfg.h"
#include "Keypad_private.h"


u8 H_KEYPAD_u8_getPressedKey(void)
{
#if (ACTIVITY_TYPE == ACTIVE_LOW)

u8 row_index,col_index;
u8 PB=NO_PRESSED_KEY;

for (row_index=0; row_index<ROWS; row_index++)
{
	M_DIO_void_setPinValue(Keypad_RowsCfg_Arr[row_index],DIO_LOW);

	for (col_index=0; col_index<COLS; col_index++)
	{
		if(M_DIO_getPinValue(Keypad_ColsCfg_Arr[col_index]) == DIO_LOW)
		{
			PB = Keypad_Arr[row_index][col_index];
			while (M_DIO_getPinValue(Keypad_ColsCfg_Arr[col_index]) == DIO_LOW);
		}
	}

	M_DIO_void_setPinValue(Keypad_RowsCfg_Arr[row_index],DIO_HIGH);
}

return PB;

#elif (ACTIVITY_TYPE == ACTIVE_HIGH)

u8 row_index,col_index;
u8 PB=NO_PRESSED_KEY;

for (row_index=0; row_index<ROWS; row_index++)
{
	M_DIO_void_setPinValue(Keypad_RowsCfg_Arr[row_index],DIO_HIGH);

	for (col_index=0; col_index<COLS; col_index++)
	{
		if(M_DIO_getPinValue(Keypad_ColsCfg_Arr[col_index]) == DIO_HIGH)
		{
			PB = Keypad_Arr[row_index][col_index];
		}
	}

	M_DIO_void_setPinValue(Keypad_RowsCfg_Arr[row_index],DIO_LOW);
}

return PB;


#endif

}
