#ifndef UART_FUNCS_H
#define UART_FUNCS_H

/******************<Summary>*****************
 * Name: uart_funcs.h
 * Purpose:
 *      > Functions for UART communication
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "pico/stdlib.h"

#include "hardware/uart.h"


/******************</Dependencies>*****************/


/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Functions>*****************/
void uart_send(uart_inst_t* uart, uint8_t *data, size_t length);
void uart_receive(uart_inst_t* uart, uint8_t *data, size_t length);
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

#endif // UART_FUNCS_H