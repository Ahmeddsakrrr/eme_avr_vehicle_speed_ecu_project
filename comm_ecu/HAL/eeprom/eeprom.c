/*
 * Eeprom.c
 *
 * Created: 9/3/2023 11:19:13 AM
 *  Author: Ahmed Sakr
 */ 
#include "eeprom.h"
#include "eeprom_Cfg.h"
#include "std.h"
#include "bit_math.h"
#include "i2c_config.h"
#include "i2c_private.h"


void Eeprom_Init(void){
	I2c_MasterInit(0);
}

Eeprom_StateType Eeprom_WriteByte(uint16_t_ address, uint8_t_ data){
	en_i2c_status_t state;
	uint8_t_ Slave_Address;
	Slave_Address= 0b1010000 |(EEPROM_PIN_A2<<2)|(address>>8); /* 1010 + A2 + pageno. */
	
	/* i want to start i2c for communication. */
	state=I2c_SendStart();
	if(state!=I2C_STATUS_MASTER_START_SENT){
		return EEPROM_FAIL;
	}

	state=I2c_SendSlaveAddress(Slave_Address,I2C_REQUEST_WRITE);
	if(state!=I2C_STATUS_MASTER_SA_W_ACK){
		I2c_SendStop();
		return EEPROM_FAIL;
	}

	state=I2c_WriteData((uint8_t_)address);
	if(state!=I2C_STATUS_MASTER_DATA_SENT_ACK){
		I2c_SendStop();
		return EEPROM_FAIL;
	}
	state = I2c_WriteData(data);
	if(state!=I2C_STATUS_MASTER_DATA_SENT_ACK){
		I2c_SendStop();
		return EEPROM_FAIL;
	}
	I2c_SendStop();
	return EEPROM_SUCCESS;
}




Eeprom_StateType Eeprom_ReadByte(uint16_t_ address, uint8_t_* data){
	en_i2c_status_t state;
	uint8_t_ Slave_Address;
	Slave_Address= 0b1010000 |(EEPROM_PIN_A2<<2)|(address>>8); /* 1010 + A2 + pageno. */

	state=I2c_SendStart();
	if(state!=I2C_STATUS_MASTER_START_SENT){
		return EEPROM_FAIL;
	}

	state=I2c_SendSlaveAddress(Slave_Address,I2C_REQUEST_WRITE);
	if(state!=I2C_STATUS_MASTER_SA_W_ACK){
		I2c_SendStop();
		return EEPROM_FAIL;
	}

	state=I2c_WriteData((uint8_t_)address);
	if(state!=I2C_STATUS_MASTER_DATA_SENT_ACK){
		I2c_SendStop();
		return EEPROM_FAIL;
	}

	/* repeated start for reading from EEprom */
	state = I2c_SendStart();
	if(state!= I2C_STATUS_MASTER_REP_START_SENT){
		I2c_SendStop();
		return EEPROM_FAIL;
	}
	state= I2c_SendSlaveAddress(Slave_Address,I2C_REQUEST_READ);
	if(state!=I2C_STATUS_MASTER_SA_R_ACK){
		I2c_SendStop();
		return EEPROM_FAIL;
	}


	I2c_EnableAck();


	state= I2c_ReadData(data);
	if(state!=I2C_STATUS_MASTER_DATA_RECEIVED_ACK){
		I2c_SendStop();
		return EEPROM_FAIL;
	}
	I2c_DisableAck();
	I2c_SendStop();
	return EEPROM_SUCCESS;
}





