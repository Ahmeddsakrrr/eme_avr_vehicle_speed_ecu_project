/*
 * throttle.c
 *
 * Created: 9/4/2023 6:57:09 PM
 *  Author: Sakr
 */ 
#include "throttle.h"
/*global variable used for measuring the readings of the padel*/
uint16_t_ throttle_readings;

en_throttle_t throttle_init(){
    en_adc_status_t ADC_status = adc_init();
    en_throttle_t intial = THROTTLE_OK;

    if(ADC_STATUS_TOTAL <= ADC_status)
    {
		intial = THROTTLE_ERROR;
    }
    else
    {
        if(ADC_OK==ADC_status)
        {
            intial = THROTTLE_OK;
        }
        else if(ADC_ERROR == ADC_status)
        {
            intial=THROTTLE_ERROR;
        }
    }
    return intial;
}
uint16_t_ throttle_read_state(void){

    adc_read(ADC_CH_0);

    if(((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024) >= 0 && ((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)<=400)
    {
        throttle_readings=0;
    }

    else if(((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)>=450 && ((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)<=700 )
    {
        throttle_readings=30;
    }
    else if(((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)>=800 && ((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)<=1200 )
    {
    throttle_readings=40;
    }

    else if(((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)>=1600 && ((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)<=2000 )
    {
        throttle_readings=60;
    }

    else if(((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)>=2100 && ((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)<=3200)
    {
        throttle_readings=80;
    }

    else if(((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)>=3300 && ((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)<=3800 )
    {
        throttle_readings=100;
    }
    else if(((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)>=3900 && ((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024)<=4200 )
    {
        throttle_readings=150;
    }
    else if (((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024) >= 4200)
    {
        throttle_readings=200;
    }
    return throttle_readings;
}