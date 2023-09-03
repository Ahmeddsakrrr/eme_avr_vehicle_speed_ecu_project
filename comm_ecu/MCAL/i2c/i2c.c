/*
 * I2c.c
 *
 *  Created on: Apr 30, 2023
 *      Author: A M
 */


/*
 * I2c.c
 *
 *  Created on: Mar 18, 2023
 *      Author: SAkr
 */

#include "i2c_config.h"
#include "i2c_private.h"


/*  0b11111000 */
#define I2C_GET_STATUS()    (TWSR&0xF8)

void I2c_MasterInit(uint8_t_ address) {
    /* Set Own Address */
    TWAR = address<<1;
    /* Setting SCL Bit Rate to 400kbps */
    TWBR = 12;
    CLR_BIT(TWSR, 0);
    CLR_BIT(TWSR, 1);
    /* Enable TWI */
    SET_BIT(TWCR, 2);
}

void I2c_SlaveInit(uint8_t_ address) {
    /* Set Own Address */
    TWAR = address<<1;
    /* Enable TWI */
    SET_BIT(TWCR, 2);
}

en_i2c_status_t I2c_SendStart() {
    /* TWI START Condition Bit */
    SET_BIT(TWCR, 5);
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);
    /* Return Status */
    return I2C_GET_STATUS();
}

en_i2c_status_t I2c_SendSlaveAddress(uint8_t_ address, en_i2c_request_t request) {
    /* Set SLA+ R/W */
    TWDR = (address<<1) | request;
    /* Clear TWI START Condition Bit and Clear Flag */
    TWCR = (1<<2) | (1<<7);
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);
    /* Return Status */
    return I2C_GET_STATUS();
}

en_i2c_status_t I2c_WriteData(uint8_t_ data) {
    /* Write Data */
    TWDR = data;
    /* Clear Flag */
    SET_BIT(TWCR, 7);
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);
    /* Return Status */
    return I2C_GET_STATUS();
}

en_i2c_status_t I2c_ReadData(uint8_t_* data) {
    /* Clear Flag */
    SET_BIT(TWCR, 7);
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);
    /* Read Data */
    *data = TWDR;
    /* Return Status */
    return I2C_GET_STATUS();
}

void I2c_SendStop(void) {
    /* Clear Flag and TWI STOP Condition Bit */
    TWCR = (1<<2) | (1<<4) | (1<<7);
}

void I2c_EnableAck(void) {
    SET_BIT(TWCR, 6);
}
void I2c_DisableAck(void) {
    CLR_BIT(TWCR, 6);
}

en_i2c_error_t I2c_MasterTransmit(uint8_t_ data[], uint8_t_ length, uint8_t_ address) {
    uint8_t_ i;
    en_i2c_status_t state;
    state = I2c_SendStart();
    if (I2C_STATUS_MASTER_START_SENT != state) {
        return I2C_ERROR_START_NOT_SENT;
    }
    state = I2c_SendSlaveAddress(address, I2C_REQUEST_WRITE);
    if (I2C_STATUS_MASTER_SA_W_ACK != state) {
        I2c_SendStop();
        return I2C_ERROR_SLA_NACK;
    }
    for (i=0; i<length; i++) {
        state = I2c_WriteData(data[i]);
        if (I2C_STATUS_MASTER_DATA_SENT_ACK != state) {
            I2c_SendStop();
            return I2C_ERROR_DATA_NACK;
        }
    }
    I2c_SendStop();
    return I2C_NO_ERROR;
}
en_i2c_error_t I2c_MasterReceive(uint8_t_ data[], uint8_t_ length, uint8_t_ address) {
    en_i2c_status_t state;
    uint8_t_ i,tempBuffer;
    I2c_EnableAck();
    state = I2c_SendStart();
    if(I2C_STATUS_MASTER_START_SENT!=state){
        return I2C_ERROR_START_NOT_SENT;
    }
    state= I2c_SendSlaveAddress(address,I2C_REQUEST_READ);
    if(I2C_STATUS_MASTER_SA_R_ACK!=state){
        return I2C_ERROR_SLA_NACK;
    }
    for(i=0;i<length;i++){
        state = I2c_ReadData(&tempBuffer);
        if(I2C_STATUS_MASTER_DATA_RECEIVED_ACK!=state){
            return I2C_ERROR_DATA_NOT_RECEIVED;
        }
        data[i] = tempBuffer;
    }
    I2c_DisableAck();

    return I2C_NO_ERROR;
}

en_i2c_error_t I2c_SlaveTransmit(uint8_t_ data[], uint8_t_ length, uint8_t_ address) {
    en_i2c_status_t state;
    uint8_t_ i;
    I2c_EnableAck();
    while(GET_BIT(TWCR,7)==0);
    if(I2C_GET_STATUS()!=I2C_STATUS_SLAVE_SA_R_RECEIVED){
        return I2C_ERROR_READ_REQUEST_NOT_RECEIVED;
    }
    for(i=0;i<length;i++){
        state=I2c_WriteData(data[i]);
        if(i==(length-1)){
            if(I2C_STATUS_SLAVE_LAST_DATA_SENT_ACK !=state){
                return I2C_ERROR_DATA_NACK;
            }
        }
        else{
            if(I2C_STATUS_SLAVE_DATA_SENT_ACK !=state){
                return I2C_ERROR_DATA_NACK;
            }
        }
    }

    I2c_DisableAck();
    return I2C_NO_ERROR;
}
en_i2c_error_t I2c_SlaveReceive(uint8_t_ data[], uint8_t_ length, uint8_t_ address) {
    en_i2c_status_t state;
    uint8_t_ i, tempBuffer;
    I2c_EnableAck();
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);

    /* Check for status */
    if (I2C_GET_STATUS() != I2C_STATUS_SLAVE_SA_W_RECEIVED) {
        return I2C_ERROR_WRITE_REQUEST_NOT_RECEIVED;
    }

    for (i=0; i<length; i++) {
        /* Read Data */
        state = I2c_ReadData(&tempBuffer);
        if (I2C_STATUS_SLAVE_SA_DATA_RECEIVED_ACK != state) {
            return I2C_ERROR_DATA_NOT_RECEIVED;
        }
        data[i] = tempBuffer;
    }

    I2c_DisableAck();
    return I2C_NO_ERROR;
}
