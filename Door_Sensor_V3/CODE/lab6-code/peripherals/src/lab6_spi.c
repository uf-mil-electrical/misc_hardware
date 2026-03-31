/******************<Dependencies>*****************/
#include "peripherals/lab6_spi.h"
/******************</Dependencies>*****************/


/******************<Public variables>*****************/
/******************</Public variables>*****************/


/******************<Function definitions>*****************/

/*******lab6_spi_init*******
 * Description
        > initializes SPI peripheral for communiaction with DAC
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void lab6_spi_init(){

	// Initialize SPI1 bus
	spi_init(SPI_PORT, SPI_SPEED);

	// Set SPI mode
	spi_set_format(SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

	// Initialize SPI pins
    gpio_set_function(SCK_PIN,  GPIO_FUNC_SPI);
    gpio_set_function(MOSI_PIN, GPIO_FUNC_SPI);

	// Set CS pin high (active-low, deactivate device)
	gpio_init(CS_PIN);
	gpio_set_dir(CS_PIN, SET_GPIO_OUTPUT);
    gpio_put(CS_PIN, GPIO_SET_HIGH);
}
/******************</Function definitions>*****************/