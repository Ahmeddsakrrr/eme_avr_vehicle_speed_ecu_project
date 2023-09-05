/*
 * app_interface.h
 *
 * Created: 9/3/2023 11:54:20 AM
 *  Author: hacke
 */ 


#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_



typedef enum
{
    APP_STATE_INIT_UI=0,
    APP_STATE_SHOW_OPTIONS,
    APP_STATE_MAIN ,
    APP_STATE_SPEED_LIMIT_ON_OFF,
    APP_STATE_SET_LIMIT,
    APP_STATE_SHOW_CAR_STATE
}en_app_state_t;



void app_init   (void);
void app_start  (void);


#endif /* APP_INTERFACE_H_ */