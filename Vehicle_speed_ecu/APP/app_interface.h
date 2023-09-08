/*
 * app_interface.h
 *
 * Created: 9/3/2023 11:54:20 AM
 *  Author: GUCALEX Team
 */ 


#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_


/* Convert char to digit macro */
#define CONVERT_CHAR_TO_DIGIT(kpd_value) (kpd_value - '0')

/* Convert digit to char macro */
#define CONVERT_DIGIT_TO_CHAR(kpd_value) (kpd_value + '0')

typedef enum
{
    APP_STATE_INIT_UI=0,
    APP_STATE_SHOW_OPTIONS,
    APP_STATE_MAIN ,
    APP_STATE_SPEED_LIMIT_ON_OFF,
    APP_STATE_SET_LIMIT,
    APP_STATE_GET_LIMIT
}en_app_state_t;

typedef enum
{
    APP_SUB_STATE_P=0,
    APP_SUB_STATE_R,
    APP_SUB_STATE_N,
    APP_SUB_STATE_D,
}en_app_sub_state_t;



void app_init   (void);
void app_start  (void);


#endif /* APP_INTERFACE_H_ */