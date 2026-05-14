/*
Notes for future expansion: 
 -  will need to define what state machines are called.
    could see error where sm called is incorrect, use pio_get_dreq()

 -  when making library, make sure the color output is passed as 3 RGB values
    and have library take care of formatting

Next steps:

 - clock speed and timing is current issue

*/

#include "ws2812_controller_functions.h"


// 0x FF 00 00 GREEN
// 0x 00 FF 00 RED
// 0x 00 00 FF BLUE

volatile uint32_t color_output = 0x0000FF00; // output a red light, color is GRB value 2 zeros at end for padding
volatile uint sm_g = 0;
const uint8_t dummy_dma_value1 = 0;
const uint8_t dummy_dma_value2 = 0;


configSettings_t neopix_settings;
PIO pio_used_for_NP = pio0;

int main()
{

    set_color_solid_mode(150, 0 ,0);
    neopix_settings = start_output_solid_mode(3, pio_used_for_NP);

    while (true) 
    {
        printf("\nbody of code reached\n");

        //gpio i dont want to write it rn
        set_color_solid_mode(150, 0 ,0);
        sleep_ms(500);
        set_color_solid_mode(0, 150 ,0);
        sleep_ms(500);
        set_color_solid_mode(0, 0 ,150);
        sleep_ms(500);
    }
}
