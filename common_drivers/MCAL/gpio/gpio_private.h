/**
 * @file    :   dio_private.h
 * @author  :   Hossam Elwahsh - https://github.com/HossamElwahsh
 * @brief   :   This file contains all Digital Input Output (DIO) registers' locations.
 * @version :   2.0
 * @date    :   2023-05-29
 *
 * @copyright Copyright (c) 2023
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/* LIB */
#include "bit_math.h"

/* ---------------------- DIO PORTS Registers Locations ---------------------- */

/** PORT A **/
#define DIO_U8_PORT_A_REG   *( ( volatile uint8_t_ * ) 0x3B )
#define DIO_U8_DDR_A_REG    *( ( volatile uint8_t_ * ) 0x3A )
#define DIO_U8_PIN_A_REG    *( ( volatile uint8_t_ * ) 0x39 )

/** PORT B **/
#define DIO_U8_PORT_B_REG   *( ( volatile uint8_t_ * ) 0x38 )
#define DIO_U8_DDR_B_REG    *( ( volatile uint8_t_ * ) 0x37 )
#define DIO_U8_PIN_B_REG    *( ( volatile uint8_t_ * ) 0x36 )

/** PORT C **/
#define DIO_U8_PORT_C_REG   *( ( volatile uint8_t_ * ) 0x35 )
#define DIO_U8_DDR_C_REG    *( ( volatile uint8_t_ * ) 0x34 )
#define DIO_U8_PIN_C_REG    *( ( volatile uint8_t_ * ) 0x33 )

/** PORT D **/
#define DIO_U8_PORT_D_REG   *( ( volatile uint8_t_ * ) 0x32 )
#define DIO_U8_DDR_D_REG    *( ( volatile uint8_t_ * ) 0x31 )
#define DIO_U8_PIN_D_REG    *( ( volatile uint8_t_ * ) 0x30 )

#endif /* DIO_PRIVATE_H_ */