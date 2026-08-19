#ifndef PI_ZERO_H
#define PI_ZERO_H

/******************<Summary>*****************
 * Name: pi_zero.h
 * Purpose:
 *      > Functions for communicating with the Raspberry Pi Zero 2W
 * 		> This is how door-sense-v3 connects to the internet and the MIL
 * 			Discord!
 * 		> When lab changes state (to open or to closed), the Pico will send
 * 			a message to the RP Zero 2W over UART, which then sends the HTTP
 * 			request to the MIL Discord.
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/



/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "pico/stdlib.h"

#include "pico/rand.h"

#include "communication/doorsense_uart.h"
#include "peripherals/pi_zero.h"

#include "pins.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
#define STARTUP_ACK_STRING				"S_ACK\n"	// message to send/expect from RP Zero 2W for startup handshake
#define NORMAL_ACK_STRING				"ACK\n"		// message to expect from the RP Zero 2W after sending lab state updates
#define ACK_TIMEOUT_MS					5000		// how long to wait (in ms) for an ACK before retrying
#define ACK_RETRY_MS					1000		// how long to wait between ACK retries
#define UART_BUF_SIZE					32			// packet size (in bits)
/******************</Defines>*****************/



/******************<Function Declarations>*****************/
void init_pi_zero();
void await_pi_zero_ack();
void send_lab_state(const char* state);
/******************</Function Declarations>*****************/

#endif // PI_ZERO_H