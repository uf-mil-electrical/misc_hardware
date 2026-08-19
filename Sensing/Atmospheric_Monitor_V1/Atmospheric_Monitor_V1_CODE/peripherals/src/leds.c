/******************<Dependencies>*****************/
#include "peripherals/leds.h"
/******************</Dependencies>*****************/



/******************<Function Definitions>*****************/

/*******set_led*******
 * Description
        > enables/disables a certain LED
        > NOTE: the RGB-LED is active-LOW
 * Arguments
        > uint8_t led: target LED pin
        > bool state: true=LED on, false=LED off
 * Returns
        > N/A
*/
void set_led(uint8_t led, bool state){

    // adjust for active-LOW RGB LED if necessary
        switch(led){
            case LED_Y0_PIN: {break;}
            case LED_Y1_PIN: {break;}
            case LED_Y2_PIN: {break;}
            case LED_Y3_PIN: {break;}
            case LED_R_PIN: {
                state = !state;
                break;
            }
            case LED_G_PIN: {
                state = !state;
                break;
            }
            case LED_B_PIN: {
                state = !state;
                break;
            }
            default: {printf("set_led(): invalid LED '%u'", led); return;}
        }

    // set LED
        gpio_put(led, state);
}



/*******set_thermistor_led*******
 * Description
        > enables/disables an LED that corresponds to a thermistor
        > only adjusts the yellow LEDs
 * Arguments
        > uint8_t led: target LED
        > bool state: true=LED on, false=LED off
 * Returns
        > N/A
*/
void set_thermistor_led(uint8_t led, bool state){

    // get GPIO corresponding to target LED
        uint8_t led_pin = 0;

        switch(led){
            case 0: {led_pin = LED_Y0_PIN; break;}
            case 1: {led_pin = LED_Y1_PIN; break;}
            case 2: {led_pin = LED_Y2_PIN; break;}
            case 3: {led_pin = LED_Y3_PIN; break;}
            default: {printf("set_thermistor_led(): invalid LED '%u'\n", led); return;}
        }

    // set LED
        gpio_put(led_pin, state);

    return;
}


/*******set_all_led*******
 * Description
        > enables/disables all LEDs
 * Arguments
        > bool state: true=LED on, false=LED off
 * Returns
        > N/A
*/
void set_all_led(bool state){
    set_led(LED_Y0_PIN, state);
    set_led(LED_Y1_PIN, state);
    set_led(LED_Y2_PIN, state);
    set_led(LED_Y3_PIN, state);

    set_led(LED_R_PIN, state);
    set_led(LED_G_PIN, state);
    set_led(LED_B_PIN, state);
}


/*******init_leds*******
 * Description
        > initializes onboard LEDs
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_leds(){
    // initialize GPIO
		gpio_init(LED_Y0_PIN);
        gpio_init(LED_Y1_PIN);
        gpio_init(LED_Y2_PIN);
        gpio_init(LED_Y3_PIN);

        gpio_init(LED_R_PIN);
        gpio_init(LED_G_PIN);
        gpio_init(LED_B_PIN);

	// set GPIO as outputs
		gpio_set_dir(LED_Y0_PIN, GPIO_OUT);
		gpio_set_dir(LED_Y1_PIN, GPIO_OUT);
		gpio_set_dir(LED_Y2_PIN, GPIO_OUT);
        gpio_set_dir(LED_Y3_PIN, GPIO_OUT);

        gpio_set_dir(LED_R_PIN, GPIO_OUT);
        gpio_set_dir(LED_G_PIN, GPIO_OUT);
        gpio_set_dir(LED_B_PIN, GPIO_OUT);

	// set LEDs high
		set_all_led(true);

    // delay
        sleep_ms(500);

    // set LEDs low
        set_all_led(false);
}

/******************</Function Definitions>*****************/