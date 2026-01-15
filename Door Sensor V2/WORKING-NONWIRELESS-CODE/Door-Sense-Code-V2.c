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

#include "pico/cyw43_arch.h"

// My code to include
#include "setup.h"
#include "peripherals/doorsense_gpio.h"
#include "peripherals/doorsense_i2c.h"
#include "peripherals/doorsense_spi.h"
#include "peripherals/doorsense_uart.h"

#include "tof_lib/tof_core.h"

//*****************</Includes>*****************

int main()
{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Enable wifi station
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms("Your Wi-Fi SSID", "Your Wi-Fi Password", CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect.\n");
        return 1;
    } else {
        printf("Connected.\n");
    }

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

/*                    


int main() {
    // First, initialize peripherals and devices
        stdio_init_all();
		sleep_ms(3000);		// brief startup delay to give user time to open serial monitor for debugging

		init_doorsense_leds();
		init_i2c(TOF_I2C_PORT, TOF_I2C_BAUDRATE, TOF_SDA, TOF_SCL);
		printf("Initialized peripherals\n");

		sleep_ms(200);
		tof_init();
		printf("Initialized ToF\n");

	// Second, run main program
		run_door_sensor();
}

*/