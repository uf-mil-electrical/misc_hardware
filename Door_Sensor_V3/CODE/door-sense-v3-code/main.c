
/******************<Dependencies>*****************/
#include <stdio.h>
#include "pico/stdlib.h"

#include "peripherals/lcd.h"
#include "peripherals/leds.h"
#include "peripherals/audio.h"
#include "peripherals/pot_adc.h"

#include "pins.h"
/******************</Dependencies>*****************/

/******************<Global Variables>*****************/
uint8_t countdown_duration = 0;
/******************</Global Variables>*****************/


/******************<DEBUG>*****************/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_BUS       i2c0
#define I2C_SDA_PIN   16    // change to your SDA pin
#define I2C_SCL_PIN   17     // change to your SCL pin
#define I2C_BAUD      100000 // 100 kHz

void i2c_scan(i2c_inst_t* bus) {
    printf("\nScanning I2C bus...\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    int found = 0;

    for (int addr = 0; addr < 0x80; addr++) {
        if (addr % 16 == 0) {
            printf("%02X ", addr);
        }

        // Reserved I2C addresses: 0x00-0x07 and 0x78-0x7F
        if ((addr >= 0x08) && (addr <= 0x77)) {
            uint8_t buf;
            int result = i2c_read_blocking(bus, addr, &buf, 1, false);
            if (result >= 0) {
                printf("%02X ", addr);
                found++;
            } else {
                printf("-- ");
            }
        } else {
            printf("   ");
        }

        if ((addr + 1) % 16 == 0) {
            printf("\n");
        }
    }

    printf("\nScan complete. %d device(s) found.\n", found);
}

int main() {
    stdio_init_all();

    // Wait for USB serial to connect before scanning
    while (!stdio_usb_connected()) { sleep_ms(100); }
    sleep_ms(500); // let terminal settle

    i2c_init(I2C_BUS, I2C_BAUD);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    i2c_scan(I2C_BUS);

    while (true) { sleep_ms(1000); }
}
/******************<DEBUG>*****************/


/******************<Main>*****************/

/*
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
		tight_loop_contents();
    }
}
*/
/******************</Main>*****************/