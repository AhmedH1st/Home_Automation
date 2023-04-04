
#ifndef UART_UART_INTERFACE_H_
#define UART_UART_INTERFACE_H_



#include "UART_types.h"
#include "UART_cfg.h"

void M_void_UART_Init_trial (void);

void M_void_UART_Init2 (void);

void M_void_UART_Init (void);

void M_void_UART_Receive_Complete_INT_Enable (void);

void M_void_UART_Receive_Complete_INT_Disable (void);

void M_void_UART_Transmit_Complete_INT_Enable (void);

void M_void_UART_Transmit_Complete_INT_Disable (void);

void M_void_UART_Receive_INT_SetCallBack (void (*localtoFunc)(void));

void M_void_UART__SendWord_Synch (u8 word);


UART_Response_t M_void_UART_ReceiveWord_Synch_NoBlocking(u8* recieved_word);

u8 M_UART_receiveWord_ASynch (void);




#endif /* UART_UART_INTERFACE_H_ */
