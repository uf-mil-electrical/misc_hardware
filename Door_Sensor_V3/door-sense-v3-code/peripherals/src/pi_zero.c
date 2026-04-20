/******************<Dependencies>*****************/
#include "peripherals/pi_zero.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
/******************</Private variables>*****************/


/******************<Helper Functions>*****************/
/*******get_current_time*******
 * Description
        > determines time since boot in ms
		> used for waiting between resending messages to Pi Zero
			if no ACK is received
 * Arguments
        > uint32_t* time_ms: time in ms since boot
 * Returns
        > N/A
*/
void get_current_time(uint32_t* time_ms){
	*time_ms = to_ms_since_boot(get_absolute_time());
}

/******************</Helper Functions>*****************/


/******************<Function definitions>*****************/

/*******init_pi_zero*******
 * Description
        > initializes UART bus needed for communicating with the
			Pi Zero 2W connected to this microcontroller
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_pi_zero(){
	// init uart bus for Pi Zero communication
		doorsense_init_uart(PI_ZERO_UART_CH, ZERO_UART_BAUDRATE, ZERO_UART_TX_PIN, ZERO_UART_RX_PIN);
}


/*******await_pi_zero_ack*******
 * Description
        > Wait for ACK from Pi Zero 2W
		> On receiving Pi Zero 2W ACK, Pico returns with its own ACK
		> Should only be used on initial startup
		> This process makes sure that a valid connection exists between
			the Pico 2 and the RP Pi Zero 2W before normal operation begins
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void await_pi_zero_ack(){
	
	// wait for ACK from Pi Zero (blocking)
		printf("Awaiting Pi Zero ACK...\n");

		while(1){
			// create buffer to store UART data
				char buf[UART_BUF_SIZE];

			// read line from UART
				doorsense_uart_read_line(PI_ZERO_UART_CH, buf, UART_BUF_SIZE);

			// parse string, ensure that it is 'S_ACK'
				if (strncmp(buf, "S_ACK", 5) == 0){
					printf("ACK received from Pi Zero, sending ACK back...\n");
					doorsense_uart_write_line(PI_ZERO_UART_CH, STARTUP_ACK_STRING);
					printf("Handshake complete, ready for normal operation\n");
					return;
				}

				else if (strlen(buf) > 0){
					printf("Unexpected message during handshake: %s\n", buf);
				}

			// delay for a bit if still waiting
				sleep_ms(250);
				printf("waiting...\n");
		}
}


/*******send_lab_state*******
 * Description
        > Sends a new lab state to the Pi Zero 2W
		> On receiving this, the Pi Zero 2W will send an HTTP request
			to the Discord Bot and update the lab-maybe-open channel name
		> This should ONLY be called if the lab state has changed!
		> Discord rate-limits channel name changes by the bot so it can
			only be changed twice within a 10-min period - no spamming pls
		> Waits for the Pi Zero 2W to ACK before terminating
 * Arguments
        > const char* state: "OPEN" or "CLOSED"
 * Returns
        > N/A
*/
void send_lab_state(const char* state){
	// create bufs for lab state message and ACK response
		char message[UART_BUF_SIZE];
	
	// format message
		snprintf(message, sizeof(message), "\n%s", state);

	// create vars to store timestamps
		uint32_t start_time = 0;
		uint32_t current_time = 0;

	// send lab state message, wait for ACK from Pi Zero

	while(true){
        printf("Sending lab state: %s\n", state);
        doorsense_uart_write_line(PI_ZERO_UART_CH, message);

        get_current_time(&start_time);

        while(true){
            char buf[UART_BUF_SIZE];
            get_current_time(&current_time);
            doorsense_uart_read_line(PI_ZERO_UART_CH, buf, UART_BUF_SIZE);

            if (strncmp(buf, "ACK", 3) == 0){
                printf("ACK received from Pi Zero\n");
                return;
            }
			/*
            else if (strncmp(buf, "S_ACK", 5) == 0){
                // Pi sent a heartbeat - ignore it and break out to resend
                // the lab state message so the Pi can process it fresh
                printf("Received S_ACK heartbeat during send, resending lab state...\n");
                break;
            }
				*/
            else if (strlen(buf) > 0){
                printf("Unexpected message while waiting for ACK: %s\n", buf);
            }

            sleep_ms(50);

            if (current_time - start_time > ACK_TIMEOUT_MS){
                printf("No ACK received, retrying in %d ms...\n", ACK_RETRY_MS);
                sleep_ms(ACK_RETRY_MS);
                break;
            }
        }
    }
}

/******************</Function definitions>*****************/


/*
while(true){
			// send lab state
			printf("Sending lab state: %s\n", state);
			doorsense_uart_write_line(PI_ZERO_UART_CH, message);

			// wait for ACK with timeout
			get_current_time(&start_time);

			while(true){
				char buf[UART_BUF_SIZE];
				get_current_time(&current_time);
				doorsense_uart_read_line(PI_ZERO_UART_CH, buf, UART_BUF_SIZE);

				if (strncmp(buf, "ACK", 3) == 0){
					printf("ACK received from Pi Zero\n");
					return;
				}
				else if (strncmp(buf, "S_ACK", 5) == 0){
					printf("Received S_ACK from Pi, sending S_ACK back...\n");
					doorsense_uart_write_line(PI_ZERO_UART_CH, STARTUP_ACK_STRING);
					continue;					
				}
				else if (strlen(buf) > 0){
					printf("Unexpected message while waiting for ACK: %s\n", buf);
				}

				sleep_ms(50);

				// if timeout time has been reached
				if (current_time - start_time > ACK_TIMEOUT_MS){
					printf("No ACK received, retrying in %d ms...\n", ACK_RETRY_MS);
					sleep_ms(ACK_RETRY_MS);
					break;
				}
			}
			
		}
*/