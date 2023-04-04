/*
 * Timer2_interface.h
 *
 *  Created on: Mar 16, 2023
 *      Author: Ahmed Hesham
 */

#ifndef TIMER_2_TIMER2_INTERFACE_H_
#define TIMER_2_TIMER2_INTERFACE_H_

#include "Timer2_types.h"
#include "Timer2_cfg.h"

void M_void_Timer2_Init(void);

void M_void_Timer2_FastPWM_OCR_Direct_input(u8 OCR_value);



#endif /* TIMER_2_TIMER2_INTERFACE_H_ */
