/*
 * Ex_interface.h
 *
 *  Created on: Feb 24, 2023
 *      Author: Ahmed Hesham
 */

#ifndef EXT_INTERRUPT_EX_INTERFACE_H_
#define EXT_INTERRUPT_EX_INTERFACE_H_

#include "Ex_types.h"
#include "Ex_cfg.h"


void M_EXTInerrupt_void_Enable (Inter_ID_t InT, Inter_Sense_Control_t sense);
void M_EXTInerrupt_void_Diable (Inter_ID_t InT);
void M_EXTInerrupt_void_Trigger (Inter_ID_t InT, Inter_Sense_Control_t sense);
void M_EXTInerrupt_void_SetCallBack (Inter_ID_t InT,  void(*pf)(void));

#define NO_OF_FUNCTIONS  3


#endif /* EXT_INTERRUPT_EX_INTERFACE_H_ */
