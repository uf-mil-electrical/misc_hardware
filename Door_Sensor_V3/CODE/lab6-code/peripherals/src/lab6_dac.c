
/******************<Dependencies>*****************/
#include "peripherals/lab6_dac.h"
/******************</Dependencies>*****************/

/******************<Lookup Tables>*****************/
// Sine function lookup table
const uint8_t sin_vals[256] = {
127,130,133,136,139,143,146,149,152,155,158,161,164,
167,170,173,176,178,181,184,187,190,192,195,198,200,
203,205,208,210,212,215,217,219,221,223,225,227,229,
231,233,234,236,238,239,240,242,243,244,245,247,248,
249,249,250,251,252,252,253,253,253,254,254,254,254,
254,254,254,253,253,253,252,252,251,250,249,249,248,
247,245,244,243,242,240,239,238,236,234,233,231,229,
227,225,223,221,219,217,215,212,210,208,205,203,200,
198,195,192,190,187,184,181,178,176,173,170,167,164,
161,158,155,152,149,146,143,139,136,133,130,127,124,
121,118,115,111,108,105,102, 99, 96, 93, 90, 87, 84,
 81, 78, 76, 73, 70, 67, 64, 62, 59, 56, 54, 51, 49,
 46, 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21,
 20, 18, 16, 15, 14, 12, 11, 10,  9,  7,  6,  5,  5,
  4,  3,  2,  2,  1,  1,  1,  0,  0,  0,  0,  0,  0,
  0,  1,  1,  1,  2,  2,  3,  4,  5,  5,  6,  7,  9,
 10, 11, 12, 14, 15, 16, 18, 20, 21, 23, 25, 27, 29,
 31, 33, 35, 37, 39, 42, 44, 46, 49, 51, 54, 56, 59,
 62, 64, 67, 70, 73, 76, 78, 81, 84, 87, 90, 93, 96,
 99,102,105,108,111,115,118,121,124 };

/******************</Lookup Tables>*****************/


/******************<Private variables>*****************/
#define table_size 256
int waveform_index = 0;
/******************</Private variables>*****************/

/******************<Function definitions>*****************/

/*******lab6_dac_write*******
 * [Keep this function unchanged]
*/
void lab6_dac_write(uint8_t channel, uint16_t value){
    if (value > 255) {value = 255;}
    uint8_t command = 0;
    if (channel == 0){command = 0x9;}
    else {command = 0xA;}
    uint16_t payload = ((uint16_t)command << 12) | ((uint16_t)value << 2);
    
    gpio_put(CS_PIN, GPIO_SET_LOW);
    spi_write16_blocking(SPI_PORT, &payload, 1);
    gpio_put(CS_PIN, GPIO_SET_HIGH);
    return;
}



/*******update_waveform*******
 * Description: Sends next value in lookup table to DAC
*/
void update_waveform(){
    // First, determine which waveform lookup table to use
    uint8_t type = 0; // Replace with actual switch reading
    uint8_t* lookup_table;

	/*
    switch(type){
        case 0: {lookup_table = sin_vals; break;}
        case 1: {lookup_table = square_vals; break;}
        case 2: {lookup_table = triangle_vals; break;}
        case 3: {lookup_table = sawtooth_vals; break;}
        default: {return;}
    }
	*/
	lookup_table = sin_vals;
    
    // Second, determine amplitude
    float amplitude = 3.3f; // Replace with actual pot reading
    
    // Third, get current value from lookup table
    uint16_t val = (uint16_t)(lookup_table[waveform_index] << 2);
    
    // Fourth, scale by amplitude
    val = (uint16_t)(val * (amplitude / 5.0f));
    
    // Fifth, send to DAC (DAC will hold this value until next transmission)
    lab6_dac_write(0, val);
    
    // Sixth, move to next index in lookup table
    waveform_index++;
    if (waveform_index >= table_size) {
        waveform_index = 0; // Wrap around to start of table
    }
}
/******************</Function definitions>*****************/