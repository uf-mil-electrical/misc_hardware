#ifndef DOORSENSE_TOF_H
#define DOORSENSE_TOF_H

/******************<Summary>*****************
 * Name: doorsense_tof.h
 * Purpose:
 *      > Functions for communicating with ToF Sensor
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"

#include "setup.h"
#include "peripherals/doorsense_i2c.h"

#include "TOF_API/core/inc/vl53l1_api.h"
/******************</Dependencies>*****************/


/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Functions>*****************/
void init_tof(void);
void DEBUG_read_tof(uint8_t addr, uint16_t reg, uint8_t* data, uint8_t num_bytes);
/******************</Functions>*****************/

#endif // DOORSENSE_TOF_H
