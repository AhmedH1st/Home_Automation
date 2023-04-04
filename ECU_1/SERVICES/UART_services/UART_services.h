/*
 * UART_services.h
 *
 *  Created on: Mar 7, 2023
 *      Author: Ahmed Hesham
 */

#ifndef UART_SERVICES_UART_SERVICES_H_
#define UART_SERVICES_UART_SERVICES_H_




void UART_SendString_Synch (u8* str);
void UART_ReceiveString (u8* str);

void UART_Send_WIFI_String_Synch (u8* str);

void UART_Recieve_WIFI_String_Synch (u8* str);


void UART_Recieve_WIFI_String_Synch_TRIAL2 (u8* str);

void UART_Recieve_WIFI_String_Synch_TRIAL3 (u8* str);

void UART_SendArr (u8* arr, u8 size);

void UART_RecieveArr (u8* arr, u8 size);



#endif /* UART_SERVICES_UART_SERVICES_H_ */
