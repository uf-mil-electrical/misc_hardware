#ifndef SETUP_H
#define SETUP_H

/******************<Summary>*****************
 * Name: setup.h
 * Purpose:
 *      > Define GPIO pins for use on Door Sensor Board
 *      > Provide macros needed for initializing peripherals
 *      > Provide declarations for functions used in main.c (Door-Sensor-V2.c)
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
/******************</Dependencies>*****************/


/******************<Endianness Conversions>*****************/
#ifndef htons
#define htons(x)	((uint16_t)(((uint16_t)(x) & 0x00ff) << 8 |		\
            ((uint16_t)(x) & 0xff00) >> 8))
#define ntohs(x)	htons(x)
#endif

#ifndef htonl
#define htonl(x)	((uint32_t)(((uint32_t)(x) & 0x000000ff) << 24 |	\
            ((uint32_t)(x) & 0x0000ff00) << 8  | 			\
            ((uint32_t)(x) & 0x00ff0000) >> 8  |			\
            ((uint32_t)(x) & 0xff000000) >> 24))
#define ntohl(x)	htonl(x)
#endif
/******************</Endianness Conversions>*****************/


/******************<General macros>*****************/
#define SET_GPIO_OUTPUT         true        // for use with gpio_set_dir
#define SET_GPIO_INPUT          false       // for use with gpio_set_dir
#define GPIO_SET_LOW            0           // for use with gpio_put
#define GPIO_SET_HIGH           1           // for use with gpio_put
/******************</General macros>*****************/



/******************<SPI Setup>*****************/
#define SPI_SPEED               1000*1000   // 1 MHz
#define SPI_PORT                spi1        // SPI port to use
/******************</SPI Setup>*****************/


/******************<I2C Setup>*****************/
#define RP2350_I2C_ADDRESS      0x40        // I2C address for this board
/******************</I2C Setup>*****************/


/******************<UART Setup>*****************/
#define UART_ID_DFPLAYER        uart0       // UART port to use for DFplayer
#define UART_ID_SPARE           uart1       // extra UART port
#define UART_BAUD_RATE          115200
/******************</UART Setup>*****************/



/******************<ToF Setup>*****************/
#define TOF_I2C_BAUDRATE        100*1000    // initialize I2C at 100 kHz
#define TOF_I2C_PORT            i2c1        // I2C port to use for ToF
#define TOF_I2C_ADDRESS         0x29        // stupid fuckass datasheet oml
/******************<ToF Setup>*****************/



/******************<GPIO Definitions>*****************/
// Override Switch
#define SW_OVERRIDE_PIN         6
#define SW_NORMAL_PIN           7

// LEDs
#define GREEN_LED               8
#define RED_LED                 9

// Reed Switch
#define REED_NO_PIN             18
#define REED_NC_PIN             19

// ToF GPIO
#define TOF_GPIO1_PIN           20
#define TOF_XSHUT_PIN           21

// Misc GPIO (not currently in use on V2)
#define GPIO26_PIN              26
#define GPIO27_PIN              27
#define GPIO28_PIN              28

// UART pins
#define DF_UART_TX_PIN          16
#define DF_UART_RX_PIN          17
#define SPARE_UART_TX_PIN       4
#define SPARE_UART_RX_PIN       5

// SPI pins
#define PIN_SCK                 10
#define PIN_MOSI                11
#define PIN_MISO                12

// I2C pins
#define TOF_SDA                 14
#define TOF_SCL                 15
/******************</GPIO Definitions>*****************/



#endif // SETUP_H