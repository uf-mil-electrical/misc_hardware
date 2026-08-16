

/******************<Dependencies>*****************/
#include <stdio.h>
#include "pico/stdlib.h"

#include "peripherals/bmp581.h"
#include "peripherals/leds.h"
#include "peripherals/thermistors.h"
/******************</Dependencies>*****************/

int main()
{
    stdio_init_all();

    // init peripherals
        init_bmp581();
        init_leds();
        init_thermistors();

    while (true) {
        scan_thermistors();
        sleep_ms(1000);
    }
}
