/*
 * UART_types.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Ahmed Hesham
 */

#ifndef UART_UART_TYPES_H_
#define UART_UART_TYPES_H_



typedef enum {
	BR_2400 = 416,
	BR_4800 = 207,
	BR_9600 = 103,    //103 at16
	BR_14k4 = 68,
	BR_19k2 = 51,
	BR_28k8 = 34,
	BR_115k2 = 8,
	BR_76k8 = 12,
	BR_57k6 = 16,
	BR_38k4 = 25

}UART_BaudRate_t;

typedef enum {
	WORD_5BIT,
	WORD_6BIT,
	WORD_7BIT,
	WORD_8BIT,
	WORD_9BIT=7

}UART_WordLength_t;

typedef enum {
	NOPARITY,
	PARITY_EVEN=2,
	PARITY_ODD

}UART_Parity_t;

typedef enum {
	SBIT_1,
	SBIT_2

}UART_StopBit_t;

typedef enum{
	UART_NORESPONSE,
	UART_RESPONSED
}UART_Response_t;


#endif /* UART_UART_TYPES_H_ */
