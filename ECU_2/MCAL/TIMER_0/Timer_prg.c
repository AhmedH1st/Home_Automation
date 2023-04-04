#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"
#include "Timer0_interface.h"
#include "Timer0_cfg.h"
#include "Timer_private.h"
#include "avr/interrupt.h"


static u8 Prescaler;
static u8 delay_func_flag;
static u16 count;
static u16 desired_count;
static void (*PtoFunction_OV)(void);
static void (*PtoFunction_OCM)(void);
static u32 frequencies_prescaler_arr [5]={16000000,2000000,250000,62500,15625};

void M_void_Timer0_Init(void)
{
	/****Mode CFG****/
	switch(Timer0_Config.mode)
	{
	case NORMAL:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;

	case PWM_PHASECORRECT:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
			break;

	case 	CTC:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
			break;

	case FASTPWM:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
			break;
	}

	/****Compare Match Output Mode Cfg****/

	TCCR0=TCCR0&(0xcf);   //Clear Bit 4,5

	if (Timer0_Config.mode == CTC)
	{
		TCCR0|=((Timer0_Config.ctc_mode)<<4);
	}
	else if (Timer0_Config.mode == PWM_PHASECORRECT || Timer0_Config.mode== FASTPWM)
	{
		TCCR0|=((Timer0_Config.pwm_mode)<<4);
	}
	else
	{
	}

	/****Prescaler set to Zero So timer is stooped until Func TIMER_Start set the prescaler****/

	TCCR0=TCCR0&(0xf8);

	//TCCR0|=Timer0_Config.prescaler;
}


void M_void_Timer0_Start(Timer0_Prescaler_t prescaler)
{
	TCCR0&=(0xf8);
	TCCR0|=prescaler;
	Prescaler=prescaler; /*********************************/
}


void M_void_Timer_Stop(void)
{
	TCCR0=TCCR0&(0xf8);
	count=0;
}

u16 M_void_Timer_GetCounts(void)
{
	return count;
}

void M_void_Timer_EnableInt(Interrupt_t interrupt)
{
	switch (interrupt)
	{
	case OV :
		SET_BIT(TIMSK,TOIE0);
		break;
	case OCM :
		SET_BIT(TIMSK,OCIE0);
		break;
	}
}

void M_void_Timer_DisableInt(Interrupt_t interrupt)
{
	switch (interrupt)
	{
	case OV :
		CLR_BIT(TIMSK,TOIE0);
		break;
	case OCM :
		CLR_BIT(TIMSK,OCIE0);
		break;
	}
}

void M_void_Timer_SetCallBack (void (*localPtoFunc)(void),Interrupt_t interrupt)
{
	switch (interrupt)
		{
		case OV :
			PtoFunction_OV=localPtoFunc;
			break;
		case OCM :
			PtoFunction_OCM=localPtoFunc;
			break;
		}
}


void M_void_Timer_SetFastPWM (u32 freq, u8 duty)
{
	u32 min=0xffffffff;
	s32 temp;
	u8 i,index=0;
	u32 desired_timer_freq=freq*256;

	for (i=0; i<5; i++)
	{//{16000000,2000000,250000,62500,15625}
		temp=(s32)frequencies_prescaler_arr[i]-desired_timer_freq;
		if (temp<0)
		{
			temp*=-1;
		}
		if (temp<min)
		{
			min=temp;
			index=i;
		}
		M_void_Timer0_Start(index+1);
	/****Calc Ton****/
	}
	switch (Timer0_Config.pwm_mode)
	{
	case PWM_NON_INVERTING:
		OCR0=(((u16)256*duty)/100)-1;
		break;

	case PWM_INVERTING:
		OCR0=255-((((u16)256*duty)/100));
		break;
	}
}


void M_void_Timer0_FastPWM_OCR_Direct_input (u8 OCR_value)
{
	switch (Timer0_Config.pwm_mode)
	{
	case PWM_NON_INVERTING:
		OCR0=OCR_value;
		break;

	case PWM_INVERTING:
		OCR0=OCR_value;
		break;
	}
}


void M_void_Timer_SetPhaseCorrectPWM (u32 freq, u8 duty)
{
	u32 min=0xffffffff;
	s32 temp;
	u8 i,index=0;
	u32 desired_timer_freq=freq*510;                //discuss
	//u32 desired_timer_freq=(freq/2)*510;

	for (i=0; i<5; i++)
	{//{16000000,2000000,250000,62500,15625}
		temp=(s32)frequencies_prescaler_arr[i]-desired_timer_freq;
		if (temp<0)
		{
			temp*=-1;
		}
		if (temp<min)
		{
			min=temp;
			index=i;
		}

	}
	M_void_Timer0_Start(index+1);

	/****Calc Ton****/

	switch (Timer0_Config.pwm_mode)
	{
	case PWM_NON_INVERTING:
		OCR0=((u16)duty*510)/(200);
		break;

	case PWM_INVERTING:
		OCR0=512-(((u16)duty*510)/(200));
		break;
	}
}

void M_void_Timer0_PhaseCorrectPWM_OCR_Direct_input (u8 duty)
{
	/****Calc Ton****/

	switch (Timer0_Config.pwm_mode)
	{
	case PWM_NON_INVERTING:
		OCR0=((u16)duty*510)/(200);
		break;

	case PWM_INVERTING:
		OCR0=512-(((u16)duty*510)/(200));
		break;
	}
}


void M_void_Timer_setDelayTimeMilliSec(u16 desired_ms, Timer0_mode_t local_timer_mode)
{
	u32 Timer_freq;
	u32 Tic_time_ns;
	u32 desired_us;
	u32 interrupt_time;
	u16 reminder_on_ocr;
	u16 prescalers_range [5]={1,8,64,256,1024};

	if (delay_func_flag==0)
	{
		M_void_Timer_Stop();

			delay_func_flag=1;

			Timer_freq=CPUCLK/prescalers_range[Prescaler-1];
			Tic_time_ns=(u32)1000000000/Timer_freq;
			desired_us=desired_ms*(u32)1000;

			interrupt_time=(Tic_time_ns*256)/1000;

			desired_count=desired_us/interrupt_time;
			reminder_on_ocr=desired_us%interrupt_time;


			count=0;
			OCR0=reminder_on_ocr;

			M_void_Timer_EnableInt(OV);
			M_void_Timer_EnableInt(OCM);

			M_void_Timer0_Start(Prescaler);
	}
}




ISR(TIMER0_OVF_vect)
{
	//count++;
	PtoFunction_OV();
}

ISR(TIMER0_COMP_vect)
{
	if (delay_func_flag)              //delay function works
	{
		if (count == desired_count)
			{
				delay_func_flag=0;
				PtoFunction_OCM();
			}
	}

	//PtoFunction_OCM();
}


