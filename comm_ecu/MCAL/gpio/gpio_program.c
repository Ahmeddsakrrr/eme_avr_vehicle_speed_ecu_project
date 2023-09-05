 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Mahmoud Abdrabo
 *
 *******************************************************************************/

#include "gpio_interface.h"
#include "bit_math.h"  /* To use the macros like SET_BIT */
#include "gpio_private.h" 		/* To use the IO Ports Registers */

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8_t_ port_num, uint8_t_ pin_num, GPIO_PinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DIO_U8_DDR_A_REG,pin_num);
			}
			else
			{
				CLR_BIT(DIO_U8_DDR_A_REG,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DIO_U8_DDR_B_REG,pin_num);
			}
			else
			{
				CLR_BIT(DIO_U8_DDR_B_REG,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DIO_U8_DDR_C_REG,pin_num);
			}
			else
			{
				CLR_BIT(DIO_U8_DDR_C_REG,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DIO_U8_DDR_D_REG,pin_num);
			}
			else
			{
				CLR_BIT(DIO_U8_DDR_D_REG,pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8_t_ port_num, uint8_t_ pin_num, uint8_t_ value)
{
	if((port_num >= NUM_OF_PORTS ) || (pin_num >= NUM_OF_PINS_PER_PORT)){

	}
	else{
		switch(port_num){
			case PORTA_ID:
				if(value == LOGIC_HIGH)
					SET_BIT(DIO_U8_PORT_A_REG,pin_num);
				else
					CLR_BIT(DIO_U8_PORT_A_REG,pin_num);
					break;
			case PORTB_ID:
				if(value == LOGIC_HIGH)
					SET_BIT(DIO_U8_PORT_B_REG,pin_num);
				else
					CLR_BIT(DIO_U8_PORT_B_REG,pin_num);
					break;
			case PORTC_ID:
				if(value == LOGIC_HIGH)
					SET_BIT(DIO_U8_PORT_C_REG,pin_num);
				else
					CLR_BIT(DIO_U8_PORT_C_REG,pin_num);
					break;
			case PORTD_ID:
				if(value == LOGIC_HIGH)
					SET_BIT(DIO_U8_PORT_D_REG,pin_num);
				else
					CLR_BIT(DIO_U8_PORT_D_REG,pin_num);
					break;
		}
	}


}


/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
 void GPIO_togglePin(uint8_t_ port_num, uint8_t_ pin_num)
{
	if((port_num >= NUM_OF_PORTS ) || (pin_num >= NUM_OF_PINS_PER_PORT)){

	}
	else{
		switch(port_num){
			case PORTA_ID:
					TOGGLE_BIT(DIO_U8_PORT_A_REG,pin_num);
					break;
			case PORTB_ID:
					TOGGLE_BIT(DIO_U8_PORT_B_REG,pin_num);
					break;
			case PORTC_ID:
					TOGGLE_BIT(DIO_U8_PORT_C_REG,pin_num);
					break;
			case PORTD_ID:
					TOGGLE_BIT(DIO_U8_PORT_D_REG,pin_num);
					break;
            default:
                break;
		}
	}


}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8_t_ GPIO_readPin(uint8_t_ port_num, uint8_t_ pin_num)
{
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)){

	}
	else{
		switch(port_num){
			case PORTA_ID:
				return BIT_IS_SET(DIO_U8_PIN_A_REG,pin_num);
			case PORTB_ID:
				return BIT_IS_SET(DIO_U8_PIN_B_REG,pin_num);
			case PORTC_ID:
				return BIT_IS_SET(DIO_U8_PIN_C_REG,pin_num);
			case PORTD_ID:
				return BIT_IS_SET(DIO_U8_PIN_D_REG,pin_num);
            default:
                return ZERO;
		}
	}
	return 0;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8_t_ port_num, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			DIO_U8_DDR_A_REG = direction;
			break;
		case PORTB_ID:
			DIO_U8_DDR_B_REG = direction;
			break;
		case PORTC_ID:
			DIO_U8_DDR_C_REG = direction;
			break;
		case PORTD_ID:
			DIO_U8_DDR_D_REG = direction;
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8_t_ port_num, uint8_t_ value)
{
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else{
		switch(port_num){
			case PORTA_ID:
				DIO_U8_PORT_A_REG = value;
				break;
			case PORTB_ID:
				DIO_U8_PORT_B_REG = value;
				break;
			case PORTC_ID:
				DIO_U8_PORT_C_REG = value;
				break;
			case PORTD_ID:
				DIO_U8_PORT_D_REG = value;
				break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8_t_ GPIO_readPort(uint8_t_ port_num)
{
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else{
		switch (port_num)
		{
		case PORTA_ID:
			return DIO_U8_PIN_A_REG;
			break;
		case PORTB_ID:
			return DIO_U8_PIN_B_REG;
			break;
		case PORTC_ID:
			return DIO_U8_PIN_C_REG;
			break;
		case PORTD_ID:
			return DIO_U8_PIN_D_REG;
			break;
		}
	}
	return 0;
}
