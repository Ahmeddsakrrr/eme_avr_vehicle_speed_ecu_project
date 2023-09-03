/*
 * Led.h
 *
 *  Created on: Jan 28, 2023
 *      Author: ahmad
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "Led_Cfg.h"

typedef enum {
    LED_OFF,
    LED_ON
} Led_StatusType;

void Led_Init(uint8_t_ port, uint8_t_ pin);
void Led_TurnOn (uint8_t_ port, uint8_t_ pin);
void Led_TurnOff (uint8_t_ port, uint8_t_ pin);
void Led_Flip (uint8_t_ port, uint8_t_ pin);
Led_StatusType Led_GetStatus (uint8_t_ port, uint8_t_ pin);



#endif /* INC_LED_H_ */
