/******************<Dependencies>*****************/
#include "peripherals/thermistors.h"
/******************</Dependencies>*****************/



/******************<NTC Thermistor Va9lues>*****************/
static const ntc_temp_refs ntc_10k_3950_vals[] = {
    {343632.6f , -40},
    {321280.9f , -39},
    {300533.9f , -38},
    {281266.0f , -37},
    {263362.4f , -36},
    {246717.7f , -35},
    {231235.5f , -34},
    {216827.3f , -33},
    {203411.8f , -32},
    {190914.4f , -31},
    {179266.6f , -30},
    {168405.3f , -29},
    {158272.6f , -28},
    {148815.1f , -27},
    {139983.7f , -26},
    {131733.2f , -25},
    {124021.6f , -24},
    {116810.7f , -23},
    {110064.8f , -22},
    {103751.2f , -21},
    {97839.6f , -20},
    {92302.0f , -19},
    {87112.4f , -18},
    {82247.1f , -17},
    {77683.7f , -16},
    {73401.8f , -15},
    {69382.3f , -14},
    {65607.7f , -13},
    {62061.6f , -12},
    {58728.8f , -11},
    {55595.3f , -10},
    {52648.0f , -9},
    {49874.7f , -8},
    {47264.3f , -7},
    {44806.2f , -6},
    {42490.6f , -5},
    {40308.6f , -4},
    {38251.6f , -3},
    {36311.7f , -2},
    {34481.7f , -1},
    {32754.7f , 0},
    {31124.3f , 1},
    {29584.7f , 2},
    {28130.1f , 3},
    {26755.6f , 4},
    {25456.2f , 5},
    {24227.4f , 6},
    {23065.0f , 7},
    {21965.0f , 8},
    {20923.9f , 9},
    {19938.0f , 10},
    {19004.1f , 11},
    {18119.3f , 12},
    {17280.7f , 13},
    {16485.7f , 14},
    {15731.7f , 15},
    {15016.4f , 16},
    {14337.6f , 17},
    {13693.3f , 18},
    {13081.6f , 19},
    {12500.5f , 20},
    {11948.5f , 21},
    {11423.9f , 22},
    {10925.2f , 23},
    {10451.0f , 24},
    {10000.0f , 25},
    {9570.9f , 26},
    {9162.6f , 27},
    {8773.8f , 28},
    {8403.7f , 29},
    {8051.2f , 30},
    {7715.4f , 31},
    {7395.3f , 32},
    {7090.3f , 33},
    {6799.5f , 34},
    {6522.1f , 35},
    {6257.6f , 36},
    {6005.1f , 37},
    {5764.2f , 38},
    {5534.2f , 39},
    {5314.6f , 40},
    {5104.9f , 41},
    {4904.5f , 42},
    {4713.0f , 43},
    {4530.0f , 44},
    {4355.1f , 45},
    {4187.8f , 46},
    {4027.8f , 47},
    {3874.8f , 48},
    {3728.3f , 49},
    {3588.2f , 50},
    {3454.0f , 51},
    {3325.5f , 52},
    {3202.5f , 53},
    {3084.6f , 54},
    {2971.7f , 55},
    {2863.5f , 56},
    {2759.7f , 57},
    {2660.3f , 58},
    {2564.9f , 59},
    {2473.4f , 60},
    {2385.6f , 61},
    {2301.4f , 62},
    {2220.6f , 63},
    {2143.1f , 64},
    {2068.6f , 65},
    {1997.0f , 66},
    {1928.3f , 67},
    {1862.3f , 68},
    {1798.9f , 69},
    {1738.0f , 70},
    {1679.4f , 71},
    {1623.1f , 72},
    {1568.9f , 73},
    {1516.8f , 74},
    {1466.7f , 75},
    {1418.5f , 76},
    {1372.2f , 77},
    {1327.5f , 78},
    {1284.5f , 79},
    {1243.1f , 80},
    {1203.3f , 81},
    {1164.9f , 82},
    {1127.9f , 83},
    {1092.3f , 84},
    {1058.0f , 85},
    {1024.9f , 86},
    {993.0f , 87},
    {962.3f , 88},
    {932.6f , 89},
    {904.0f , 90},
    {876.4f , 91},
    {849.8f , 92},
    {824.1f , 93},
    {799.4f , 94},
    {775.4f , 95},
    {752.3f , 96},
    {730.0f , 97},
    {708.5f , 98},
    {687.7f , 99},
    {667.6f , 100},
    {648.2f , 101},
    {629.5f , 102},
    {611.3f , 103},
    {593.8f , 104},
    {576.9f , 105},
    {560.5f , 106},
    {544.7f , 107},
    {529.3f , 108},
    {514.5f , 109},
    {500.2f , 110},
    {486.3f , 111},
    {472.9f , 112},
    {459.9f , 113},
    {447.4f , 114},
    {435.2f , 115},
    {423.4f , 116},
    {412.0f , 117},
    {400.9f , 118},
    {390.2f , 119},
    {379.9f , 120},
    {369.8f , 121},
    {360.1f , 122},
    {350.6f , 123},
    {341.5f , 124},
    {332.6f , 125}
};

const size_t ntc_10k_3950_vals_size = sizeof(ntc_10k_3950_vals)/sizeof(ntc_10k_3950_vals[0]);
/******************</NTC Thermistor Values>*****************/


/******************<Global Variables>*****************/
float thermistor_temps[4];       // stores the temp measured at each thermistor
/******************</Global Variables>*****************/



/******************<Private Functions>*****************/

/*******get_adc_channel*******
 * Description
        > returns the ADC channel corresponding to the passed-in
            GPIO pin
        > GPIO26 = ADC CH0, ..., GPIO29 = ADC CH3
 * Arguments
        > uint8_t adc_pin: GPIO pin corresponding to an ADC channel
        > uint* adc_ch: pointer to loc to store ADC channel
            - returns 99 if input is invalid
 * Returns
        > N/A
*/
void get_adc_channel(uint8_t adc_pin, uint* adc_ch){

    switch (adc_pin){
        case 26: {*adc_ch = 0; break;}
        case 27: {*adc_ch = 1; break;}
        case 28: {*adc_ch = 2; break;}
        case 29: {*adc_ch = 3; break;}
        default: {*adc_ch = 99;}
    }

}



/*******get_thermistor_pin*******
 * Description
        > gets the GPIO pin that corresponds to a certain thermistor
 * Arguments
        > uint8_t thermistor: target thermistor (0-3)
        > uint8_t* pin: pointer to location to store thermistor pin
        > returns 99 for an invalid thermistor
 * Returns
        > N/A
*/
void get_thermistor_pin(uint8_t thermistor, uint8_t* pin){

    switch (thermistor){
        case 0: {*pin = THERMISTOR_0_PIN; break;}
        case 1: {*pin = THERMISTOR_1_PIN; break;}
        case 2: {*pin = THERMISTOR_2_PIN; break;}
        case 3: {*pin = THERMISTOR_3_PIN; break;}
        default: {*pin = 99;}
    }

}



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


/*******approx_temp_from_lut*******
 * Description
        > performs linear interpolation to get an approx temp
            based on values in res to temp look-up table
 * Arguments
        > float res: resistance of NTC thermistor
		> ntc_temp_refs ntc_lut*: NTC lookup table to use
		> size_t lut_size: size of lut being used
        > float* temp: pointer to float to store approximated temp
 * Returns
        > N/A
*/
void approx_temp_from_lut(float res, const ntc_temp_refs* ntc_lut, size_t lut_size, float* temp){
    
    // set output temp to highest temp in LUT to start
        float output_temp = ntc_lut[lut_size - 1].temperature;

    // if resistance is larger than largest in LUT, set output temp to be lowest
        if (res > ntc_lut[0].resistance){
            output_temp = ntc_lut[0].temperature;
        }

    // if resistance is smaller than largest in LUT, perform linear interpolation to find best match
        else{
            for (size_t i = 0; i < lut_size; i++){

                // if the ratio is between two ratios in ntc_vals
                if (res <= ntc_lut[i].resistance && res >= ntc_lut[i+1].resistance){
                    float res_hi = ntc_lut[i].resistance;
                    float temp_hi = (float)ntc_lut[i].temperature;

                    float res_lo = ntc_lut[i+1].resistance;
                    float temp_lo = (float)ntc_lut[i+1].temperature;

                    float fraction = (res - res_hi) / (res_lo - res_hi);
                    output_temp = temp_hi + fraction * (temp_lo - temp_hi);
                    break;
                }
            }
        }

    // return approximated temperature
        *temp = output_temp;
}
/******************</Private Functions>*****************/


/******************<Function Definitions>*****************/

/*******get_adc_channel*******
 * Description
        > initializes ADC
        > inits GPIO pins connected to thermistors
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_thermistors(){
    // init ADC system
        adc_init();

    // init each ADC pin
        adc_gpio_init(THERMISTOR_0_PIN);
        adc_gpio_init(THERMISTOR_1_PIN);
        adc_gpio_init(THERMISTOR_2_PIN);
        adc_gpio_init(THERMISTOR_3_PIN);

    // get channel for thermistor 0
        uint active_adc_ch = 0;
        get_adc_channel(THERMISTOR_0_PIN, &active_adc_ch);

    // set adc to read thermistor 0 for now
        adc_select_input(active_adc_ch);
}



/*******read_thermistor_value*******
 * Description
        > measures voltage at one thermistor
        > converts voltage to approx temperature
        > stores temperature in global array
 * Arguments
        > uint8_t target_thermistor: thermistor to read from (0 to 3)
 * Returns
        > N/A
*/
void read_thermistor_value(uint8_t target_thermistor){
    // validate input
        if (target_thermistor > 3){
            printf("read_thermistor_voltage(): invalid thermistor (%u)\n", target_thermistor);
            return;
        }

    // get GPIO pin for selected thermistor
        uint8_t thermistor_pin = 0;
        get_thermistor_pin(target_thermistor, &thermistor_pin);

    // get ADC channel, set ADC input
        uint adc_ch = 0;
        get_adc_channel(thermistor_pin, &adc_ch);
        if (adc_ch == 99){printf("read_thermistor_voltage(): invalid ADC channel (%u)"), adc_ch;}
        adc_select_input(adc_ch);

    // get raw ADC value
        uint16_t raw_adc_val = adc_read();

    // convert raw val to voltage
        float adc_voltage = (float)(raw_adc_val) * (ADC_VREF / ADC_RESOLUTION);

    // check if thermistor is present based on set threshold voltage
        if (adc_voltage <= MIN_THERM_VOLTAGE){
            set_thermistor_led(target_thermistor, false);
            thermistor_temps[target_thermistor] = 0.0f;
            return;
        }
        else {
            set_thermistor_led(target_thermistor, true);
        }

    // convert voltage measurement to resistance measurement
        float res = (RES_LADDER_RB * (ADC_VREF - adc_voltage)) / adc_voltage;

    // approximate temp from resistance
        float temp = 0.0f;
        approx_temp_from_lut(res, ntc_10k_3950_vals, ntc_10k_3950_vals_size, &temp);

    // update corresponding global variable
        thermistor_temps[target_thermistor] = temp;

    // [DEBUG] print value
        printf("read_thermistor_voltage(%u): ADC voltage = %f, res = %f, temp = %f\n", target_thermistor, adc_voltage, res, temp);
}


/*******scan_thermistors*******
 * Description
        > gets temperatures from each thermistor
        > high-level function to be called from main()
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void scan_thermistors(){
    for (int i = 0; i < 4; i++){
        read_thermistor_value(i);
        sleep_ms(20);
    }
}
/******************</Function Definitions>*****************/
