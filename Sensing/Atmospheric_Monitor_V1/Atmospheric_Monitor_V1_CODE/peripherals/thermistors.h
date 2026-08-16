#ifndef THERMISTORS_H
#define THERMISTORS_H

/******************<Summary>*****************
 * Name: thermistors.h
 * Purpose:
 *      > Functions for onboard LEDs
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/adc.h"

#include "peripherals/leds.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
// ADC operation
#define ADC_VREF				3.3f		// ADC VREF = 3.3V
#define ADC_RESOLUTION			4096.0f		// ADC resolution = 12-bit

#define RES_LADDER_RB           10000.0f    // other resistor in R_therm res ladder

// Thermistor detection voltage threshold
#define MIN_THERM_VOLTAGE       0.5         // if this or lower voltage measured, therm is assumed absent
/******************</Defines>*****************/



/******************<Structs>*****************/
/*******ntc_temp_refs*******
 * Description
        > stores values to be used to interpolate a temperature
            given a resistance from the NTC thermistor
        > NTC thermistor used: B57164K0103J000 (Digikey)
        > See thermistor datasheet, page 5, R/T no 1012
 * Data
        > float resistance: measured resistance of thermistor
        > int temperature: the temp (in C) that corresponds to the ratio value
*/
typedef struct {
    float resistance;
    int temperature;
} ntc_temp_refs;
/******************</Structs>*****************/



/******************<Function Declarations>*****************/
void init_thermistors();
void read_thermistor_value(uint8_t target_thermistor);
void scan_thermistors();
/******************</Function Declarations>*****************/

#endif // THERMISTORS_H
