/*
 * LCD_interface.h
 *
 *  Created on: Feb 19, 2023
 *      Author: Ahmed Hesham
 */
#include "STD_TYPES.h"
#include "LCD_Types.h"
#include "LCD_cfg.h"
#include "LCD_private.h"

#ifndef LCD_LCD_INTERFACE_H_
#define LCD_LCD_INTERFACE_H_


void H_LCD_Init(void);
void H_LCD_ClearDisplay();
void H_LCD_SendData(u8 data);
void H_LCD_SendIns(u8 inst);
void H_LCD_Latch(u8 message);
void H_LCD_WriteChar (u8 ch);
void H_LCD_WriteNum (u32 num);
void H_LCD_Writestr (u8* str);
void H_LCD_ReturnHome (void);
void H_LCD_WriteBinary (s16 num);
void H_LCD_GoTOAddress_UsingLine_Col(LCD_Line_t Line, LCD_Digit_t digit);
void H_LCD_SET_Address (u8 address);
void H_LCD_CreateCustomChar (u8* customArr);













#endif /* LCD_LCD_INTERFACE_H_ */
