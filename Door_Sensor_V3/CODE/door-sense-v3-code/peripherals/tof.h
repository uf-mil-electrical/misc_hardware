#ifndef TOF_H
#define TOF_H

/******************<Summary>*****************
 * Name: pot_adc.h
 * Purpose:
 *      > high-level functions for interacting with
 * 			the ToF sensor and its library
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "pico/stdlib.h"

#include "pins.h"
#include "libraries/tof/tof_calibration.h"
#include "libraries/tof/tof_core.h"
#include "libraries/tof/tof_i2c.h"
#include "libraries/tof/tof_registers.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Global variables>*****************/
/******************</Global variables>*****************/


/******************<Function Declarations>*****************/
void get_distance(uint16_t* distance, bool* data_read);
/******************</Function Declarations>*****************/

#endif // TOF_H