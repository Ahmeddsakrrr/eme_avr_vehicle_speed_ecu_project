/*
 * Timers_Services.c
 *
 * Created: 8/29/2023 10:33:08 AM
 *  Author: ahmed
 */ 



#include "mem_map.h"
#include "std.h"
#include "Timers_Services.h"




void delay_ms(uint16_t_ time)
{
	TIMER2_OC_InterruptDisable();
	TIMER2_SET_OCReg(OCR2_1U_OVERFLOW);//overflow every 1m
	Timer2_change(TIMER2_SCALER_64);	
	while(time!=LOW)
	{
		 while(GET_BIT(TIFR,OCF2)==LOW);
		 SET_BIT(TIFR,OCF2);
		 
		 time--;
	}
}





void delay_us(uint16_t_ time)
{
	TIMER2_OC_InterruptDisable();
	
	 if(time <= OVERFLOW_TIME_8PRESCALER)
	 {
		 TIMER2_SET_OCReg(((time * OCR2_8FREQ)-ONE_TICK));
		 Timer2_change(TIMER2_SCALER_8);
		 while(GET_BIT(TIFR,OCF2)==LOW);
		 SET_BIT(TIFR,OCF2);
		
		 
	 }
	 
	 else
	 {
		  TIMER2_SET_OCReg(((time/ OCR2_64TIMER)-ONE_TICK));
		 Timer2_change(TIMER2_SCALER_64);
		 while(GET_BIT(TIFR,OCF2)==LOW);
		  SET_BIT(TIFR,OCF2);
		 
	 }
	
}



