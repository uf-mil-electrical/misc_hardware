
/******************<Dependencies>*****************/
#include "peripherals/switches.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
/******************</Private variables>*****************/


/******************<Public variables>*****************/
/******************</Public variables>*****************/



/******************<Helper functions>*****************/

/*******init_switches()*******
 * Description
        > initializes digital switches onboard Door-Sense-V3
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_switches(){
	// initialize GPIO
		gpio_init(PROMPT_SW_PIN);
		gpio_init(OVERRIDE_SW_PIN);

	// set GPIO as inputs
		gpio_set_dir(PROMPT_SW_PIN, GPIO_IN);
		gpio_set_dir(OVERRIDE_SW_PIN, GPIO_IN);
}


/*******get_prompt_sw_state()*******
 * Description
        > returns value of either digital switch connected 
			to Door-Sense-V3
 * Arguments
        > char sw: 'm'=prompt mode switch, 'o'=override switch
		> bool *current_state: pointer to variable that stores switch state result
 * Returns
*/
void get_sw_state(char sw, bool *current_state){
	uint8_t target_sw = 99;
	
	// Select which switch to toggle
		switch(sw){
			case 'p': {target_sw = PROMPT_SW_PIN; break;}
			case 'o': {target_sw = OVERRIDE_SW_PIN; break;}
			default: {
				printf("get_sw_state(): INVALID SWITCH\n");
				return;
			}
		}

	// Get and return switch state
		*current_state = gpio_get(target_sw);
		return;
}
/******************</Function definitions>*****************/