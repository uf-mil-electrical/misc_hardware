#ifndef PINS_H
#define PINS_H

/******************<Summary>*****************
 * Name: pins.h
 * Purpose:
 *      > Defines pins used for this project
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
/******************</Dependencies>*****************/


/******************<General macros>*****************/
#define GPIO_SET_LOW            0           // for use with gpio_put
#define GPIO_SET_HIGH           1           // for use with gpio_put
/******************</General macros>*****************/


/******************<LEDs>*****************/
#define LED_Y0_PIN              19
#define LED_Y1_PIN              20
#define LED_Y2_PIN              21
#define LED_Y3_PIN              22

#define LED_R_PIN               9
#define LED_G_PIN               10
#define LED_B_PIN               11
/******************</LEDs>*****************/


/******************<BMP581 Sensor>*****************/
#define BMP581_SPI_BUS          spi0
#define BMP581_SPI_BAUDRATE     100 * 1000      // init at 100kHz

#define BMP581_CS_PIN           1
#define BMP581_SCK_PIN          2
#define BMP581_MOSI_PIN         3
#define BMP581_MISO_PIN         4

#define BMP581_INT_PIN          5
/******************</BMP581 Sensor>*****************/


#endif // PINS_H