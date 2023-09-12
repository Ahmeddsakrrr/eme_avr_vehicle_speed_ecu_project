/*
 * throttle.c
 *
 * Created: 9/4/2023 6:57:09 PM
 *  Author: Sakr
 */ 
#include "throttle.h"
/*global variable used for measuring the readings of the throttle pedal */
uint16_t_ throttle_readings;


/* Minimum ADC Reading */
#define THROTTLE_MIN_ADC_VAL        (450)

/* Maximum ADC Reading */
#define THROTTLE_MAX_ADC_VAL        (4200)

/* Max user throttle value to map readings to it */
#define THROTTLE_MAX_SPEED_MAPPING  (220)

/* Maps a value to a different linear scale */
#define MAP_VALUE(value, max_val, max_desired_output) ((value * max_desired_output) / max_val)

#define THROTTLE_ADC_READING ((uint32_t_)uint16_g_last_reading[THROTTLE_ADC_CHANNEL]*5000/1024)

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

    adc_read(THROTTLE_ADC_CHANNEL);

    if(THROTTLE_ADC_READING < THROTTLE_MIN_ADC_VAL)
    {
        /* output Zero */
        throttle_readings = ZERO;
    }
    else if(THROTTLE_ADC_READING > THROTTLE_MAX_ADC_VAL)
    {
        /* output max throttle value */
        throttle_readings = THROTTLE_MAX_SPEED_MAPPING;
    }
    else
    {
        /* ADC value in range - process and map it accordingly */
        throttle_readings = MAP_VALUE((THROTTLE_ADC_READING - THROTTLE_MIN_ADC_VAL), THROTTLE_MAX_ADC_VAL, THROTTLE_MAX_SPEED_MAPPING);
    }

    return throttle_readings;
}