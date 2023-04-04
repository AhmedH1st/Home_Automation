/*
 * ADC_cfg.h
 *
 *  Created on: Feb 25, 2023
 *      Author: Ahmed Hesham
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_
#include "ADC_types.h"


typedef struct{
	ADC_Reference_V_t ADC_REF_VOL;
	ADC_Prescaler_mode_t mode;
	ADC_Auto_Trigger_Setting_t trigger_mode;    //add in Init func if necessary
	ADC_Data_adjust_t adjust;


}ADC_Config_t;


extern ADC_Config_t ADC_configurion;




#endif /* ADC_CFG_H_ */
