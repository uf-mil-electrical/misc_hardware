/*

Header file for the code controlling ws2812 LEDs. 

*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h" 
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "LED_output.pio.h"

#define NUMBER_OF_NP 3

// Additional initialization functions
void init_dma();
void init_pio();


// Data will be copied from location of color_red to DREQ_PIO0_TX
extern volatile uint32_t color_output; // output a red light, color is GRB value 2 zeros at end for padding
extern volatile uint sm_g;

