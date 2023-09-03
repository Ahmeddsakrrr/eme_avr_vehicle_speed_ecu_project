


#include "buzz_interface.h"

void buzz_init(void)
{
	GPIO_setupPinDirection(BUZZ_PORT , BUZZ_PIN ,PIN_OUTPUT);
}

void buzz_on(void)
{
	 GPIO_writePin(BUZZ_PORT,  BUZZ_PIN, PIN_OUTPUT);
}

void buzz_off(void)
{
	GPIO_writePin(BUZZ_PORT,  BUZZ_PIN, LOGIC_LOW);
}