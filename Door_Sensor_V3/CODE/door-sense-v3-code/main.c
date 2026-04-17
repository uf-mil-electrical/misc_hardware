
/******************<Dependencies>*****************/
#include <stdio.h>
#include "pico/stdlib.h"

#include "pico/time.h"

#include "peripherals/lcd.h"
#include "peripherals/leds.h"
#include "peripherals/audio.h"
#include "peripherals/pot_adc.h"
#include "peripherals/switches.h"
#include "peripherals/tof.h"

#include "operation/operation.h"

#include "pins.h"
/******************</Dependencies>*****************/




/******************<Main>*****************/

int main()
{
    stdio_init_all();

	sleep_ms(2000);
	printf("initializing...\n");

	init_doorsense_peripherals();
	printf("initialized! ready to start\n");

	sleep_ms(2000);

	while(true){
		run_doorsense();
	}
}

/******************</Main>*****************/