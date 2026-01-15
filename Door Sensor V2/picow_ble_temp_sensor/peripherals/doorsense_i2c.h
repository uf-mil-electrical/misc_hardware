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
void init_i2c(i2c_inst_t* i2c_bus, uint baudrate, uint8_t SDA_pin, uint8_t SCL_pin);
int i2c_write_raw(i2c_inst_t* i2c_bus, uint8_t addr, uint8_t* data, uint8_t num_bytes);
int i2c_write_register(i2c_inst_t* i2c_bus, uint8_t addr, uint16_t reg, uint8_t* data, uint8_t num_bytes);
int i2c_read_register(i2c_inst_t* i2c_bus, uint8_t addr, uint16_t reg, uint8_t* data, uint8_t num_bytes);
void i2c_device_scan();
/******************</Functions>*****************/

#endif // DOORSENSE_I2C_H