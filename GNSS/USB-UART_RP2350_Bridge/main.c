
/******************<Summary>*****************
 * Project: USB-UART Bridge
 * Purpose:
 *      > Allows data to be sent from a laptop to a UART-only device
 *          using the RP2350 as an intermediary USB-UART bridge
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


//**********<Dependencies>**********//
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
//**********</Dependencies>**********//


//**********<Hardware Definitions>**********//
#define UART_PORT           uart0
#define UART_TX_PIN         0
#define UART_RX_PIN         1
#define UART_BAUDRATE       9600
//**********</Hardware Definitions>**********//


//**********<Initialization Functions>**********//
static void init_uart_bridge(void){

    // init UART peripheral & pins
        uart_init(UART_PORT, UART_BAUDRATE);
        gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // disable flow control (CTS/RTS)
        uart_set_hw_flow(UART_PORT, false, false);

    // send raw bytes, do not use SDK's line-buffered chars
        uart_set_fifo_enabled(UART_PORT, true);
}
//**********</Initialization Functions>**********//


//**********<Main>**********//
int main()
{
    stdio_init_all();

    // init bridge
        init_uart_bridge();

    // disable CRLF translation in both directions
        stdio_set_translate_crlf(&stdio_usb, false);

    // main program loop
        bool success = false;
        while (true) {
            // USB TX to UART RX
                int ch = getchar_timeout_us(0);
                while (ch != PICO_ERROR_TIMEOUT){
                    uart_putc_raw(UART_PORT, (char)ch);
                    success = true;
                    ch = getchar_timeout_us(0);
                }

            // UART TX to USB RX
                while(uart_is_readable(UART_PORT)){
                    char c = uart_getc(UART_PORT);
                    putchar_raw(c);
                    success = true;
                }

            // clear completed transmissions
                if (success){stdio_flush();}
                else{
                    sleep_us(100);
                }
        }
}
//**********</Main>**********//