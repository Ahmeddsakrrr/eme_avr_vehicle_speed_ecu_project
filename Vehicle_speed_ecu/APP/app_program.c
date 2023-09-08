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

uint8_t_ uint8_g_received_data=0 ;

/* App functions prototypes */
static void send_limit_speed(uint8_t_ uint8_a_speed );
static void receive_limit_speed();
static void app_switch_state(en_app_state_t state);

/* App state */
static  en_app_state_t  en_gs_app_state   =                  APP_STATE_INIT_UI ;
static  en_app_sub_state_t  en_gs_app_sub_state   =          APP_SUB_STATE_P ;

/* App global variables */
uint8_t_ uint8_g_readings;
uint8_t_ uint8_Gear_mode =                         KPD_CAR_MODE_P;
uint8_t_ Speed_limit_f   =                           SPEED_LIMIT_OFF;
uint8_t_ uint8_g_kpd_value= NULL;
uint32_t_ uint16_throttle_g_readings;

/* Global static set speed index */
static uint8_t_ uint8_gs_set_speed_index= 3;

/* Global speed limit */
uint8_t_ uint8_g_speed_limit= 200;

void app_init(void)
{
    /* Init LCD */
    lcd_init();

    /* Init BUZZ */
    buzz_init();

    /* Init KL15 */
    KL_Switch_init();

    /*init ldr*/
    ldr_init();

    /* Init LED */
    Led_Init(LED_RED_ARGS);
    Led_Init(LED_GREEN_ARGS);
    Led_Init(LED_BLUE_ARGS);
    Led_Init(LED_YELLOW_ARGS);

    /* Init Throttle */
    throttle_init();

    /* Init Keypad */
    keypad_init();
	
	/* Init TIMER 2 */
	timer2_init(TIMER2_CTC_MODE);

}
void app_start(void)
{
    /* local variables */
    static uint8_t_  uint8_l_speed_limit_btn =0;

    /*get keypad current value*/
    uint8_g_kpd_value= keypad_read();

    while (TRUE) {

        uint8_g_kpd_value =keypad_read();

        uint16_throttle_g_readings= throttle_read_state();

        switch (en_gs_app_state)
        {

            case APP_STATE_INIT_UI:
            {
                app_switch_state(APP_STATE_INIT_UI);
                break;
            }

            case APP_STATE_SHOW_OPTIONS:
            {
                /* if set button is pressed */
                if(APP_STATE_SET_LIMIT == uint8_g_kpd_value)
                {
                    /* Switch state to set speed limit */
                    app_switch_state(APP_STATE_SET_LIMIT);
                }
                else if(APP_STATE_MAIN == uint8_g_kpd_value)
                {
                    /* Switch state to main */
                    app_switch_state(APP_STATE_MAIN);
                }
                else if(APP_STATE_SPEED_LIMIT_ON_OFF == uint8_g_kpd_value)
                {
                    /* Increment the speed limit btn variable */
                    uint8_l_speed_limit_btn++;
                    /* Switch state to limit on/off */
                    app_switch_state(APP_STATE_SPEED_LIMIT_ON_OFF);
                }
                else
                {
                    /* Do Nothing */
                }
                break;
            }

            case APP_STATE_MAIN:
            {
                if(KPD_CAR_MODE_P == uint8_g_kpd_value){
                    en_gs_app_sub_state=APP_SUB_STATE_P;
                    app_switch_state(APP_STATE_MAIN);

                }

                else if(KPD_CAR_MODE_R==uint8_g_kpd_value )
                {
                    en_gs_app_sub_state=APP_SUB_STATE_R;
                    app_switch_state(APP_STATE_MAIN);
                    Led_TurnOn(LED_YELLOW_ARGS);


                }
                else if(KPD_CAR_MODE_N==uint8_g_kpd_value) {
                    en_gs_app_sub_state = APP_SUB_STATE_N;
                    app_switch_state(APP_STATE_MAIN);
                    Led_Flip(LED_BLUE_ARGS);
                }
                else if(KPD_CAR_MODE_D==uint8_g_kpd_value) {
                    en_gs_app_sub_state = APP_SUB_STATE_D;
                    app_switch_state(APP_STATE_MAIN);
                    Led_TurnOn(LED_GREEN_ARGS);
                }

                           /* check the substates */
                if(en_gs_app_sub_state == APP_SUB_STATE_P) {
                     if(uint16_throttle_g_readings>0){
                         /* alert with the buzzer "you can't move the car in park mode */
                        buzz_on();
                        lcd_set_cursor(LCD_LINE3,LCD_COL0);
                        lcd_send_string("error ");
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
                else if (en_gs_app_sub_state == APP_SUB_STATE_N) {

                    LCD_printNumber(uint16_throttle_g_readings, LCD_LINE2, LCD_COL9);
                    delay_ms(5000);
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
            case APP_STATE_SPEED_LIMIT_ON_OFF:
            {
                if(uint8_l_speed_limit_btn % 2 == ZERO){
                    Speed_limit_f = SPEED_LIMIT_ON;

                }
                else if(uint8_l_speed_limit_btn %2 != ZERO){
                    Speed_limit_f = SPEED_LIMIT_OFF;
                }
                app_switch_state(APP_STATE_SPEED_LIMIT_ON_OFF);

                break;
            }
            case APP_STATE_SET_LIMIT:
            {
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

static void app_switch_state(en_app_state_t state){
    switch (state) {
        case APP_STATE_INIT_UI: {
            lcd_clear();
            lcd_send_string(APP_STR_TITLE);
            /*SWITCH TO STATE MAIN*/
            app_switch_state(APP_STATE_SHOW_OPTIONS);
            break;
        }
        case APP_STATE_SHOW_OPTIONS:
        {
            /* clear lcd */
            lcd_clear();

            /*show title*/
            lcd_send_string(APP_STR_TITLE);

            /* lcd shows the options int the main */
            lcd_set_cursor(LCD_LINE1, LCD_COL0);
            lcd_send_string("1-MAIN");

            lcd_set_cursor(LCD_LINE2, LCD_COL0);
            lcd_send_string("2-SPEEDLIMIT(ON/OFF)");

            lcd_set_cursor(LCD_LINE3, LCD_COL0);
            lcd_send_string("3-SET LIMIT");

            /* Update global app state flag */
            en_gs_app_state= APP_STATE_SHOW_OPTIONS;
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
            case APP_STATE_SPEED_LIMIT_ON_OFF:
            {
                /*clear lcd*/
                lcd_clear();
                if(Speed_limit_f == SPEED_LIMIT_OFF)
                {
                    /*INFORM THAT SPEED LIMIT IS OFF*/
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("Speed limit off");
                    delay_ms(300);
                    /*return back to the options menu */
                }
                else if(Speed_limit_f == SPEED_LIMIT_ON)
                {

                    /*INFORM THAT SPEED LIMIT IS ON*/
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("Speed limit on");
                    delay_ms(300);
                }
                en_gs_app_state= APP_STATE_SPEED_LIMIT_ON_OFF;
                break;
            }
            case APP_STATE_SET_LIMIT :
            {
                /* clear lcd */
                lcd_clear();

                /* Show Title */
                lcd_send_string(APP_STR_TITLE);

                /* Set LCD Cursor position */
                lcd_set_cursor(LCD_LINE2,LCD_COL7);
                lcd_send_string("Enter speed limit : ");

                /* reset index flag */
                uint8_gs_set_speed_index=3;

                /* Update the global state to set limit */
                en_gs_app_state = APP_STATE_SET_LIMIT;
                break;
            }
        }

    }


static void send_limit_speed(uint8_t_ uint8_a_speed )
{
	uint8_g_received_data=spi_transceiver(START );
	
	while(uint8_g_received_data!=ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(START);
	}
	
	
	uint8_g_received_data=spi_transceiver(SEND_LIMIT_SPEED);
	while(uint8_g_received_data!=ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(SEND_LIMIT_SPEED);
		
	}
	
	uint8_g_received_data=spi_transceiver(uint8_a_speed);
	while(uint8_g_received_data!=ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(uint8_a_speed);
	}
}

static void receive_limit_speed()
{
	uint8_g_received_data=spi_transceiver(START );
	while(uint8_g_received_data!=ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(START );
	}
	
	uint8_g_received_data=spi_transceiver(RECIVED_LIMIT_SPEED);
	
	while(uint8_g_received_data!=ACK)
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(RECIVED_LIMIT_SPEED);
	}
	delay_us(150);
	uint8_g_received_data=spi_transceiver(RECIVED_LIMIT_SPEED);
	
	while(((uint8_g_received_data<30) || uint8_g_received_data>220))
	{
		delay_us(5);
		uint8_g_received_data=spi_transceiver(RECIVED_LIMIT_SPEED);
		
		
	}
}