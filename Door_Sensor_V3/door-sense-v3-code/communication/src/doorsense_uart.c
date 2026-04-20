/******************<Dependencies>*****************/
#include "communication/doorsense_uart.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
/******************</Private variables>*****************/


/******************<Public variables>*****************/
/******************</Public variables>*****************/


/******************<Function definitions>*****************/

/*******doorsense_init_uart*******
 * Description
        > initializes a UART bus for communication
 * Arguments
        > uart_inst_t* uart_bus: uart system to initialize
		> int baudrate: baudrate at which to initialize bus
		> uint8_t TX_pin: gpio pin to use for UART TX
		> uint8_t RX_pin: gpio pin to use for UART RX
 * Returns
        > N/A
*/
void doorsense_init_uart(uart_inst_t* uart_bus, int baudrate, uint8_t TX_pin, uint8_t RX_pin){
	uart_init(uart_bus, baudrate);
	gpio_set_function(TX_pin, GPIO_FUNC_UART);
	gpio_set_function(RX_pin, GPIO_FUNC_UART);
}




/*******doorsense_uart_read_line*******
 * Description
        > reads a string from a UART channel
		> strings being read must end with a newline char ('\n')
		> strings read by this function are terminated with
			a null char ('\0')
 * Arguments
        > uart_inst_t* uart_bus: uart bus from which to read
		> char* buf: buffer in which to store data
		> size_t buf_size: size of buffer including terminating char
 * Returns
        > N/A
*/
void doorsense_uart_read_line(uart_inst_t* uart_bus, char* buf, size_t buf_size){
	// create index to keep track of which char was read from RX FIFO
		size_t read_index = 0;

	// read every available char until buffer is filled
		while (read_index < buf_size - 1){
			// check if data is available in RX FIFO
				if (!uart_is_readable(uart_bus)){break;}

			// read char
				char c = uart_getc(uart_bus);

			// if char is newline, entire string has been read
				if (c == '\n'){break;}

			// add to buf, ignore carriage returns
				if (c != '\r'){buf[read_index] = c;}

			// increment index
				read_index += 1;
		}

	// add null terminator to end of string
		buf[read_index] = '\0';
}



/*******doorsense_uart_write_line*******
 * Description
        > writes a string to a UART channel
		> nonblocking
		> only writes if TX FIFO is not full
 * Arguments
        > uart_inst_t* uart_bus: uart bus to which to read
		> char* data: data to send
 * Returns
        > N/A
*/
void doorsense_uart_write_line(uart_inst_t* uart_bus, char* data){
	// write each char to UART TX FIFO
		while(*data){
			if (uart_is_writable(uart_bus)){
				uart_putc_raw(uart_bus, *data);
				data++;
			}
		}
}
/******************</Function definitions>*****************/
