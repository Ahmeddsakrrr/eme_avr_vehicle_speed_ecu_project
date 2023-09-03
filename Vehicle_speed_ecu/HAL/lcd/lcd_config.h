/*
 * 4-Bit mode LCD Interfacing Config File
 * lcd_config.h
 *
 * Created: 18/4/2023 3:45:35 PM
 *  Author: Hossam
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "gpio_interface.h"


/** LCD Data */
/* LCD_DATA_PORT Options
 * PORT_A: 0
 * PORT_B: 1
 * PORT_C: 2
 * PORT_D: 3
 * */
#define LCD_DATA_PORT PORTB_ID

// DATA PINS
#define LCD_DATA_PIN_D4         PIN0_ID
#define LCD_DATA_PIN_D5         PIN1_ID
#define LCD_DATA_PIN_D6         PIN2_ID
#define LCD_DATA_PIN_D7         PIN4_ID
#define LCD_DATA_PINS_MASK      DIO_MASK_BITS_0_1_2_4

/** LCD Control */
/* LCD_CTRL_PORT Options
 * PORT_A: 0
 * PORT_B: 1
 * PORT_C: 2
 * PORT_D: 3
 * */
#define LCD_CTRL_PORT       PORTA_ID
#define LCD_CTRL_PIN_RS     PIN3_ID
#define LCD_CTRL_PIN_RW     PIN1_ID
#define LCD_CTRL_PIN_EN     PIN2_ID


//#define HIGHER_NIBBLE_SHIFT(cmd)    cmd
//#define LOWER_NIBBLE_SHIFT(cmd)     cmd << 4


#endif /* LCD_CONFIG_H_ */