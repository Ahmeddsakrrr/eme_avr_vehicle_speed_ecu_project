/*
 * spi_interface.h
 *
 * Created: 1/5/2023 5:18:17 PM
 *  Author: Hossam Elwahsh
 */


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "spi_config.h"

/**
 * Initializes SPI protocol
 */
void spi_init();


/**
 * Receive and Transmit one byte via SPI
 *
 * @param [in]u8_a_byte byte to send
 *
 * @return Received byte
 */
uint8_t_ spi_transceiver(uint8_t_ u8Ptr_a_byte);

/**
 * Syncs and restarts SPI communications between Master and Slave by setting SS pin High then Low again
 */
void spi_restart();

/**
 * stops SPI communications by setting SS pin to HIGH
 */
void spi_stop();

#endif /* SPI_INTERFACE_H_ */