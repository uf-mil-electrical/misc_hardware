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
/******************</Function definitions>*****************/