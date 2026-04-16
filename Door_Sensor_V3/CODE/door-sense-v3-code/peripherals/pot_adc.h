#ifndef POT_ADC_H
#define POT_ADC_H

/******************<Summary>*****************
 * Name: pot_adc.h
 * Purpose:
 *      > functions for measuring potentiometer values
 * 			using RP2350's ADC
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "pico/stdlib.h"

#include "hardware/adc.h"
#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
#define ADC_VREF				3.3f		// ADC VREF = 3.3V
#define ADC_RESOLUTION			4096.0f		// ADC resolution = 12-bit

#define MIN_COUNTDOWN_TIME		5
#define MAX_COUNTDOWN_TIME		15
/******************</Defines>*****************/


/******************<Global variables>*****************/
/******************</Global variables>*****************/


/******************<Function Declarations>*****************/
void init_potentiometer_adc();
float read_pot_val();
void update_countdown_duration(uint8_t* countdown_duration);
/******************</Function Declarations>*****************/

#endif // POT_ADC_H