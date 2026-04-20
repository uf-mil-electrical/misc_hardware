#ifndef LEDS_H
#define LEDS_H

/******************<Summary>*****************
 * Name: leds.h
 * Purpose:
 *      > functions for LEDSs
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "pico/stdlib.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/



/******************<Global variables>*****************/
/******************</Global variables>*****************/



/******************<Function Declarations>*****************/
void init_leds();
void set_led(char led, bool state);
void set_all_leds(bool state);
/******************</Function Declarations>*****************/

#endif // LEDS_H