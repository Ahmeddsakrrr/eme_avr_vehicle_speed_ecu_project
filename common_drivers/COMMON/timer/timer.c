#include "gpio_interface.h"
#include "timer.h"

/*************************Pointer to functions to be assigned to ISR*********************************/

static void (*Timer1_OVF_Fptr) (void)=NULL_PTR;
static void (*Timer1_OCA_Fptr) (void)=NULL_PTR;
static void (*Timer1_OCB_Fptr) (void)=NULL_PTR;
static void (*Timer1_ICU_Fptr) (void)=NULL_PTR;
/******************************************************************************************/


/*timer 0 functions*/


void TIMER0_Init(Timer0Mode_type mode)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	
}
void Timer0_change(Timer0Scaler_type scaler)
{
	TCCR0&=0XF8;/* 0b11111000 */
	TCCR0|=scaler;
}

void TIMER0_OC0Mode(OC0Mode_type mode)
{
	switch (mode)
	{
		case OC0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OC0_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}

void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}





/**********************************************Timer 2 functions*******************************************/

void TIMER2_Init(Timer2Mode_type mode)
{
	switch (mode)
	{
		case TIMER2_NORMAL_MODE:
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		case TIMER2_PHASECORRECT_MODE:
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		case TIMER2_CTC_MODE:
		CLR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
		case TIMER2_FASTPWM_MODE:
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
	}
}
void Timer2_change(Timer2Scaler_type scaler)
{
	TCCR2&=0XF8;/* 0b11111000 */
	TCCR2|=scaler;
}
void TIMER2_OC0Mode(OC2Mode_type mode)
{
	switch (mode)
	{
		case OC2_DISCONNECTED:
		CLR_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		case OC2_TOGGLE:
		SET_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		case OC2_NON_INVERTING:
		CLR_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
		case OC2_INVERTING:
		SET_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
	}
}


void TIMER2_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE2);
}
void TIMER2_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE2);
}
void TIMER2_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE2);
}
void TIMER2_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE2);
}

void TIMER2_SET_OCReg(uint8_t_ oc_value)
{
	OCR2=oc_value;
}


/*************************************************************************/
/*timer 1 functions*/
void Timer1_Init( Timer1Mode_type mode)
{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_8_BIT:
		
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
	}

	

}

void Timer1_change(Timer1Scaler_type scaler)
{
	TCCR1B&=0XF8;
	TCCR1B|=scaler;
}
void Timer1_OCRA1Mode(OC1A_Mode_type oc1a_mode)
{
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
void Timer1_OCRB1Mode(OC1B_Mode_type oc1b_mode)
{
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	SET_BIT(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	CLR_BIT(TCCR1B,ICES1);
}



/****************************Timer 1 Interrupt functions**************************************/

void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

/*********************************Timer 2 ISR functions*********************************************/

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULL_PTR)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_Fptr!=NULL_PTR)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_Fptr!=NULL_PTR)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_Fptr!=NULL_PTR)
	{
		Timer1_ICU_Fptr();
	}
}







