/******************<Dependencies>*****************/
#include "peripherals/lcd.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
bool old_lab_state = false;			// stores lab state from last time update_lcd() was called, if different, will update LCD, reduces flickering on LCD
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


/*******clear_lcd*******
 * Description
        > clears LCD screen
		> resets cursor to (0,0)
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void clear_lcd(){
	home();
	clear();
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



/*******print_waiting_for_pi*******
 * Description
        > on startup, Pico waits for an ACK from the Pi Zero before beginning
			normal operation
		> this screen is shown to show the user that the Pico is just waiting
			and that the system is starting up normally
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void print_waiting_for_pi(){
	lcd_print("Waiting for Pi", 0, 0);
	lcd_print("Takes 30-90s...", 0, 1);
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



/*******print_countdown_bar*******
 * Description
        > when countdown is running, this function can be called to
			graphically show the time remaining in the countdown on the LCD
 * Arguments
        > int32_t time_remaining_ms: time remaining in countdown in ms
		> uint8_t countdown_duration: total countdown length in s
 * Returns
        > N/A
*/
void print_countdown_bar(int32_t time_remaining_ms, uint8_t countdown_duration){

	// cast countdown_duration to int32_t
		int32_t total_time_ms = (int32_t)countdown_duration * 1000;

	// create char array to store bar
		uint8_t bar_str_len = 3 + NUM_COUNTDOWN_BARS;		// 1 char for '[', 1 char for ']', 1 char for '\0', rest for segments
		char bar_str[bar_str_len];	

	// calculate how many segments should be filled
		int filled = (int)((float)time_remaining_ms / (float)total_time_ms * NUM_COUNTDOWN_BARS + 0.5f);

	// clamp to max num of bar segments
		if (filled < 0) {filled = 0;}
		if (filled > NUM_COUNTDOWN_BARS) {filled = NUM_COUNTDOWN_BARS;}

	// build the bar string
		bar_str[0] = '[';

		for (int i = 0; i < NUM_COUNTDOWN_BARS; i++) {
			bar_str[i + 1] = (i < filled) ? '\xFF' : ' ';
		}

		bar_str[bar_str_len - 2] = ']';
		bar_str[bar_str_len - 1] = '\0';

	// print bar string to LCD
    	lcd_print(bar_str, 0, 1);
}




/*******update_lcd_screen*******
 * Description
        > displays information to the LCD
		> high-level function to be called from the run_doorsense function
 * Arguments
        > bool lab_state: false=lab is closed, true=lab is open
		> bool countdown_active: false=inactive, true=active
		> int32_t time_remaining: remaining countdown time (in ms) when countdown is running
		> uint8_t countdown_duration: duration of countdown (in s)
 * Returns
        > N/A
*/
void update_lcd_screen(bool lab_state, bool countdown_active, int32_t time_remaining, uint8_t countdown_duration){

	// if countdown is not running
		if (!countdown_active){
			lcd_print("Lab is", 0, 0);
			lcd_print(lab_state ? "OPEN     " : "CLOSED   ", 7, 0);
			lcd_print("Cntdwn: ", 0, 1);

			uint8_t duration = 0;
			get_countdown_duration(&duration);
			print_countdown_duration(duration);
		}


	// if countdown is running
		else {
			lcd_print("Cntdwn running!", 0, 0);
			print_countdown_bar(time_remaining, countdown_duration);
		}
}

/******************</Function definitions>*****************/