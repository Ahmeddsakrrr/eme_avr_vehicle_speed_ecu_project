/*
 * lcd.c
 *
 * Created: 18/4/2023 3:44:59 PM
 *  Author: Hossam
 */

#include "lcd_interface.h"
#include "lcd_private.h"
#include <stdlib.h>
#include "bit_math.h"

/*  current cursor position (0 -> 15 @line1, 16 -> 31 @line2) */
static uint8_t_ u8_gs_cursor = 0;
static uint8_t_ u8_gs_line = LCD_LINE0;

/**
 * @brief Initializes the LCD module.
 * This function initializes the LCD module by configuring the data port,
 * configuring the LCD to 4-bit mode,setting the display to on with cursor
 * and blink, setting the cursor to increment to the right, and clearing the display.
 * It also pre-stores a bell shape at CGRAM location 0.
 *
 * @return void
 */
void lcd_init(void)
{
    /* init delay timer */
    LCD_INIT_DELAY_TIMER();

    GPIO_setupPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
    GPIO_writePort(LCD_DATA_PORT, 0x00);

    GPIO_setupPinDirection(LCD_CTRL_PORT, LCD_CTRL_PIN_RS, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_CTRL_PORT, LCD_CTRL_PIN_EN, PIN_OUTPUT);

    LCD_TIMER_MS_DELAY(LCD_MS_DELAY_INIT); /*  10 ms */
    lcd_send_command(LCD_CMD_RETURN_HOME); /*  Return home */
    lcd_send_command(LCD_CMD_MODE_4Bit); /*  4 bit mode, 2 lines, 5*7 matrix */
    lcd_send_command(LCD_CMD_DCB); /*  Display on, Cursor on, Blink on */
    lcd_send_command(LCD_CMD_INC_CURSOR_RIGHT); /*  Increment cursor (shift to right) */
    lcd_send_command(LCD_CMD_CLEAR); /*  Clear display */
    LCD_TIMER_MS_DELAY(LCD_MS_DELAY_STORE);

    /*  pre-storing bell shape at CGRAM location 0 */
    lcd_store_custom_character(
            (uint8_t_[]) {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00},
            LCD_CUSTOMCHAR_LOC0
    );
    LCD_TIMER_MS_DELAY(LCD_MS_DELAY_STORE);

    /*  display bell top right */
/*     LCD_setCursor(LCD_LINE0, LCD_COL15); */
/*     LCD_sendChar(LCD_CUSTOMCHAR_LOC0); */
}

/**
 * @brief Sends a command to the LCD controller
 *
 * Sends the upper nibble of the command to the LCD's data pins, selects the command register by setting RS to low,
 * generates an enable pulse, delays for a short period, then sends the lower nibble of the command and generates
 * another enable pulse. Finally, it delays for a longer period to ensure the command has been executed by the LCD
 * controller.
 *
 * @param [in]u8_a_cmd The command to be sent
 */
void lcd_send_command(uint8_t_ u8_a_cmd) {

    /*  RS select command register */
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_RS,  LOGIC_LOW);

	/*  send upper nibble */
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D7, GET_BIT(u8_a_cmd, 7));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D6, GET_BIT(u8_a_cmd, 6));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D5, GET_BIT(u8_a_cmd, 5));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D4, GET_BIT(u8_a_cmd, 4));


/* 	dio_port_write(LCD_DATA_PORT, HIGHER_NIBBLE_SHIFT(u8_a_cmd), LCD_DATA_PINS_MASK); */

    /*  Enable Pulse */
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_EN,  LOGIC_HIGH);
    LCD_TIMER_US_DELAY(LCD_US_DELAY_PULSE);
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_EN, LOGIC_LOW);

	LCD_TIMER_US_DELAY(LCD_US_DELAY_HOLD);

    /*  send lower nibble */

    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D7, GET_BIT(u8_a_cmd, 3));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D6, GET_BIT(u8_a_cmd, 2));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D5, GET_BIT(u8_a_cmd, 1));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D4, GET_BIT(u8_a_cmd, 0));


/*     DIO_portWrite(LCD_DATA_PORT, LOWER_NIBBLE_SHIFT(u8_a_cmd), LCD_DATA_PINS_MASK); */

    /*  Enable Pulse */
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_EN,  LOGIC_HIGH);
    LCD_TIMER_US_DELAY(LCD_US_DELAY_PULSE);
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_EN, LOGIC_LOW);

    LCD_TIMER_MS_DELAY(LCD_MS_DELAY_STORE); /*  2ms */
}

/**
 * @brief Sends a single character to the LCD display
 *
 * This function sends a single character to the LCD display by selecting the data register and sending the
 * higher nibble and lower nibble of the character through the data port.
 * The function uses a pulse on the enable pin to signal the LCD to read the data on the data port.
 * The function also includes delays to ensure proper timing for the LCD to read the data.
 *
 * @param [in]u8_a_data single char ASCII data to show
 */
void lcd_send_char(uint8_t_ u8_a_data)
{
	
	/*  Select Data Register */
	GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_RS, LOGIC_HIGH);


    /*  send upper nibble */
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D7, GET_BIT(u8_a_data, 7));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D6, GET_BIT(u8_a_data, 6));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D5, GET_BIT(u8_a_data, 5));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D4, GET_BIT(u8_a_data, 4));

    /* old */
/*     DIO_portWrite(LCD_DATA_PORT, HIGHER_NIBBLE_SHIFT(u8_a_data), LCD_DATA_PINS_MASK); */

    /*  Enable Pulse */
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_EN,  LOGIC_HIGH);
    LCD_TIMER_US_DELAY(LCD_US_DELAY_PULSE);
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_EN, LOGIC_LOW);

    LCD_TIMER_US_DELAY(LCD_US_DELAY_HOLD);

    /*  send lower nibble */

    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D7, GET_BIT(u8_a_data, 3));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D6, GET_BIT(u8_a_data, 2));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D5, GET_BIT(u8_a_data, 1));
    GPIO_writePin(LCD_DATA_PORT, LCD_DATA_PIN_D4, GET_BIT(u8_a_data, 0));

    /*  Enable Pulse */
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_EN,  LOGIC_HIGH);
    LCD_TIMER_US_DELAY(LCD_US_DELAY_PULSE);
    GPIO_writePin(LCD_CTRL_PORT, LCD_CTRL_PIN_EN, LOGIC_LOW);

    LCD_TIMER_MS_DELAY(LCD_MS_DELAY_STORE); /*  2ms */

	LCD_TIMER_MS_DELAY(LCD_MS_DELAY_CHAR);
}

/**
 * @brief Displays a null-terminated string on the LCD screen.
 *
 * This function iterates through a null-terminated string and displays it
 * on the LCD screen. If the character '\\n' is encountered, the cursor is
 * moved to the beginning of the next line.
 *
 * @param [in]u8Ptr_a_str A pointer to the null-terminated string to be displayed.
 *
 * @return void
 */
void lcd_send_string(uint8_t_ * u8Ptr_a_str)
{
	while( *u8Ptr_a_str != '\0')
	{
		if(*u8Ptr_a_str == '\n')
		{
            INC_WITH_MOD(u8_gs_line, LCD_LINES_TOTAL);
            lcd_set_cursor(u8_gs_line, LCD_COL0);
			u8Ptr_a_str++;
			continue;
		}
        lcd_send_char(*u8Ptr_a_str);
        u8Ptr_a_str++;
        u8_gs_cursor++;

        /* if reached end of line */
        if(u8_gs_cursor == LCD_LINE_COLS)
        {
            /* go to next line */
            INC_WITH_MOD(u8_gs_line, LCD_LINES_TOTAL);
            lcd_set_cursor(u8_gs_line, LCD_COL0);
        }
        else
        {
            /* Do nothing */
        }
    }
}

/**
 * @brief Set the cursor position on the LCD.
 *
 * @param [in]u8_a_line the line number to set the cursor to, either LCD_LINE0 or LCD_LINE1
 * @param [in]u8_a_col the column number to set the cursor to, from LCD_COL0 to LCD_COL15
 *
 * @return STD_OK if the operation was successful, STD_NOK otherwise.
 */
uint8_t_ lcd_set_cursor(uint8_t_ u8_a_line, uint8_t_ u8_a_col)
{
    if(u8_a_line > LCD_LINE3 || u8_a_col > LCD_COL19) return STD_NOK;

    unsigned short firstCharAddr[] = {LCD_LINE0_ADDR, LCD_LINE1_ADDR, LCD_LINE2_ADDR, LCD_LINE3_ADDR}; /*  Address of the first character of each line */
    lcd_send_command(LCD_LINES_BASE_RAM_LOC + firstCharAddr[u8_a_line] + u8_a_col);
	/*  update global cursor */
	u8_gs_cursor = (u8_a_line * LCD_LINE_COLS) + u8_a_col;
    /*  update global line */
    u8_gs_line = u8_a_line;

    return STD_OK;
}

/*  locations: LCD_CUSTOMCHAR_LOC0 -> LOC7 */

/**
 * @brief Stores a custom character bitmap pattern in the CGRAM of the LCD module
 *
 * @param [in]u8_a_pattern Pointer to an array of 8 bytes representing the bitmap pattern of the custom character
 * @param [in]u8_a_location The CGRAM location where the custom character should be stored (from LCD_CUSTOMCHAR_LOC0 to 7)
 *
 * @return STD_OK if successful, otherwise STD_NOK
 */
uint8_t_ lcd_store_custom_character(uint8_t_ * u8_a_pattern, uint8_t_ u8_a_location) {

    if(u8_a_location > LCD_CGRAM_LOC_COUNT) return STD_NOK;

    /*  set CGRAM Address */
    lcd_send_command(LCD_CGRAM_ADDR + (u8_a_location * LCD_CGRAM_LOC_SIZE));

    /*  store custom character bitmap bytes */
    for (int i = 0; i < LCD_CGRAM_LOC_SIZE; ++i) {
        lcd_send_char(u8_a_pattern[i]);
    }

    return STD_OK;
}

/**
 * Clears the LCD display
 */
void lcd_clear(void)
{
    lcd_send_command(LCD_CMD_CLEAR);
    u8_gs_cursor = 0;
}

/**
 * Fancy right shift clear for the LCD display
 */
void lcd_shift_clear(void)
{
    for (int i = 0; i < LCD_LINE_COLS; ++i)
    {
        lcd_send_command(LCD_CMD_DISP_SHIFT_RIGHT);
        LCD_TIMER_MS_DELAY(LCD_MS_DELAY_SHIFT);
    }
    lcd_send_command(LCD_CMD_CLEAR);
    u8_gs_cursor = ZERO;
}


void LCD_printNumber(uint16_t_ uint16_a_number, uint8_t_ lcd_line, uint8_t_ lcd_col)
{
    char str_buff[10] = {0};

    /* Convert number to string */
    itoa(uint16_a_number, str_buff, 10);

    /* Set LCD Cursor Location */
    lcd_set_cursor(lcd_line, lcd_col);

    /* print Number */
    lcd_send_string((uint8_t_ *)str_buff);
}

/**
 * @brief   :   Prints a number starting from unit digit first and going backward in LCD position
 * @param[in] uint16_a_number   : Number to print
 * @param[in] lcd_line          : LCD line to print at
 * @param[in] lcd_col           : LCD column to start at (going backwards)
 */
void lcd_print_number_from_end(uint16_t_ uint16_a_number, uint8_t_ lcd_line, uint8_t_ lcd_col)
{
    int digit;

    /* print */
    do
    {
        lcd_set_cursor(lcd_line, lcd_col);

        digit = uint16_a_number % 10;
        lcd_send_char(digit + '0'); /*  print ASCII digit */
        lcd_col--;
    } while (uint16_a_number /= 10);

}