/** 
 * ---------------------------------------------------------------+ 
 *  LCD Driver Port for Rasp Pi Pico 
 * ---------------------------------------------------------------+ 
 *              Raspberry Pi Pico RP2040 Port by:
 *              Shane Aspenwall on 2/8/2024
 * 
 *              Original Code from micropython-charlcd library
 * ---------------------------------------------------------------+
 *              For 16x2 Character LCDs:
 *                  -- 4-bit data + 3 control wires (BL, RS, E)
 *                  -- a 2N7000 transistor can be used with a gpio tied
 *                     to the gate to control the backlight safely
 *                     [3.3V --- Source, GPIO --- Gate, K+ --- Drain]
 * 
 */
#ifndef __CHARLCD_H__
#define __CHARLCD_H__

#include <stdio.h>
#include <stdint.h>

// LCD Modes
#define LCD_CHR 1  // Character mode
#define LCD_CMD 0  // Command mode

// LCD RAM address for display lines
#define LCD_LINES1 0x80
#define LCD_LINES2 0xC0
#define LCD_LINES3 0x94
#define LCD_LINES4 0xD4
#define LCD_ROW_OFFSETS1 0x00
#define LCD_ROW_OFFSETS2 0x40
#define LCD_ROW_OFFSETS3 0x14
#define LCD_ROW_OFFSETS4 0x54

// Command constants
#define LCD_CLEAR 0x01
#define LCD_CURSORSHIFT 0x10
#define LCD_DISPLAYCONTROL 0x08
#define LCD_HOME 0x02
#define LCD_SETDDRAMADDR 0x80
#define LCD_SETCGRAMADDR 0x40

// Control flags
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// Move flags
#define LCD_DISPLAYMOVE 0x08
#define LCD_MOVELEFT 0x00
#define LCD_MOVERIGHT 0x04

// Timing constants
#define E_PULSE 500 //0.0005 seconds, which is 500us
#define E_DELAY 500 //0.0005 seconds which is 500us
#define HOMEDELAY 50 //0.05 seconds, which is 50ms

// include libraries
#include <stdio.h>
#include <string.h>
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pico/time.h"

void init_lcd(uint8_t regsel, uint8_t enable, uint8_t backl, uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7, uint8_t col, uint8_t row);
void clear(void);
void create_char(uint8_t location, uint8_t pattern[]);
void backlight(bool enable);
void enable(bool enable);
void home(void);
void lcd_byte(uint8_t bits, uint8_t mode);
void message(char message[]);
void move_left(void);
void move_right(void);
void set_cursor(uint8_t x, uint8_t y);
void set_line(uint8_t num);
void show_blink(bool show);
void show_underline(bool show);

#endif