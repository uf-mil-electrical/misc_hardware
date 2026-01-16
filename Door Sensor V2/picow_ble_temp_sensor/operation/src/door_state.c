/******************<Dependencies>*****************/
#include "operation/door_state.h"
/******************</Dependencies>*****************/


/******************<Global Variables>*****************/
bool first_range = true;			// on first range reading, clear interrupt twice
uint16_t distance = 0;				// ToF distance reading

volatile uint32_t times_isr_fired;	// keeps track of how many times the timer ISR has been called (once every 500ms)
bool lab_open;						// true=lab is open, false=lab is closed
/******************</Global Variables>*****************/



/******************<Interrupt Service Routines>*****************/

/*******repeating_timer_callback*******
 * Description
        > is called when the repeating timer overflows
		> increments value of times_isr_fired variable
*/
bool repeating_timer_callback(struct repeating_timer *t){
	times_isr_fired += 1;

	return true;
}

/******************</Interrupt Service Routines>*****************/



/******************<Public Functions>*****************/
/*******is_door_open*******
 * Description
        > determines whether door is open or closed
 * Arguments
		> N/A
 * Returns
        > bool: true=door open, false=door closed
*/
bool is_door_open(){
	// First, wait until new data is ready to be read
		uint8_t dataReady;
		
		do {
			dataReady = tof_check_data_ready();
			sleep_us(1);
		} while (dataReady == 0);

	// Second, read and display result
		distance = tof_get_distance();
		//printf("is_door_open(): distance = %5d\n", distance);

	// Third, clear interrupt to prepare to read a new measurement
		tof_clear_int();

		if (first_range) {  // Clear twice on first measurement
			tof_clear_int();
			first_range = false;
		}

	// Fourth, return appropriate value
		if ( (distance <= DOOR_DISTANCE) && (distance != 0) ){
			//printf("is_door_open(): door is OPEN\n");
			return true;
		}
		else {
			//printf("is_door_open(): door is CLOSED\n");
			return false;
		}
}


/*******run_door_sensor*******
 * Description
        > master function, called by main() after inits are complete
		> this function monitors the ToF sensor's values and communicates
		  with the Discord bot to indicate if the lab is opened or closed
 * Arguments
		> N/A
 * Returns
        > N/A
*/
void run_door_sensor(){
	// Code to run on startup
		// First, create a repeating timer (will be configured in next step)
			struct repeating_timer timer;

		// Second, assume that lab is currently closed
			lab_open = false;

		// Third, assume that the door is closed and no change to lab_open needs to happen
			bool change_state = false; // determines if the lab will change from being open or closed

	// Main program loop
	while(1){

		// Check to see if lab_open state is different from is_door_open state
		
			bool door_state = is_door_open();	// get current door state

			if (lab_open != door_state) {

				printf("Door state change detected!\n");

				// i: reset the times_isr_fired count
					times_isr_fired = 0;

				// ii: configure timer to fire once every 500ms
					add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer);

				// iii: run this code for 10 seconds UNLESS door changes state before 10 seconds elapse
					while(1){
						// blink LED (change state once every 500ms)
						if (times_isr_fired % 2 == 0){set_led('g', true);}
						else {set_led('g', false);}

						// check if door state has changed since countdown start, cancel timer if so
						if (door_state != is_door_open()){
							cancel_repeating_timer(&timer);
							change_state = false;
							set_led('g', false);
							printf("Cancelled state change\n");
							break;
						}

						// check to see if timer has counted to 10 seconds
						if (times_isr_fired >= 20){			// 500ms * 20 = 10 seconds
							cancel_repeating_timer(&timer);
							change_state = true;
							printf("New lab state\n");
							break;
						}

						// brief safety delay
						sleep_ms(10);
					}
			}

			// If door state has changed and 10 seconds have elapsed, update lab_open status
			if (change_state == true){
				lab_open = door_state;
				change_state = false;

				if (lab_open == true){set_led('g', true);}
				else {set_led('g', false);}

				printf("CHANGED STATE to %d\n", lab_open);
			}
	}
}

/******************</Public Functions>*****************/