/*
 * Timer_types.h
 *
 *  Created on: Feb 26, 2023
 *      Author: Ahmed Hesham
 */

#ifndef TIMER_0_TIMER_TYPES_H_
#define TIMER_0_TIMER_TYPES_H_

typedef enum{
	NORMAL,
	PWM_PHASECORRECT,
	CTC,
	FASTPWM

}Timer0_mode_t;

typedef enum{
	CTC_NORMAL_OC_DISCONNECT,
	CTC_TOGGLE,
	CTC_CLEAR,
	CTC_SET
}Timer0_CTC_mode_t;

typedef enum {
	PWM_NORMAL_OC_DISCONNECT,
	PWM_NONE,
	PWM_NON_INVERTING,
	PWM_INVERTING
}Timer0_PWM_mode_t;


typedef enum {
	TIMEROFF,
	NOPRESCALING,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNALCLK_FALLINGEDGE,
	EXTERNALCLK_RISINGEDGE

}Timer0_Prescaler_t;

typedef enum{
	OV,
	OCM
}Interrupt_t;




typedef struct{
	Timer0_mode_t mode;
	Timer0_CTC_mode_t ctc_mode;
	Timer0_PWM_mode_t pwm_mode;
	//Timer0_Prescaler_t prescaler;

}Timer0_cfg_t;




#endif /* TIMER_0_TIMER_TYPES_H_ */
