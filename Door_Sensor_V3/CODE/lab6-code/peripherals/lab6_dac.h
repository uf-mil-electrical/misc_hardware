#ifndef LAB6_DAC_H
#define LAB6_DAC_H

/******************<Summary>*****************
 * Name: lab6_dac.h
 * Purpose:
 *      > Updates the DAC to output a waveform
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "pico/stdlib.h"

#include "hardware/spi.h"

#include "peripherals/lab6_spi.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/



/******************<Global variables>*****************/
/******************</Global variables>*****************/



/******************<Function Declarations>*****************/
void lab6_dac_write(uint8_t channel, uint16_t value);
float get_sample_delay();
void update_waveform();
/******************</Function Declarations>*****************/

#endif // LAB6_DAC_H