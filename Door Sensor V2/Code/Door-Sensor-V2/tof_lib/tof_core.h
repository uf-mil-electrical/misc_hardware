#ifndef TOF_CORE_H
#define TOF_CORE_H

/******************<Summary>*****************
 * Name: tof_core.h
 * Purpose:
 *      > Provides declarations for functions responsible for core ToF functionality
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

#include "tof_lib/tof_i2c.h"
#include "tof_lib/tof_registers.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
#define VL53L1X_SENSOR_ID		0xEACC		// expected model ID & type for this ToF sensor
/******************</Defines>*****************/


/******************<Functions>*****************/
void tof_init();
void tof_enable(bool enable);
uint16_t tof_get_id();
uint8_t tof_check_booted();
uint8_t tof_check_data_ready();
void tof_set_int_priority(bool active_high);
bool tof_get_int_polarity();
void tof_clear_int();
uint8_t tof_get_distance_mode();
int tof_set_distance_mode(uint8_t mode);
uint16_t tof_get_timing_budget();
int tof_set_timing_budget(uint16_t time_budget);
uint16_t tof_get_measurement_period();
void tof_set_measurement_period();
uint16_t tof_get_distance();
/******************</Functions>*****************/

#endif // TOF_CORE_H