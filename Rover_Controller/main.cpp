#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <RF24.h>

// SPI defines
#define SPI_PORT spi1
#define PIN_MISO 12
#define PIN_CSN   13
#define PIN_SCK  10
#define PIN_MOSI 11
#define PIN_CE 15
#define PIN_IRQ 14

// Radio address
const uint8_t address[] = "ROVER";

// Create RF24 object
RF24 radio(PIN_CE, PIN_CSN);

// Create SPI object for RF24
SPI spi;

int main()
{
    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi.begin(SPI_PORT, PIN_SCK, PIN_MOSI, PIN_MISO);

    // Initialize the radio
    if(!radio.begin(&spi)){
        printf("Radio hardware is not responding!\n");
    }
    else{
        printf("Radio hardware detected!\n");
        
        // configure radio settings
        radio.setChannel(76);
        radio.setDataRate(RF24_1MBPS);
        radio.setCRCLength(RF24_CRC_16);
        radio.setPALevel(RF24_PA_LOW);

        /* // configure as transmitter
        radio.openWritingPipe(address);
        radio.stopListening();

        uint32_t counter = 0;
        while(true){
            bool success = radio.write(&counter, sizeof(counter));

            if (success){
                printf("Sent: %1u\n", counter);
            }
            else{
                printf("Send failed: %1u\n", counter);
            }
            
            ++counter;
            sleep_ms(1000);
        } */

        // configure as reciever
        radio.openReadingPipe(1, address);
        radio.startListening();

        uint32_t counter;

        while(true){
            if(radio.available()){
                radio.read(&counter, sizeof(counter));
                printf("Recieved: %1u\n", counter);
            }
            sleep_ms(10);
        }
    }
    while(true){
        sleep_ms(1000);
    }

}
