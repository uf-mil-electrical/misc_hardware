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

#include "communication/doorsense_uart.h"
#include "libraries/dfplayer/dfplayer.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/



/******************<Global variables>*****************/
/******************</Global variables>*****************/



/******************<Function Declarations>*****************/
void init_dfplayer();
void play_track(uint8_t track);
/******************</Function Declarations>*****************/

#endif // DOORSENSE_UART_H