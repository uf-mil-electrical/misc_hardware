

/******************<Dependencies>*****************/
#include "peripherals/doorsense_gpio.h"
/******************</Dependencies>*****************/


/******************<Public Functions>*****************/

/*******init_doorsense_leds*******
 * Description
        > initializes the two LEDs onboard V2
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_doorsense_leds(){

    // First, init LED pins, set as OUTPUTS
        gpio_init(GREEN_LED);
        gpio_set_dir(GREEN_LED, SET_GPIO_OUTPUT);

        gpio_init(RED_LED);
        gpio_set_dir(RED_LED, SET_GPIO_OUTPUT);


    // Second, set LED pins LOW (turn off)
        gpio_put(GREEN_LED, GPIO_SET_LOW);
        gpio_put(RED_LED, GPIO_SET_LOW);


    // Lastly, return to main program
        return;
}


/*******set_led*******
 * Description
        > sets the value (on/off) of an LED
 * Arguments
        >char "target": target LED ('r'=red, 'g'=green)
        > bool "value": value to set (false=OFF, true=ON)
 * Returns
        > N/A
*/
void set_led(char target, bool value){

    // First, validate inputs
        if (target != 'r' && target != 'g'){
            printf("set_led(): Invalid LED");
            return;
        }

        if (value > 1){
            printf("set_led(): Invalid value");
            return;
        }

    // Second, adjust LED accordingly
        uint8_t led = 0;
        if (target == 'r'){led = RED_LED;}
        else {led = GREEN_LED;}


        gpio_put(led, value);

    // Lastly, return to main program
        return;

}

/******************</Public Functions>*****************/