#include "Timer0_interface.h"
#include "STD_TYPES.h"
#include "Timer0_cfg.h"

Timer0_cfg_t Timer0_Config ={FASTPWM,                                //Timer Mode
							 CTC_NORMAL_OC_DISCONNECT,	           //CTC_OC_Mode
							 PWM_NON_INVERTING,	                   //PWM_OC_Mode
							 //PRESCALER_256                        //PRESCALER_mode
};
