#ifndef DOORSENSE_DFPLAYER_H
#define DOORSENSE_DFPLAYER_H

/******************<Summary>*****************
 * Name: doorsense_dfplayer.h
 * Purpose:
 *      > Functions for using the DFPlayer Mini MP3 module
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "pico/stdlib.h"

#include "peripherals/doorsense_uart.h"
#include "setup.h"
/******************</Dependencies>*****************/


/******************<Defines>*****************/
// Dictionary equivalent for sources
#define SOURCE_SDCARD 		0x02
#define SOURCE_USB 			0x01
#define SOURCE_AUX 			0x04
#define SOURCE_SLEEP 		0x05
#define SOURCE_FLASH 		0x03

// MP3 Files
#define BILL_NYE_TRACK 		1	// debug test track
#define MIL_OPEN_TRACK 		2 	// normal lab open announcement	
#define MIL_CLOSE_TRACK 	3	// normal lab close announcement
/******************</Defines>*****************/


/******************<Functions>*****************/
void dfplayer_init(uart_inst_t *uart, uint32_t sleep_time_ms, bool debug);
bool send_bytes(uint8_t *byte_string, size_t length, uint8_t *response);
bool read_reply(uint8_t *response);
uint16_t calc_checksum(uint8_t *data, size_t length);
bool send_command(uint8_t command, uint16_t value, uint8_t feedback, uint8_t *response);
bool reset(void);
int query_num_files(const char *source);
int get_volume(void);
bool set_volume(uint8_t volume);
bool volume_up(void);
bool volume_down(void);
bool select_source(const char *source);
bool stop(void);
bool play(uint16_t track_number);
bool play_next(void);
bool play_previous(void);
bool play_loop(uint16_t track_num);
bool pause(void);
bool start(void);
int get_status(void);
/******************</Functions>*****************/

#endif // DOORSENSE_DFPLAYER_H