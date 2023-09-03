/*
 * IncFile1.h
 *
 * Created: 8/27/2023 9:21:41 AM
 *  Author: A M
 */ 


#ifndef LDR_H_
#define LDR_H_
#include "ldr_interface.h"
#include "std.h"
#include "adc_interface.h"

#define LDR_ADC_CHANNEL ADC_CH_0

#define CONVERT_ANALOG_TO_PERCENT(analog_signal) (100 - ((analog_signal * 100.0) / 1024))

#define LDR_VALUE    CONVERT_ANALOG_TO_PERCENT(uint16_g_last_reading[LDR_ADC_CHANNEL])

#define LDR_PRESSED_THRESHOLD 30

typedef enum
{
    LDR_OK = 0      ,
    LDR_ERROR,
    LDR_TOTAL
}en_ldr_status_t;

en_ldr_status_t ldr_init();
en_ldr_status_t ldr_read(void);

#endif /* LDR_H_ */