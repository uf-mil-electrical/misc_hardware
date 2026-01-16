/******************<Dependencies>*****************/
#include "operation/door_state.h"
/******************</Dependencies>*****************/


/******************<Global Variables>*****************/
bool first_range = true;			// on first range reading, clear interrupt twice
uint16_t distance = 0;				// ToF distance reading
/******************</Global Variables>*****************/


/******************<Public Functions>*****************/





/*******is_door_open*******
 * Description
        > determines whether door is open or closed
		> non-blocking, only call if data is ready to be read from ToF
 * Arguments
		> N/A
 * Returns
        > bool: true=door open, false=door closed
*/
bool is_door_open(){

	// First, read and display result
		distance = tof_get_distance();
		//printf("is_door_open(): distance = %5d\n", distance);

	// Second, clear interrupt to prepare to read a new measurement
		tof_clear_int();

		if (first_range) {  // Clear twice on first measurement
			tof_clear_int();
			first_range = false;
		}

	// Third, return appropriate value
		if ( (distance <= DOOR_DISTANCE) && (distance != 0) ){
			//printf("is_door_open(): door is OPEN\n");
			return true;
		}
		else {
			//printf("is_door_open(): door is CLOSED\n");
			return false;
		}
}

/******************</Public Functions>*****************/