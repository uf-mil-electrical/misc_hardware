/*

File containing the .c functions that control the neopixels

*/

#include "ws2812_controller_functions.h"
extern volatile uint32_t color_output; 
extern volatile uint sm_g;
extern volatile volatile uint8_t dummy_dma_value1;
extern volatile volatile uint8_t dummy_dma_value2;
static int to_pio_dma_channel;
static int new_output_dma_channel;


/*


*/
void __isr dma_irq_handler() {
    if (dma_channel_get_irq0_status(to_pio_dma_channel)) {
        dma_channel_acknowledge_irq0(to_pio_dma_channel);

        // Wait for FIFO to drain — this is fast, just a few cycles
        while (!pio_sm_is_tx_fifo_empty(pio0, sm_g));

        // Re-arm to_pio but don't start — reset_timer will chain to it
        dma_channel_set_read_addr(to_pio_dma_channel, &color_output, false);
        dma_channel_set_trans_count(to_pio_dma_channel, NUMBER_OF_NP, false);

        // Start the reset timer channel — it will chain to to_pio after 50us
        dma_channel_set_trans_count(new_output_dma_channel, 1, true);
    }
}

/*
    init_pio()


*/
void init_pio()
{
    // definition of variables to start program
    PIO pio = pio0;
    uint sm = pio_claim_unused_sm(pio0, true);
    sm_g = sm;
    uint offset = pio_add_program(pio, &LED_output_program);

    // properly load .pio program
    LED_output_program_init(pio0, sm, offset);

}

/*
    init_dma()

*/
void init_dma()
{
    // Get a free channel, panic() if there are none
    new_output_dma_channel = dma_claim_unused_channel(true);
    to_pio_dma_channel = dma_claim_unused_channel(true);

    int neopix_timer = 0;
    dma_timer_claim(neopix_timer);
    dma_timer_set_fraction(neopix_timer, 1, 25000);


    //TIMER
    dma_channel_config new_output_dma_channel_config = dma_channel_get_default_config(new_output_dma_channel);

    channel_config_set_transfer_data_size(&new_output_dma_channel_config, DMA_SIZE_8); 

    channel_config_set_dreq(&new_output_dma_channel_config, dma_get_timer_dreq(neopix_timer)); // timer 

    channel_config_set_read_increment(&new_output_dma_channel_config, false);  // don't increment
    channel_config_set_write_increment(&new_output_dma_channel_config, false); // don't increment

    channel_config_set_chain_to(&new_output_dma_channel_config, to_pio_dma_channel);

    dma_channel_configure(
        new_output_dma_channel,                             // Channel to be configured
        &new_output_dma_channel_config,                     // The configuration we just created
        &dummy_dma_value2,                            // The initial write address, the TX of the pio0's FIFO
        &dummy_dma_value1,                                  // The initial read address
        1,                                              // Number of transfers; one. 
        true                                            // Start immediately.
    );

    
    // TO PIO
    dma_channel_config to_pio_dma_channel_config = dma_channel_get_default_config(to_pio_dma_channel);

    channel_config_set_transfer_data_size(&to_pio_dma_channel_config, DMA_SIZE_32); //modified to transfer a word 

    channel_config_set_read_increment(&to_pio_dma_channel_config, false); // modify in future tests to display animations
    channel_config_set_write_increment(&to_pio_dma_channel_config, false); // modified so write loc. doesn't increment

    channel_config_set_dreq(&to_pio_dma_channel_config, pio_get_dreq(pio0, sm_g, true)); //configured to trigger when .pio requests more data

    dma_channel_configure(
        to_pio_dma_channel,                             // Channel to be configured
        &to_pio_dma_channel_config,                     // The configuration we just created
        &pio0_hw->txf[sm_g],                            // The initial write address, the TX of the pio0's FIFO
        &color_output,                                  // The initial read address
        NUMBER_OF_NP,                                   // Number of transfers
        false                                           // Start immediately.
    );

    dma_channel_set_irq0_enabled(to_pio_dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_irq_handler);
    irq_set_enabled(DMA_IRQ_0, true);

}