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
/*APP STRINGS*/

#define APP_STR_TITLE               "Team GUCALEX"
#define CAR_STATE                    "carstate"




#define KPD_MAIN                                    '1'
#define KPD_SPEEDLIMIT                              '2'
#define KPD_SETLIMIT                                '3'
#define SPEED_LIMIT_OFF                              0
#define SPEED_LIMIT_ON                               1
#define speed_


                                                                    /*      {'1','2','3','P'},
                                                                            {'4','5','6','R'},
                                                                            {'7','8','9','N'},
                                                                            {'+','0','K','D'},*/
#define KPD_CAR_MODE_P                  'P'
#define KPD_CAR_MODE_R                  'R'
#define KPD_CAR_MODE_N                  'N'
#define KPD_CAR_MODE_D                  'D'
#define KPD_OK                          'K'




#define   ACK                             1
#define   NO_ACK                          0

#define   START                           5
#define   SEND_LIMIT_SPEED                10
#define   RECIVED_LIMIT_SPEED             15

#define   MIN_SPEED                       30
#define   MAX_SPEED                       220
#define   EEPROM_ADDRESS                  5


#endif /* APP_CONFIG_H_ */