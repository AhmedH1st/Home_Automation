/*
 * ADC_types.h
 *
 *  Created on: Feb 25, 2023
 *      Author: Ahmed Hesham
 */

#ifndef ADC_ADC_TYPES_H_
#define ADC_ADC_TYPES_H_


typedef enum {
	Ch_0,
	Ch_1,
	Ch_2,
	Ch_3,
	Ch_4,
	Ch_5,
	Ch_6,
	Ch_7
}ADC_Channel_ID_t;

typedef enum {
	CK_2=1,
	CK_4,
	CK_8,
	CK_16,
	CK_32,
	CK_64,
	CK_128
}ADC_Prescaler_mode_t;

typedef enum {
	AREF,
	AVCC,
	VREF_256=3
}ADC_Reference_V_t;

typedef enum {
	DISABLE,
	ENABLE
}ADC_Auto_Trigger_Setting_t;

typedef enum {
	RIGHT,
	LEFT
}ADC_Data_adjust_t;

#endif /* ADC_ADC_TYPES_H_ */
