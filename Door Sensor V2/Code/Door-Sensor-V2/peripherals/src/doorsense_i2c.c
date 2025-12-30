/******************<Dependencies>*****************/
#include "peripherals/doorsense_i2c.h"
/******************</Dependencies>*****************/


/******************<Public Functions>*****************/

/*******init_doorsense_i2c*******
 * Description
        > initializes I2C bus for communicating with other devices
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_doorsense_i2c(void){
    // First, initialialize I2C in master mode
       i2c_init(I2C_PORT, I2C_BAUDRATE);
       gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
       gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
       gpio_pull_up(I2C_SDA);
       gpio_pull_up(I2C_SCL);

    // Lastly, return to main program
        return;
}


/******************</Public Functions>*****************/