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
#define SET_GPIO_OUTPUT         true        // for use with gpio_set_dir
#define SET_GPIO_INPUT          false       // for use with gpio_set_dir
#define GPIO_SET_LOW            0           // for use with gpio_put
#define GPIO_SET_HIGH           1           // for use with gpio_put
/******************</General macros>*****************/


/******************<SPI Setup>*****************/
#define SPI_PORT 				spi0
#define SPI_SPEED				1000*1000	// operate at 1MHz
#define CS_PIN   				10
#define SCK_PIN  				6
#define MOSI_PIN 				3
/******************</SPI Setup>*****************/



/******************<Switch Setup>*****************/
#define SW_0_PIN				16
#define SW_1_PIN				17
#define FREQ_SWITCH_PIN			28
#define AMP_SWITCH_PIN			26

#define FREQ_ADC_CHANNEL		2		// GP28 is ADC Ch 2
#define AMP_ADC_CHANNEL			0		// GP26 is ADC Ch 1
/******************</Switch Setup>*****************/


/******************<DAC Setup>*****************/
#define SAMPLE_RATE		10000.0f						// 10kHz sample rate
#define SAMPLE_DELAY	(SPI_SPEED / (int)SAMPLE_RATE)	// time to delay between updating values
/******************</DAC Setup>*****************/


/******************<Functions>*****************/
/******************</Functions>*****************/


#endif // PINS_H