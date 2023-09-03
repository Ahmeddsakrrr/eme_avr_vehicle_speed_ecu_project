/*
 * Led.c
 *
 *  Created on: Jan 28, 2023
 *      Author: ahmad
 */

#include "std.h"
#include "gpio.h"
#include "Led.h"
#include "bit_math.h"


void Led_Init(uint8_t_ port, uint8_t_ pin) {
    GPIO_setupPinDirection(port, pin, PIN_OUTPUT);
}

void Led_TurnOn (uint8_t_ port, uint8_t_ pin) {
    GPIO_writePin(port, pin, LOGIC_HIGH);
}

void Led_TurnOff (uint8_t_ port, uint8_t_ pin) {
        GPIO_writePin(port, pin, LOGIC_LOW);
}

Led_StatusType Led_GetStatus (uint8_t_ port, uint8_t_ pin)
{
    Led_StatusType state = LED_OFF;
    if (GPIO_readPin(port, pin) == LOGIC_HIGH)
    {
        state = LED_ON;
    }
    return state;
}

void Led_Flip (uint8_t_ port, uint8_t_ pin)
{
    GPIO_togglePin(port, pin);
}
