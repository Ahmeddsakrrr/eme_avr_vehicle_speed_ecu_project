/*
 * throttle.h
 *
 * Created: 9/4/2023 6:56:57 PM
 *  Author: sakr
 */ 


#ifndef THROTTLEE_H_
#define THROTTLEE_H_

#include "adc_interface.h"

#define THROTTLE_ADC_CHANNEL ADC_CH_7
extern uint16_t_ throttle_readings;

typedef enum
{
    THROTTLE_OK = 0,
    THROTTLE_ERROR,
    THROTTLE_TOTAL
}en_throttle_t;

en_throttle_t throttle_init();
uint16_t_ throttle_read_state(void);

#endif /* THROTTLEE_H_ */