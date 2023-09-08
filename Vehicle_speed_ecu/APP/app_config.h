/*
 * app_config.h
 *
 * Created: 9/3/2023 11:54:54 AM
 *  Author: GUCALEX Team
 */ 


#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/* App Lights */
#define APP_INTERIOR_LIGHT_ARGS         LED_RED_ARGS
#define APP_INTERIOR_LIGHT_PORT         LED_RED_PIN
#define APP_INTERIOR_LIGHT_PIN          LED_RED_PORT

#define APP_CAR_FRONT_LEFT_LIGHT_ARGS   LED_BLUE_ARGS
#define APP_CAR_FRONT_LEFT_LIGHT_PIN    LED_BLUE_PIN
#define APP_CAR_FRONT_LEFT_LIGHT_PORT   LED_BLUE_PORT

#define APP_CAR_FRONT_RIGHT_LIGHT_ARGS  LED_GREEN_ARGS
#define APP_CAR_FRONT_RIGHT_LIGHT_PIN   LED_GREEN_PIN
#define APP_CAR_FRONT_RIGHT_LIGHT_PORT  LED_GREEN_PORT

/*APP STRINGS */

#define APP_STR_TITLE               "Team GUCALEX"

#define APP_STR_CAR_OFF     "Welcome .. GUCALEX"
#define APP_STR_CAR_READY   "Please start Motor"
#define APP_STR_CAR_RUNNING   "Car Motor Running."


#define KPD_MAIN            '1'
#define KPD_SPEED_LIMIT     '2'
#define KPD_SET_LIMIT       '3'
#define SPEED_LIMIT_OFF     (0)
#define SPEED_LIMIT_ON      (1)

/* Keypad Layout
 *
 * {'1','2','3','P'}
 * {'4','5','6','R'}
 * {'7','8','9','N'}
 * {'+','0','K','D'}
 * */
#define KPD_CAR_MODE_P                  'P'
#define KPD_CAR_MODE_R                  'R'
#define KPD_CAR_MODE_N                  'N'
#define KPD_CAR_MODE_D                  'D'
#define KPD_OK                          'K'

#define   APP_CAR_SPD_LIMIT_MIN_SPEED   (30)
#define   APP_CAR_MAX_SPEED             (220)
#define APP_CAR_BATTERY_TIMEOUT_IN_SEC  (10)
#define APP_LDR_NIGHT_THRESHOLD         (55)

#endif /* APP_CONFIG_H_ */