/*
 * app_program.c
 *
 * Created: 9/3/2023 11:54:14 AM
 *  Author: GUCALEX Team
 */

#include "app_interface.h"
#include "app_config.h"
#include "app_private.h"
#include "lcd_interface.h"
#include "throttle.h"

static void app_switch_state(en_app_state_t state);
/*App state */
static  en_app_state_t  en_gs_app_state   =                  APP_STATE_INIT_UI ;
static  en_app_state_t  en_gs_next_app_state =               APP_STATE_INIT_UI ;

/*APP GLOBAL VARIABLES*/
uint8_t_ uint8_g_readings;
uint8_t_ uint8_Gear_mode =                         KPD_CAR_MODE_P;
uint8_t_ Speed_limit_f   =                           SPEED_LIMIT_OFF;

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

    /* Init LCD */
    lcd_init();


}
void app_start(void)
{
    /*local variabes*/
    uint8_t_ uint8_kpd_value;

    /*init local variables*/
     uint8_kpd_value=NULL;
     /*get keypad current value*/


    while (TRUE) {
        uint8_kpd_value =keypad_read();

        switch (en_gs_app_state)
        {

            case APP_STATE_INIT_UI:
            {
                app_switch_state(APP_STATE_INIT_UI);
                break;
            }

            case APP_STATE_SHOW_OPTIONS:
            {
                /*if btn is pressed*/
                if(KPD_MAIN == uint8_kpd_value)
                {
                    en_gs_next_app_state=APP_STATE_MAIN;
                    app_switch_state(APP_STATE_MAIN);

                }
                else if(KPD_SPEEDLIMIT == uint8_kpd_value)
                {
                en_gs_next_app_state=APP_STATE_SPEED_LIMIT_ON_OFF;
                    app_switch_state(APP_STATE_SPEED_LIMIT_ON_OFF);

                }

                break;
            }

            case APP_STATE_MAIN:
            {
                break;
            }
            case APP_STATE_SPEED_LIMIT_ON_OFF:
            {
                break;
            }
            case APP_STATE_SET_LIMIT:
            {
                break;
            }
            case APP_STATE_SHOW_CAR_STATE:
            {
                if(APP_STATE_MAIN==en_gs_next_app_state ){
                    app_switch_state(APP_STATE_MAIN);
                }
                else if (APP_STATE_SPEED_LIMIT_ON_OFF==en_gs_next_app_state)
                {
                    app_switch_state(APP_STATE_SPEED_LIMIT_ON_OFF);
                }
                else if(APP_STATE_SET_LIMIT==en_gs_next_app_state)
                {
                    app_switch_state(APP_STATE_SET_LIMIT);
                }
                else if(APP_STATE_SHOW_CAR_STATE==en_gs_next_app_state){
                    app_switch_state(APP_STATE_SHOW_CAR_STATE);
                }
                else {
                    /*Do nothing*/
                }
                break;
            }
            default:
                break;
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
            /*clear lcd*/
            lcd_clear();
            /*show title*/
            lcd_send_string(APP_STR_TITLE);
            /*lcd shows the options int the main..*/
            lcd_set_cursor(LCD_LINE1,LCD_COL0);
            lcd_send_string("1-MAIN");

            lcd_set_cursor(LCD_LINE2,LCD_COL0);
            lcd_send_string("2-SPEEDLIMIT(ON/OFF)");

            lcd_set_cursor(LCD_LINE3,LCD_COL0);
            lcd_send_string("3-SET LIMIT");
            en_gs_app_state=APP_STATE_SHOW_OPTIONS;
            break;
            case     APP_STATE_MAIN :
            {
                lcd_clear();

                if(uint8_g_readings==KPD_CAR_MODE_P){

                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("1-GEAR : P");

                    lcd_set_cursor(LCD_LINE2,LCD_COL0);
                    lcd_send_string("2-SPEED : 0");

                    if(uint16_g_last_reading[ADC_CH_0]>0){
                        /*alert with the buzzer "you can't move the car in park mode"*/
                        buzz_on();
                        lcd_set_cursor(LCD_LINE3,LCD_COL0);
                        lcd_send_string("you can't move the car in park mode");
                    }
                    en_gs_app_state = APP_STATE_MAIN;
                    break;
                }


                if(uint8_g_readings==KPD_CAR_MODE_N){
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("1-GEAR : N");

                    lcd_set_cursor(LCD_LINE2,LCD_COL0);
                    lcd_send_string("2-SPEED : ");
                    lcd_print_number(uint16_g_last_reading[ADC_CH_0],LCD_LINE1,LCD_COL10);
                    en_gs_app_state = APP_STATE_MAIN;
                    break;
                }



                if(uint8_g_readings==KPD_CAR_MODE_R){
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("1-GEAR : R");

                    lcd_set_cursor(LCD_LINE2,LCD_COL0);
                    lcd_send_string("2-SPEED : ");

                    /*speed will be max 30 km/hr in reverse mood*/
                    if(uint16_g_last_reading[ADC_CH_0]<30)
                    {
                        lcd_print_number(uint16_g_last_reading[ADC_CH_0], 1, 10);
                    }
                    else if(uint16_g_last_reading[ADC_CH_0]>30){
                        lcd_print_number(30,LCD_LINE1,LCD_COL10);
                    }

                    en_gs_app_state = APP_STATE_MAIN;
                    break;
                }


            }
            case APP_STATE_SPEED_LIMIT_ON_OFF:
            {
                /*clear lcd*/
                lcd_clear();
                if(Speed_limit_f == SPEED_LIMIT_OFF)
                {
                    /*INFORM THAT SPEED LIMIT IS OFF*/
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("Speed limit turned off");
                    /*return back to the options menu */
                }
                else if(Speed_limit_f == SPEED_LIMIT_ON)
                {
                    /*INFORM THAT SPEED LIMIT IS ON*/
                    lcd_set_cursor(LCD_LINE1,LCD_COL0);
                    lcd_send_string("Speed limit turned on");
                    Speed_limit_f = SPEED_LIMIT_OFF;
                }
                
                
                
                
                
                

                app_switch_state(APP_STATE_SHOW_OPTIONS);
                break;
            }
            case APP_STATE_SET_LIMIT :
            {
                /*clear lcd*/
                lcd_clear();
                /**/
                lcd_set_cursor(LCD_LINE1,LCD_COL0);
                lcd_send_string("Enter speed limit : ");

                en_gs_app_state = APP_STATE_SET_LIMIT;
                break;

            }
            case APP_STATE_SHOW_CAR_STATE:
            {
                /*clear lcd*/
                lcd_clear();
                lcd_send_string(APP_STR_TITLE);
                lcd_set_cursor(LCD_LINE2,LCD_COL0);
                lcd_send_string(CAR_STATE);
                en_gs_app_state = APP_STATE_SHOW_CAR_STATE;

            }
        }
        default:
            break;
    }


}