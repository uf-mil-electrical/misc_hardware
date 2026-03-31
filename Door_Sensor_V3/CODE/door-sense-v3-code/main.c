#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"

#include "peripherals/lcd.h"
#include "peripherals/leds.h"
//#include "peripherals/audio.h"
#include "libraries/dfplayer/dfplayer.h"

#include "pins.h"

#define GPIO_TX         12       // To RX on the player
#define GPIO_RX         13       // To TX on the player
#define DFPLAYER_UART   uart0

dfplayer_t dfplayer;


int main()
{
    stdio_init_all();

	dfplayer_init(&dfplayer, DFPLAYER_UART, GPIO_TX, GPIO_RX);
	sleep_ms(200);

	dfplayer_set_volume(&dfplayer, 30);
    sleep_ms(200);

	//dfplayer_play(&dfplayer, 1);
	dfplayer_play_mp3_folder(&dfplayer, 1);
	sleep_ms(4000);
	dfplayer_play_mp3_folder(&dfplayer, 2);
	sleep_ms(3000);
	dfplayer_play_mp3_folder(&dfplayer, 3);
	sleep_ms(4000);
	dfplayer_play_mp3_folder(&dfplayer, 4);
	sleep_ms(4000);
	dfplayer_play_mp3_folder(&dfplayer, 5);
	sleep_ms(4000);
	dfplayer_play_mp3_folder(&dfplayer, 6);
	sleep_ms(4000);
	dfplayer_play_mp3_folder(&dfplayer, 7);
	sleep_ms(4000);
	dfplayer_play_mp3_folder(&dfplayer, 8);
	sleep_ms(4000);


	/*
	// Initialize LCD
		doorsense_init_lcd();

	// Initialize LEDs
		init_leds();
		set_led('r', true);
		sleep_ms(100);
		set_led('y', true);
		sleep_ms(100);
		set_led('g', true);
		sleep_ms(100);
		set_led('w', true);

		*/

	// Initialize DF player
		//init_dfplayer();
	
	// Play one track

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
