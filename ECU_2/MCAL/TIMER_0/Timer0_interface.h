/*
 * Timer_interface.h
 *
 *  Created on: Feb 26, 2023
 *      Author: Ahmed Hesham
 */

#ifndef TIMER_0_TIMER0_INTERFACE_H_
#define TIMER_0_TIMER0_INTERFACE_H_
#include "STD_TYPES.h"
#include "Timer_types.h"

void M_void_Timer0_Init(void);
void M_void_Timer0_Start(Timer0_Prescaler_t prescaler);
void M_void_Timer_Stop(void);
u16 M_void_Timer_GetCounts(void);
void M_void_Timer_EnableInt(Interrupt_t interrupt);
void M_void_Timer_DisableInt(Interrupt_t interrupt);
void M_void_Timer_SetCallBack (void (*localPtoFunc)(void),Interrupt_t interrupt);
void M_void_Timer_SetFastPWM (u32 freq, u8 duty);
void M_void_Timer_SetPhaseCorrectPWM (u32 freq, u8 duty);
void M_void_Timer_setDelayTimeMilliSec(u16 desired_ms, Timer0_mode_t local_timer_mode);

void M_void_Timer0_FastPWM_OCR_Direct_input (u8 OCR_value);
void M_void_Timer0_PhaseCorrectPWM_OCR_Direct_input (u8 duty);









#endif /* TIMER_0_TIMER0_INTERFACE_H_ */
