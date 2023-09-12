/*
 * app_private.h
 *
 * Created: 9/3/2023 11:54:49 AM
 *  Author: GUCALEX Team
 */ 


#ifndef APP_PRIVATE_H_
#define APP_PRIVATE_H_

/* Includes */

/* Includes HAL */
#include "buzz_interface.h"
#include "KL_switch.h"
#include "kpd_interface.h"
#include "lcd_interface.h"
#include "Led.h"
#include "ldr_interface.h"
#include "throttle.h"
#include "spi_config.h"

/* Include COMMON */
#include "std.h"
#include "bit_math.h"
#include "interrupts.h"
#include "timer_interface.h"
#include "Timers_Services.h"

/* Include MCAL */
#include "spi_interface.h"

/* Helping Macros/Code Beautify */
#define CONVERT_CHAR_TO_DIGIT(kpd_value) (kpd_value - '0')
#define CONVERT_DIGIT_TO_CHAR(kpd_value) (kpd_value + '0')
#define SHOW_TITLE_CENTERED_ON_LCD() lcd_set_cursor(LCD_LINE0, LCD_COL3);\
                            lcd_send_string(APP_STR_TITLE)

#define APP_BUZZ(BUZZ_DURATION) buzz_on();\
                                delay_ms(BUZZ_DURATION);\
                                buzz_off()

#define APP_STR_CLEAR_3_CHARS		((uint8_t_ *)"   ")

/* Returns speed that complies with speed limit if enabled */
#define APP_PARSE_SPEED(speed_val, limit_enabled, max_speed_limit) (limit_enabled == TRUE ? (speed_val > max_speed_limit ? max_speed_limit : speed_val) : (speed_val))
#define APP_PARSE_GEAR(speed_val) (((speed_val * APP_D_GEARS_COUNT / APP_HIGHEST_GEAR_SPEED) + ONE) > APP_D_GEARS_COUNT ? APP_D_GEARS_COUNT : ((speed_val * APP_D_GEARS_COUNT / APP_HIGHEST_GEAR_SPEED) + ONE))

#define APP_UI_SHOW_DASHBOARD()     lcd_set_cursor(LCD_LINE1,LCD_COL0); \
lcd_send_string(APP_STR_L1_DASHBOARD)

#define APP_UI_CLEAR_SPEED()    lcd_set_cursor(LCD_LINE2, LCD_COL14);\
lcd_send_string(APP_STR_CLEAR_3_CHARS)
#define APP_UI_UPDATE_SPEED(speed)   APP_UI_CLEAR_SPEED(); \
lcd_print_number_from_end(speed,APP_STR_SPEED_LCD_POS_ARG)
#define APP_UI_UPDATE_GEAR(gear_char)   lcd_set_cursor(APP_STR_GEAR_LCD_POS_ARG); \
lcd_send_char(gear_char)
#define APP_UI_UPDATE_GEAR_RATIO(gear_ratio) lcd_print_number_from_end(gear_ratio, APP_STR_GEAR_RATIO_LCD_POS_ARG)

/* Communication commands */
#define   APP_COMM_CMD_ACK      1
#define   APP_COMM_CMD_NO_ACK   0

#define   APP_COMM_CMD_START                 5
#define   APP_COMM_CMD_END                   5
#define   APP_COMM_CMD_REQUESTING_SPD_LIMIT  15
#define   APP_COMM_CMD_SENDING_SPD_LIMIT     10
#define   MAXMUM_COUNT                       5
#define   EEPROM_DEFAULT_DATA                0xff

/* Memory Addresses */
#define   EEPROM_SPD_ADDRESS    5

#endif /* APP_PRIVATE_H_ */