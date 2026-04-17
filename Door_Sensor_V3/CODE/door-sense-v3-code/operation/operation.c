/******************<Dependencies>*****************/
#include "operation/operation.h"
/******************</Dependencies>*****************/



/******************<Public variables>*****************/
uint8_t countdown_duration = 0;				// time in SECONDS between door state change and lab state change
bool run_countdown = false;					// true=countdown to change lab state is running
int32_t countdown_time_remaining_ms = 0;	// time until countdown completes in ms
uint8_t second_count = 0;					// counter, incremented once per countdown update, used for blinking LEDs

uint32_t last_tof_check_time = 0;			// time since ToF sensor has last been checked
uint32_t last_sw_check_time = 0;			// time since switch & pot values were checked
uint32_t last_countdown_update_time = 0;	// time since countdown time has been updated

uint16_t tof_distance = 0;					// distance measurement from ToF sensor
bool tof_data_ready = false;				// true=tof ready to provide data, false=tof not ready to provide data

bool door_state = false;					// current door state
bool candidate_state = false;				// candidate door state (state being considered during countdown)
bool lab_state = false;						// true=lab is open, false=lab is closed
bool change_state = false;					// true=lab state will change after countdown, false=no change

bool override_active = false;				// is override active? lab state will not change while true
bool special_prompts_allowed = false;		// true=use regular voice prompts, false=use special voice prompts
/******************</Public variables>*****************/


/******************<Private Helper Functions>*****************/
/*******reset_countdown_time_in_ms*******
 * Description
        > reset countdown_time_remaining to be the full duration of the countdown
		> converts countdown_time (in seconds) to countdown_time_remaining (in ms)
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void reset_countdown_time_in_ms(){
	countdown_time_remaining_ms = countdown_duration * 1000;	
}


/*******update_leds*******
 * Description
        > updates the LEDs on door-sense-v3 to match current conditions
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void update_leds(){

	// if lab is open
	if (lab_state){
		set_led('g', true);
		set_led('r', false);
	}

	// if lab is closed
	if (!lab_state){
		set_led('g', false);
		set_led('r', true);
	}

	// if countdown is running
	if (run_countdown){set_led('w', true);}

	// if countdown is not running
	if (!run_countdown){set_led('w', false);}

	// if override is active
	if (override_active){set_led('y', true);}

	// if override is not active
	if (!override_active){set_led('y', false);}
}
/******************</Private Helper Functions>*****************/


/******************<Initialization Functions>*****************/

/*******init_peripherals*******
 * Description
        > initializes all onboard peripherals
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_doorsense_peripherals(){

	// Initialize LCD
		doorsense_init_lcd();

	// Initialize LEDs
		init_leds();
		set_all_leds(true);
		sleep_ms(100);
		set_all_leds(false);

	// Initialize switches
		init_switches();

	// Initialize ADC
		init_potentiometer_adc();

	// Initialize DF player
		init_dfplayer();

	// Initialize ToF sensor
		sleep_ms(200);
		tof_init();
		sleep_ms(200);

	// Get and print initial countdown time to LCD
		get_countdown_duration(&countdown_duration);
		print_countdown_duration(countdown_duration);

	// Set LEDs to match current conditions
		update_leds();
}

/******************</Initialization Functions>*****************/



/******************<Normal Operation>*****************/

/*******run_doorsense*******
 * Description
        > normal operation for door-sense-v3
		> this is what main will run after init
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void run_doorsense(){
	// Get current time
		uint32_t current_time = to_ms_since_boot(get_absolute_time());

	// Check ToF sensor at regular intervals
		if (current_time - last_tof_check_time >= TOF_CHECK_INTERVAL_MS){
			// reset last check time
				last_tof_check_time = current_time;

			// read from ToF
				get_distance(&tof_distance, &tof_data_ready);

			// if nonzero data was successfully read from ToF
				if (tof_data_ready && tof_distance != 0){
					tof_data_ready = false;		// reset data ready status

					// determine if door is open or closed based on distance
						door_state = (tof_distance <= DOOR_OPEN_DISTANCE);

						printf("door is %s\n", door_state ? "OPEN" : "CLOSED");

					// check that door state is different from lab state, countdown not started, override not active
						if ( (door_state != lab_state) && (run_countdown == false) && (override_active == false) ){
							printf("Door state change detected!");
							candidate_state = door_state;			// set candidate door state
							reset_countdown_time_in_ms();			// reset countdown_time_ms	
							run_countdown = true;					// run countdown
							update_leds();							// turn on white LED
						}

					// cancel countdown if door state changes during the countdown
						if ( (run_countdown == true) && (candidate_state != door_state) ){
							printf("Cancelled state change\n");
							reset_countdown_time_in_ms();			// reset countdown_time_ms
							set_led('w', false);					// turn off white LED
							run_countdown = false;					// stop countdown
							update_leds();							// turn off white LED
						}
				}
		}

	// Check digital switches & potentiometer at regular intervals
	if (current_time - last_sw_check_time >= SWITCH_CHECK_INTERVAL_MS){
		// check potentiometer/ADC val for countdown duration
			get_countdown_duration(&countdown_duration);

		// check override switch
			get_sw_state('o', &override_active);

		// check prompt switch
			get_sw_state('p', &special_prompts_allowed);

			//printf("SWITCHES: override = %s, special prompts = %s\n", override_active ? "ACTIVE" : "INACTIVE", special_prompts_allowed ? "ALLOWED" : "NOT ALLOWED");
	}

	// If countdown is running and should be updated...
		if ( (run_countdown == true) && (current_time - last_countdown_update_time >= COUNTDOWN_UPDATE_INTERVAL_MS) ){
			// reset last update time
				last_countdown_update_time = current_time;
				
			// decrement countdown time remaining
				countdown_time_remaining_ms = countdown_time_remaining_ms - COUNTDOWN_UPDATE_INTERVAL_MS;

			// blink white LED
				second_count += 1;
				if (second_count % 2 == 0){set_led('w', true);}
				else {set_led('w', false);}

			// check to see if countdown time has elapsed
				if (countdown_time_remaining_ms <= 0){
					run_countdown = false;
					change_state = true;
					printf("new lab state!");
				}
		}

	// If the lab state needs to be changed...
		if (change_state){
			// reset change state variable
				change_state = false;

			// update lab state
				lab_state = candidate_state;

			if (lab_state == true){
				printf("lab is now open!\n");
				update_leds();		// turn on green LED, turn off red LED
			}

			else {
				printf("lab is now closed!\n");
				update_leds();		// turn off green LED, turn on red LED
			}
		}
}

/******************</Normal Operation>*****************/