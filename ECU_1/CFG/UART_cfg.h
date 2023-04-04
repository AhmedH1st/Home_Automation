
#ifndef UART_CFG_H_
#define UART_CFG_H_



#include "UART_types.h"

typedef struct{
	UART_BaudRate_t baud_rate;
	UART_WordLength_t word_len;
	UART_Parity_t parity;
	UART_StopBit_t no_stopBits;

}UART_cfg_t;


extern UART_cfg_t UART_configuration;

#endif /* UART_CFG_H_ */
