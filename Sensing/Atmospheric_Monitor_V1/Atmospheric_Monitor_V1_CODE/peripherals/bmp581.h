#ifndef BMP581_H
#define BMP581_H

/******************<Summary>*****************
 * Name: bmp581.h
 * Purpose:
 *      > Functions for interacting with BMP581 sensor
 *      > BMP581: absolute barometric pressure sensor,
 *          can also measure temperature
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"

#include "communication/pico_spi.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Function Declarations>*****************/
void set_bmp581_cs(bool state);
void init_bmp581();
/******************</Function Declarations>*****************/

#endif // BMP581_H
