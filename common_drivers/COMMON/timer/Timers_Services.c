/*
 * Timers_Services.c
 *
 * Created: 8/29/2023 10:33:08 AM
 *  Author: ahmed
 */ 



#include "mem_map.h"
#include "std.h"
#include "Timers_Services.h"




void delay_ms(uint16_t_ uint16_a_time)
{
	timer2_oc_interrupt_disable();
	timer2_set_oc2_reg(OCR2_1U_OVERFLOW);//overflow every 1m
	timer2_change(TIMER2_SCALER_64);	
	while(uint16_a_time!=LOW)
	{
		 while(GET_BIT(TIFR,OCF2)==LOW);
		 SET_BIT(TIFR,OCF2);
		 
		 timer2_change--;
	}
}





void delay_us(uint16_t_ uint16_a_time)
{
	timer2_oc_interrupt_disable();
	
	 if(uint16_a_time <= OVERFLOW_TIME_8PRESCALER)
	 {
		timer2_set_oc2_reg(((time * OCR2_8FREQ)-ONE_TICK));
		 timer2_change(TIMER2_SCALER_8);
		 while(GET_BIT(TIFR,OCF2)==LOW);
		 SET_BIT(TIFR,OCF2);
		
		 
	 }
	 
	 else
	 {
		  timer2_set_oc2_reg(((time/ OCR2_64TIMER)-ONE_TICK));
		 timer2_change(TIMER2_SCALER_64);
		 while(GET_BIT(TIFR,OCF2)==LOW);
		  SET_BIT(TIFR,OCF2);
		 
	 }
	
}



