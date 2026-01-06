
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

/******************</Public Functions>*****************/