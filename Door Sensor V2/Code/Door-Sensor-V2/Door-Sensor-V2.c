/*
  __  __ _____ _                                             
 |  \/  |_   _| |                                            
 | \  / | | | | |                                            
 | |\/| | | | | |                                            
 | |  | |_| |_| |____                                        
 |_|__|_|_____|______|       _____                           
 
 |  __ \                    / ____|                          
 | |  | | ___   ___  _ __  | (___   ___ _ __  ___  ___  _ __ 
 | |  | |/ _ \ / _ \| '__|  \___ \ / _ \ '_ \/ __|/ _ \| '__|
 | |__| | (_) | (_) | |     ____) |  __/ | | \__ \ (_) | |   
 |_____/ \___/ \___/|_|    |_____/ \___|_| |_|___/\___/|_|   

 \ \    / /__ \                                              
  \ \  / /   ) |                                             
   \ \/ /   / /                                              
    \  /   / /_                                              
     \/   |____|                                             
                                                             
    Door Sensor Board V2
    Pico 2 W
    Written by Russell MacGregor                     
*/



//*****************<Includes>***************** */
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "pico/time.h"
#include "hardware/irq.h"

#include "hardware/spi.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"

// My code to include
#include "setup.h"
#include "peripherals/doorsense_gpio.h"
#include "peripherals/doorsense_i2c.h"
#include "peripherals/doorsense_spi.h"
#include "peripherals/doorsense_uart.h"

#include "tof_lib/tof_core.h"

//*****************</Includes>*****************

int main() {
    // First, initialize peripherals
        stdio_init_all();
		sleep_ms(1500);
		init_i2c(TOF_I2C_PORT, TOF_I2C_BAUDRATE, TOF_SDA, TOF_SCL);
		printf("Initialized I2C\n");

		tof_init();
		printf("Initialized ToF\n");

	// Second, measure and print continuously
		bool first_range = true;
		uint16_t distance = 0;

		while (1) {
			// Wait until we have new data
				uint8_t dataReady;
				do {
					dataReady = tof_check_data_ready();
					sleep_us(1);
				} while (dataReady == 0);

			// Read and display result
				distance = tof_get_distance();
				printf("dist = %5d\n", distance);

			// Clear the sensor for a new measurement
				tof_clear_int();

				if (first_range) {  // Clear twice on first measurement
					tof_clear_int();
					first_range = false;
				}
		}
}
