/*
 * comm_ecu.c
 *
 * Created: 9/3/2023 11:40:20 AM
 * Author : GUCALEX Team
 */ 



#include "mem_map.h"
#include "std.h"
#include "spi_interface.h"
#include "i2c_config.h"
#include "eeprom.h"
#include "app_private.h"
#include "app_config.h"
#include "app_interface.h"

int main(void)
{
     app_init();
     app_start();
}

