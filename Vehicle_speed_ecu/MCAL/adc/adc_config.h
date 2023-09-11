/*
 * adc_config.h
 *
 * Created: 8/24/2023 11:46:31 AM
 *  Author: Hossam Elwahsh
 */ 


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


#define ADC_CPU_FREQ_HZ         16000000UL  /*  16   MHz */
#define ADC_MAX_FREQ_HZ         200000      /*  200  KHz */
#define ADC_PORT                PORTA_ID

#define ADC_IN_USE_CHANNELS     8

/* Channel reading updated from ISR */
#define INT_CHANNEL ADC_CH_1

extern st_adc_config_t st_g_adc_config_arr[ADC_IN_USE_CHANNELS];

#endif /* ADC_CONFIG_H_ */