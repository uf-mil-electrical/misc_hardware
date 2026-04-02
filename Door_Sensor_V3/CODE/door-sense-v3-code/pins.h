#ifndef PINS_H
#define PINS_H

/******************<Summary>*****************
 * Name: pins.h
 * Purpose:
 *      > Defines pins used for this project
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
/******************</Dependencies>*****************/


/******************<General macros>*****************/
#define GPIO_SET_LOW            0           // for use with gpio_put
#define GPIO_SET_HIGH           1           // for use with gpio_put
/******************</General macros>*****************/


/******************<I2C Setup>*****************/
/******************</I2C Setup>*****************/


/******************<UART Setup>*****************/
#define DFPLAYER_UART_CH		uart0
#define DF_UART_BAUDRATE		9600
#define DF_UART_RX_PIN			13
#define DF_UART_TX_PIN			12


#define PI_ZERO_UART_CH			uart1
#define ZERO_UART_BAUDRATE		115200
#define ZERO_UART_RX_PIN		9
#define ZERO_UART_TX_PIN		8
/******************</UART Setup>*****************/


/******************<LEDs>*****************/
#define LED_R_PIN				5
#define LED_Y_PIN				6
#define LED_G_PIN				4
#define LED_W_PIN				2
/******************</LEDs>*****************/


/******************<Switches & Pots>*****************/
#define PROMPT_SW_PIN			1
#define OVERRIDE_SW_PIN			0
#define COUNTDOWN_ADC_PIN		26

#define COUNTDOWN_ADC_CH		0		// GP26 is ADC Ch 0
/******************</Switches & Pots>*****************/


/******************<LCD>*****************/
#define LCD_RS					15			// high=data, low=instruction code
#define LCD_EN					18			// chip enable
#define LCD_4					19			// data pin 4
#define LCD_5					20			// data pin 5
#define LCD_6					21			// data pin 6
#define LCD_7					22			// data pin 7
#define LCD_BACKLIGHT			3			// backlight anode
/******************</LCD>*****************/

#endif // PINS_H