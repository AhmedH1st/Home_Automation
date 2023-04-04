#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "Mcu_HW.h"
#include "avr/interrupt.h"
#include "Timer1_interface.h"

/*#include "LCD_interface.h"
#include "util/delay.h"*/


static void (*PTOFUNC_ICU)(void);


void M_void_Timer1_Init (void)
{
	/*****Set to work on normal mode .. and maybe complete the driver whin have time*****/

	/**********these config done to serve the ultrasonic project**************************/
	/*TCCR1A=0;         //normal mode


	TCCR1B=0x43;      //normal mode with /64 scaler so tick time=4us and ICU set to capture rising edge(initial)*/

	/*************** these config done to serve RGB Project (as no time to completer driver)*********************/

	/*************** work on fast PWM mode, 8bit TOP, NON_inverting  *************************/

	TCCR1A=0xA1;

	TCCR1B=0x0C;

	// Fcpu=16M
	//prescaler\=256 --> F-timer=16M/256=62500 -->TicTime=1000000/62500=16us
	//PWMfreq =Ftimer/OF= 62500/256= 244HZ

}



void M_void_Timer1_FastPWM_OCR_Direct_input (Timer1_OCR_t OCR_ID ,u8 OCR_value)
{
	switch(OCR_ID)
	{
	case OCR_1A:
		OCR1A=(u16)OCR_value;
		break;

	case OCR_1B:
		OCR1B=(u16)OCR_value;
		break;
	}
}
















void M_void_Timer1_IC_Interrupt_Enable(void)
{
	SET_BIT(TIMSK,TICIE1);
}

void M_void_Timer1_IC_Interrupt_Disable (void)
{
	CLR_BIT(TIMSK,TICIE1);
}

void M_void_Timer1_zero(void)
{
	TCNT1=0;
}


void M_void_Timer1_ICU_Interrupt_SetCallBack (void(*plocalToFunc)(void))
{
	PTOFUNC_ICU=plocalToFunc;
}






ISR(TIMER1_CAPT_vect)
{
	PTOFUNC_ICU();
}
