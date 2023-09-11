/*
 * adc_program.c
 *
 * Created: 8/24/2023 11:32:31 AM
 *  Author: Hossam Elwahsh
 */ 

#include "adc_interface.h"
#include "adc_private.h"
#include "adc_config.h"

/* Global Variables */
/* ADC Reading */
uint16_t_ uint16_g_last_reading[ADC_IN_USE_CHANNELS] = {0};

/* Private variables */
static boolean init_success = FALSE;

en_adc_status_t adc_init(void)
{
    en_adc_status_t en_adc_status_retval = ADC_OK;
    st_adc_config_t st_l_adc_config;

#ifndef ADC_CPU_FREQ_HZ
    #error MUST SET ADC_CPUT_FREQ_HZ IN ADC_CONFIG.H
    retval = ADC_ERROR;
#else
    /* Disable ADC until config is done */
    CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADEN_BIT);

    /* Validate and Configure ADC */

    /* validate and configure adc channel */
    for (int i = 0; i < ADC_IN_USE_CHANNELS; ++i)
    {
        /* Fetch ADC configuration item */
        st_l_adc_config = st_g_adc_config_arr[i];

        if(ADC_MODE_OFF != st_l_adc_config.en_adc_mode)
        {
            if(
                /* valid channel */
                    (st_l_adc_config.en_adc_channel < ADC_CH_TOTAL) &&

                    /* valid pre-scaler */
                    ((ADC_CPU_FREQ_HZ / st_l_adc_config.en_adc_prescaler) < ADC_MAX_FREQ_HZ))
            {
                /* init ADC channel pin as input */
                GPIO_setupPinDirection(ADC_PORT, st_l_adc_config.en_adc_channel, PIN_INPUT);

                /* SETUP PRESCALER */
                switch (st_l_adc_config.en_adc_prescaler) {

                    case ADC_PS_BY_2:
                    {
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS0_BIT);
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS1_BIT);
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS2_BIT);
                        break;
                    }
                    case ADC_PS_BY_4:
                    {
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS0_BIT);
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS1_BIT);
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS2_BIT);
                        break;
                    }
                    case ADC_PS_BY_8:
                    {
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS0_BIT);
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS1_BIT);
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS2_BIT);
                        break;
                    }
                    case ADC_PS_BY_16:
                    {
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS0_BIT);
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS1_BIT);
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS2_BIT);
                        break;
                    }
                    case ADC_PS_BY_32:
                    {
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS0_BIT);
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS1_BIT);
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS2_BIT);
                        break;
                    }
                    case ADC_PS_BY_64:
                    {
                        CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS0_BIT);
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS1_BIT);
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS2_BIT);
                        break;
                    }
                    case ADC_PS_BY_128:
                    {
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS0_BIT);
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS1_BIT);
                        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADPS2_BIT);
                        break;
                    }
                    default:
                    {
                        en_adc_status_retval = ADC_ERROR;
                        break;
                    }
                }

                /* Setup VREF */
                switch (st_l_adc_config.en_adc_vref_src)
                {
                    case ADC_VREF_AREF:
                    {
                        CLR_BIT(ADC_ADMUX_REG, ADC_ADMUX_REFS0_BIT);
                        CLR_BIT(ADC_ADMUX_REG, ADC_ADMUX_REFS1_BIT);
                        break;
                    }
                    case ADC_VREF_AVCC:
                    {
                        SET_BIT(ADC_ADMUX_REG, ADC_ADMUX_REFS0_BIT);
                        CLR_BIT(ADC_ADMUX_REG, ADC_ADMUX_REFS1_BIT);
                        break;
                    }
                    case ADC_VREF_INTERNAL_VREF:
                    {
                        SET_BIT(ADC_ADMUX_REG, ADC_ADMUX_REFS0_BIT);
                        SET_BIT(ADC_ADMUX_REG, ADC_ADMUX_REFS1_BIT);
                        break;
                    }
                    default:
                    {
                        en_adc_status_retval = ADC_ERROR;
                        break;
                    }
                }

                /* ADC Interrupt */
                if(ADC_MODE_INTERRUPT == st_l_adc_config.en_adc_mode)
                {
                    /* Enable global interrupt */
                    SET_BIT(AVR_SREG_REG, AVR_SREG_GLOBAL_INTERRUPT_ENABLE_BIT);

                    /* Enable ADC interrupt */
                    SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADIE_BIT);
                }
                else
                {
                    /* Disable ADC interrupt */
                    CLR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADIE_BIT);
                }

            }
            else
            {
                en_adc_status_retval = ADC_ERROR;
            }
        }
        else
        {
            /* Skip */
            continue;
        }
    }

    /* Enable ADC */
    if(ADC_OK == en_adc_status_retval)
    {
        /* ENABLE ADC EN BIT */
        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADEN_BIT);

        init_success = TRUE;
    }
    else
    {
        /* empty */
    }

#endif

    return en_adc_status_retval;
}

en_adc_status_t adc_read(en_adc_channel_t en_a_adc_channel)
{
    en_adc_status_t en_adc_status_retval = ADC_OK;

    if(
            (FALSE == init_success) ||                                              /*  ADC not init */
            (en_a_adc_channel >= ADC_IN_USE_CHANNELS) ||                            /*  Invalid channel */
            (ADC_MODE_OFF == st_g_adc_config_arr[en_a_adc_channel].en_adc_mode)     /*  Invalid channel */
    )
    {
        en_adc_status_retval = ADC_ERROR;
    }
    else
    {
        /* update mux value to select proper ADC Channel */

        /* set mux value - bit 0 */
/*         WRITE_BIT(ADC_ADMUX_REG, ADC_ADMUX_MUX0_BIT, GET_BIT(en_a_adc_channel, ADC_ADMUX_MUX0_BIT)); */

        /* set mux value - bit 1 */
/*         WRITE_BIT(ADC_ADMUX_REG, ADC_ADMUX_MUX1_BIT, GET_BIT(en_a_adc_channel, ADC_ADMUX_MUX1_BIT)); */

        /* set mux value - bit 2 */
/*         WRITE_BIT(ADC_ADMUX_REG, ADC_ADMUX_MUX2_BIT, GET_BIT(en_a_adc_channel, ADC_ADMUX_MUX2_BIT)); */

        /* Clear MUX Bits */
        ADC_ADMUX_REG &= 0xE0; /*  clear mux bits */

        /* Set to match required ADC Channel */
        ADC_ADMUX_REG |= (en_a_adc_channel & 0x0F); /*  set to match required ADC channel */


        /* start conversion */
        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADSC_BIT);

        if(ADC_MODE_POLLING == st_g_adc_config_arr[en_a_adc_channel].en_adc_mode)
        {
            /* poll conversion complete */
            while(ZERO == GET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADIF_BIT));

            uint16_g_last_reading[en_a_adc_channel] = ADC_ADCL_REG;
            uint16_g_last_reading[en_a_adc_channel] += ((ADC_ADCH_REG & 0x03) << 8);

            /* Clear interrupt flag by setting it to 1 */
            SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_ADIF_BIT);
        }
        else
        {
            /* Do nothing in interrupt */
        }
    }

    return en_adc_status_retval;
}

ISR(ADC_INT)
{
    /* ADC Read Complete - update last read value */
    uint16_g_last_reading[INT_CHANNEL] = ADC_ADCL_REG;
    uint16_g_last_reading[INT_CHANNEL] += ((ADC_ADCH_REG & 0x03) << 8);
}
