/*
 * ECU1App_types.h
 *
 *  Created on: Mar 15, 2023
 *      Author: Ahmed Hesham
 */

#ifndef ECU1_APP_ECU1APP_TYPES_H_
#define ECU1_APP_ECU1APP_TYPES_H_


#define PIN_DIGITS                   4
#define MAX_NUM_FAULT_PIN            3
#define ENTER                        1
#define BLOCK                        2
#define RESET                        3
#define ADD_FP                       4

#define SIGNAL_TO_MCU2_PIN           DIO_PC7
#define SIGNAL_From_MCU2_PIN         DIO_PA1
#define FIRST_CFG_FLAG_ADDRESS       300

#define FP_LAST_PAGE_ID_ADDRESS      600

#define PIN_1ST_BYTE                 400
#define PIN_2ND_BYTE                 401
//#define PIN_3RD_BYTE               402
//#define PIN_4TH_BYTE               403

#define DAY_EEPROM_BYTE              500
#define DATE_EEPROM_BYTE             501
#define MONTH_EEPROM_BYTE            502
#define YEAR_EEPROM_BYTE             503

#define SEC_EEPROM_BYTE              504
#define MIN_EEPROM_BYTE              505
#define HOUR_EEPROM_BYTE             505
#define HOURMODE_EEPROM_BYTE         506


typedef enum{
	WRONG_PIN,
	RIGHT_PIN,

}ECU_PIN_t;

#endif /* ECU1_APP_ECU1APP_TYPES_H_ */
