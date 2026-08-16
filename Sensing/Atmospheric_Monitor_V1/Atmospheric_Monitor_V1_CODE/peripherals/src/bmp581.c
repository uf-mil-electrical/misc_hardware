/******************<Dependencies>*****************/
#include "peripherals/bmp581.h"
/******************</Dependencies>*****************/



/******************<Function Definitions>*****************/

/*******set_bmp581_cs*******
 * Description
        > enables or disables BMP581 SPI CS pin (active-low)
 * Arguments
        > bool state: true=set CS low, false=set CS high
 * Returns
        > N/A
*/
void set_bmp581_cs(bool state){
    if (state){gpio_put(BMP581_CS_PIN, GPIO_SET_LOW);}
    else {gpio_put(BMP581_CS_PIN, GPIO_SET_HIGH);}
}



/*******init_bmp581*******
 * Description
        > inits BMP581 sensor
        > inits relevant SPI bus
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_bmp581(){
    // init relevant SPI bus
        init_pico_spi(BMP581_SPI_BUS, BMP581_SPI_BAUDRATE, BMP581_MOSI_PIN, BMP581_MISO_PIN, BMP581_SCK_PIN);

    // init relevant CS pin
        gpio_init(BMP581_CS_PIN);
        gpio_set_dir(BMP581_CS_PIN, GPIO_OUT);
        set_bmp581_cs(false);                   // disable IC on init
}

/******************</Function Definitions>*****************/