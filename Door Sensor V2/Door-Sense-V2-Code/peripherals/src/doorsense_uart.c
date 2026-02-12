
/******************<Dependencies>*****************/
#include "peripherals/doorsense_uart.h"
/******************</Dependencies>*****************/


/******************<Public Functions>*****************/

/*******init_doorsense_uart*******
 * Description
        > initializes both UART buses on the Pico 2W
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_doorsense_uart(){

    // First, initialize DFPlayer UART port
        uart_init(UART_ID_DFPLAYER, UART_BAUD_RATE);
        gpio_set_function(DF_UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(DF_UART_RX_PIN, GPIO_FUNC_UART);

    // Second, initialize spare UART port
        uart_init(UART_ID_SPARE, UART_BAUD_RATE);
        gpio_set_function(SPARE_UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(SPARE_UART_RX_PIN, GPIO_FUNC_UART);

    // Lastly, return to main program
        return;
}


/*******uart_send*******
 * Description
        > sends a byte string via UART
 * Arguments
        > uart_inst_t* uart - UART instance to use
		> uint8_t *data - pointer to data to send
		> size_t length - length of data to send
 * Returns
        > N/A
*/
void uart_send(uart_inst_t* uart, uint8_t *data, size_t length) {
	uart_write_blocking(uart, data, length);
}



/*******uart_receive*******
 * Description
        > receives a byte string via UART
 * Arguments
        > uart_inst_t* uart - UART instance to use
		> uint8_t *data - pointer to data to receive
		> size_t length - length of data to receive
 * Returns
        > N/A
*/
void uart_receive(uart_inst_t* uart, uint8_t *data, size_t length) {
	uart_read_blocking(uart, data, length);
}

/******************</Public Functions>*****************/