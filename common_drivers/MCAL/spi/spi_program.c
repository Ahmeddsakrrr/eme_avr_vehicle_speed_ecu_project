/*
 * spi_program.c
 *
 * Created: 1/5/2023 5:18:05 PM
 *  Author: Hossam Elwahsh
 */

#include "spi_interface.h"
#include "spi_private.h"

/**
 * Initializes SPI protocol
 */
void spi_init()
{
    /* Set SPI data order */
    WRITE_BIT(SPI_U8_SPCR_REG, SPI_SPCR_DODR_BIT, SPI_DORD);

    /* Init SPI Pins */
#if SPI_MODE == SPI_MODE_MASTER
    /* Init SPI port pins */
    DIO_init(SPI_MISO, SPI_PORT, DIO_IN);
    DIO_portInit(SPI_PORT, DIO_PORT_OUT, SPI_MASTER_OUT_PINS);

    /* SET slave select pin to high */
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_HIGH);

//    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_CPHA_BIT);

    /* Init SPI Clock Speed in master only */
    //region Init Clock Speed
#if SPI_CLOCK == SPI_CLOCK_FOSC_4
    // disable speed doubler
    CLR_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_16
    // disable speed doubler
    CLR_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_64
    // disable speed doubler
    CLR_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_128
    // disable speed doubler
    CLR_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_2
    // enable speed doubler
    SET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_8
    // enable speed doubler
    SET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_32
    // enable speed doubler
    SET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#endif
    //endregion

    /* SET SPI mode to master */
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_MSTR_BIT);

    /* SPI Enable */
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPE_BIT);

    /* SET slave select pin to low to start communications */
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_LOW);

#elif SPI_MODE == SPI_MODE_SLAVE
    /* Init SPI port pins */
    DIO_portInit(SPI_PORT, DIO_PORT_IN, SPI_SLAVE_IN_PINS);
    DIO_init(SPI_MISO, SPI_PORT, DIO_OUT);

    DIO_portInit(SPI_PORT, DIO_PORT_IN, SPI_SLAVE_IN_PINS);
    DIO_init(SPI_MISO, SPI_PORT, DIO_OUT);

    /* Init SPI slave GPIO Notify pin as OUTPUT */
    DIO_init(SPI_SLAVE_SEND_NOTIFY_PIN, SPI_PORT, DIO_OUT);

    /* SET SPI mode to slave */
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_MSTR_BIT);

    /* SPI Enable */
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPE_BIT);
#endif

}

/**
 * Receive and Transmit one byte via SPI
 *
 * @param [in]u8Ptr_a_byte byte to send
 *
 * @return Received byte
 */
uint8_t_ spi_transceiver(uint8_t_ u8Ptr_a_byte)
{
#if SPI_MODE == SPI_MODE_MASTER

    char flush_buffer;
    SPI_U8_SPDR_REG = u8_a_byte;			/* Write data to SPI data register */
    while(!(SPI_U8_SPSR_REG & (1<<SPI_SPSR_SPIF_BIT)));	/* Wait till transmission complete */
    flush_buffer = SPI_U8_SPDR_REG;		/* Flush received data */
/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
    return flush_buffer;

#elif SPI_MODE == SPI_MODE_SLAVE

    SPI_U8_SPDR_REG = u8Ptr_a_byte;

    while(!GET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPIF_BIT));

    uint8_t_ u8_l_receivedByte = SPI_U8_SPDR_REG;

    return u8_l_receivedByte;
#endif
}

/**
 * Syncs and restarts SPI communications between Master and Slave by setting SS pin High then Low again
 */
void spi_restart()
{
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_HIGH);
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_LOW);
}


/**
 * stops SPI communications by setting SS pin to HIGH
 */
void spi_stop()
{
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_HIGH);
}