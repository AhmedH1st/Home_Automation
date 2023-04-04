#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#include "DIO_Interface.h"

/*
 * Determine NO Rows & Cols In your Matrix
 */

#define ROWS    4
#define COLS    4
/*****************************************************/

/*
 * Determine your Cols are ACTIVE_LOW (or) ACTIVE_HIGH
 */

#define ACTIVITY_TYPE   ACTIVE_LOW
/*****************************************************/

/*
 * Determine your prefer of Handling the Keypad
 * Whether you want to deal with it as a PBs Matrix
 * or Handling it Like A calculator
 * Choose:
 *
 * PB_HANDLING  oR  CALC_HANDLING
 */

#define KEYPAD_INTERFACING     CALC_HANDLING



/*************************************************/

extern const Dio_Pin_Type Keypad_RowsCfg_Arr[ROWS];

extern const Dio_Pin_Type Keypad_ColsCfg_Arr[COLS];

extern const u8 Keypad_Arr [ROWS][COLS];

#endif /* KEYPAD_CFG_H_ */
