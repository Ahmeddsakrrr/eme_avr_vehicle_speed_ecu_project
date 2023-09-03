/*
 * Timers_Services.h
 *
 * Created: 8/29/2023 10:33:40 AM
 *  Author: ahmed
 */ 


#ifndef TIMERS_SERVICES_H_
#define TIMERS_SERVICES_H_

#define   OCR2_8FREQ                                  2
#define   OCR2_64TIMER                                4
#define   OCR2_1U_OVERFLOW                            250
#define   LOW                                          0
#define   ONE_TICK                                     1

#define   OVERFLOW_TIME_8PRESCALER                   64
#include "timer.h"
void delay_ms(uint16_t_ time);
void delay_us(uint16_t_ time);


#endif /* TIMERS_SERVICES_H_ */