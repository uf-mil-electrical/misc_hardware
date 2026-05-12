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
volatile uint8_t dummy_dma_value1 = 0;
volatile uint8_t dummy_dma_value2 = 0;


int main()
{
    init_uart(); // remove when working
    init_pio();
    init_dma();

    while (true) 
    {
        printf("\nbody of code reached\n");

        sleep_ms(100);
        color_output = 0xFF000000;
        sleep_ms(100);
        color_output = 0x00FF0000;
        sleep_ms(100);
        color_output = 0x0000FF00;

        
    }
}
