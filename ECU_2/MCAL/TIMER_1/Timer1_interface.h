/*
 * Timer1_interface.h
 *
 *  Created on: Mar 2, 2023
 *      Author: Ahmed Hesham
 */

#ifndef TIMER_1_TIMER1_INTERFACE_H_
#define TIMER_1_TIMER1_INTERFACE_H_

#include "Timer1_types.h"
#include "Timer1_cfg.h"

void M_void_Timer1_Init (void);
void M_void_Timer1_IC_Interrupt_Enable(void);
void M_void_Timer1_IC_Interrupt_Disable(void);
void M_void_Timer1_ICU_Interrupt_SetCallBack(void(*plocalToFunc)(void));
void M_void_Timer1_zero(void);



void M_void_Timer1_FastPWM_OCR_Direct_input (Timer1_OCR_t OCR_ID ,u8 OCR_value);






#endif /* TIMER_1_TIMER1_INTERFACE_H_ */
