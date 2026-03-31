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

/******************</Function definitions>*****************/
