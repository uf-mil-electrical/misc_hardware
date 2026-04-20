#ifndef DOORSENSE_UART_H
#define DOORSENSE_UART_H

/******************<Summary>*****************
 * Name: doorsense_uart.h
 * Purpose:
 *      > functions for UART communication
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "pico/stdlib.h"

#include "hardware/uart.h"
#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
/******************</Defines>*****************/



/******************<Global variables>*****************/
/******************</Global variables>*****************/



/******************<Function Declarations>*****************/
void doorsense_init_uart(uart_inst_t *uart_bus, int baudrate, uint8_t TX_pin, uint8_t RX_pin);
void doorsense_uart_read_line(uart_inst_t* uart_bus, char* buf, size_t buf_size);
void doorsense_uart_write_line(uart_inst_t* uart_bus, char* data);
/******************</Function Declarations>*****************/

#endif // DOORSENSE_UART_H