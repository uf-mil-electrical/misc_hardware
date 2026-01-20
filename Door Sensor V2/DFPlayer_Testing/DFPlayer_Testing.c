#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"


// UART defines
#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 12
#define UART_RX_PIN 13

#include "uart_lib/uart_funcs.h"



int main()
{
    stdio_init_all();

    // Set up UART
		uart_init(UART_ID, BAUD_RATE);
		gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
		gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

	// Init DFPlayer
		dfplayer_init(UART_ID, 100, true); // 100ms sleep time, debug enabled
		sleep_ms(1000);
		printf("Resetting DFPlayer...\n");
		if (reset()) {
			printf("DFPlayer reset successful!\n");
		} else {
			printf("DFPlayer reset failed!\n");
		}

		sleep_ms(500);

		printf("Selecting SD card source...\n");
    	if (!select_source("sdcard")) {
        	printf("Failed to select SD card source, but continuing...\n");
    	}

		sleep_ms(200);
    
	// Query number of files on SD card
		printf("Checking number of files on SD card...\n");
		int num_files = query_num_files("sdcard");
		if (num_files > 0) {
			printf("Found %d files on SD card\n", num_files);
		} else {
			printf("Could not determine number of files on SD card\n");
		}
		
		sleep_ms(200);
    
    // Set volume (0-30)
		printf("Setting volume...\n");
		if (set_volume(20)) {
			printf("Volume set to 20\n");
		}
		
		sleep_ms(200);
    
    // Play the first track (test.mp3)
		printf("Playing test.mp3 (track 1)...\n");
		if (play(1)) {
			printf("Playback started\n");
		} else {
			printf("Failed to start playback\n");
		}
    
    // Main loop
    while (1) {
        // Check playback status every 2 seconds
        sleep_ms(2000);
        
        int status = get_status();
        switch (status) {
            case -1:
                printf("Error getting status\n");
                break;
            case 0:
                printf("Playback stopped\n");
                // If playback has stopped, restart it
                play(1);
                break;
            case 1:
                printf("Playback in progress\n");
                break;
            case 2:
                printf("Playback paused\n");
                break;
            default:
                printf("Unknown status: %d\n", status);
                break;
        }
    }
    
    return 0;
}
