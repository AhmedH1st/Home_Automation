/*
 * EEPROM_interface.h
 *
 *  Created on: Mar 11, 2023
 *      Author: Ahmed Hesham
 */

#ifndef EX_EEPROM_EEPROM_INTERFACE_H_
#define EX_EEPROM_EEPROM_INTERFACE_H_

#include "EEPROM_types.h"

void EEPROM_Init (void);
EEPROM_status_t EEPROM_WriteByte (u8 byte, u16 address);
EEPROM_status_t EEPROM_ReadByte (u8* byte, u16 address);



#endif /* EX_EEPROM_EEPROM_INTERFACE_H_ */
