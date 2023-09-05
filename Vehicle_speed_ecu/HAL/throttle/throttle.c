/*
 * throttle.c
 *
 * Created: 9/4/2023 6:57:09 PM
 *  Author: Sakr
 */ 
#include "throttle.h"

en_throttle_t throttle_init(){
    en_adc_status_t ADC_status = adc_init();
    en_throttle_t intial;

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

    adc_read(ADC_CH_2);

    if(uint16_g_last_reading[ADC_CH_2]>=0 &&uint16_g_last_reading[ADC_CH_2]<=150)
    {
        throttle_readings=0;
    }

    else if(uint16_g_last_reading[ADC_CH_2]>=700 && uint16_g_last_reading[ADC_CH_2]<=944 )
    {
        throttle_readings=500;
    }

}