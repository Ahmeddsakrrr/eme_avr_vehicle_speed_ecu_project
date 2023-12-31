/*
 * spi_config.h
 *
 * Created: 1/5/2023 5:18:24 PM
 *  Author: Hossam Elwahsh
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "gpio_interface.h"

/******* MACRO HELPERS ********/
#define SPI_U8_DUMMY_VAL 0xFF

/******* AVAILABLE OPTIONS ********/
/* SPI MODES (OPTIONS) */
#define SPI_MODE_MASTER 1
#define SPI_MODE_SLAVE  0

/* SPI CLOCK (OPTIONS) */
#define SPI_CLOCK_FOSC_2    2
#define SPI_CLOCK_FOSC_4    4
#define SPI_CLOCK_FOSC_8    8
#define SPI_CLOCK_FOSC_16   16
#define SPI_CLOCK_FOSC_32   32
#define SPI_CLOCK_FOSC_64   64
#define SPI_CLOCK_FOSC_128  128

/* COMMUNICATION DATA ORDER (OPTIONS) */
#define SPI_DORD_MSB_FIRST 0
#define SPI_DORD_LSB_FIRST 1

/******* CONFIGURATIONS ********/
/* PORT and PINS */
#define SPI_PORT    PORTB_ID
#define SPI_SS      PIN4_ID
#define SPI_MOSI    PIN5_ID
#define SPI_MISO    PIN6_ID
#define SPI_SCK     PIN7_ID

/* MASTER / SLAVE TRIGGERS */

#define MASTER_REQ_RECEIVE_INT      EXI_U8_INT0
#define MASTER_REQ_RECEIVE_SENSE    EXI_U8_SENSE_FALLING_EDGE

/*  GPIO pin for slave mode to notify master to receive next data from slave */
#define SPI_SLAVE_SEND_NOTIFY_PIN PIN0_ID

/* Helping Bundled PINs Masks */
/*  pins that are always OUTPUT for master mode */
#define SPI_MASTER_OUT_PINS     DIO_MASK_BITS_4_5_7
/*  pins that are always INPUT for slave mode */
#define SPI_SLAVE_IN_PINS       DIO_MASK_BITS_4_5_7

/*  SPI Data Order */
#define SPI_DORD SPI_DORD_MSB_FIRST

/*  SPI MODE */
/* #define SPI_MODE    SPI_MODE_MASTER */
#define SPI_MODE  SPI_MODE_SLAVE

/*  Clock */
#define SPI_CLOCK SPI_CLOCK_FOSC_16


#endif /* SPI_CONFIG_H_ */