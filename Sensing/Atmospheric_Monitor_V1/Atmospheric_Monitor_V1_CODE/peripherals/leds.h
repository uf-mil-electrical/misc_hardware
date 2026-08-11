#ifndef LEDS_H
#define LEDS_H

/******************<Summary>*****************
 * Name: leds.h
 * Purpose:
 *      > Functions for onboard LEDs
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/pwm.h"
#include "pico/time.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Function Declarations>*****************/
void set_led(uint8_t led, bool state);
void set_all_led(bool state);
void init_leds();
/******************</Function Declarations>*****************/

#endif // LEDS_H
