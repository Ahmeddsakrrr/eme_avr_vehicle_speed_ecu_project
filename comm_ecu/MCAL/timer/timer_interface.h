

#ifndef TIMERS_H_
#define TIMERS_H_

#include "std.h"
#include "bit_math.h"
#include "mem_map.h"


typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}en_timer0_scaler_t;

#define TIMER1_START()    timer1_change(TIMER1_SCALER_256);
#define TIMER1_STOP()     timer1_change(TIMER1_STOP);

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}en_timer0_mode_t;


typedef enum
{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING

}en_oc0_mode_t;

void timer_Init(en_timer0_mode_t en_timer0_mode_a_mode);
void timer0_change(en_timer0_scaler_t en_timer0_scaler_a_scaler);
void timer0_oc0_mode(en_oc0_mode_t en_oc0_mode_a_mode);
void timer0_ov_interrupt_enable(void);
void timer_ov_interrupt_disable(void);
void timer0_oc_interrupt_enable(void);
void timer0_oc_interrupt_disable(void);
void timer0_ov_set_callback(void(*local_fptr)(void));



/************************************************ Timer2*********************************************************/


typedef enum{
	TIMER2_STOP=0,
	TIMER2_SCALER_1,
	TIMER2_SCALER_8,
	TIMER2_SCALER_32,
	TIMER2_SCALER_64,
	TIMER2_SCALER_128,
	TIMER2_SCALER_256,
	TIMER2_SCALER_1024,
	
}en_timer2_scaler_t;


typedef enum
{
	TIMER2_NORMAL_MODE=0,
	TIMER2_PHASECORRECT_MODE,
	TIMER2_CTC_MODE,
	TIMER2_FASTPWM_MODE

}en_timer2_mode_t;


typedef enum
{
	OC2_DISCONNECTED=0,
	OC2_TOGGLE,
	OC2_NON_INVERTING,
	OC2_INVERTING

}en_oc2_mode_t;


void timer2_init(en_timer2_mode_t en_timer2_mode_a_mode);
void timer2_change(en_timer2_scaler_t en_timer2_scaler_a_scaler);
void timer2_oc0_mode(en_oc2_mode_t en_oc2_mode_a_mode);
void timer2_ov_enterruptenable(void);
void timer2_ov_interrupt_disable(void);
void timer2_oc_interruptenable(void);
void timer2_oc_interrupt_disable(void);
void timer2_set_oc2_reg(uint8_t_ uint8_a_value);


/*********************************************************************************************************/

typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}en_timer1_scaler_t;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE,
	TIMER1_FASTPWM_8_BIT

}en_timer1_mode_t;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}en_oc1a_mode_t;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}en_oc1b_mode_t;


typedef enum{
	RISING,
	FALLING

}en_icu_edge_t;



void timer1_input_capture_edge(en_icu_edge_t en_icu_edge_a_edge);
void timer1_init( en_timer1_mode_t  en_timer1_mode_a_mode);
void timer1_ocra1_mode(en_timer1_mode_t en_timer1_mode_a_mode);
void timer1_ocrb1_mode(en_timer1_mode_t  en_timer1_mode_a_mode);
void timer1_change(en_timer1_mode_t en_timer1_mode_a_mode);

void timer1_icu_interrupt_enable(void);
void timer1_icu_interrupt_disable(void);

void timer1_ovf_interrupt_enable(void);
void timer1_ovf_interrupt_disable(void);

void timer1_oca_interrupt_enable(void);
void timer1_oca_interrupt_disable(void);

void timer1_ocb_interrupt_disable(void);
void timer1_ocb_interrupt_enable(void);

void timer1_ovf_set_callback(void(*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void));
void timer1_oca_set_callback(void(*LocalFptr)(void));
void timer1_icu_set_callback(void(*LocalFptr)(void));



#endif /* TIMERS_H_ */