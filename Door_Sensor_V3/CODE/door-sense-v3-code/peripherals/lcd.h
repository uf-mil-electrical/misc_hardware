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

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/



/******************<Global variables>*****************/
/******************</Global variables>*****************/



/******************<Function Declarations>*****************/
void doorsense_init_lcd();
void lcd_print(char str[], uint8_t x, uint8_t y);
void print_countdown_duration(uint8_t duration);
void print_open_screen();
/******************</Function Declarations>*****************/

#endif // LCD_H