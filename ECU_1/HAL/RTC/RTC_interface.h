/*
 * RTC_interface.h
 *
 *  Created on: Mar 11, 2023
 *      Author: Ahmed Hesham
 */

#ifndef RTC_RTC_INTERFACE_H_
#define RTC_RTC_INTERFACE_H_


#include "RTC_types.h"
#include "RTC_private.h"

void RTC_Init (void);
void RTC_Set_Time (u8 Hours, u8 Mins, u8 Secs, RTC_Hours_t Hours_zone);
void RTC_Set_Date (u8 Day, u8 Date, u8 Month, u8 Year);
void RTC_Get_Time (u8* Hours, u8* Mins, u8* Secs, RTC_Hours_t* Hours_zone);
void RTC_Get_Date (u8* Day, u8* Date, u8* Month, u8* Year);
void RTC_LCD_Print (void);




#endif /* RTC_RTC_INTERFACE_H_ */
