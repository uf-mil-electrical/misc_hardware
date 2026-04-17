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

    return;
}


/*******lcd_print*******
 * Description
        > prints a string to the LCD
 * Arguments
        > char str[]: string to print to LCD
		> uint8_t x: column where first char should be printed
		> uint8_t y: row where first char should be printed
 * Returns
        > N/A
*/
void lcd_print(char str[], uint8_t x, uint8_t y){
	// ensure x,y coords are valid
		if (x > 15 || y > 1){return;}

	// set cursor
		set_cursor(x,y);

	// print message
		message(str);
}


/*******print_countdown_duration*******
 * Description
        > prints how long the countdown will be to update lab state
			once a door state change is detected
		> always prints to row=1, col=8
 * Arguments
        > uint8_t duration: countdown duration
 * Returns
        > N/A
*/
void print_countdown_duration(uint8_t duration){
	// cast uint8_t to an array of chars
		char buf[3];
		snprintf(buf, sizeof(buf), "%2u", duration);
	
	// print value to LCD
		lcd_print(buf, 8, 1);
}



/*******print_open_screen*******
 * Description
        > displays information that should be shown when the lab is OPEN
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void print_open_screen(){

	// update LCD display
	lcd_print("Lab is OPEN!", 0, 0);
	lcd_print("Cntdwn: ## sec", 0, 1);
}

/******************</Function definitions>*****************/