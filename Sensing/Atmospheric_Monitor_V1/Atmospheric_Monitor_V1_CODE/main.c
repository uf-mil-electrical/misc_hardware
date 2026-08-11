

/******************<Dependencies>*****************/
#include <stdio.h>
#include "pico/stdlib.h"

#include "peripherals/leds.h"
/******************</Dependencies>*****************/

int main()
{
    stdio_init_all();

    init_leds();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
