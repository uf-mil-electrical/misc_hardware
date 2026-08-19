#ifndef PICO_SPI_H
#define PICO_SPI_H

/******************<Summary>*****************
 * Name: pico_spi.h
 * Purpose:
 *      > Functions for SPI communication
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "pins.h"
/******************</Dependencies>*****************/


/******************<Defines>*****************/
#define SPI_TIMEOUT_DELAY       1000     // for SPI read: wait 1000us, then proceed if no data is captured
/******************</Defines>*****************/


/******************<Functions>*****************/
//void init_pico_i2c(i2c_inst_t* i2c_bus, uint8_t sda_pin, uint8_t scl_pin, uint baudrate, bool master_mode);
//void pico_i2c_read(i2c_inst_t* i2c_bus, uint8_t read_address, uint8_t* data, uint8_t num_bytes);
//void pico_i2c_write(i2c_inst_t* i2c_bus, uint8_t write_address, uint8_t* data, uint8_t num_bytes);
/******************</Functions>*****************/



#endif // PICO_SPI_H