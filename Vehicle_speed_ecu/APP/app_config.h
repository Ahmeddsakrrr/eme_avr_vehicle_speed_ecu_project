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

#define APP_STR_TITLE                   ((uint8_t_ *)"Team GUCALEX")
#define APP_STR_CAR_OFF                 ((uint8_t_ *)"Welcome .. GUCALEX")
#define APP_STR_CAR_READY               ((uint8_t_ *)"Please start Motor")
#define APP_STR_ENTER_SPD_LIMIT         ((uint8_t_ *)"Enter speed limit:")
#define APP_STR_SPD_LIMIT_PLACEHOLDER   ((uint8_t_ *)"_**")
#define APP_STR_SAVING_LIMIT            ((uint8_t_ *)"Please wait...")
#define APP_STR_OPT_DASHBOARD           ((uint8_t_ *)"(1) Dashboard")
#define APP_STR_OPT_SPEED_LIMIT_SW_OFF  ((uint8_t_ *)"(3) Limit OFF")
#define APP_STR_OPT_SPEED_LIMIT_SW_ON   ((uint8_t_ *)"(3) Limit  ON")
#define APP_STR_OPT_SET_SPEED_LIMIT     ((uint8_t_ *)"(2) Set Speed Limit")
#define APP_STR_ERROR                   ((uint8_t_ *)"Error")
#define APP_STR_L1_DASHBOARD_GEAR_P		((uint8_t_ *)"GEAR: P")
#define APP_STR_L1_DASHBOARD_GEAR_N		((uint8_t_ *)"GEAR: N")
#define APP_STR_L1_DASHBOARD_GEAR_R		((uint8_t_ *)"GEAR: R")
#define APP_STR_L1_DASHBOARD_GEAR_D		((uint8_t_ *)"GEAR: D")
#define APP_STR_L2_DASHBOARD_SPEED		((uint8_t_ *)"SPEED:   ")


#define KPD_MAIN                '1'
#define KPD_SET_LIMIT           '2'
#define KPD_SPEED_LIMIT_TOGGLE  '3'
#define SPEED_LIMIT_OFF     (0)
#define SPEED_LIMIT_ON      (1)

/* Keypad Layout
 *
 * {'1','2','3','P'}
 * {'4','5','6','R'}
 * {'7','8','9','N'}
 * {'X','0','K','D'}
 * */
#define KPD_CAR_MODE_P                  'P'
#define KPD_CAR_MODE_R                  'R'
#define KPD_CAR_MODE_N                  'N'
#define KPD_CAR_MODE_D                  'D'
#define KPD_OK                          'K'
#define KPD_EXIT                        'X'

#define APP_CAR_SPD_LIMIT_MIN_SPEED     (30)
#define APP_CAR_MAX_SPEED               (220)
#define APP_CAR_BATTERY_TIMEOUT_IN_SEC  (10)
#define APP_LDR_NIGHT_THRESHOLD         (30)
#define APP_NOTIFY_BUZZ_DURATION_MS     (70)
#endif /* APP_CONFIG_H_ */