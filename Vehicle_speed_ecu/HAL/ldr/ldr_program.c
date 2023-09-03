/*
 * ldr.c
 *
 * Created: 8/27/2023 9:21:31 AM
 *  Author: Hossam Elwahsh
 */
#include "ldr_interface.h"

en_ldr_status_t ldr_init()
{
   en_adc_status_t     en_adc_status_l_status = adc_init();
   en_ldr_status_t    en_ldr_status_l_retval = LDR_OK;

    if(ADC_ERROR == en_adc_status_l_status)
    {
        en_ldr_status_l_retval = LDR_ERROR;
    }
    else
    {
        /* Do nothing */
    }

    return en_ldr_status_l_retval;
}

en_ldr_status_t ldr_read(void)
{
    en_ldr_status_t    en_ldr_status_l_retval = LDR_OK;

    if(ADC_OK != adc_read(LDR_ADC_CHANNEL))
    {
        en_ldr_status_l_retval = LDR_ERROR;
    }
    else
    {
        /* Do Nothing */
    }

    return en_ldr_status_l_retval;
}
