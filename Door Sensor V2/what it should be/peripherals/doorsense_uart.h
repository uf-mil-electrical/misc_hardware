#ifndef DOORSENSE_UART_H
#define DOORSENSE_UART_H

/******************<Summary>*****************
 * Name: doorsense_UART.h
 * Purpose:
 *      > Functions for UART communication
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/uart.h"

#include "setup.h"
/******************</Dependencies>*****************/


/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Functions>*****************/
void init_doorsense_uart();
/******************</Functions>*****************/

#endif // DOORSENSE_UART_H