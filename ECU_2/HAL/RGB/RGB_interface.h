/*
 * RGB_interface.h
 *
 *  Created on: Mar 9, 2023
 *      Author: Ahmed Hesham
 */

#ifndef RGB_RGB_INTERFACE_H_
#define RGB_RGB_INTERFACE_H_

#include "RGB_types.h"
#include "RGB_cfg.h"


void H_void_Set_RGB_Color (RGB_User_Colors_t Color_ID);
void H_void_Set_RGB_Values (u8 red, u8 green, u8 blue);
void H_void_RGB_ShowRoom (void);


#endif /* RGB_RGB_INTERFACE_H_ */
