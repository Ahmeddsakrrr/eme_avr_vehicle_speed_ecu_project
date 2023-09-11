/*
 * adc_lconfig.c
 *
 * Created: 8/24/2023 2:22:04 PM
 *  Author: Hossam Elwahsh
 */ 
#include "adc_interface.h"
#include "adc_config.h"

st_adc_config_t st_g_adc_config_arr[ADC_IN_USE_CHANNELS] =
{
        {ADC_CH_0, ADC_MODE_POLLING, ADC_PS_BY_128, ADC_VREF_AVCC},
        {ADC_CH_1, ADC_MODE_POLLING, ADC_PS_BY_128, ADC_VREF_AVCC},
        {ADC_CH_2, ADC_MODE_OFF, ADC_PS_BY_128, ADC_VREF_AVCC},
        {ADC_CH_3, ADC_MODE_OFF, ADC_PS_BY_128, ADC_VREF_AVCC},
        {ADC_CH_4, ADC_MODE_OFF, ADC_PS_BY_128, ADC_VREF_AVCC},
        {ADC_CH_5, ADC_MODE_OFF, ADC_PS_BY_128, ADC_VREF_AVCC},
        {ADC_CH_6, ADC_MODE_OFF, ADC_PS_BY_128, ADC_VREF_AVCC},
		{ADC_CH_7, ADC_MODE_POLLING, ADC_PS_BY_128, ADC_VREF_AVCC}
};
