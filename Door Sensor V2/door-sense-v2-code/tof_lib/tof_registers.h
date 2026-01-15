#ifndef TOF_REGISTERS_H
#define TOF_REGISTERS_H

/******************<Summary>*****************
 * Name: tof_registers.h
 * Purpose:
 *      > Contains memory addresses for ToF registers
 * 		> Contains some macros for ToF functionality
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Macros>*****************/
#define START_RANGING_GC		0x40	// write this to SYSTEM__MODE_START to START reading range data
#define STOP_RANGING_GC			0x00	// write this to SYSTEM__MODE_START to STOP ranging

#define CLEAR_INT_GC			0x01	// write this to SYSTEM__INTERRUPT_CLEAR after reading range data
/******************</Macros>*****************/


/******************<Config Registers>*****************/
#define TOF_CONFIG_START_ADDR	0x2D	// start address for tof config on device
#define TOF_CONFIG_END_ADDR		0x87	// end address for tof config on device
/******************</Config Registers>*****************/



/******************<Memory Addresses>*****************/
#define SOFT_RESET											0x0000
#define VL53L1X_I2C_SLAVE__DEVICE_ADDRESS					0x0001
#define VL53L1X_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND       0x0008
#define ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS 		0x0016
#define ALGO__CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS 	0x0018
#define ALGO__CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS 	0x001A
#define ALGO__PART_TO_PART_RANGE_OFFSET_MM					0x001E
#define MM_CONFIG__INNER_OFFSET_MM							0x0020
#define MM_CONFIG__OUTER_OFFSET_MM 							0x0022
#define GPIO_HV_MUX__CTRL									0x0030
#define GPIO__TIO_HV_STATUS       							0x0031
#define SYSTEM__INTERRUPT_CONFIG_GPIO 						0x0046
#define PHASECAL_CONFIG__TIMEOUT_MACROP     				0x004B
#define RANGE_CONFIG__TIMEOUT_MACROP_A_HI   				0x005E
#define RANGE_CONFIG__VCSEL_PERIOD_A        				0x0060
#define RANGE_CONFIG__VCSEL_PERIOD_B						0x0063
#define RANGE_CONFIG__TIMEOUT_MACROP_B_HI  					0x0061
#define RANGE_CONFIG__TIMEOUT_MACROP_B_LO  					0x0062
#define RANGE_CONFIG__SIGMA_THRESH 							0x0064
#define RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS			0x0066
#define RANGE_CONFIG__VALID_PHASE_HIGH      				0x0069
#define VL53L1X_SYSTEM__INTERMEASUREMENT_PERIOD				0x006C
#define SYSTEM__THRESH_HIGH 								0x0072
#define SYSTEM__THRESH_LOW 									0x0074
#define SD_CONFIG__WOI_SD0                  				0x0078
#define SD_CONFIG__INITIAL_PHASE_SD0        				0x007A
#define ROI_CONFIG__USER_ROI_CENTRE_SPAD					0x007F
#define ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE		0x0080
#define SYSTEM__SEQUENCE_CONFIG								0x0081
#define VL53L1X_SYSTEM__GROUPED_PARAMETER_HOLD 				0x0082
#define SYSTEM__INTERRUPT_CLEAR       						0x0086
#define SYSTEM__MODE_START                 					0x0087
#define VL53L1X_RESULT__RANGE_STATUS						0x0089
#define VL53L1X_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0		0x008C
#define RESULT__AMBIENT_COUNT_RATE_MCPS_SD					0x0090
#define VL53L1X_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0				0x0096
#define VL53L1X_RESULT__PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0 	0x0098
#define VL53L1X_RESULT__OSC_CALIBRATE_VAL					0x00DE
#define VL53L1X_FIRMWARE__SYSTEM_STATUS                     0x00E5
#define VL53L1X_IDENTIFICATION__MODEL_ID                    0x010F
#define VL53L1X_ROI_CONFIG__MODE_ROI_CENTRE_SPAD			0x013E
/******************</Memory Addresses>*****************/



#endif // TOF_REGISTERS_H