#ifndef SWITCHES_H
#define SWITCHES_H

/******************<Summary>*****************
 * Name: switches.h
 * Purpose:
 *      > functions for digital switches
 * 		> prompt type and override switches only
 * 		> for countdown_length pot, see pot_adc.h
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
void init_switches();
void get_sw_state(char sw, bool *current_state);
/******************</Function Declarations>*****************/

#endif // SWITCHES_H