/*
 * spi_program.c
 *
 * Created: 1/5/2023 5:18:05 PM
 *  Author: Hossam Elwahsh
 */

#include "spi_interface.h"
#include "spi_private.h"
#include "spi_config.h"

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
    GPIO_setupPinDirection(SPI_PORT, SPI_SS, PIN_OUTPUT);
    GPIO_setupPinDirection(SPI_PORT, SPI_MOSI, PIN_OUTPUT);
    GPIO_setupPinDirection(SPI_PORT, SPI_MISO, PIN_INPUT);

    /* SET slave select pin to high */
    GPIO_writePin(SPI_PORT, SPI_SS, LOGIC_HIGH);

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
    GPIO_writePin(SPI_PORT, SPI_SS, LOGIC_LOW);

#elif SPI_MODE == SPI_MODE_SLAVE
    /* Init SPI port pins */

    GPIO_setupPinDirection(SPI_PORT, SPI_SS, PIN_INPUT);
    GPIO_setupPinDirection(SPI_PORT, SPI_MOSI, PIN_INPUT);
    GPIO_setupPinDirection(SPI_PORT, SPI_MISO, PIN_OUTPUT);

    /* Init SPI slave GPIO Notify pin as OUTPUT */
    GPIO_setupPinDirection(SPI_PORT, SPI_SLAVE_SEND_NOTIFY_PIN, PIN_OUTPUT);

    /* SET SPI mode to slave */
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_MSTR_BIT);

    /* SPI Enable */
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPE_BIT);
#endif

}

/**
 * Receive and Transmit one byte via SPI
 *
 * @param [in]u8_a_byte byte to send
 *
 * @return Received byte
 */
uint8_t_ spi_transceiver(uint8_t_ u8_a_byte)
{
#if SPI_MODE == SPI_MODE_MASTER

    char flush_buffer;
    SPI_U8_SPDR_REG = u8_a_byte;			/* Write data to SPI data register */
    while(!(SPI_U8_SPSR_REG & (1<<SPI_SPSR_SPIF_BIT)));	/* Wait till transmission complete */
    flush_buffer = SPI_U8_SPDR_REG;		/* Flush received data */
/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
    return flush_buffer;

#elif SPI_MODE == SPI_MODE_SLAVE

    SPI_U8_SPDR_REG = u8_a_byte;

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
    GPIO_writePin(SPI_PORT, SPI_SS, LOGIC_HIGH);
    GPIO_writePin(SPI_PORT, SPI_SS, LOGIC_LOW);
}


/**
 * stops SPI communications by setting SS pin to HIGH
 */
void spi_stop()
{
    GPIO_writePin(SPI_PORT, SPI_SS, LOGIC_HIGH);
}