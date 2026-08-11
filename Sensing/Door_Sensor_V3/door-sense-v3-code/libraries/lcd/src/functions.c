/* Additional Functions */

#include "libraries/lcd/functions.h"

/* ------------ Defines / Variables / Data ---------- */
const uint LED_PIN = PICO_DEFAULT_LED_PIN;


void LCD_test(){
    init_lcd(LCD_RS, LCD_EN, LCD_BACKLIGHT, LCD_4, LCD_5, LCD_6, LCD_7, 16, 2);
    backlight(true);
    home();
    clear();
    set_cursor(0,0);
    message("Test Complete!");
    set_cursor(0,1);
    message("Did it work?");
    show_blink(true);
    return;
}