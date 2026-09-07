/*

File containing the .c functions that control the neopixels

*/

#include "ws2812_controller_functions.h"

volatile uint32_t color_output_solid; 

extern configSettings_t neopix_settings;

// extern volatile uint sm_g;
extern volatile uint8_t dummy_dma_value1;
extern volatile uint8_t dummy_dma_value2;
// static int to_pio_dma_channel;
// static int new_output_dma_channel;


/*


*/
void __isr dma_irq_handler() {
    if (dma_channel_get_irq0_status(neopix_settings.to_pio_dma_channel)) {
        dma_channel_acknowledge_irq0(neopix_settings.to_pio_dma_channel);

        // Wait for FIFO to drain — this is fast, just a few cycles
        while (!pio_sm_is_tx_fifo_empty(neopix_settings.pio, neopix_settings.sm));

        // Re-arm to_pio but don't start — reset_timer will chain to it
        dma_channel_set_read_addr(neopix_settings.to_pio_dma_channel, &color_output, false);
        dma_channel_set_trans_count(neopix_settings.to_pio_dma_channel, neopix_settings.num_pixels, false);

        // Start the reset timer channel — it will chain to to_pio after 50us
        dma_channel_set_trans_count(neopix_settings.new_output_dma_channel, 1, true);
    }
}


/*

config_neopixel_gpio_pins(int gpio_pin1, int gpio_pin2)

Starts output of a solid color to the neopixel pins. Claims and starts relevant pio state machines and 2 DMA channels. 
Must be used after a function to set the color output.

*/
bool config_neopixel_gpio_pins(int gpio_pin1, int gpio_pin2)
{

}



/*

set_color_solid_mode(uint8_t red_value, uint8_t blue_value, uint8_t green_value)

Sets the color that will be output by the NeoPixels in solid color mode. 

*/
void set_color_solid_mode(uint8_t red_value, uint8_t blue_value, uint8_t green_value)
{
    // NP color is GRB order 2 zeros at end for padding
    color_output_solid = (green_value << 24) | (red_value << 16) | (blue_value << 8);
}



/*

*/
bool set_color_animated_mode()
{

}




/*

*/
struct configSettings start_output_solid_mode(int num_pixels, PIO pio_used_for_NP)
{
    // this struct holds all the configuration settings of the neopixel thing
    struct configSettings np_settings;

    // definition of variables to start program
    np_settings.num_pixels = num_pixels;
    np_settings.pio = pio_used_for_NP;
    np_settings.sm = pio_claim_unused_sm(np_settings.pio, true);
    np_settings.offset = pio_add_program(np_settings.pio, &LED_output_program);

    // properly load .pio program
    LED_output_program_init(np_settings.pio, np_settings.sm, np_settings.offset);



    // DMA channels

    // Get a free channel, panic() if there are none
    np_settings.new_output_dma_channel = dma_claim_unused_channel(true);
    np_settings.to_pio_dma_channel = dma_claim_unused_channel(true);

    // settings for the timer that controls the low/new frame portion of the NP protocol
    int neopix_timer = 0;
    dma_timer_claim(neopix_timer);
    dma_timer_set_fraction(neopix_timer, 1, 25000); 


    //TIMER
    np_settings.new_output_dma_channel_config = dma_channel_get_default_config(np_settings.new_output_dma_channel);

    channel_config_set_transfer_data_size(&np_settings.new_output_dma_channel_config, DMA_SIZE_8); 

    channel_config_set_dreq(&np_settings.new_output_dma_channel_config, dma_get_timer_dreq(neopix_timer)); // timer 

    channel_config_set_read_increment(&np_settings.new_output_dma_channel_config, false);  // don't increment
    channel_config_set_write_increment(&np_settings.new_output_dma_channel_config, false); // don't increment

    channel_config_set_chain_to(&np_settings.new_output_dma_channel_config, np_settings.to_pio_dma_channel);

    dma_channel_configure(
        np_settings.new_output_dma_channel,                             // Channel to be configured
        &np_settings.new_output_dma_channel_config,                     // The configuration we just created
        &dummy_dma_value2,                            // The initial write address, the TX of the pio0's FIFO
        &dummy_dma_value1,                                  // The initial read address
        1,                                              // Number of transfers; one. 
        true                                            // Start immediately.
    );

    
    // TO PIO
    np_settings.to_pio_dma_channel_config = dma_channel_get_default_config(np_settings.to_pio_dma_channel);

    channel_config_set_transfer_data_size(&np_settings.to_pio_dma_channel_config, DMA_SIZE_32); //modified to transfer a word 

    channel_config_set_read_increment(&np_settings.to_pio_dma_channel_config, false); // modify in future tests to display animations
    channel_config_set_write_increment(&np_settings.to_pio_dma_channel_config, false); // modified so write loc. doesn't increment

    channel_config_set_dreq(&np_settings.to_pio_dma_channel_config, pio_get_dreq(pio0, sm_g, true)); //configured to trigger when .pio requests more data

    dma_channel_configure(
        np_settings.to_pio_dma_channel,                             // Channel to be configured
        &np_settings.to_pio_dma_channel_config,                     // The configuration we just created
        &pio0_hw->txf[np_settings.sm],                            // The initial write address, the TX of the pio0's FIFO
        &color_output,                                  // The initial read address
        NUMBER_OF_NP,                                   // Number of transfers
        false                                           // Start immediately.
    );

    dma_channel_set_irq0_enabled(np_settings.to_pio_dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_irq_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    return np_settings;
}



/*

*/
bool start_output_animated_mode()
{

}



/*

*/
bool stop_color_output()
{

}


// OLD FUNCTIONS

// /*
//     init_pio()


// */
// void init_pio()
// {
//     // definition of variables to start program
//     PIO pio = pio0;
//     uint sm = pio_claim_unused_sm(pio, true);
//     sm_g = sm;
//     uint offset = pio_add_program(pio, &LED_output_program);

//     // properly load .pio program
//     LED_output_program_init(pio, sm, offset);

// }

// /*
//     init_dma()

// */
// void init_dma()
// {
//     // Get a free channel, panic() if there are none
//     new_output_dma_channel = dma_claim_unused_channel(true);
//     to_pio_dma_channel = dma_claim_unused_channel(true);

//     int neopix_timer = 0;
//     dma_timer_claim(neopix_timer);
//     dma_timer_set_fraction(neopix_timer, 1, 25000);


//     //TIMER
//     dma_channel_config new_output_dma_channel_config = dma_channel_get_default_config(new_output_dma_channel);

//     channel_config_set_transfer_data_size(&new_output_dma_channel_config, DMA_SIZE_8); 

//     channel_config_set_dreq(&new_output_dma_channel_config, dma_get_timer_dreq(neopix_timer)); // timer 

//     channel_config_set_read_increment(&new_output_dma_channel_config, false);  // don't increment
//     channel_config_set_write_increment(&new_output_dma_channel_config, false); // don't increment

//     channel_config_set_chain_to(&new_output_dma_channel_config, to_pio_dma_channel);

//     dma_channel_configure(
//         new_output_dma_channel,                             // Channel to be configured
//         &new_output_dma_channel_config,                     // The configuration we just created
//         &dummy_dma_value2,                            // The initial write address, the TX of the pio0's FIFO
//         &dummy_dma_value1,                                  // The initial read address
//         1,                                              // Number of transfers; one. 
//         true                                            // Start immediately.
//     );

    
//     // TO PIO
//     dma_channel_config to_pio_dma_channel_config = dma_channel_get_default_config(to_pio_dma_channel);

//     channel_config_set_transfer_data_size(&to_pio_dma_channel_config, DMA_SIZE_32); //modified to transfer a word 

//     channel_config_set_read_increment(&to_pio_dma_channel_config, false); // modify in future tests to display animations
//     channel_config_set_write_increment(&to_pio_dma_channel_config, false); // modified so write loc. doesn't increment

//     channel_config_set_dreq(&to_pio_dma_channel_config, pio_get_dreq(pio0, sm_g, true)); //configured to trigger when .pio requests more data

//     dma_channel_configure(
//         to_pio_dma_channel,                             // Channel to be configured
//         &to_pio_dma_channel_config,                     // The configuration we just created
//         &pio0_hw->txf[sm_g],                            // The initial write address, the TX of the pio0's FIFO
//         &color_output,                                  // The initial read address
//         NUMBER_OF_NP,                                   // Number of transfers
//         false                                           // Start immediately.
//     );

//     dma_channel_set_irq0_enabled(to_pio_dma_channel, true);
//     irq_set_exclusive_handler(DMA_IRQ_0, dma_irq_handler);
//     irq_set_enabled(DMA_IRQ_0, true);

// }
