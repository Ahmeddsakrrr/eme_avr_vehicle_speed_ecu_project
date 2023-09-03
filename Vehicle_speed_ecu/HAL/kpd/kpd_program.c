/*
 * kpd_program.c
 *
 * Created: 8/18/2023 2:53:46 PM
 *  Author: Hossam Elwahsh
 */ 

#include "kpd_config.h"
#include "kpd_interface.h"
#include "timer.h"
#include "Timers_Services.h"

#define  F_CPU    16000000UL

#define KPD_INIT_DELAY_TIMER()  TIMER2_Init(TIMER2_NORMAL_MODE)
#define KPD_TIMER_MS_DELAY(ms_delay_val) delay_ms(ms_delay_val)

const uint8_t_ keypad_values[4][4] = {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'+','0','-','D'},
};

const uint8_t_ keypad_cols[KEYPAD_COLS_TOTAL] = {
        PIN7_ID,
        PIN6_ID,
        PIN5_ID,
        PIN3_ID
};

const uint8_t_ keypad_rows[KEYPAD_ROWS_TOTAL] = {
        PIN5_ID,
        PIN4_ID,
        PIN3_ID,
        PIN2_ID
};


void keypad_init(void)
{
    /* Init keypad */
    KPD_INIT_DELAY_TIMER();

    /* init rows */
    for (int i = 0; i < KEYPAD_ROWS_TOTAL; ++i) {
        /* init pin as input */
        GPIO_setupPinDirection( KEYPAD_ROW_PORT , keypad_rows[i] , PIN_INPUT);
        /* enable pin pull up */
        GPIO_writePin( KEYPAD_ROW_PORT , keypad_rows[i] , LOGIC_HIGH);
    }

    /* init columns */
    for (int i = 0; i < KEYPAD_ROWS_TOTAL; ++i)
    {
        /* init pin as input */
        GPIO_setupPinDirection( KEYPAD_COLUMN_PORT , keypad_rows[i] , PIN_INPUT);
    }

}


uint8_t_ keypad_read(void)
{
    uint8_t_ uint8_val_retval = NULL;

    for (int row = 0; row < KEYPAD_ROWS_TOTAL; ++row)
    {

        /* set row as output -> low */
        GPIO_setupPinDirection(KEYPAD_ROW_PORT, keypad_rows[row], PIN_OUTPUT);
        GPIO_writePin(KEYPAD_ROW_PORT, keypad_rows[row], LOGIC_LOW);

        for (int col = 0; col < KEYPAD_COLS_TOTAL; ++col)
        {
            uint8_t_ u8_l_dio_pin_val = LOGIC_HIGH;

            u8_l_dio_pin_val = GPIO_readPin(KEYPAD_COLUMN_PORT, keypad_cols[col]);

            if (u8_l_dio_pin_val == LOGIC_LOW)
            {
                /* debounce */
                KPD_TIMER_MS_DELAY(KEYPAD_DEBOUNCE_DELAY_MS);

                u8_l_dio_pin_val = GPIO_readPin(KEYPAD_COLUMN_PORT, keypad_cols[col]);

                /* block till user release key */
                while (u8_l_dio_pin_val == LOGIC_LOW)
                {
                    u8_l_dio_pin_val = GPIO_readPin(KEYPAD_COLUMN_PORT, keypad_cols[col]);
                }

                /* revert row to input */
                GPIO_setupPinDirection(KEYPAD_ROW_PORT, keypad_rows[row], PIN_INPUT);


                return keypad_values[row][col];

                /*if (u8_l_dio_pin_val == LOGIC_LOW)
                {

                }*/
            }
        }

        /* revert row to input */
        GPIO_setupPinDirection(KEYPAD_ROW_PORT, keypad_rows[row], PIN_INPUT);
    }

    return uint8_val_retval;
}