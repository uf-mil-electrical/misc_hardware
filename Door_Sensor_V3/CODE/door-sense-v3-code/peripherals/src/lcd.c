/******************<Dependencies>*****************/
#include "peripherals/lcd.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
/******************</Private variables>*****************/


/******************<Public variables>*****************/
/******************</Public variables>*****************/


/******************<Function definitions>*****************/

/*******doorsense_init_lcd*******
 * Description
        > initializes LCD display
		> initializes selected GPIO to interact with LCD
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void doorsense_init_lcd(){
	
	// Initialize LCD
		init_lcd(LCD_RS, LCD_EN, LCD_BACKLIGHT, LCD_4, LCD_5, LCD_6, LCD_7, 16, 2);
		backlight(true);
		home();
		clear();

	// Print messages
		set_cursor(2,0);
		message("hello");
		set_cursor(0,1);
		message("world");
		show_blink(true);

    return;
}


/*******lcd_print_vals*******
 * Description
        > prints the measured and ideal resistances of
			the resistor being measured
 * Arguments
        > float measured_res: measured value of the resistor
		> float ideal_res: interpolated ideal value of the res
		> bool valid: is the resistance between 1k and 1Meg?
 * Returns
        > N/A
*/
void lcd_print_vals(float measured_res, float ideal_res, bool valid){

	// if the value is out of range, print out of range
		if (!valid){
			set_cursor(7,0);
			message("out of ra");

			set_cursor(7,1);
			message("out of ra");
			return;
		}

	// convert floating-point values to char arrays (strings)
		char meas_res_str[10];  // 9 chars + null terminator
		char ideal_res_str[10];

		char meas_temp[9];
		char ideal_temp[9];

		sprintf(meas_temp, "%.2f", measured_res);
		sprintf(ideal_temp, "%.0f", ideal_res);

		sprintf(meas_res_str, "%-9s", meas_temp);
		sprintf(ideal_res_str, "%-9s", ideal_temp);

	// print measured resistance
		set_cursor(7,0);
		message(meas_res_str);

	// print interpolated ideal resistance
		set_cursor(7,1);
		message(ideal_res_str);

	// Lastly, return
		return;
}
/******************</Function definitions>*****************/