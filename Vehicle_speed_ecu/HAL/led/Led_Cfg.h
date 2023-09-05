/*
 * Led_Cfg.h
 *
 *  Created on: Jan 28, 2023
 *      Author: ahmad sakr
 */

#ifndef INC_LED_CFG_H_
#define INC_LED_CFG_H_

#include "gpio_interface.h"

/************************* USER CONFIGURATIONS *************************/
#define LED_ON_VOLTAGE      LOGIC_HIGH

#define LED_RED_ARGS        PORTB_ID,PIN7_ID
#define LED_RED_PIN         PIN7_ID
#define LED_RED_PORT        PORTB_ID

#define LED_GREEN_ARGS      PORTA_ID,PIN4_ID
#define LED_GREEN_PIN       PIN4_ID
#define LED_GREEN_PORT      PORTA_ID

#define LED_BLUE_ARGS       PORTA_ID,PIN5_ID
#define LED_BLUE_PIN        PIN5_ID
#define LED_BLUE_PORT       PORTA_ID

#define LED_YELLOW_ARGS     PORTA_ID,PIN6_ID
#define LED_YELLOW_PORT     PORTA_ID
#define LED_YELLOW_PIN      PIN6_ID

/********************** END OF USER CONFIGURATIONS **********************/

#endif /* INC_LED_CFG_H_ */
