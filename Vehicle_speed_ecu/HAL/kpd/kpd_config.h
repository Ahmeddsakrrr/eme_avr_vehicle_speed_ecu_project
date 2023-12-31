/*
 * kpd_config.c
 *
 * Created: 8/18/2023 2:53:29 PM
 *  Author: Hossam Elwahsh
 */ 

#include "gpio_interface.h"

#ifndef KPD_CONFIG_H
#define KPD_CONFIG_H


#define   KEYPAD_COLUMN_PORT     PORTD_ID
#define   KEYPAD_ROW_PORT        PORTC_ID

#define KEYPAD_DEBOUNCE_DELAY_MS    100
#define KEYPAD_COLS_TOTAL           4
#define KEYPAD_ROWS_TOTAL           4

#endif