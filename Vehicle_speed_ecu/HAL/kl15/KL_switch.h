/*
 * IncFile1.h
 *
 * Created: 8/27/2023 9:21:41 AM
 *  Author: A M
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#include "adc_interface.h"


typedef enum
{
    OFF =0 ,
    Ready ,
    ON,
    SKIP
}en_read_states_t;

typedef enum
{
    KLSWITCH_OK = 0      ,
    KLSWITCH_ERROR,
    KLSWITCH_TOTAL
}en_klswitch_t;


en_klswitch_t KL_Switch_init();
en_read_states_t KL_Switch_Read_state(void);



#endif /* INCFILE1_H_ */