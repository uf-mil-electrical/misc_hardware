
/******************<Dependencies>*****************/
#include "peripherals/doorsense_tof.h"
/******************</Dependencies>*****************/


/******************<Data Structures>*****************/
/******************</Data Structures>*****************/


/******************<Public Functions>*****************/
/*******init_tof*******
 * Description
        > initializes the ToF sensor
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_tof(){
    // First, init the XSHUT pin, set as OUTPUT, turn OFF (low)
        gpio_init(TOF_XSHUT_PIN);
        gpio_set_dir(TOF_XSHUT_PIN, SET_GPIO_OUTPUT);
        gpio_put(TOF_XSHUT_PIN, GPIO_SET_LOW);

    // Second, init the GPIO1 pin, set as INPUT
    	gpio_init(TOF_GPIO1_PIN);
		gpio_set_dir(TOF_GPIO1_PIN, SET_GPIO_INPUT);

	// Third, turn ToF sensor/XSHUT ON (high)
		gpio_put(TOF_XSHUT_PIN, GPIO_SET_HIGH);

	// Fourth, 


    // Lastly, return to main program
        return;
}


/*******DEBUG_read_tof*******
 * Description
        > FOR DEBUGGING ONLY, USE THE ST API FOR NORMAL USE
        > reads data from the i2c bus
        > only reads from one of the two on-board I2C buses! (currently set to i2c1 by I2C_PORT in setup.h)
 * Arguments
        > uint8_t addr: address of device to read from
        > uint8_t reg: register to read from
        > uint8_t data: pointer to an array to store received data
        > uint8_t num_bytes: number of bytes to read from target device
 * Returns
        > N/A
*/
void read_tof(uint8_t addr, uint16_t reg, uint8_t* data, uint8_t num_bytes){
		uint8_t buf[6];

       // First, separate register address intwo two bytes
              uint8_t regbuf[2] = { (uint8_t)(reg >> 8), (uint8_t)(reg & 0xFF) };

       // Second, write to ToF module to specify a read will occur
              i2c_write_blocking(I2C_PORT, TOF_ADDRESS, regbuf, 2, true);

       // Third, read from a specific register on the ToF module
              i2c_read_blocking(I2C_PORT, TOF_ADDRESS, data, 1, false);

       // Fourth, print the received data
              printf("I2C data received: %u\n", buf[0]);

       // Lastly, return to main program
              return;
}
/******************</Public Functions>*****************/