#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include <util/delay.h>
#include "Bit_Math.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "avr/interrupt.h"
#include "LCD_interface.h"

void (*PTOFUNC_RECEIVE_COMPLETE)(void);
void (*PTOFUNC_TRANSMIT_COMPLETE)(void);

void M_void_UART_Init_trial (void)
{
	UBRRL=((u8)UART_configuration.baud_rate);
	UBRRH= ((u16)UART_configuration.baud_rate)>>8;

	CLR_BIT(UCSRA,U2X);

	//UCSRC = (1<<URSEL)|(1<<USBS)|(1<<UCSZ1);

	SET_BIT(UCSRB,RXEN);     //Enable Receiver

	SET_BIT(UCSRB,TXEN);     //Enable Transmitter
}


void M_void_UART_Init (void)
{
	//SET_BIT(UCSRC,URSEL);

	/***Select ASynchronous mode***/

	CLR_BIT(UCSRC,UMSEL);

	/***cfg parity mode***/

	UCSRC=UCSRC & (0xcf);
	UCSRC=UCSRC | (UART_configuration.parity<<4);

	/***cfg Stop Bit mode***/

	UCSRC &= (0xf7);
	UCSRC |= (UART_configuration.no_stopBits<<USBS);

	/***cfg word length mode***/

	if (UART_configuration.word_len == WORD_9BIT)
	{
		SET_BIT(UCSRC,1);
		SET_BIT(UCSRC,2);
		SET_BIT(UCSRB,2);

	}
	else
	{
		UCSRC=UCSRC & (0xf9);
		UCSRC=UCSRC| (UART_configuration.word_len<<1);
	}

	CLR_BIT(UCSRA,U2X);    /************/

	/***cfg Baud Rate mode***/

	CLR_BIT(UCSRC,URSEL);
//(UCSRC & (0x7f)) |
	UBRRH= ((u16)UART_configuration.baud_rate)>>8;
	//UBRRH=(UCSRC & (0<<URSEL)) |((u16)UART_configuration.baud_rate)>>8;   //old
	UBRRL=((u8)UART_configuration.baud_rate);

	/************************/



	/***TURN ON UART (Send & Receive)***/

	SET_BIT(UCSRB,RXEN);     //Enable Receiver

	SET_BIT(UCSRB,TXEN);     //Enable Transmitter


}






void M_void_UART_Init2 (void)
{
	/***cfg Baud Rate mode***/

	CLR_BIT(UCSRC,URSEL);
	//(UCSRC & (0<<URSEL)) |
	UBRRH= ((u16)UART_configuration.baud_rate)>>8;
	UBRRL=((u8)UART_configuration.baud_rate);

	/************************/


	//SET_BIT(UCSRC,URSEL);

	/***Select ASynchronous mode***/

	//CLR_BIT(UCSRC,UMSEL);

	/***cfg parity mode***/

	UCSRC=(UCSRC | (1<<URSEL)) | (UCSRC & (0xcf)) ;
	UCSRC=(UCSRC | (1<<URSEL)) | (UCSRC | (UART_configuration.parity<<4));

	/***cfg Stop Bit mode***/

	UCSRC =(UCSRC | (1<<URSEL)) | (UCSRC & (0xf7));
	UCSRC =(UCSRC | (1<<URSEL)) | (UCSRC | (UART_configuration.no_stopBits<<USBS));

	/***cfg word length mode***/

	if (UART_configuration.word_len == WORD_9BIT)
	{
		SET_BIT(UCSRC,1);
		SET_BIT(UCSRC,2);
		SET_BIT(UCSRB,2);

	}
	else
	{
		UCSRC=(UCSRC | (1<<URSEL)) | (UCSRC & (0xf9));
		UCSRC=(UCSRC | (1<<URSEL)) | (UCSRC | (UART_configuration.word_len<<1));
	}

	/***TURN ON UART (Send & Receive)***/

	SET_BIT(UCSRC,URSEL);

	CLR_BIT(UCSRA,U2X);

	SET_BIT(UCSRB,RXEN);     //Enable Receiver

	SET_BIT(UCSRB,TXEN);     //Enable Transmitter


}









void M_void_UART_Receive_Complete_INT_Enable (void)
{
	SET_BIT(UCSRB,RXCIE);
}

void M_void_UART_Receive_Complete_INT_Disable (void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void M_void_UART_Transmit_Complete_INT_Enable (void)
{
	SET_BIT(UCSRB,TXCIE);
}

void M_void_UART_Transmit_Complete_INT_Disable (void)
{
	CLR_BIT(UCSRB,TXCIE);
}


void M_void_UART_Receive_INT_SetCallBack (void (*localtoFunc)(void))
{
	PTOFUNC_RECEIVE_COMPLETE=localtoFunc;
}

void M_void_UART_Transmit_INT_SetCallBack (void (*localtoFunc)(void))
{
	PTOFUNC_TRANSMIT_COMPLETE=localtoFunc;
}


void M_void_UART__SendWord_Synch (u8 word)
{
	while ((GET_BIT(UCSRA,UDRE)) == 0);
	UDR=word;
}



UART_Response_t M_void_UART_ReceiveWord_Synch_NoBlocking(u8* recieved_word)
{
	UART_Response_t response;
	u16 Run_Out=0;

	while (GET_BIT(UCSRA,RXC) == 0  && Run_Out<200)
	{
		Run_Out++;
		_delay_us(100);
	}
	if (Run_Out<200)
	{
		response=UART_RESPONSED;
		*recieved_word=UDR;
	}
	else
	{
		response=UART_NORESPONSE;
	}

	return response;
}



u8 M_UART_receiveWord_ASynch (void)
{
	return UDR;
}




ISR (USART_RXC_vect)
{
	PTOFUNC_RECEIVE_COMPLETE();
}







