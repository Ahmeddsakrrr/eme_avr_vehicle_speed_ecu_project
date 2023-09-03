#include "gpio.h"
#include "timer.h"

/*************************Pointer to functions to be assigned to ISR*********************************/

static void (*timer1_ovf_fptr) (void)=NULL_PTR;
static void (*timer1_oca_fptr) (void)=NULL_PTR;
static void (*timer1_ocb_fptr) (void)=NULL_PTR;
static void (*timer1_icu_fptr) (void)=NULL_PTR;
/******************************************************************************************/


/*timer 0 functions*/


void timer_Init(en_timer0_mode_t en_timer0_mode_a_mode)
{
	switch (en_timer0_mode_a_mode)
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
void timer0_change(en_timer0_scaler_t en_timer0_scaler_a_scaler)
{
	TCCR0&=0XF8;//0b11111000
	TCCR0|=en_timer0_scaler_a_scaler;
}

void timer0_oc0_mode(en_oc0_mode_t en_oc0_mode_a_mode)
{
	switch (en_oc0_mode_a_mode)
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

void timer0_ov_interrupt_enable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void timer_ov_interrupt_disable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void timer0_oc_interrupt_enable(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void timer0_oc_interrupt_disable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}





/**********************************************Timer 2 functions*******************************************/

void timer2_init(en_timer2_mode_t en_timer2_mode_a_mode)
{
	switch (en_timer2_mode_a_mode)
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
void timer2_change(en_timer2_scaler_t en_timer2_scaler_a_scaler)
{
	TCCR2&=0XF8;//0b11111000
	TCCR2|=en_timer2_scaler_a_scaler;
}
void timer2_oc0_mode(en_oc2_mode_t en_oc2_mode_a_mode)
{
	switch (en_oc2_mode_a_mode)
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


void timer2_ov_enterruptenable(void)
{
	SET_BIT(TIMSK,TOIE2);
}
void timer2_ov_interrupt_disable(void)
{
	CLR_BIT(TIMSK,TOIE2);
}
void timer2_oc_interruptenable(void)
{
	SET_BIT(TIMSK,OCIE2);
}
void timer2_oc_interrupt_disable(void)
{
	CLR_BIT(TIMSK,OCIE2);
}

void timer2_set_oc2_reg(uint8_t_ uint8_a_value)
{
	OCR2=uint8_a_value;
}


/*************************************************************************/
/*timer 1 functions*/
void timer1_init( en_timer1_mode_t  en_timer1_mode_a_mode)
{
	switch (en_timer1_mode_a_mode)
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

void timer1_change(en_timer1_mode_t en_timer1_mode_a_mode)
{
	TCCR1B&=0XF8;
	TCCR1B|=en_timer1_mode_a_mode;
}
void timer1_ocra1_mode(en_timer1_mode_t en_timer1_mode_a_mode)
{
	switch (en_timer1_mode_a_mode)
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
void timer1_ocrb1_mode(en_timer1_mode_t  en_timer1_mode_a_mode)
{
	switch (en_timer1_mode_a_mode)
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
void timer1_input_capture_edge(en_icu_edge_t en_icu_edge_a_edge)
{
	if(en_icu_edge_a_edge==RISING)
	SET_BIT(TCCR1B,ICES1);
	
	else if(en_icu_edge_a_edge==FALLING)
	CLR_BIT(TCCR1B,ICES1);
}



/****************************Timer 1 Interrupt functions**************************************/

void timer1_icu_interrupt_enable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void timer1_icu_interrupt_disable(void)
{
	CLR_BIT(TIMSK,TICIE1);
}
void timer1_ovf_interrupt_enable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void timer1_ovf_interrupt_disable(void)
{
	CLR_BIT(TIMSK,TOIE1);
}
void timer1_oca_interrupt_enable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void timer1_oca_interrupt_disable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}
void timer1_ocb_interrupt_enable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void timer1_ocb_interrupt_disable(void)
{
	CLR_BIT(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void timer1_ovf_set_callback(void(*LocalFptr)(void))
{
	timer1_ovf_fptr=LocalFptr;
}
void timer1_oca_set_callback(void(*LocalFptr)(void))
{
	timer1_oca_fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	timer1_ocb_fptr=LocalFptr;
}
void timer1_icu_set_callback(void(*LocalFptr)(void))
{
	timer1_icu_fptr=LocalFptr;
}

/*********************************Timer 2 ISR functions*********************************************/

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(timer1_ovf_fptr!=NULL_PTR)
	{
		timer1_ovf_fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(timer1_oca_fptr!=NULL_PTR)
	{
		timer1_oca_fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(timer1_ocb_fptr!=NULL_PTR)
	{
		timer1_ocb_fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(timer1_icu_fptr!=NULL_PTR)
	{
		timer1_icu_fptr();
	}
}







