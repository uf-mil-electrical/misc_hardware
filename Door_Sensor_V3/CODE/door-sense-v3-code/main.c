
/******************<Dependencies>*****************/
#include <stdio.h>
#include "pico/stdlib.h"

#include "peripherals/lcd.h"
#include "peripherals/leds.h"
#include "peripherals/audio.h"
#include "peripherals/pot_adc.h"

#include "pins.h"
/******************</Dependencies>*****************/




/******************<Main>*****************/
int main()
{
    stdio_init_all();

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
		sleep_ms(100);
		set_all_leds(false);

	// Initialize ADC
		init_potentiometer_adc();

	// Initialize DF player
		init_dfplayer();

		play_track(1);
		sleep_ms(4000);
		play_track(2);
		sleep_ms(4000);
		play_track(3);
		sleep_ms(4000);
		play_track(4);
		sleep_ms(4000);
		play_track(5);
		sleep_ms(4000);
		play_track(6);
		sleep_ms(4000);
		play_track(7);
		sleep_ms(4000);
		play_track(8);
		sleep_ms(4000);
		play_track(9);
		sleep_ms(4000);
		play_track(10);
		sleep_ms(4000);
		play_track(11);
		sleep_ms(4000);

		lcd_print("meow", 0, 0);
		lcd_print("meow", 0, 1);
	

    while (true) {
		update_countdown_duration();
        sleep_ms(250);
    }
}
/******************</Main>*****************/