
/******************<Dependencies>*****************/
#include "tof_lib/tof_core.h"
/******************</Dependencies>*****************/



/******************<Default Configuration>*****************/
const uint8_t VL53L1X_DEFAULT_CONFIGURATION[] = {
  0x00, /* 0x2d : set bit 2 and 5 to 1 for fast plus mode (1MHz I2C), else don't touch */
  0x00, /* 0x2e : bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
  0x00, /* 0x2f : bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
  0x01, /* 0x30 : set bit 4 to 0 for active high interrupt and 1 for active low (bits 3:0 must be 0x1), use SetInterruptPolarity() */
  0x02, /* 0x31 : bit 1 = interrupt depending on the polarity, use CheckForDataReady() */
  0x00, /* 0x32 : not user-modifiable */
  0x02, /* 0x33 : not user-modifiable */
  0x08, /* 0x34 : not user-modifiable */
  0x00, /* 0x35 : not user-modifiable */
  0x08, /* 0x36 : not user-modifiable */
  0x10, /* 0x37 : not user-modifiable */
  0x01, /* 0x38 : not user-modifiable */
  0x01, /* 0x39 : not user-modifiable */
  0x00, /* 0x3a : not user-modifiable */
  0x00, /* 0x3b : not user-modifiable */
  0x00, /* 0x3c : not user-modifiable */
  0x00, /* 0x3d : not user-modifiable */
  0xff, /* 0x3e : not user-modifiable */
  0x00, /* 0x3f : not user-modifiable */
  0x0F, /* 0x40 : not user-modifiable */
  0x00, /* 0x41 : not user-modifiable */
  0x00, /* 0x42 : not user-modifiable */
  0x00, /* 0x43 : not user-modifiable */
  0x00, /* 0x44 : not user-modifiable */
  0x00, /* 0x45 : not user-modifiable */
  0x20, /* 0x46 : interrupt configuration 0->level low detection, 1-> level high, 2-> Out of window, 3->In window, 0x20-> New sample ready , TBC */
  0x0b, /* 0x47 : not user-modifiable */
  0x00, /* 0x48 : not user-modifiable */
  0x00, /* 0x49 : not user-modifiable */
  0x02, /* 0x4a : not user-modifiable */
  0x0a, /* 0x4b : not user-modifiable */
  0x21, /* 0x4c : not user-modifiable */
  0x00, /* 0x4d : not user-modifiable */
  0x00, /* 0x4e : not user-modifiable */
  0x05, /* 0x4f : not user-modifiable */
  0x00, /* 0x50 : not user-modifiable */
  0x00, /* 0x51 : not user-modifiable */
  0x00, /* 0x52 : not user-modifiable */
  0x00, /* 0x53 : not user-modifiable */
  0xc8, /* 0x54 : not user-modifiable */
  0x00, /* 0x55 : not user-modifiable */
  0x00, /* 0x56 : not user-modifiable */
  0x38, /* 0x57 : not user-modifiable */
  0xff, /* 0x58 : not user-modifiable */
  0x01, /* 0x59 : not user-modifiable */
  0x00, /* 0x5a : not user-modifiable */
  0x08, /* 0x5b : not user-modifiable */
  0x00, /* 0x5c : not user-modifiable */
  0x00, /* 0x5d : not user-modifiable */
  0x01, /* 0x5e : not user-modifiable */
  0xcc, /* 0x5f : not user-modifiable */
  0x0f, /* 0x60 : not user-modifiable */
  0x01, /* 0x61 : not user-modifiable */
  0xf1, /* 0x62 : not user-modifiable */
  0x0d, /* 0x63 : not user-modifiable */
  0x01, /* 0x64 : Sigma threshold MSB (mm in 14.2 format for MSB+LSB), use SetSigmaThreshold(), default value 90 mm  */
  0x68, /* 0x65 : Sigma threshold LSB */
  0x00, /* 0x66 : Min count Rate MSB (MCPS in 9.7 format for MSB+LSB), use SetSignalThreshold() */
  0x80, /* 0x67 : Min count Rate LSB */
  0x08, /* 0x68 : not user-modifiable */
  0xb8, /* 0x69 : not user-modifiable */
  0x00, /* 0x6a : not user-modifiable */
  0x00, /* 0x6b : not user-modifiable */
  0x00, /* 0x6c : Intermeasurement period MSB, 32 bits register, use SetIntermeasurementInMs() */
  0x00, /* 0x6d : Intermeasurement period */
  0x0f, /* 0x6e : Intermeasurement period */
  0x89, /* 0x6f : Intermeasurement period LSB */
  0x00, /* 0x70 : not user-modifiable */
  0x00, /* 0x71 : not user-modifiable */
  0x00, /* 0x72 : distance threshold high MSB (in mm, MSB+LSB), use SetD:tanceThreshold() */
  0x00, /* 0x73 : distance threshold high LSB */
  0x00, /* 0x74 : distance threshold low MSB ( in mm, MSB+LSB), use SetD:tanceThreshold() */
  0x00, /* 0x75 : distance threshold low LSB */
  0x00, /* 0x76 : not user-modifiable */
  0x01, /* 0x77 : not user-modifiable */
  0x0f, /* 0x78 : not user-modifiable */
  0x0d, /* 0x79 : not user-modifiable */
  0x0e, /* 0x7a : not user-modifiable */
  0x0e, /* 0x7b : not user-modifiable */
  0x00, /* 0x7c : not user-modifiable */
  0x00, /* 0x7d : not user-modifiable */
  0x02, /* 0x7e : not user-modifiable */
  0xc7, /* 0x7f : ROI center, use SetROI() */
  0xff, /* 0x80 : XY ROI (X=Width, Y=Height), use SetROI() */
  0x9B, /* 0x81 : not user-modifiable */
  0x00, /* 0x82 : not user-modifiable */
  0x00, /* 0x83 : not user-modifiable */
  0x00, /* 0x84 : not user-modifiable */
  0x01, /* 0x85 : not user-modifiable */
  0x00, /* 0x86 : clear interrupt, use ClearInterrupt() */
  0x00  /* 0x87 : start ranging, use StartRanging() or StopRanging(), If you want an automatic start after VL53L1X_init() call, put 0x40 in location 0x87 */
};
/******************</Default Configuration>*****************/



/******************<Public Functions>*****************/
/*******tof_init*******
 * Description
        > initializes I2C bus connected to ToF sensor
		> initializes ToF sensor
 * Arguments
 * Returns
        > int: error code
*/
int tof_init(){
	// First, initialize the I2C bus used for ToF communication
		//init_i2c(TOF_I2C_PORT, TOF_I2C_BAUDRATE, TOF_SDA, TOF_SCL);

	// Second, init GPIO pins related to ToF sensor
		//i: GPIO1 pin (input)
			gpio_init(TOF_GPIO1_PIN);
			gpio_set_dir(TOF_GPIO1_PIN, SET_GPIO_INPUT);

		//ii: XSHUT pin (output)
			gpio_init(TOF_XSHUT_PIN);
        	gpio_set_dir(TOF_XSHUT_PIN, SET_GPIO_OUTPUT);
        	gpio_put(TOF_XSHUT_PIN, GPIO_SET_HIGH);			// set high to turn ToF ON
			sleep_ms(50);

	// Third, validate sensor model ID & type
		uint16_t tof_id = tof_get_id();

		if (tof_id != VL53L1X_SENSOR_ID){
			printf("tof_init(): invalid sensor model ID / type)\n");
			//return -1;
		}

	// Fourth, wait for sensor to boot
		do {
			sleep_ms(250);
			printf("tof_init(): waiting for sensor boot...\n");
		} while (tof_check_booted() == 0);

		printf("tof_init(): sensor booted.\n");
		

	// Fifth, write default configuration to ToF sensor (see "tof_config.h")
		uint8_t tmp_addr = 0;		// stores a temporary register addr

		for (tmp_addr = TOF_CONFIG_START_ADDR; tmp_addr <= TOF_CONFIG_END_ADDR; tmp_addr++){
			tof_write_byte(tmp_addr, VL53L1X_DEFAULT_CONFIGURATION[tmp_addr - TOF_CONFIG_START_ADDR]);
		}
		
	// Sixth, enable range data collection (ranging)
		tof_enable(true);

	// Seventh, wait until some data is ready (ensures successful boot)
		while (tof_check_data_ready() == 0) {
    		sleep_ms(2);
		}

	// Eighth, clear read interrupt, stop ranging
		tof_clear_int();
		tof_clear_int();	// clear twice as a precaution

		tof_enable(false);
		

	// Ninth, specify timeout period for Voltage High Voltage (VHV) biasing
		tof_write_byte(VL53L1X_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND, 0x09); // fuck if I know

	// Tenth, specify that VHV calibration should start using previously-stored temp reference
		tof_write_byte(0x0B, 0);	// also not a damn clue, asked ChatGPT what this meant and still unsure
		
	// Eleventh, set distance mode
		tof_set_distance_mode(1);	// short-range operation		

	// Twelfth, set timing budget
		tof_set_timing_budget(100);	// timing budget = 100ms

	// Thirteenth, set measurement period
		tof_set_measurement_period(100);

	// Thirteenth, start ranging
		tof_enable(true);

	// Lastly, return to main program
		return 1;
}



/*******tof_enable*******
 * Description
        > enables/disables ranging onboard ToF sensor
 * Arguments
		> bool enable: true=start, false=stop
 * Returns
        > N/A
*/
void tof_enable(bool enable){
	// First, enable/disable ranging
		if (enable == true){
			tof_write_byte(SYSTEM__MODE_START, START_RANGING_GC);
		}

		else {
			tof_write_byte(SYSTEM__MODE_START, STOP_RANGING_GC);
		}

	// Lastly, return to main program
		return;
}



/*******tof_get_id*******
 * Description
        > gets the sensor model ID & type
 * Arguments
		> N/A
 * Returns
        > uint16_t: sensor ID
*/
uint16_t tof_get_id(){
	// First, read ID/type register value
		uint16_t id_reg = 0;
		tof_read_word(VL53L1X_IDENTIFICATION__MODEL_ID, &id_reg);

	// Lastly, return the register's value
		return id_reg;
}



/*******tof_check_booted*******
 * Description
        > checks to see if ToF sensor has booted
 * Arguments
		> N/A
 * Returns
        > uint8_t: 1=successful boot, 0=not booted
*/
uint8_t tof_check_booted(){
	// First, read from firmware status register
		uint8_t status_val = 0;
		tof_read_byte(VL53L1X_FIRMWARE__SYSTEM_STATUS, &status_val);

	// Lastly, return status_val (is 0 or 1)
		return status_val;
}



/*******tof_check_data_ready*******
 * Description
        > checks to see if range data is ready to be read from the ToF sensor
 * Arguments
		> N/A
 * Returns
        > bool: true=data ready, false=no data ready
*/

/*
bool tof_check_data_ready(){
	// First, determine if result interrupt polarity is active-high/low
		bool active_high = tof_get_int_polarity();

	// Second, read bit 0 from ToF result status register
		uint8_t status_byte = 0;
		tof_read_byte(GPIO__TIO_HV_STATUS, &status_byte);
		uint8_t status_b0 = status_byte & 0b00000001;		// extract bit 0

	// Third, check if data is ready to be read based on interrupt priority
		bool data_ready = (status_b0 == active_high);

	// Lastly, return value of data ready
		return data_ready;
}
*/



uint8_t tof_check_data_ready() {
  uint8_t tmp, iPol;

  iPol = tof_get_int_polarity();
  tof_read_byte(GPIO__TIO_HV_STATUS, &tmp);

  // Check if value is ready based on interrupt polarity
  uint8_t dataReady = (tmp & 0x1) == iPol;
  return dataReady;
}


/*******tof_set_int_polarity*******
 * Description
        > sets the "data ready" interrupt to active-high or active-low
 * Arguments
		> bool active_high: true=set int to active-high, false=set int to active-low
 * Returns
        > N/A
*/
void tof_set_int_priority(bool active_high){
	// First, get value of GPIO_HV_MUX__CTRL register, disregard bit 4
		uint8_t reg_val = 0;
		tof_read_byte(GPIO_HV_MUX__CTRL, &reg_val);
		reg_val = reg_val & 0b11101111;		// get every bit except bit 4

	// Second, determine new value of bit 4, insert into register value
		reg_val = reg_val | (!(active_high & 1)) << 4;

	// Third, write new reg value to GPIO_HV_MUX__CTRL
		tof_write_byte(GPIO_HV_MUX__CTRL, reg_val);

	// Lastly, return to main program
		return;
}



/*******tof_get_int_polarity*******
 * Description
        > determines whether the "data ready" interrupt is active-high or active-low
 * Arguments
		> N/A
 * Returns
        > uint8_t: polarity
*/
uint8_t tof_get_int_polarity(){
	uint8_t tmp, iPol;

  tof_read_byte(GPIO_HV_MUX__CTRL, &tmp);
  tmp = tmp & 0x10;
  iPol = !(tmp>>4);
  return iPol;
}


/*******tof_clear_int*******
 * Description
        > clears data ready interrupt
		> needs to be called after reading data from ToF
 * Arguments
		> N/A
 * Returns
        > N/A
*/
void tof_clear_int(){
	// First, write CLEAR_INT to SYSTEM__INTERRUPT_CLEAR
		tof_write_byte(SYSTEM__INTERRUPT_CLEAR, CLEAR_INT_GC);

	// Lastly, return to main program
		return;
}



/*******tof_get_distance_mode*******
 * Description
        > gets distance mode for ToF sensor
 * Arguments
		> N/A
 * Returns
        > uint8_t: 0=short-range, 1=long-range
*/
uint8_t tof_get_distance_mode(){
	// First, read value of distance mode register
		uint8_t distance_reg_val = 0;
		tof_read_byte(PHASECAL_CONFIG__TIMEOUT_MACROP, &distance_reg_val);

	// Second, return distance mode
		switch(distance_reg_val){
			case (0x14): {return 1; break;}	// short-range
			case (0x0A): {return 2; break;} // long-range
			default: {return 0; break;}
		}
}



/*******tof_set_distance_mode*******
 * Description
        > sets distance mode for ToF sensor (short- or long-range)
 * Arguments
		> uint8_t mode: 0=short-range, 1=long-range
 * Returns
        > int: error code
*/
int tof_set_distance_mode(uint8_t mode){
	// First, get current timing budget
		uint16_t timing_budget = tof_get_timing_budget();

	// Second, update distance mode
		switch(mode) {	// don't ask about the magic numbers there's literally 0 documentation 0_o
			case 1: { // short-range (stupid magic numbers)
				tof_write_byte(PHASECAL_CONFIG__TIMEOUT_MACROP, 0x14);
				tof_write_byte(RANGE_CONFIG__VCSEL_PERIOD_A, 0x07);
				tof_write_byte(RANGE_CONFIG__VCSEL_PERIOD_B, 0x05);
				tof_write_byte(RANGE_CONFIG__VALID_PHASE_HIGH, 0x38);
				tof_write_word(SD_CONFIG__WOI_SD0, 0x0705);
				tof_write_word(SD_CONFIG__INITIAL_PHASE_SD0, 0x0606);
				break;
			}
			case 2: { // long-range (unavoidable magic numbers)
				tof_write_byte(PHASECAL_CONFIG__TIMEOUT_MACROP, 0x0A);
				tof_write_byte(RANGE_CONFIG__VCSEL_PERIOD_A, 0x0F);
				tof_write_byte(RANGE_CONFIG__VCSEL_PERIOD_B, 0x0D);
				tof_write_byte(RANGE_CONFIG__VALID_PHASE_HIGH, 0xB8);
				tof_write_word(SD_CONFIG__WOI_SD0, 0x0F0D);
				tof_write_word(SD_CONFIG__INITIAL_PHASE_SD0, 0x0E0E);
				break;
			}
			default: {
				printf("tof_set_distance_mode(): invalid mode\n");
				return -1;
				break;
			}
		}

	// Third, reset timing budget to what it was before changing distance mode
		tof_set_timing_budget(timing_budget);

	// Lastly, return to main program
		return 0;
}




/*******tof_get_timing_budget*******
 * Description
        > gets timing budget for ToF sensor in ms
 * Arguments
		> N/A
 * Returns
        > uint16_t: timing budget
*/
uint16_t tof_get_timing_budget(){
	// First, read raw timing budget register value
		uint16_t raw_budget = 0;
		tof_read_word(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, &raw_budget);

	// Second, return uint16_t value for timing budget
		switch(raw_budget){
			case 0x001D: {return 15; break;}
			case 0x0051: {return 20; break;}
			case 0x001E: {return 20; break;}
			case 0x00D6: {return 33; break;}
			case 0x0060: {return 33; break;}
			case 0x01AE: {return 50; break;}
			case 0x00AD: {return 50; break;}
			case 0x02E1: {return 100; break;}
			case 0x01CC: {return 100; break;}
			case 0x03E1: {return 200; break;}
			case 0x02D9: {return 200; break;}
			case 0x0591: {return 500; break;}
			case 0x048F: {return 500; break;}
			default: {return 0; break;}
		}
}



/*******tof_set_timing_budget*******
 * Description
        > sets timing budget for ToF sensor in ms
 * Arguments
		> uint16_t time_budget: timing budget in ms
 * Returns
        > int: error code
*/
int tof_set_timing_budget(uint16_t time_budget){
	// First, get distance mode
		uint16_t distance_mode = tof_get_distance_mode();

	// Second, get range values for new timing budget
		uint32_t rangeA, rangeB;

		if (distance_mode == 1){ // short-distance mode
			switch(time_budget){
				case 15: {rangeA = 0x001D, rangeB = 0x0027; break;}
				case 20: {rangeA = 0x0051, rangeB = 0x006E; break;}
				case 33: {rangeA = 0x00D6, rangeB = 0x006E; break;}
				case 50: {rangeA = 0x01AE, rangeB = 0x01E8; break;}
				case 100: {rangeA = 0x02E1, rangeB = 0x0388; break;}
				case 200: {rangeA = 0x03E1, rangeB = 0x0496; break;}
				case 500: {rangeA = 0x0591, rangeB = 0x05C1; break;}
				default: {
					printf("tof_set_timing_budget: invalid time budget for short-range operation");
					return -1;
				}
			}
		}

		else { // long-distance mode
			switch(time_budget){
				case 20: {rangeA = 0x001E, rangeB = 0x0022; break;}
				case 33: {rangeA = 0x0060, rangeB = 0x006E; break;}
				case 50: {rangeA = 0x00AD, rangeB = 0x00C6; break;}
				case 100: {rangeA = 0x01CC, rangeB = 0x01EA; break;}
				case 200: {rangeA = 0x02D9, rangeB = 0x02F8; break;}
				case 500: {rangeA = 0x048F, rangeB = 0x04A4; break;}
				default: {
					printf("tof_set_timing_budget: invalid time budget for long-range operation");
					return -1;
				}
			}
		}

	// Third, write new range values to timing budget registers
		tof_write_word(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, rangeA);
		tof_write_word(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, rangeB);

	// Lastly, return to main program
		return 0;
}




/*******tof_get_measurement_period*******
 * Description
        > gets inter-measurement period (time between readings)
 * Arguments
		> N/A
 * Returns
        > uint16_t: inter-measurement period in ms
*/
uint16_t tof_get_measurement_period(){
	// First, get measurement period register value
		uint32_t period_reg_val = 0;
		tof_read_2_words(VL53L1X_SYSTEM__INTERMEASUREMENT_PERIOD, &period_reg_val);

	// Second, get current clock PLL
		uint16_t clockPLL = 0;
		tof_read_word(VL53L1X_RESULT__OSC_CALIBRATE_VAL, &clockPLL);
		clockPLL = clockPLL & 0x3FF;

	// Third, determine current measurement period
		uint16_t meas_period = (uint16_t)(((uint16_t)period_reg_val)/(clockPLL*1.065));

	// Lastly, return value
		return meas_period;
}



/*******tof_set_measurement_period*******
 * Description
        > sets inter-measurement period (time between readings)
 * Arguments
		> uint32_t period: inter-measurement period in ms
 * Returns
        > N/A
*/
void tof_set_measurement_period(uint32_t period){
	// First, get ToF clock PLL
		uint16_t clockPLL;
		tof_read_word(VL53L1X_RESULT__OSC_CALIBRATE_VAL, &clockPLL);
		clockPLL = clockPLL & 0x3FF; 	// 0x3FF = 0011 1111 1111, disregard bits 10 and 11

	// Second, write new period to measurement period register
		tof_write_2_words(VL53L1X_SYSTEM__INTERMEASUREMENT_PERIOD, (uint32_t)(clockPLL * period * 1.075));
}



/*******tof_get_distance*******
 * Description
        > THE BIG ONE
		> Measures distance to nearest object in mm
 * Arguments
		> N/A
 * Returns
        > uint16_t: distance in mm
*/
uint16_t tof_get_distance(){
	// First, read from distance register
		uint16_t distance = 0;
		tof_read_word(VL53L1X_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0, &distance);

	// Lastly, return distance
		return distance;
}

/******************</Public Functions>*****************/