/*
 * ECU2App_private.h
 *
 *  Created on: Mar 16, 2023
 *      Author: Ahmed Hesham
 */

#ifndef ECU2APP_ECU2APP_PRIVATE_H_
#define ECU2APP_ECU2APP_PRIVATE_H_


void Start_Fan (void);
void Stop_Fan (void);
void Fan_High (void);
void Fan_Low (void);
void RGB_Red (void);
void RGB_Blue (void);
void RGB_Yellow (void);
void RGB_White (void);
void RGB_Off (void);
void Temp_Read (void);
void LogOut (void);
void Set_RGBLuminaire (void);
String_cmp_t String_Compare (void);



#endif /* ECU2APP_ECU2APP_PRIVATE_H_ */
