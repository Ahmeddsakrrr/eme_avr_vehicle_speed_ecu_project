/*
 * adc_interface.h
 *
 * Created: 8/24/2023 11:32:38 AM
 *  Author: Hossam Elwahsh
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "std.h"

extern uint16_t_ uint16_g_last_reading[];

typedef enum
{
    ADC_PS_BY_2     = 2  ,
    ADC_PS_BY_4     = 4  ,
    ADC_PS_BY_8     = 8  ,
    ADC_PS_BY_16    = 16  ,
    ADC_PS_BY_32    = 32  ,
    ADC_PS_BY_64    = 64  ,
    ADC_PS_BY_128   = 128
}en_adc_prescaler_t;

typedef enum
{
    ADC_CH_0 = 0 ,
    ADC_CH_1     ,
    ADC_CH_2     ,
    ADC_CH_3     ,
    ADC_CH_4     ,
    ADC_CH_5     ,
    ADC_CH_6     ,
    ADC_CH_7     ,
    ADC_CH_TOTAL
}en_adc_channel_t;

typedef enum
{
    ADC_VREF_AREF = 0x00,
    ADC_VREF_AVCC = 0x01,
    ADC_VREF_INTERNAL_VREF = 0x03
}en_adc_vref_src_t;

typedef enum
{
    ADC_MODE_POLLING    = 0 ,
    ADC_MODE_INTERRUPT      ,
    ADC_MODE_OFF            ,
    ADC_MODE_TOTAL
}en_adc_mode_t;

typedef enum
{
    ADC_OK = 0      ,
    ADC_ERROR       ,
    ADC_STATUS_TOTAL
}en_adc_status_t;

typedef struct
{
    en_adc_channel_t    en_adc_channel;
    en_adc_mode_t       en_adc_mode;
    en_adc_prescaler_t  en_adc_prescaler;
    en_adc_vref_src_t   en_adc_vref_src;
}st_adc_config_t;

en_adc_status_t adc_init(void);

en_adc_status_t adc_read(en_adc_channel_t en_a_adc_channel);

#endif /* ADC_INTERFACE_H_ */