/*
 * adc_private.h
 *
 * Created: 8/24/2023 11:32:44 AM
 *  Author: Hossam Elwahsh
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
#include "std.h"
#include "gpio_interface.h"
#include "bit_math.h"
#include "interrupts.h"

/* ADMUX - ADC Multiplexer selection register */
#define ADC_ADMUX_REG    *((volatile uint8_t_ *) 0x27)

/* ADC Reference Selection Bits
 * 00 : AREF, Internal Vref Turned off
 * 01 : AVCC With external capacitor at AREF pin
 * 10 : Reserved
 * 11 : Internal 2.56V with external VREF cap at AREF pin
 * */
#define ADC_ADMUX_REFS1_BIT 7
#define ADC_ADMUX_REFS0_BIT 6

/* ADC Left Adjust Result */
#define ADC_ADMUX_ADLAR_BIT 5

/* MUX Bits */
#define ADC_ADMUX_MUX4_BIT  4
#define ADC_ADMUX_MUX3_BIT  3
#define ADC_ADMUX_MUX2_BIT  2
#define ADC_ADMUX_MUX1_BIT  1
#define ADC_ADMUX_MUX0_BIT  0


/* ADCH - ADC Data register high byte */
#define ADC_ADCH_REG     *((volatile uint8_t_ *) 0x25)

/* ADCH - ADC Data register low byte */
#define ADC_ADCL_REG     *((volatile uint8_t_ *) 0x24)


/* ADCSRA - ADC Control and status register */
#define ADC_ADCSRA_REG   *((volatile uint8_t_ *) 0x26)

/* ADC Enable */
#define ADC_ADCSRA_ADEN_BIT     7

/* ADC Start Conversion */
#define ADC_ADCSRA_ADSC_BIT     6

/* ADC Auto Trigger */
#define ADC_ADCSRA_ADATE_BIT    5

/* ADC Interrupt Flag */
#define ADC_ADCSRA_ADIF_BIT     4

/* ADC Interrupt Enable */
#define ADC_ADCSRA_ADIE_BIT     3

/* ADC Prescaler Select Bit 2 */
#define ADC_ADCSRA_ADPS2_BIT    2

/* ADC Prescaler Select Bit 1 */
#define ADC_ADCSRA_ADPS1_BIT    1

/* ADC Prescaler Select Bit 0 */
#define ADC_ADCSRA_ADPS0_BIT    0


#define AVR_SREG_REG            *( ( volatile uint8_t_ * ) 0x5F )
#define AVR_SREG_GLOBAL_INTERRUPT_ENABLE_BIT      7

#endif /* ADC_PRIVATE_H_ */