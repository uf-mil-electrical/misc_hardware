
/******************<Dependencies>*****************/
#include "peripherals/doorsense_spi.h"
/******************</Dependencies>*****************/


/******************<Public Functions>*****************/

/*******init_doorsense_spi*******
 * Description
        > initializes SPI bus on Pico 2W
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_doorsense_spi(){
    // First, initialize external/spare SPI port
        spi_init(SPI_PORT, SPI_SPEED);
        gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
        gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
        gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Second, set CS pin active low (commented out here, use one of the spare GPIO pins as needed)
        //gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
        //gpio_set_dir(PIN_CS, GPIO_OUT);
        //gpio_put(PIN_CS, 1);

    // Lastly, return to main program
        return;
}

/******************</Public Functions>*****************/