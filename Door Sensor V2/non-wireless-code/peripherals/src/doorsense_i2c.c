/******************<Dependencies>*****************/
#include "peripherals/doorsense_i2c.h"
/******************</Dependencies>*****************/


/******************<Private Functions>*****************/
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}
/******************</Private Functions>*****************/


/******************<Public Functions>*****************/
/*******init_i2c*******
 * Description
        > initializes a specific I2C bus as a master
 * Arguments
        > i2c_inst_t* i2c_bus: i2c0 or i2c1
		>       uint baudrate: i2c peripheral baudrate
		> 			  SDA_pin: GPIO pin # for use as SDA pin (must be valid for the chosen i2c bus)
		> 			  SCL_pin: GPIO pin # for use as SCL pin (must be valid for the chosen i2c bus)
 * Returns
        > N/A
*/
void init_i2c(i2c_inst_t* i2c_bus, uint baudrate, uint8_t SDA_pin, uint8_t SCL_pin){
	// First, initialialize I2C in master mode
       i2c_init(i2c_bus, baudrate);
       gpio_set_function(SDA_pin, GPIO_FUNC_I2C);
       gpio_set_function(SCL_pin, GPIO_FUNC_I2C);
       gpio_pull_up(SDA_pin);
       gpio_pull_up(SCL_pin);

    // Lastly, return to main program
        return;
}


/*******i2c_write_raw*******
 * Description
        > writes data to an i2c device
 * Arguments
        > i2c_inst_t* i2c_bus: i2c0 or i2c1
		> 		 uint8_t addr: 7-bit device I2C address
		> 	    uint8_t* data: array of data to write
		>   uint8_t num_bytes: number of bytes to write
 * Returns
        > int: error code
*/
int i2c_write_raw(i2c_inst_t* i2c_bus, uint8_t addr, uint8_t* data, uint8_t num_bytes){
	// First, write to I2C bus
		int w = i2c_write_blocking(i2c_bus, addr, data, num_bytes, false);	// issue stop at end of transmission
	
	// [DEBUG] print error/success messages
		if (w != num_bytes){
			printf("i2c_write_raw(): write failed (error=%d)\n", w);
			return -1;
		}

		//printf("i2c_write_raw(): successful write");

	// Lastly, return to main program
		return 0;
}


/*******i2c_write_register*******
 * Description
        > writes data to a specific register on a I2C device
 * Arguments
        > i2c_inst_t* i2c_bus: i2c0 or i2c1
		> 		 uint8_t addr: 7-bit device I2C address
		> 		 uint16_t reg: register address on device
		> 	    uint8_t* data: array of data to write
		>   uint8_t num_bytes: number of bytes to write
 * Returns
        > int: error code
*/
int i2c_write_register(i2c_inst_t* i2c_bus, uint8_t addr, uint16_t reg, uint8_t* data, uint8_t num_bytes){
	// First, validate inputs
		if (num_bytes == 0){
			printf("i2c_write_register(): num_bytes must be greater than 0\n");
			return -1;
		}

		if (num_bytes > 254){
			printf("i2c_write_register(): num_bytes must be smaller than 254\n");
			return -1;
		}
	
	// Second, separate 16-bit register addr into two bytes
		uint8_t regbuf[2] = { 		// this assumes register MSB comes first, then LSB
			(uint8_t)(reg >> 8),
			(uint8_t)(reg & 0xFF) 
		};

	// Third, prepare data array: [reg_msb][reg_lsb][data0][data1]...[dataN-1]
		uint8_t buffer[2 + num_bytes];
		buffer[0] = regbuf[0];
		buffer[1] = regbuf[1];

		for (uint8_t i = 0; i < num_bytes; i++){
			buffer[i + 2] = data[i];
		}

	// Fourth, write data to register on target I2C device
		int w = i2c_write_timeout_us(i2c_bus, addr, buffer, 2 + num_bytes, false, I2C_TIMEOUT_DELAY);

	// [DEBUG] print error/success messages
		// i: failure
			if ( w != (2 + num_bytes) ){
				printf("i2c_write_register(): write failed (error=%d)\n", w);
				return -1;
			}

		// ii: success
			//printf("i2c_write_register(): successful write\n");


	// Lastly, return to main program
		return 0;
}


/*******i2c_read_register*******
 * Description
        > reads data from a specific register on a I2C device
 * Arguments
        > i2c_inst_t* i2c_bus: i2c0 or i2c1
		> 		 uint8_t addr: 7-bit device I2C address
		> 		 uint16_t reg: register address on device
		> 	    uint8_t* data: array to store read data
		>   uint8_t num_bytes: number of bytes to read from register
 * Returns
        > int: error code
*/
int i2c_read_register(i2c_inst_t* i2c_bus, uint8_t addr, uint16_t reg, uint8_t* data, uint8_t num_bytes){
	// First, validate inputs
		if (num_bytes == 0){
			printf("i2c_read_register: num_bytes must be greater than 0\n");
			return -1;
		}
	
	// Second, separate 16-bit register addr into two bytes
		uint8_t regbuf[2] = { 		// this assumes register MSB comes first, then LSB
			(uint8_t)(reg >> 8),
			(uint8_t)(reg & 0xFF) 
		};

	// Third, write to I2C device register to prepare for read
		int w = i2c_write_timeout_us(i2c_bus, addr, regbuf, 2, true, I2C_TIMEOUT_DELAY);	// 2 here for MSB/LSB register bytes

	// Fourth, read from the specific register onboard the device
		int r = i2c_read_timeout_us(i2c_bus, addr, data, num_bytes, false, I2C_TIMEOUT_DELAY);

	// [DEBUG] print error/success messages
		// i: i2c write
			if (w != 2){
				printf("i2c_read_register(): write failed (%d byte(s) written)\n", w);
				return -1;
			}

		// ii: i2c read
			if (r != num_bytes){
				printf("i2c_read_register(): read failed (%d byte(s) read)\n", r);
				return -1;
			}

		// iii: success
			//printf("i2c_read_register(): successfully read %u bytes\n", num_bytes);

	// Lastly, return to main program
		return 0;
}


/*******i2c_device_scan*******
 * Description
        > detects connected I2C devices based on address
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void i2c_device_scan(){

    printf("\nI2C Bus Scan\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
        if (addr % 16 == 0) {
            printf("%02x ", addr);
        }

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if (reserved_addr(addr))
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read_blocking(TOF_I2C_PORT, addr, &rxdata, 1, false);

        printf(ret < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
    }
    printf("Done.\n");
    return;
}
/******************</Public Functions>*****************/