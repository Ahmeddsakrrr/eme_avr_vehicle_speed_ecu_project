/*
 * app_config.h
 *
 * Created: 9/3/2023 11:54:54 AM
 *  Author: hacke
 */ 


#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
/*APP STRINGS*/

#define APP_STR_TITLE               "Team GUCALEX"
#define CAR_STATE                    "carstate"




#define MAIN                        '1'
#define SPEEDLIMIT                  '2'
#define SETLIMIT                    '3'


                                                                    /*      {'1','2','3','P'},
                                                                            {'4','5','6','R'},
                                                                            {'7','8','9','N'},
                                                                            {'+','0','K','D'},*/
#define KPD_CAR_MODE_P                  'P'
#define KPD_CAR_MODE_R                  'R'
#define KPD_CAR_MODE_N                  'N'
#define KPD_CAR_MODE_D                  'D'
#define KPD_OK                          'K'


#endif /* APP_CONFIG_H_ */