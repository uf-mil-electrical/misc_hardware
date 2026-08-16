/******************<Dependencies>*****************/
#include "communication/pico_spi.h"
/******************</Dependencies>*****************/


/******************<SPI Functions>*****************/

/*******init_pico_spi*******
 * Description
        > initializes a SPI bus for communicating with other devices
 * Arguments
        > spi_inst_t* spi_bus: SPI bus to init (spi0 or spi1)
        > uint baudrate: baudrate to use for this SPI bus
 * Returns
        > N/A
*/
void init_pico_spi(spi_inst_t* spi_bus, uint baudrate, uint8_t mosi_pin, uint8_t miso_pin, uint8_t sck_pin){
    // init target SPI bus
        spi_init(spi_bus, baudrate);

    // init relevant GPIO pins
        gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
        gpio_set_function(miso_pin, GPIO_FUNC_SPI);
        gpio_set_function(sck_pin, GPIO_FUNC_SPI);
}



/*******pico_read_spi*******
 * Description
        > reads data from a SPI bus
 * Arguments
        > //
 * Returns
        > N/A
*/
void pico_spi_read(){
}


/*******pico_spi_write*******
 * Description
        > write data to a SPI bus
 * Arguments
        > //
 * Returns
        > N/A
*/
void pico_spi_write(){
}


/******************</SPI Functions>*****************/
