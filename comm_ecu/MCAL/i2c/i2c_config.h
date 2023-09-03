/*
 * I2c.h
 *
 *  Created on: Apr 30, 2023
 *      Author: A M
 */

#ifndef I2C_H_
#define I2C_H_



#endif /* I2C_H_ */
/*
 * I2c.h
 *
 *  Created on: Mar 18, 2023
 *      Author: Sakr
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "std.h"
#include "bit_math.h"

typedef enum
{

    /************************************************************************
     * Master Status
     ***********************************************************************/

    /* A START condition has been transmitted */
    I2C_STATUS_MASTER_START_SENT = 0x08,

    /* A repeated START condition has been transmitted */
    I2C_STATUS_MASTER_REP_START_SENT = 0x10,

    /* SLA+W has been transmitted; ACK has been received */
    I2C_STATUS_MASTER_SA_W_ACK = 0x18,

    /* SLA+W has been transmitted; NOT ACK has been received */
    I2C_STATUS_MASTER_SA_W_NACK = 0x20,

    /* SLA+R has been transmitted; ACK has been received */
    I2C_STATUS_MASTER_SA_R_ACK = 0x40,

    /* SLA+R has been transmitted; NOT ACK has been received */
    I2C_STATUS_MASTER_SA_R_NACK = 0x48,

    /* Data byte has been transmitted; ACK has been received */
    I2C_STATUS_MASTER_DATA_SENT_ACK = 0x28,

    /* Data byte has been transmitted; NOT ACK has been received */
    I2C_STATUS_MASTER_DATA_SENT_NACK = 0x30,

    /* Data byte has been received; ACK has been returned */
    I2C_STATUS_MASTER_DATA_RECEIVED_ACK = 0x50,

    /* Data byte has been received; NOT ACK has been returned */
    I2C_STATUS_MASTER_DATA_RECEIVED_NACK = 0x58,

    /* Arbitration lost */
    I2C_STATUS_MASTER_ARBITRATION_LOST = 0x38,

    /************************************************************************
     * Slave Status
     ***********************************************************************/

    /* Own SLA+W has been received; ACK has been returned */
    I2C_STATUS_SLAVE_SA_W_RECEIVED = 0x60,

    /* Own SLA+R has been received; ACK has been returned */
    I2C_STATUS_SLAVE_SA_R_RECEIVED = 0xA8,

    /* General call address has been received; ACK has been returned */
    I2C_STATUS_SLAVE_GC_RECEIVED = 0x70,

    /* Previously addressed with own SLA+W; data has been received; ACK has been returned */
    I2C_STATUS_SLAVE_SA_DATA_RECEIVED_ACK = 0x80,

    /* Previously addressed with own SLA+W; data has been received; NOT ACK has been returned */
    I2C_STATUS_SLAVE_SA_DATA_RECEIVED_NACK = 0x88,

    /* Previously addressed with general call; data has been received; ACK has been returned */
    I2C_STATUS_SLAVE_GC_DATA_RECEIVED_ACK = 0x90,

    /* Previously addressed with general call; data has been received; NOT ACK has been returned */
    I2C_STATUS_SLAVE_GC_DATA_RECEIVED_NACK = 0x98,

    /* Last data byte in TWDR has been transmitted (TWEA = �0�); ACK has been received */
    I2C_STATUS_SLAVE_LAST_DATA_SENT_ACK = 0xC8,

    /* Data byte in TWDR has been transmitted; ACK has been received */
    I2C_STATUS_SLAVE_DATA_SENT_ACK = 0xB8,

    /* Data byte in TWDR has been transmitted; NOT ACK has been received */
    I2C_STATUS_SLAVE_DATA_SENT_NACK = 0xC0,

    /* A STOP condition or repeated START condition has been received while still addressed as slave */
    I2C_STATUS_SLAVE_STOP_OR_REP_START_RECEIVED = 0xA0

} en_i2c_status_t;

typedef enum
{
    I2C_REQUEST_WRITE = 0,
    I2C_REQUEST_READ  = 1
} en_i2c_request_t;

typedef enum
{
    I2C_NO_ERROR,
    I2C_ERROR_SLA_NACK,
    I2C_ERROR_DATA_NACK,
    I2C_ERROR_DATA_NOT_RECEIVED,
    I2C_ERROR_WRITE_REQUEST_NOT_RECEIVED,
    I2C_ERROR_READ_REQUEST_NOT_RECEIVED,
    I2C_ERROR_START_NOT_SENT,
} en_i2c_error_t;

void I2c_MasterInit(uint8_t_ address);
void I2c_SlaveInit(uint8_t_ address);
en_i2c_status_t I2c_SendStart();
en_i2c_status_t I2c_SendSlaveAddress(uint8_t_ address, en_i2c_request_t request);
en_i2c_status_t I2c_WriteData(uint8_t_ data);
en_i2c_status_t I2c_ReadData(uint8_t_* data);
void I2c_SendStop(void);

void I2c_EnableAck(void);
void I2c_DisableAck(void);

en_i2c_error_t I2c_MasterTransmit(uint8_t_ data[], uint8_t_ length, uint8_t_ address);
en_i2c_error_t I2c_MasterReceive(uint8_t_ data[], uint8_t_ length, uint8_t_ address);
en_i2c_error_t I2c_SlaveTransmit(uint8_t_ data[], uint8_t_ length, uint8_t_ address);
en_i2c_error_t I2c_SlaveReceive(uint8_t_ data[], uint8_t_ length, uint8_t_ address);

#endif /* INC_I2C_H_ */
