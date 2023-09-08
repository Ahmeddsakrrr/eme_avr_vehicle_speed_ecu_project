/*
 * app_program.c
 *
 * Created: 9/3/2023 11:54:14 AM
 *  Author: GUCALEX Team
 */

/* App includes */
#include "app_interface.h"
#include "app_config.h"
#include "app_private.h"


/* App functions prototypes */
static void send_limit_speed(uint8_t_ uint8_a_speed );
static void receive_limit_speed();
static void app_switch_state(en_app_state_t en_a_app_state);
static void app_key_changed(en_read_states_t en_l_kl_state);
static void app_timer_tick_event(void);

/* App state */
static  en_app_state_t  en_gs_app_state   =                  APP_STATE_INIT_UI  ;
static  en_app_sub_state_t  en_gs_app_sub_state   =          APP_SUB_STATE_P    ;

/* Booleans/Flags */
static boolean  bool_gs_is_night    = FALSE;
static boolean  bool_car_sleep_mode = FALSE;
static boolean  bool_gs_speed_limit_enabled = FALSE;

/* Time elapsed */

/* App global variables */
static uint8_t_     uint8_g_received_data       =   ZERO                ;
static uint8_t_     uint8_g_readings                                    ;
static uint8_t_     uint8_Gear_mode             =   KPD_CAR_MODE_P      ;
static uint8_t_     uint8_g_kpd_value           =   NULL                ;
static uint32_t_    uint16_throttle_g_readings                          ;
static uint8_t_     uint8_gs_seconds_elapsed    =   ZERO                ;
static uint8_t_     uint8_gs_set_speed_index    =   3                   ;
static uint8_t_     uint8_g_speed_limit         =   APP_CAR_MAX_SPEED   ;

void app_init(void)
{
    /* Init LCD */
    lcd_init();

    /* Init BUZZ */
    buzz_init();

    /* Init KL15 */
    KL_Switch_init();

    /*init ldr */
    ldr_init();

    timer1_init(TIMER1_NORMAL_MODE);
    timer1_ovf_set_callback(app_timer_tick_event);
    timer1_ovf_interrupt_enable();
    sei();

    /* Init Interior LED */
    Led_Init(APP_INTERIOR_LIGHT_ARGS);

    /* Init Front LEDs */
    Led_Init(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
    Led_Init(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);

    /* Init Throttle */
    throttle_init();

    /* Init Keypad */
    keypad_init();

	/* Init TIMER 2 */
	timer2_init(TIMER2_CTC_MODE);

}
void app_start(void)
{
    /* Switch app to initial state - CAR OFF */
    app_switch_state(APP_STATE_INIT_UI);

    /* local variables */
    en_read_states_t en_l_kl_state;
    static uint8_t_  uint8_l_speed_limit_btn = ZERO;

    /*get keypad current value*/
    uint8_g_kpd_value = keypad_read();

    while (TRUE)
    {
        /* Read LDR */
        ldr_read();

        /* Update is night flag */
        bool_gs_is_night = APP_LDR_NIGHT_THRESHOLD > LDR_VALUE;
//        lcd_print_number_from_end(LDR_VALUE, LCD_LINE3, LCD_COL19);

        /* Read KL15 Switch State */
        en_l_kl_state = KL_Switch_Read_state();

        /* Read Keypad */
        uint8_g_kpd_value = keypad_read();

        uint16_throttle_g_readings = throttle_read_state();

        switch (en_gs_app_state)
        {
            case APP_STATE_INIT_UI:
            {
                /* Init APP LCD UI */
                app_switch_state(APP_CAR_OFF);
                break;
            }
            case APP_CAR_OFF:
            {
                /* Check key state */
                if(OFF != en_l_kl_state)
                {
                    app_key_changed(en_l_kl_state);
                }
                else
                {
                    /* Do nothing */
                }

                break;
            }
            case APP_CAR_READY:
            {
                /* Check key state */
                if (Ready != en_l_kl_state) {
                    app_key_changed(en_l_kl_state);
                } else {
                    /* Do nothing */
                }

                /* Check timer */
                if (APP_CAR_BATTERY_TIMEOUT_IN_SEC < uint8_gs_seconds_elapsed)
                {
                    /* Turn car off */
                    bool_car_sleep_mode = TRUE;
                    app_switch_state(APP_CAR_OFF);
                }

                break;
            }
            case APP_STATE_SHOW_OPTIONS:
            {
                /* Check key state */
                if(ON != en_l_kl_state)
                {
                    app_key_changed(en_l_kl_state);
                }
                else
                {
                    /* Do nothing */
                }

                /* Check day/night light */
                if(TRUE == bool_gs_is_night)
                {
                    /* Night, turn on car front lights */
                    Led_TurnOn(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
                    Led_TurnOn(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
                }
                else
                {
                    /* Day, turn off car front lights */
                    Led_TurnOff(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
                    Led_TurnOff(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
                }

                /* if set button is pressed */
                if(KPD_SET_LIMIT == uint8_g_kpd_value)
                {
                    /* Switch state to set speed limit */
                    app_switch_state(APP_STATE_SET_LIMIT);
                }
                else if(KPD_MAIN == uint8_g_kpd_value)
                {
                    /* Switch state to main */
                    app_switch_state(APP_STATE_MAIN);
                }
                else if(KPD_SPEED_LIMIT_TOGGLE == uint8_g_kpd_value)
                {
                    /* Toggle speed limit */
                    bool_gs_speed_limit_enabled = (!bool_gs_speed_limit_enabled);

                    if(FALSE == bool_gs_speed_limit_enabled)
                    {
                        /* INFORM THAT SPEED LIMIT IS OFF */
                        lcd_set_cursor(LCD_LINE3,LCD_COL0);
                        lcd_send_string(APP_STR_OPT_SPEED_LIMIT_SW_OFF);
                        APP_BUZZ(APP_NOTIFY_BUZZ_DURATION_MS);
                        /* Return back to the options menu */
                    }
                    else if(TRUE == bool_gs_speed_limit_enabled)
                    {
                        /* INFORM THAT SPEED LIMIT IS ON */
                        lcd_set_cursor(LCD_LINE3,LCD_COL0);
                        lcd_send_string(APP_STR_OPT_SPEED_LIMIT_SW_ON);
                        APP_BUZZ(APP_NOTIFY_BUZZ_DURATION_MS);

                        /* todo retrieve limit from eeprom, if no data request user to input limit first */
                    }
                }
                else
                {
                    /* Do Nothing */
                }
                break;
            }

            case APP_STATE_MAIN:
            {
                /* Check key state */
                if(ON != en_l_kl_state)
                {
                    app_key_changed(en_l_kl_state);
                }
                else
                {
                    /* Do nothing */
                }


                /* Check day/night light */
                if(TRUE == bool_gs_is_night)
                {
                    /* Night, turn on car front lights */
                    Led_TurnOn(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
                    Led_TurnOn(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
                }
                else
                {
                    /* Day, turn off car front lights */
                    Led_TurnOff(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
                    Led_TurnOff(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
                }

                if(KPD_EXIT == uint8_g_kpd_value)
                {
                    /* Exit and go back to options screen */
                    app_switch_state(APP_STATE_SHOW_OPTIONS);
                }
                else if(KPD_CAR_MODE_P == uint8_g_kpd_value)
                {
                    en_gs_app_sub_state=APP_SUB_STATE_P;
                    app_switch_state(APP_STATE_MAIN);
                }
                else if(KPD_CAR_MODE_R==uint8_g_kpd_value )
                {
                    en_gs_app_sub_state=APP_SUB_STATE_R;
                    app_switch_state(APP_STATE_MAIN);
                    Led_TurnOn(LED_YELLOW_ARGS);
                }
                else if(KPD_CAR_MODE_N==uint8_g_kpd_value)
                {
                    en_gs_app_sub_state = APP_SUB_STATE_N;
                    app_switch_state(APP_STATE_MAIN);
                    Led_Flip(LED_BLUE_ARGS);
                }
                else if(KPD_CAR_MODE_D==uint8_g_kpd_value)
                {
                    en_gs_app_sub_state = APP_SUB_STATE_D;
                    app_switch_state(APP_STATE_MAIN);
                    Led_TurnOn(LED_GREEN_ARGS);
                }

               /* check the substates */
                if(en_gs_app_sub_state == APP_SUB_STATE_P)
                {
                     if(uint16_throttle_g_readings>ZERO){
                         /* alert with the buzzer "you can't move the car in park mode */
                        buzz_on();
                        lcd_set_cursor(LCD_LINE3,LCD_COL0);
                        lcd_send_string(APP_STR_ERROR);
                         Led_TurnOn(LED_RED_ARGS);
                    }
                     buzz_off();
                }
                else if (en_gs_app_sub_state == APP_SUB_STATE_R)
                {
                    LCD_printNumber(uint16_throttle_g_readings,LCD_LINE3,LCD_COL0);
                    /*speed will be max 30 km/hr in reverse mood*/
                    if(uint16_throttle_g_readings<30)
                    {
                        LCD_printNumber(uint16_throttle_g_readings, LCD_LINE2, LCD_COL10);
                    }
                    else if(uint16_throttle_g_readings>30)
                    {
                        LCD_printNumber(30,LCD_LINE2,LCD_COL10);
                    }
                }
                else if (en_gs_app_sub_state == APP_SUB_STATE_N)
                {
//                    LCD_printNumber(uint16_throttle_g_readings, LCD_LINE2, LCD_COL9);
                    LCD_printNumber(000, LCD_LINE2, LCD_COL9);

                }
                else if (en_gs_app_sub_state ==APP_SUB_STATE_D)
                {

                   // LCD_printNumber(((uint32_t_)uint16_g_last_reading[ADC_CH_0]*5000/1024),3,0);
                              /*THE CLUTCH GEARS D1 D2 D3 D4 D5 D6 D7*/
                    if(uint16_throttle_g_readings>=0 && uint16_throttle_g_readings<=30 && uint16_throttle_g_readings<=uint8_g_speed_limit)
                    {
                        LCD_printNumber(1,LCD_LINE1,LCD_COL10);
                        LCD_printNumber(0,LCD_LINE2,LCD_COL10);
                        LCD_printNumber(uint16_throttle_g_readings,LCD_LINE2,LCD_COL11);

                    }

                    else if(uint16_throttle_g_readings>30 && uint16_throttle_g_readings<=40 && uint16_throttle_g_readings<=uint8_g_speed_limit)
                    {
                        LCD_printNumber(2,LCD_LINE1,LCD_COL10);
                        LCD_printNumber(0,LCD_LINE2,LCD_COL10);
                        LCD_printNumber(uint16_throttle_g_readings,LCD_LINE2,LCD_COL11);
                    }

                    else if(uint16_throttle_g_readings>40 && uint16_throttle_g_readings<=60 && uint16_throttle_g_readings<=uint8_g_speed_limit)
                    {
                        LCD_printNumber(3,LCD_LINE1,LCD_COL10);
                        LCD_printNumber(0,LCD_LINE2,LCD_COL10);
                        LCD_printNumber(uint16_throttle_g_readings,LCD_LINE2,LCD_COL11);
                    }

                    else if(uint16_throttle_g_readings>60 && uint16_throttle_g_readings<=80 && uint16_throttle_g_readings<=uint8_g_speed_limit)
                    {
                        LCD_printNumber(4,LCD_LINE1,LCD_COL10);
                        LCD_printNumber(0,LCD_LINE2,LCD_COL10);
                        LCD_printNumber(uint16_throttle_g_readings,LCD_LINE2,LCD_COL11);
                    }

                    else if(uint16_throttle_g_readings>80 && uint16_throttle_g_readings<=100 && uint16_throttle_g_readings<=uint8_g_speed_limit)
                    {
                        LCD_printNumber(5,LCD_LINE1,LCD_COL10);
                        LCD_printNumber(uint16_throttle_g_readings,LCD_LINE2,LCD_COL10);
                    }

                    else if(uint16_throttle_g_readings>100 && uint16_throttle_g_readings<=150 && uint16_throttle_g_readings<=uint8_g_speed_limit)
                    {

                        LCD_printNumber(6,LCD_LINE1,LCD_COL10);
                        LCD_printNumber(uint16_throttle_g_readings,LCD_LINE2,LCD_COL10);
                    }

                    else if (uint16_throttle_g_readings>150 && uint16_throttle_g_readings<=200 && uint16_throttle_g_readings<=uint8_g_speed_limit)
                    {
                        LCD_printNumber(7,LCD_LINE1,LCD_COL10);
                        LCD_printNumber(uint16_throttle_g_readings,LCD_LINE2,LCD_COL10);
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                break;
            }
            case APP_STATE_SET_LIMIT:
            {
                /* Check key state */
                if(ON != en_l_kl_state)
                {
                    app_key_changed(en_l_kl_state);
                }
                else
                {
                    /* Do nothing */
                }


                if(NULL != uint8_g_kpd_value){
                    if(uint8_g_kpd_value >= '0' && uint8_g_kpd_value <= '9')
                    {
                        /* Parse Numbers */
                        if(3 == uint8_gs_set_speed_index)
                        {
                            uint8_g_speed_limit= CONVERT_CHAR_TO_DIGIT(uint8_g_kpd_value) * 100;

                            /* Send pressed char */
                            LCD_sendChar(uint8_g_kpd_value);
                        }
                        else if(2 == uint8_gs_set_speed_index)
                        {
                            uint8_g_speed_limit+= CONVERT_CHAR_TO_DIGIT(uint8_g_kpd_value) * 10;

                            /* Send pressed char */
                            LCD_sendChar(uint8_g_kpd_value);
                        }
                        else if(1 == uint8_gs_set_speed_index)
                        {
                            uint8_g_speed_limit+= CONVERT_CHAR_TO_DIGIT(uint8_g_kpd_value);

                            /* Send pressed char */
                            LCD_sendChar(uint8_g_kpd_value);
                        }

                        /* Update index */
                        DECREMENT(uint8_gs_set_speed_index);

                        /* Check if the index equal to zero */
                        if(ZERO == uint8_gs_set_speed_index )
                        {
                            /* Send speed limit to the slave microcontroller using SPI */
                            /* todo show please wait screen */
                            lcd_clear();
                            lcd_set_cursor(LCD_LINE2, LCD_COL2);
                            lcd_send_string(APP_STR_SAVING_LIMIT);
                            send_limit_speed(uint8_g_speed_limit);
                        }
                        else
                        {
                            /* Do Nothing */
                        }
                    }
                }
                else
                {
                    /* Do Nothing, no key is pressed */
                }
                break;
            }
            default:
            {
                break;
            }

        }
    }
}

static void app_switch_state(en_app_state_t en_a_app_state)
{

    switch (en_a_app_state)
    {
        case APP_STATE_INIT_UI:
        {
            /* Init LCD UI */
            lcd_clear();
            lcd_send_string(APP_STR_TITLE);
            break;
        }
        case APP_CAR_OFF:
        {
            /* Turn off all car LEDs */
            Led_TurnOff(APP_INTERIOR_LIGHT_ARGS);
            Led_TurnOff(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
            Led_TurnOff(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);

            /* Update UI */
            lcd_set_cursor(LCD_LINE2, LCD_COL1);
            lcd_send_string(APP_STR_CAR_OFF);
            break;
        }
        case APP_CAR_READY:
        {
            lcd_clear();

            SHOW_TITLE_CENTERED_ON_LCD();

            /* Turn on car interior light */
            Led_TurnOn(APP_INTERIOR_LIGHT_ARGS);

            /* Turn off car front lights */
            Led_TurnOff(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
            Led_TurnOff(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);

            /* Update UI */
            lcd_set_cursor(LCD_LINE2, LCD_COL1);
            lcd_send_string(APP_STR_CAR_READY);

            /* Start watchdog timer to prevent battery drain */
            TIMER1_START();
            break;
        }
        case APP_STATE_SHOW_OPTIONS:
        {
            /* clear lcd */
            lcd_clear();

            /* Turn on car interior */
            Led_TurnOn(APP_INTERIOR_LIGHT_ARGS);

            /* Check day/night light */
            if(TRUE == bool_gs_is_night)
            {
                /* Night, turn on car front lights */
                Led_TurnOn(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
                Led_TurnOn(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
            }
            else
            {
                /* Day, turn off car front lights */
                Led_TurnOff(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
                Led_TurnOff(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
            }

            SHOW_TITLE_CENTERED_ON_LCD();

            /* lcd shows the options int the main */
            lcd_set_cursor(LCD_LINE1, LCD_COL0);
            lcd_send_string(APP_STR_OPT_DASHBOARD);

            lcd_set_cursor(LCD_LINE2, LCD_COL0);
            lcd_send_string(APP_STR_OPT_SET_SPEED_LIMIT);

            lcd_set_cursor(LCD_LINE3, LCD_COL0);
            lcd_send_string(APP_STR_OPT_SPEED_LIMIT_SW_OFF);

            /* Update global app en_a_app_state flag */
            en_gs_app_state = APP_STATE_SHOW_OPTIONS;
            break;
        }
        case     APP_STATE_MAIN :
            {
                lcd_clear();
                lcd_set_cursor(LCD_LINE0,LCD_COL0);
                lcd_send_string(" P R N D");
                if(en_gs_app_sub_state==APP_SUB_STATE_P){
                    lcd_clear();
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("1-GEAR : P");

                    lcd_set_cursor(LCD_LINE2,LCD_COL0);
                    lcd_send_string("2-SPEED : ");
                    LCD_printNumber(0,LCD_LINE2,LCD_COL10);
                    /*PARK MODE INDICATION*/

                    en_gs_app_state = APP_STATE_MAIN;
                    break;
                }

                else if(en_gs_app_sub_state == APP_SUB_STATE_N){
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("1-GEAR : N");

                    lcd_set_cursor(LCD_LINE2,LCD_COL0);
                    lcd_send_string("2-SPEED:");
                    //lcd_print_number(uint16_g_last_reading[ADC_CH_0],LCD_LINE1,LCD_COL10);
                    en_gs_app_state = APP_STATE_MAIN;
                    break;
                }

                else if(en_gs_app_sub_state == APP_SUB_STATE_R){
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("1-GEAR : R");

                    lcd_set_cursor(LCD_LINE2,LCD_COL0);
                    lcd_send_string("2-SPEED : ");

                    en_gs_app_state = APP_STATE_MAIN;
                    break;
                }

                else if(en_gs_app_sub_state == APP_SUB_STATE_D){
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("1-GEAR : D");

                    lcd_set_cursor(LCD_LINE2,LCD_COL0);
                    lcd_send_string("2-SPEED : ");

                    en_gs_app_state = APP_STATE_MAIN;
                    break;
                }
                break;

            }

            case APP_STATE_SET_LIMIT:
            {
                /* Clear LCD */
                lcd_clear();

                SHOW_TITLE_CENTERED_ON_LCD();

                /* Set LCD Cursor position */
                lcd_set_cursor(LCD_LINE2,LCD_COL0);
                lcd_send_string(APP_STR_ENTER_SPD_LIMIT);

                lcd_set_cursor(LCD_LINE3,LCD_COL8);
                lcd_send_string(APP_STR_SPD_LIMIT_PLACEHOLDER);

                /* reset cursor to overwrite placeholder str with user input */
                lcd_set_cursor(LCD_LINE3,LCD_COL8);

                /* reset index flag */
                uint8_gs_set_speed_index = 3;
                break;
            }
        }

    /* Update global app state flag */
    en_gs_app_state = en_a_app_state;
}



static void app_reset_battery_drain_watchdog()
{
    /* Stop timer */
    TIMER1_STOP();

    /* Reset elapsed time */
    uint8_gs_seconds_elapsed = ZERO;
}

static void app_key_changed(en_read_states_t en_l_kl_state)
{
    switch (en_l_kl_state)
    {
        case OFF:
        {
            /* Stop watchdog */
            app_reset_battery_drain_watchdog();

            /* Switch to car on */
            app_switch_state(APP_CAR_OFF);

            /* reset sleep flag */
            bool_car_sleep_mode = FALSE;
            break;
        }
        case Ready:
        {
            /* Check if car is sleeping */
            if(TRUE == bool_car_sleep_mode)
            {
                /* Do Nothing */
            }
            else
            {
                app_switch_state(APP_CAR_READY);
            }
            break;
        }
        case ON:
        {
            /* Check if car is sleeping */
            /* Stop watchdog */
            app_reset_battery_drain_watchdog();

            /* Switch to car on */
            app_switch_state(APP_STATE_SHOW_OPTIONS);

            /* reset sleep flag */
            bool_car_sleep_mode = FALSE;
            break;
        }
    }
}


static void app_timer_tick_event(void)
{
    /* Timer Ticked 1 second */
    uint8_gs_seconds_elapsed++;
}

static void send_limit_speed(uint8_t_ uint8_a_speed )
{
	uint8_g_received_data=spi_transceiver(APP_COMM_CMD_START );
	
	while(uint8_g_received_data != APP_COMM_CMD_ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(APP_COMM_CMD_START);
	}
	
	
	uint8_g_received_data=spi_transceiver(APP_COMM_CMD_SENDING_SPD_LIMIT);
	while(uint8_g_received_data != APP_COMM_CMD_ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(APP_COMM_CMD_SENDING_SPD_LIMIT);
		
	}
	
	uint8_g_received_data=spi_transceiver(uint8_a_speed);
	while(uint8_g_received_data != APP_COMM_CMD_ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(uint8_a_speed);
	}
}

static void receive_limit_speed()
{
	uint8_g_received_data=spi_transceiver(APP_COMM_CMD_START );
	while(uint8_g_received_data != APP_COMM_CMD_ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(APP_COMM_CMD_START );
	}
	
	uint8_g_received_data=spi_transceiver(APP_COMM_CMD_REQUESTING_SPD_LIMIT);
	
	while(uint8_g_received_data != APP_COMM_CMD_ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(APP_COMM_CMD_REQUESTING_SPD_LIMIT);
	}
	delay_us(150);
	uint8_g_received_data=spi_transceiver(APP_COMM_CMD_REQUESTING_SPD_LIMIT);
	
	while(((uint8_g_received_data<30) || uint8_g_received_data>220))
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(APP_COMM_CMD_REQUESTING_SPD_LIMIT);
		
		
	}
}