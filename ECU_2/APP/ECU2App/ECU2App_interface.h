/*
 * ECU2App_interface.h
 *
 *  Created on: Mar 16, 2023
 *      Author: Ahmed Hesham
 */

#ifndef ECU2APP_ECU2APP_INTERFACE_H_
#define ECU2APP_ECU2APP_INTERFACE_H_

#include "ECU2App_types.h"
#include "ECU2App_private.h"

//extern u8 LAST_SET_RED;
//extern u8 LAST_SET_GREEN;
//extern u8 LAST_SET_BLUE;





void ECU2_Init (void);
void ECU2_Runnable (void);
void First_Home_Step (void);




#endif /* ECU2APP_ECU2APP_INTERFACE_H_ */
