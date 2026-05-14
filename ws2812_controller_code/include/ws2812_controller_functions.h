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

bool config_neopixel_gpio_pins(int gpio_pin1, int gpio_pin2);
struct configSettings start_output_solid_mode(int num_pixels, PIO pio_used_for_NP);
bool start_output_animated_mode();
bool stop_color_output();
void set_color_solid_mode(uint8_t red_value, uint8_t blue_value, uint8_t green_value);
bool set_color_animated_mode();


typedef struct configSettings {
    int num_pixels;

    PIO pio;
    uint sm;
    uint offset;

    int new_output_dma_channel;
    int to_pio_dma_channel;
    dma_channel_config new_output_dma_channel_config;
    dma_channel_config to_pio_dma_channel_config;

} configSettings_t;


// Data will be copied from location of color_red to DREQ_PIO0_TX
extern volatile uint32_t color_output; // output a red light, color is GRB value 2 zeros at end for padding
extern volatile uint sm_g;