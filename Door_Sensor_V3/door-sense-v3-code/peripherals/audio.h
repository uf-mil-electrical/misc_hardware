#ifndef AUDIO_H
#define AUDIO_H

/******************<Summary>*****************
 * Name: audio.h
 * Purpose:
 *      > functions for DFPlayer communication
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "pico/stdlib.h"

#include "pico/rand.h"

#include "communication/doorsense_uart.h"
#include "libraries/dfplayer/dfplayer.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
#define ARRAY_SIZE(arr) 	(sizeof(arr) / sizeof(arr[0]))			// used to determine the num of elements in an array
/******************</Defines>*****************/



/******************<Function Declarations>*****************/
void init_dfplayer();
void play_track(uint16_t track);
void play_audio_prompt(bool special_prompts_allowed, uint8_t event_type);
/******************</Function Declarations>*****************/

#endif // DOORSENSE_UART_H