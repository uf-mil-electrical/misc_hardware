#ifndef TOF_I2C_H
#define TOF_I2C_H

/******************<Summary>*****************
 * Name: tof_i2c.h
 * Purpose:
 *      > Provides helper functions for reading/writing to the ToF sensor
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
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Functions>*****************/
void tof_read_byte(uint16_t reg, uint8_t* data);
void tof_read_word(uint16_t reg, uint16_t* data);
void tof_read_2_words(uint16_t reg, uint32_t* data);

void tof_write_byte(uint16_t reg, uint8_t data);
void tof_write_word(uint16_t reg, uint16_t data);
void tof_write_2_words(uint16_t reg, uint32_t data);
/******************</Functions>*****************/

#endif // TOF_I2C_H