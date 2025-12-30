#ifndef DOORSENSE_I2C_H
#define DOORSENSE_I2C_H

/******************<Summary>*****************
 * Name: doorsense_i2c.h
 * Purpose:
 *      > Functions for I2C communication
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/i2c.h"

#include "setup.h"
/******************</Dependencies>*****************/


/******************<Defines>*****************/
#define I2C_TIMEOUT_DELAY       1000     // for I2C read: wait 1000us, then proceed if no data is captured
/******************</Defines>*****************/


/******************<Functions>*****************/
void init_doorsense_i2c(void);
/******************</Functions>*****************/

#endif // DOORSENSE_I2C_H