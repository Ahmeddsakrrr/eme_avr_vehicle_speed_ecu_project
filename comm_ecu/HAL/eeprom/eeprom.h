/*
 * Eeprom.h
 *
 * Created: 9/3/2023 11:18:52 AM
 *  Author: Ahmed Sakr
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "std.h"

typedef enum {
	EEPROM_FAIL,
	EEPROM_SUCCESS,
} Eeprom_StateType;


void Eeprom_Init(void);
Eeprom_StateType Eeprom_WriteByte(uint16_t_ address, uint8_t_ data);
Eeprom_StateType Eeprom_ReadByte(uint16_t_ address, uint8_t_* data);





#endif /* EEPROM_H_ */