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
uint32_t last_lcd_update_time = 0;			// time since LCD was last updated
uint32_t last_countdown_update_time = 0;	// time since countdown time has been updated

uint16_t tof_distance = 0;					// distance measurement from ToF sensor
bool tof_data_ready = false;				// true=tof ready to provide data, false=tof not ready to provide data

uint8_t num_like_readings = 0;				// number of ToF readings that agree on whether or not the door is open/closed

bool door_state = false;					// current door state (false=closed, true=open)
bool raw_door_state = false;				// instantaneous door state (from uncorrected ToF readings)
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
	if (run_countdown){
		if (second_count % 2 == 0){set_led('w', true);}
		else {set_led('w', false);}
	}
	else {set_led('w', false);}

	// if override is active
	if (override_active){set_led('y', true);}

	// if override is not active
	if (!override_active){set_led('y', false);}
}



/*******determine_door_state*******
 * Description
        > checks the readings from the ToF sensor and history
			and determines if the door is open or not
		> protects against noisy / random values that pop in
			around valid readings
		> important for when nothing is in range of door sensor
			(it sometimes spits out random values when nothing in range)
 * Arguments
        > uint16_t distance: distance measured by ToF sensor
 * Returns
        > N/A
*/
void determine_door_state(uint16_t distance){
	// is something within the DOOR_OPEN_DISTANCE range?
		bool new_reading = (tof_distance > 0 && tof_distance <= DOOR_OPEN_DISTANCE);

	// debounce readings: require NUM_LIKE_READINGS_NEEDED readings to change door state
		if (new_reading == raw_door_state){
			if (num_like_readings < NUM_LIKE_READINGS_NEEDED){
				num_like_readings += 1;
			}
		}
		else {
			// reading changed, reset streak
			raw_door_state = new_reading;
			num_like_readings = 1;
		}

	// only change door_state once consistent readings have been established
		if (num_like_readings >= NUM_LIKE_READINGS_NEEDED){
			door_state = raw_door_state;
		}
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

	// Initialize audio / DF player
		init_dfplayer();

	// Initialize ToF sensor
		sleep_ms(200);
		tof_init();
		sleep_ms(200);

	// Initialize Pi Zero
		init_pi_zero();

		// play waiting for Pi voice prompt
		play_audio_prompt(false, 10);

		// show "waiting for Pi Zero ACK screen"
		print_waiting_for_pi();

		// wait for ACK from Pi Zero
		await_pi_zero_ack();

	// clear LCD
		clear_lcd();
		sleep_ms(10);

	// Play door sensor online prompt
		play_audio_prompt(false, 11);

	// Print initial LCD screen
		update_lcd_screen(lab_state, run_countdown, countdown_time_remaining_ms, countdown_duration);

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
				printf("distance = %u\n", tof_distance);

			// if nonzero data was successfully read from ToF
				if (tof_data_ready){
					tof_data_ready = false;		// reset data ready status

					// determine if door is open or closed based on distance
						determine_door_state(tof_distance);

					// check that door state is different from lab state, countdown not started, override not active
						if ( (door_state != lab_state) && (run_countdown == false) && (override_active == false) ){
							printf("Countdown started\n");
							candidate_state = door_state;			// set candidate door state
							reset_countdown_time_in_ms();			// reset countdown_time_ms	
							run_countdown = true;					// run countdown
							update_leds();							// update LEDs
						}

					// cancel countdown if door state changes during the countdown
						if ( (run_countdown == true) && (candidate_state != door_state) && (override_active == false) ){
							printf("Countdown cancelled because door state returned to prev state\n");
							reset_countdown_time_in_ms();			// reset countdown_time_ms
							run_countdown = false;					// stop countdown
							lcd_print("       ", 10, 1); 			// clear countdown bars if still present
							update_leds();							// update LEDs
						}

					// cancel countdown if override is enabled during countdown
						if ( (run_countdown == true) && (override_active == true) ){
							printf("Countdown cancelled because override was enabled\n");
							reset_countdown_time_in_ms();
							run_countdown = false;
							lcd_print("       ", 10, 1); 			// clear countdown bars if still present
							update_leds();
						}
				}
		}

	// Check digital switches & potentiometer at regular intervals
	if (current_time - last_sw_check_time >= SWITCH_CHECK_INTERVAL_MS){

		// check potentiometer/ADC val for countdown duration, don't check while countdown in progress
			if (!run_countdown) {get_countdown_duration(&countdown_duration);}

		// check override switch
			get_sw_state('o', &override_active);

		// check prompt switch
			get_sw_state('p', &special_prompts_allowed);

		// update LEDs
			update_leds();
	}

	

	// Update LCD at regular intervals
	if (current_time - last_lcd_update_time >= UPDATE_LCD_INTERVAL_MS){
		update_lcd_screen(lab_state, run_countdown, countdown_time_remaining_ms, countdown_duration);
	}


	// If countdown is running and should be updated...
		if ( (run_countdown == true) && (current_time - last_countdown_update_time >= COUNTDOWN_UPDATE_INTERVAL_MS) ){
			// reset last update time
				last_countdown_update_time = current_time;
				
			// decrement countdown time remaining
				countdown_time_remaining_ms = countdown_time_remaining_ms - COUNTDOWN_UPDATE_INTERVAL_MS;

			// blink white LED (handled in update_leds, but counter incremented here)
				second_count += 1;

			// check to see if countdown time has elapsed
				if (countdown_time_remaining_ms <= 0){
					run_countdown = false;
					change_state = true;
					//printf("new lab state!\n");
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
				send_lab_state("OPEN");							// send lab state to Pi Zero
				play_audio_prompt(special_prompts_allowed, 0);	// play a lab-now-open voice prompt
				update_leds();									// turn on green LED, turn off red LED
			}

			else {
				printf("lab is now closed!\n");							
				send_lab_state("CLOSED");						// send lab state to Pi Zero
				play_audio_prompt(special_prompts_allowed, 1);	// play a lab-now-closed voice prompt
				update_leds();									// turn off green LED, turn on red LED
			}
		}
}

/******************</Normal Operation>*****************/