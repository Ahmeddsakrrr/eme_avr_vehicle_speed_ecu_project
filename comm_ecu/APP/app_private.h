/*
 * app_private.h
 *
 * Created: 9/3/2023 11:54:49 AM
 *  Author: GUCALEX Team
 */ 


#ifndef APP_PRIVATE_H_
#define APP_PRIVATE_H_

/* Includes */

/* Includes */
#include "Led.h"
/* HAL Includes */
#include "eeprom.h"

/* COMMON Includes */
#include "spi_interface.h"
#include "spi_private.h"
#include "spi_config.h"

/* Communication commands */
#define   APP_COMM_CMD_ACK                      1
#define   APP_COMM_CMD_NO_ACK                   0
#define   APP_COMM_CMD_START                    5
#define   APP_COMM_CMD_END                      5
#define   APP_COMM_CMD_REQUESTING_SPEED_LIMIT   10
#define   APP_COMM_CMD_SENDING_SPDEED_LIMIT     15

/* Memory Addresses */
#define   EEPROM_SPD_ADDRESS   (uint16_t_)     5


#endif /* APP_PRIVATE_H_ */