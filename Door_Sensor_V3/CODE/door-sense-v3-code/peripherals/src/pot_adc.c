
/******************<Dependencies>*****************/
#include "peripherals/pot_adc.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
/******************</Private variables>*****************/


/******************<Public variables>*****************/
uint8_t countdown_duration;
/******************</Public variables>*****************/



/******************<Helper functions>*****************/

/*******get_scaled_val*******
 * Description
        > scales some ADC voltage (float) to a uint8_t value in a
			given range
 * Arguments
        > float voltage: voltage read from ADC
		> uint8_t out_min: minimum value in desired range
		> uint8_t out_max: maximum value in desired range
 * Returns
        > uint8_t: scaled value (casted to uint8_t)
*/
uint8_t get_scaled_val(float voltage, uint8_t out_min, uint8_t out_max) {
    // First, convert to desired range
    float scaled = out_min + (voltage / 3.3f) * (float)(out_max - out_min);

    // Second, clamp to output range to guard against noise (less than 0/greater than 3.3)
    if (scaled < out_min) { scaled = out_min; }
    if (scaled > out_max) { scaled = out_max; }

    // Third, round to nearest integer before casting to avoid truncation bias
    return (uint8_t)(scaled + 0.5f);
}
/******************<Helper functions>*****************/


/******************<Function definitions>*****************/

/*******init_potentiometer_adc*******
 * Description
        > initializes ADC pin to read potentiometer values
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_potentiometer_adc(){
	// initialize relevant GPIO
		gpio_init(COUNTDOWN_ADC_PIN);
		gpio_set_dir(COUNTDOWN_ADC_PIN, GPIO_IN);

	// initialize ADC system
		adc_init();
		adc_gpio_init(COUNTDOWN_ADC_PIN);
		adc_select_input(COUNTDOWN_ADC_CH);
}


/*******read_pot_val*******
 * Description
        > reads voltage at pot ADC pin
 * Arguments
        > N/A
 * Returns
        > float: raw ADC voltage
*/
float read_pot_val(){
	// read val from ADC pin
		uint16_t adc_val = adc_read();

	// convert raw value to voltage
		float adc_voltage = (float)(adc_val) * (ADC_VREF / ADC_RESOLUTION);

	// return ADC voltage
		return adc_voltage;
}



/*******update_countdown_duration*******
 * Description
        > determines what the duration of the countdown should be
			based on the voltage seen at the pot's ADC pin
		> updates the global variable "countdown_duration"
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void update_countdown_duration(){
	// read potentiometer ADC value
		float voltage = read_pot_val();

	// cast float ADC voltage to desired range
		uint8_t duration = get_scaled_val(voltage, MIN_COUNTDOWN_TIME, MAX_COUNTDOWN_TIME);

	// update global variable
		countdown_duration = duration;
}
/******************</Function definitions>*****************/