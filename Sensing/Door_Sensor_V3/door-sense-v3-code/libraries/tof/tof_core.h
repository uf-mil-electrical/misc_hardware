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

#include "pins.h"

#include "libraries/tof/tof_i2c.h"
#include "libraries/tof/tof_registers.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
#define VL53L1X_SENSOR_ID		0xEACC		// expected model ID & type for this ToF sensor
/******************</Defines>*****************/


/******************<Structs>*****************/

// Used when measuring distance to door
// Includes distance and also the tof sensor's status on whether it was a valid measurement or not
typedef struct {
    uint16_t distance_mm;
    uint8_t  range_status;
    bool     target_detected;
} tof_measurement_t;
/******************</Structs>*****************/


/******************<Functions>*****************/
int tof_init();
void tof_enable(bool enable);
uint16_t tof_get_id();
uint8_t tof_check_booted();
uint8_t tof_check_data_ready();
void tof_set_int_priority(bool active_high);
uint8_t tof_get_int_polarity();
void tof_clear_int();
uint8_t tof_get_distance_mode();
int tof_set_distance_mode(uint8_t mode);
uint16_t tof_get_timing_budget();
int tof_set_timing_budget(uint16_t time_budget);
uint16_t tof_get_measurement_period();
void tof_set_measurement_period();
uint16_t tof_get_distance();
uint8_t tof_get_range_status();
tof_measurement_t tof_get_measurement();
/******************</Functions>*****************/

#endif // TOF_CORE_H