#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "hardware/dma.h"
#include "charlcd.h"

#include "pins.h"

/* ------------ Functions ----------- */
//Module init
void LCD_test(void);

/* ---------------------------------- */
#endif /* FUNCTIONS_H_ */