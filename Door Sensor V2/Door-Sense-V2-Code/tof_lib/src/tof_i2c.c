/******************<Dependencies>*****************/
#include "tof_lib/tof_i2c.h"
/******************</Dependencies>*****************/



/******************<ToF I2C Read Functions>*****************/

/*******tof_read_byte*******
 * Description
        > reads one byte from a specific register on the ToF sensor
 * Arguments
        > uint16_t reg: register address on ToF
		> uint8_t* data: pointer to 8-bit variable
 * Returns
        > N/A
*/
void tof_read_byte(uint16_t reg, uint8_t* data){
	i2c_read_register(TOF_I2C_PORT, TOF_I2C_ADDRESS, reg, data, 1);
}


/*******tof_read_word*******
 * Description
        > reads two bytes from a specific register on the ToF sensor
		> automatically inserts both bytes into a 16-bit variable
 * Arguments
        > uint16_t reg: register address on ToF
		> uint16_t* data: pointer to 16-bit variable
 * Returns
        > N/A
*/
void tof_read_word(uint16_t reg, uint16_t* data){
	i2c_read_register(TOF_I2C_PORT, TOF_I2C_ADDRESS, reg, (uint8_t*)data, 2);
	*data = ntohs(*data);
}



/*******tof_read_2_words*******
 * Description
        > reads four bytes from a specific register on the ToF sensor
		> automatically inserts all bytes into a 32-bit variable
 * Arguments
        > uint16_t reg: register address on ToF
		> uint32_t* data: pointer to 16-bit variable
 * Returns
        > N/A
*/
void tof_read_2_words(uint16_t reg, uint32_t* data){
	i2c_read_register(TOF_I2C_PORT, TOF_I2C_ADDRESS, reg, (uint8_t*)data, 4);
	*data = ntohl(*data);
}

/******************</ToF I2C Read Functions>*****************/



/******************<ToF I2C Write Functions>*****************/

/*******tof_write_byte*******
 * Description
        > writes one byte to a specific register on the ToF sensor
 * Arguments
        > uint16_t reg: register address on ToF
		> uint8_t data: byte of data to write
 * Returns
        > N/A
*/
void tof_write_byte(uint16_t reg, uint8_t data){
	i2c_write_register(TOF_I2C_PORT, TOF_I2C_ADDRESS, reg, &data, 1);
}



/*******tof_write_word*******
 * Description
        > writes two bytes to a specific register on the ToF sensor
		> takes in one 16-bit value, automatically buffers it into 2 8-bit values
 * Arguments
        > uint16_t reg: register address on ToF
		> uint16_t data: data to write
 * Returns
        > N/A
*/
void tof_write_word(uint16_t reg, uint16_t data){
	data = htons(data);
	i2c_write_register(TOF_I2C_PORT, TOF_I2C_ADDRESS, reg, (uint8_t*)&data, 2);
}



/*******tof_write_2_words*******
 * Description
        > writes four bytes to a specific register on the ToF sensor
		> takes in one 32-bit value, automatically buffers it into 4 8-bit values
 * Arguments
        > uint16_t reg: register address on ToF
		> uint32_t data: data to write
 * Returns
        > N/A
*/
void tof_write_2_words(uint16_t reg, uint32_t data){
	data = htonl(data);
	i2c_write_register(TOF_I2C_PORT, TOF_I2C_ADDRESS, reg, (uint8_t*)&data, 4);
}

/******************</ToF I2C Write Functions>*****************/