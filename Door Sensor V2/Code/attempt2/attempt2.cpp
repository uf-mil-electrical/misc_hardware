#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
//#include "pico/cyw43_arch.h"
#include "lib/vl53l1x-pico/VL53L1X.h"
#include "setup.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15


VL53L1X sensor;

int main()
{
    stdio_init_all();
	printf("alas");

	//i: GPIO1 pin (input)
	gpio_init(TOF_GPIO1_PIN);
	gpio_set_dir(TOF_GPIO1_PIN, SET_GPIO_INPUT);

	//ii: XSHUT pin (output)
	gpio_init(TOF_XSHUT_PIN);
	gpio_set_dir(TOF_XSHUT_PIN, SET_GPIO_OUTPUT);
	gpio_put(TOF_XSHUT_PIN, GPIO_SET_HIGH);			// set high to turn ToF ON
	sleep_ms(50);

	sensor.setAddress(0x29);

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);


	sensor.setTimeout(500);
	if (!sensor.init()){
		printf("womp womp");
		while (1);
  	}

	sensor.setDistanceMode(VL53L1X::Long);
  	sensor.setMeasurementTimingBudget(50000);

	sensor.startContinuous(50);


	uint16_t result = sensor.read();
	printf("result");
	if (sensor.timeoutOccurred()) { printf("timeout");}
}
