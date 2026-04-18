#ifndef LCD_H
#define LCD_H

/******************<Summary>*****************
 * Name: lcd.h
 * Purpose:
 *      > functions for LCD display
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "libraries/lcd/charlcd.h"
#include "libraries/lcd/functions.h"

#include "peripherals/pot_adc.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
#define NUM_COUNTDOWN_BARS				14		// number of bars to display for graphical countdown bar
/******************</Defines>*****************/



/******************<Global variables>*****************/
/******************</Global variables>*****************/



/******************<Function Declarations>*****************/
void doorsense_init_lcd();
void clear_lcd();
void lcd_print(char str[], uint8_t x, uint8_t y);
void print_countdown_duration(uint8_t duration);
void update_lcd_screen(bool lab_state, bool countdown_active, int32_t time_remaining, uint8_t countdown_duration);
/******************</Function Declarations>*****************/

#endif // LCD_H