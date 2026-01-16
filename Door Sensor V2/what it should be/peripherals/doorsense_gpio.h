#ifndef DOORSENSE_GPIO_H
#define DOORSENSE_GPIO_H

/******************<Summary>*****************
 * Name: doorsense_gpio.h
 * Purpose:
 *      > Functions for initializing all non-communication pins
 *      > Includes functions for on-board LEDs, switches
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"

#include "setup.h"
/******************</Dependencies>*****************/


/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Functions>*****************/
void init_doorsense_leds();
void set_led(char target, bool value);
/******************</Functions>*****************/

#endif // DOORSENSE_GPIO_H