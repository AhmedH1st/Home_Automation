#ifndef _LED_INTERFACE_H_
#define _LED_INTERFACE_H_

#include "LED_cfg.h"
#include "LED_Types.h"

#define LED_RED        0
#define LED_BLUE       1
#define LED_GREEN      2
#define LED_YELLOW     3



void H_LED_void_turnON (u8 LedID);
void H_LED_TurnOff (u8 LedID);
void H_LED_Toggle (u8 LedID);


#endif
