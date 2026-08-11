/******************<Dependencies>*****************/
#include "peripherals/leds.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
/******************</Private variables>*****************/


/******************<Public variables>*****************/
/******************</Public variables>*****************/


/******************<Function definitions>*****************/
/*******init_leds*******
 * Description
        > initializes LEDs
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_leds(){
	// initialize GPIO
		gpio_init(LED_R_PIN);
		gpio_init(LED_Y_PIN);
		gpio_init(LED_G_PIN);
		gpio_init(LED_W_PIN);

	// set GPIO as outputs
		gpio_set_dir(LED_R_PIN, GPIO_OUT);
		gpio_set_dir(LED_Y_PIN, GPIO_OUT);
		gpio_set_dir(LED_G_PIN, GPIO_OUT);
		gpio_set_dir(LED_W_PIN, GPIO_OUT);

	// set LEDs low on init
		gpio_put(LED_R_PIN, GPIO_SET_LOW);
		gpio_put(LED_Y_PIN, GPIO_SET_LOW);
		gpio_put(LED_G_PIN, GPIO_SET_LOW);
		gpio_put(LED_W_PIN, GPIO_SET_LOW);
}


/*******set_led*******
 * Description
        > change state of one LED
 * Arguments
        > char led: target led ('r', 'y', 'g', 'w')
		> bool state: state to set LED
 * Returns
        > N/A
*/
void set_led(char led, bool state){
	switch(led){
		case ('r'): {gpio_put(LED_R_PIN, state); break;}
		case ('y'): {gpio_put(LED_Y_PIN, state); break;}
		case ('g'): {gpio_put(LED_G_PIN, state); break;}
		case ('w'): {gpio_put(LED_W_PIN, state); break;}
		default: {printf("set_led(): invalid LED"); break;}
	}
}


/*******set_all_leds*******
 * Description
        > change state of all LEDs
 * Arguments
		> bool state: state to set LEDs
 * Returns
        > N/A
*/
void set_all_leds(bool state){
	set_led('r', state);
	set_led('y', state);
	set_led('g', state);
	set_led('w', state);
}
/******************</Function definitions>*****************/