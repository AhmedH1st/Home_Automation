#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "Keypad_cfg.h"


/*
 * Config the Pins your keypad ROWS are Connected to
 */

const Dio_Pin_Type Keypad_RowsCfg_Arr[ROWS]={DIO_PC5,DIO_PC4,DIO_PC3,DIO_PC2};

/*
 * Config the Pins your keypad COLS are Connected to
 */
const Dio_Pin_Type Keypad_ColsCfg_Arr[COLS]={DIO_PD7,DIO_PD6,DIO_PD5,DIO_PD3};


#if (KEYPAD_INTERFACING == CALC_HANDLING)

const u8 Keypad_Arr [ROWS][COLS] = {{'7','8','9','/'},
								   {'4','5','6','*'},
								   {'1','2','3','-'},
								   {'c','0','=','+'}};

#elif (KEYPAD_INTERFACING == PB_HANDLING)

const u8 Keypad_Arr [ROWS][COLS] = {{1,2,3,4},
								   {5,6,7,8},
								   {9,10,11,12},
								   {13,14,15,16}};

#endif



