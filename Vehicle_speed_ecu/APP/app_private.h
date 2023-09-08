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
#include "timer_interface.h"
#include "Timers_Services.h"

/* Include MCAL */
#include "spi_interface.h"

/* Helping Macros */
/* Convert char to digit macro */
#define CONVERT_CHAR_TO_DIGIT(kpd_value) (kpd_value - '0')

/* Convert digit to char macro */
#define CONVERT_DIGIT_TO_CHAR(kpd_value) (kpd_value + '0')

/* Communication commands */
#define   APP_COMM_CMD_ACK      1
#define   APP_COMM_CMD_NO_ACK   0

#define   APP_COMM_CMD_START                 5
#define   APP_COMM_CMD_REQUESTING_SPD_LIMIT  10
#define   APP_COMM_CMD_SENDING_SPD_LIMIT     15

/* Memory Addresses */
#define   EEPROM_SPD_ADDRESS    5

#endif /* APP_PRIVATE_H_ */