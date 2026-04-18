#ifndef OPERATION_H
#define OPERATION_H

/******************<Summary>*****************
 * Name: operation.h
 * Purpose:
 *      > functions for main door sensor operation
 * 		> this exists to keep main.c as minimal as possible
 * 		> door-sense-v3 operation is contained here
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "pico/stdlib.h"

#include "pico/time.h"

#include "peripherals/lcd.h"
#include "peripherals/leds.h"
#include "peripherals/audio.h"
#include "peripherals/pot_adc.h"
#include "peripherals/switches.h"
#include "peripherals/tof.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
#define DOOR_OPEN_DISTANCE				200		// if object is within 200 distance units of sensor, door is considered OPEN

#define TOF_CHECK_INTERVAL_MS			150		// how often to check ToF sensor for data ready (in ms)
#define COUNTDOWN_UPDATE_INTERVAL_MS 	250		// how often to update the countdown (in ms)
#define SWITCH_CHECK_INTERVAL_MS		300		// how often to check digital switch & potentiometer values 
#define UPDATE_LCD_INTERVAL_MS			200		// how often to update the LCD
/******************</Defines>*****************/


/******************<Function Declarations>*****************/
void init_doorsense_peripherals();
void run_doorsense();
/******************</Function Declarations>*****************/

#endif // OPERATION_H