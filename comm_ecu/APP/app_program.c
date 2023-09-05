

#include "app_interface.h"
#include "app_config.h"
#include "app_private.h"




uint8_t_ uint8_g_recived_data=0 ;
uint8_t_  uint8_g_send_limit_speed=0;
uint8_t_  uint8_g_send_check_data=0;

static void   receive_limit_speed();
static void  send_limit_speed();


void app_init()
{
	/* Init SPI */
	spi_init();
	/* Init EEPROM */
	Eeprom_Init();
}



void app_start()
{

	while(TRUE)
	{
		/* start spi communication */
		
		uint8_g_recived_data=spi_transceiver(NO_ACK);
		
		
		/* check whether the data is valid ,
		if its valid transmit ACK=1 ,if its not transmit NO_ACK=0 */
		
		if(uint8_g_recived_data==START)
		{
			uint8_g_recived_data=spi_transceiver(ACK);
			uint8_g_recived_data=spi_transceiver(NO_ACK);
			
			/* check the received data wants information about limited speed or  ,
			wants to send the limited speed  */
			while(uint8_g_send_check_data==0){
				switch(uint8_g_recived_data)
				{
					
					case RECIVED_LIMIT_SPEED:
					
					receive_limit_speed();
					break;
					
					case SEND_LIMIT_SPEED:
					send_limit_speed();
									break;
					default:
					uint8_g_recived_data=spi_transceiver(NO_ACK);
					break;
				}
			}
		}
		else
		{
			/* do nothing*/
		}
		uint8_g_send_check_data=0;
	}
}



/*	check if the speed within the range of 30 to 220
	if the speed falls the range it is saved in EEPROM
	if its not a NO_ACK is sent and wait for a valid speed */

static void receive_limit_speed()
{
	uint8_g_recived_data=spi_transceiver(ACK);
	uint8_g_recived_data=spi_transceiver(NO_ACK);
	
	while((uint8_g_recived_data <MIN_SPEED )||( uint8_g_recived_data >MAX_SPEED))
	{
		uint8_g_recived_data=spi_transceiver(NO_ACK);
		
		
	}
	uint8_g_recived_data=spi_transceiver(ACK);
	
	Eeprom_WriteByte(EEPROM_ADDRESS,uint8_g_recived_data);
	uint8_g_send_check_data=1;
}




/* retrieve the saved speed from EEPROM and transmit it*/
static void send_limit_speed()
{
	
	uint8_g_recived_data=spi_transceiver(ACK);
	
	Eeprom_ReadByte(EEPROM_ADDRESS,& uint8_g_send_limit_speed);
	
	uint8_g_recived_data=spi_transceiver( uint8_g_send_limit_speed);
	uint8_g_send_check_data=1;
}
