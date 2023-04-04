/*
 * Ex_cfg.h
 *
 *  Created on: Feb 24, 2023
 *      Author: Ahmed Hesham
 */

#ifndef EX_CFG_H_
#define EX_CFG_H_

#include "Ex_types.h"


#define NO_EXTER_INTER   3

typedef enum{
	LOW_LVL,
	CHANGING_LVL,
	FALLING_EDGE,
	RISING_EDGE
}Inter_Sense_Control_t;


/*typedef enum{
	DISABLE,
	ENABLE
}Inter_Status_t;*/







typedef struct{
	Inter_Sense_Control_t ex_int_sense;
	Inter_ID_t ex_int_ID;
}Ex_inter_t;







#endif /* EX_CFG_H_ */
