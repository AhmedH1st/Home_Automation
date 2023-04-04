/*
 * Call_Back_functions.h
 *
 *  Created on: Feb 26, 2023
 *      Author: Ahmed Hesham
 */

#ifndef INTERRUPTS_CALLBACK_CALL_BACK_FUNCTIONS_H_
#define INTERRUPTS_CALLBACK_CALL_BACK_FUNCTIONS_H_

#include "STD_TYPES.h"

/********VARIABLES RELATED TO ULTRASONIC PROJECT**********/


extern volatile u8 ICU_flag;
extern volatile u16 t1;
extern volatile u16 t2;

/***********************************************************/


void ADC_Int_Func (void);
void Timer0_OV_Int(void);
void Timer0_OCM_Int(void);
void UART_ReceiveWord (void);
void UART_Receive_Wifi (void);

/********VARIABLES RELATED TO UART RECIEVE PROCESS PROJECTT**********/

extern volatile u8 UART_RECIEVED_WORD;
extern volatile u8 UART_RECIEVED_STR [100];
extern volatile u8 Rec_Com_flag;

/***********************************************************/
extern volatile u8 EX_INTERRUPT_FLAG;


void EXT_INT1_FUNC(void);
void EXT_INT2_FUNC(void);
void EXT_INT3_FUNC(void);

#endif /* INTERRUPTS_CALLBACK_CALL_BACK_FUNCTIONS_H_ */
