
/******************<Dependencies>*****************/
#include "peripherals/tof.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
/******************</Private variables>*****************/


/******************<Public variables>*****************/
/******************</Public variables>*****************/


/******************<Function definitions>*****************/

/*******get_distance()*******
 * Description
        > gets distance measurement from ToF
		> waits until data is ready to be read from the tof sensor
 * Arguments
        > uint16_t* distance: distance measurement from ToF
		> bool *data_read:  true=data read, false=data not ready to be read
 * Returns
        > N/A
*/
void get_distance(uint16_t* distance, bool* data_read){
	// Is data ready to be read from the tof sensor?
		if (tof_check_data_ready() == 0){
			printf("ERROR: ToF data NOT READY\n");
			tof_clear_int();
			tof_clear_int();
			sleep_ms(250);
			*data_read = false;
			return;
		}
		else {
			*data_read = true;
		}

	// Get distance from ToF sensor
		*distance = tof_get_distance();
		tof_clear_int();
		tof_clear_int();
		sleep_ms(50);
		//printf("distance = %u\n", *distance);

	return;
}

/******************</Function definitions>*****************/