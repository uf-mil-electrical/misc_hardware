#ifndef DOOR_STATE_H
#define DOOR_STATE_H

/******************<Summary>*****************
 * Name: door_state.h
 * Purpose:
 *      > Major functions for regular operation
 * 		> E.g., determining if door open, pushing update to Discord, etc.
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "setup.h"

#include "tof_lib/tof_core.h"
#include "tof_lib/tof_i2c.h"
#include "tof_lib/tof_registers.h"

#include "peripherals/doorsense_gpio.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Functions>*****************/
bool is_door_open();
void run_door_sensor();
/******************</Functions>*****************/

#endif // DOOR_STATE_H