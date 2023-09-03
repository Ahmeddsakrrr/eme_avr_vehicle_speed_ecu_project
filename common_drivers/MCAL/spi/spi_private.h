/*
 * spi_private.h
 *
 * Created: 1/5/2023 8:01:12 PM
 *  Author: Hossam
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#include "bit_math.h"

/** SPI REGISTERS **/
#define SPI_U8_SPDR_REG     *( ( volatile uint8_t_ * ) 0x2F )
#define SPI_U8_SPSR_REG     *( ( volatile uint8_t_ * ) 0x2E )
#define SPI_U8_SPCR_REG     *( ( volatile uint8_t_ * ) 0x2D )

/* SPI status register bits (SPSR) */
/*  SPI Interrupt flag, cleared by first reading from SPDR with this flag raised high */
#define SPI_SPSR_SPIF_BIT   7

/*  SPI write collision flag */
#define SPI_SPSR_WCOL_BIT   6

/*  double SPI Speed flag (HIGH: dbl, LOW: normal) */
#define SPI_SPSR_SPI2X_BIT  0

/* SPI Control register bits (SPCR) */
/*  SPI Interrupt enable bit, needs global interrupt in SREG enabled to work */
#define SPI_SPCR_SPIE_BIT   7
/*  SPI Enable, need to be set to enable any SPI operations */
#define SPI_SPCR_SPE_BIT    6
/*  Data order, (1: LSB transmitted first, 0: MSB transmitted first) */
#define SPI_SPCR_DODR_BIT   5
/*  Master/Slave select, (1: master, 0: slave) */
#define SPI_SPCR_MSTR_BIT   4
/*  Clock polarity */
#define SPI_SPCR_CPOL_BIT   3
/*  Clock phase */
#define SPI_SPCR_CPHA_BIT   2
/*  clock rate select (has no effect on slave) */
#define SPI_SPCR_SPR1_BIT   1
/*  clock rate select (has no effect on slave) */
#define SPI_SPCR_SPR0_BIT   0



#endif /* SPI_PRIVATE_H_ */