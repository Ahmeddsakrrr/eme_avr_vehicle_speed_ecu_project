/*
 * app_interface.h
 *
 * Created: 9/3/2023 11:54:20 AM
 *  Author: GUCALEX Team
 */ 


#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_


typedef enum
{
    APP_STATE_INIT_UI   =   0   ,
    APP_CAR_OFF                 ,
    APP_CAR_READY               ,
/*    APP_CAR_ON                  ,*/
    APP_STATE_SHOW_OPTIONS      ,
    APP_STATE_MAIN              ,
    APP_STATE_SET_LIMIT         ,
    APP_STATE_GET_LIMIT         ,
    APP_STATE_TOTAL
}en_app_state_t;

typedef enum
{
    APP_SUB_STATE_P =   0   ,
    APP_SUB_STATE_R         ,
    APP_SUB_STATE_N         ,
    APP_SUB_STATE_D         ,
    APP_SUB_STATE_TOTAL
}en_app_sub_state_t;



void app_init   (void);
void app_start  (void);


#endif /* APP_INTERFACE_H_ */