/*
 * I2C_interface.h
 *
 *  Created on: Mar 10, 2023
 *      Author: Ahmed Hesham
 */

#ifndef I2C_I2C_INTERFACE_H_
#define I2C_I2C_INTERFACE_H_

#include "I2C_types.h"
#include "I2C_cfg.h"


void M_void_I2C_Init (void);
I2C_Error_t M_void_I2C_Start(void);
void M_void_I2C_Stop(void);
I2C_Error_t M_void_I2C_SendByte (u8 Byte);
u8 M_void_I2C_RecieveByte_Ack (void);
u8 M_void_I2C_RecieveByte_NO_Ack (void);
I2C_reply_t M_void_I2C_GetStatus (void);





#endif /* I2C_I2C_INTERFACE_H_ */
