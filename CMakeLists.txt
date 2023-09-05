cmake_minimum_required(VERSION 3.26)
project(Vehicle_speed_ecu C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(comm_ecu/APP)
include_directories(common_drivers/COMMON)
include_directories(common_drivers/COMMON/timer)
include_directories(common_drivers/MCAL/spi)
include_directories(common_drivers/MCAL/gpio)
include_directories(Vehicle_speed_ecu/APP)
include_directories(Vehicle_speed_ecu/HAL/buzz)
include_directories(Vehicle_speed_ecu/HAL/kl15)
include_directories(Vehicle_speed_ecu/HAL/kpd)
include_directories(Vehicle_speed_ecu/HAL/lcd)
include_directories(Vehicle_speed_ecu/HAL/ldr)
include_directories(Vehicle_speed_ecu/HAL/led)
include_directories(Vehicle_speed_ecu/MCAL/adc)
include_directories(Vehicle_speed_ecu/MCAL/gpio)
include_directories("C:/Users/A M/eme_avr_vehicle_speed_ecu_project/Vehicle_speed_ecu/HAL/throttle/")


add_executable(Vehicle_speed_ecu
        comm_ecu/APP/app_config.h
        comm_ecu/APP/app_interface.h
        comm_ecu/APP/app_private.h
        comm_ecu/APP/app_program.c
        common_drivers/COMMON/timer/timer.c
        common_drivers/COMMON/timer/timer.h
        common_drivers/COMMON/timer/Timers_Services.c
        common_drivers/COMMON/timer/Timers_Services.h
        common_drivers/COMMON/bit_math.h
        common_drivers/COMMON/interrupts.h
        common_drivers/COMMON/mem_map.h
        common_drivers/COMMON/std.h
        common_drivers/MCAL/spi/spi_config.h
        common_drivers/MCAL/spi/spi_interface.h
        common_drivers/MCAL/spi/spi_private.h
        common_drivers/MCAL/spi/spi_program.c
        Vehicle_speed_ecu/APP/app_config.h
        Vehicle_speed_ecu/APP/app_interface.h
        Vehicle_speed_ecu/APP/app_private.h
        Vehicle_speed_ecu/APP/app_program.c
        Vehicle_speed_ecu/HAL/buzz/buzz_interface.h
        Vehicle_speed_ecu/HAL/buzz/buzz_program.c
        Vehicle_speed_ecu/HAL/kl15/KL_switch.c
        Vehicle_speed_ecu/HAL/kl15/KL_switch.h
        Vehicle_speed_ecu/HAL/kpd/kpd_config.h
        Vehicle_speed_ecu/HAL/kpd/kpd_interface.h
        Vehicle_speed_ecu/HAL/kpd/kpd_program.c
        Vehicle_speed_ecu/HAL/lcd/lcd_config.h
        Vehicle_speed_ecu/HAL/lcd/lcd_interface.h
        Vehicle_speed_ecu/HAL/lcd/lcd_private.h
        Vehicle_speed_ecu/HAL/lcd/lcd_program.c
        Vehicle_speed_ecu/HAL/ldr/ldr_interface.h
        Vehicle_speed_ecu/HAL/ldr/ldr_program.c
        Vehicle_speed_ecu/HAL/led/Led.c
        Vehicle_speed_ecu/HAL/led/Led.h
        Vehicle_speed_ecu/HAL/led/Led_Cfg.h
        Vehicle_speed_ecu/MCAL/adc/adc_config.h
        Vehicle_speed_ecu/MCAL/adc/adc_interface.h
        Vehicle_speed_ecu/MCAL/adc/adc_lconfig.c
        Vehicle_speed_ecu/MCAL/adc/adc_private.h
        Vehicle_speed_ecu/MCAL/adc/adc_program.c
        common_drivers/MCAL/gpio/gpio_program.c
        common_drivers/MCAL/gpio/gpio_interface.h
        common_drivers/MCAL/gpio/gpio_private.h
        Vehicle_speed_ecu/main.c
        Vehicle_speed_ecu/MCAL/i2c/i2c_private.h
        Vehicle_speed_ecu/HAL/throttle/throttle.c
        Vehicle_speed_ecu/HAL/throttle/throttle.c
        Vehicle_speed_ecu/HAL/throttle/throttle.c
        Vehicle_speed_ecu/HAL/throttle/throttle.h
        Vehicle_speed_ecu/HAL/throttle/throttle.h
        "C:/Users/A M/eme_avr_vehicle_speed_ecu_project/Vehicle_speed_ecu/HAL/throttle/throttle.h"
        Vehicle_speed_ecu/HAL/throttle/throttle.h
        Vehicle_speed_ecu/HAL/throttlee/throttlee.c
        Vehicle_speed_ecu/HAL/throttlee/throttlee.c

)
