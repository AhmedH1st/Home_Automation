/*
 * ECU1App_private.h
 *
 *  Created on: Mar 15, 2023
 *      Author: Ahmed Hesham
 */

#ifndef ECU1_APP_ECU1APP_PRIVATE_H_
#define ECU1_APP_ECU1APP_PRIVATE_H_

void ECU1_StandBy(void);
void ECU1_PIN_Verification (void);
void EUC1_FirstConfig_PIN(void);
void EUC1_FirstConfig_FP (void);
void ECU1_Entry (void);
void ECU1_Block (void);
void ECU1_InHome (void);
ECU_PIN_t ECU1_CheckPIN (u16 EnteredPin);
void ECU1_Reset_PIN (void);
void ECU1_Add_FP (void);

#endif /* ECU1_APP_ECU1APP_PRIVATE_H_ */
