/*
 * Timer1_types.h
 *
 *  Created on: Mar 9, 2023
 *      Author: Ahmed Hesham
 */

#ifndef TIMER_1_TIMER1_TYPES_H_
#define TIMER_1_TIMER1_TYPES_H_


typedef enum {
	RISING,
	FALLING

}Timer1_ICU_Mode_t;

typedef enum {
	TIMER1_NORMAL,
	TIMER1_FASTPWM_8PWM

}Timer1_Mode_t;

typedef enum {
	OCR_1A,
	OCR_1B

}Timer1_OCR_t;


#endif /* TIMER_1_TIMER1_TYPES_H_ */
