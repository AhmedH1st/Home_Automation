
#include "ADC_cfg.h"
#include "ADC_types.h"
#include "ADC_private.h"


#ifndef ADC_ADC_INTERFACE_H_
#define ADC_ADC_INTERFACE_H_

#include "ADC_types.h"
#include "ADC_cfg.h"



void M_ADC_void_Init (void);

u16 M_ADC_GetRead (ADC_Channel_ID_t ch);

void M_ADC_getDigitalValueAsynchCallBack(ADC_Channel_ID_t ch, void (*P_localToFunc)(void));









#endif /* ADC_ADC_INTERFACE_H_ */
