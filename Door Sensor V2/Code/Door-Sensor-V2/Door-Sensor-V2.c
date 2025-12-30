/*
  __  __ _____ _                                             
 |  \/  |_   _| |                                            
 | \  / | | | | |                                            
 | |\/| | | | | |                                            
 | |  | |_| |_| |____                                        
 |_|__|_|_____|______|       _____                           
 
 |  __ \                    / ____|                          
 | |  | | ___   ___  _ __  | (___   ___ _ __  ___  ___  _ __ 
 | |  | |/ _ \ / _ \| '__|  \___ \ / _ \ '_ \/ __|/ _ \| '__|
 | |__| | (_) | (_) | |     ____) |  __/ | | \__ \ (_) | |   
 |_____/ \___/ \___/|_|    |_____/ \___|_| |_|___/\___/|_|   

 \ \    / /__ \                                              
  \ \  / /   ) |                                             
   \ \/ /   / /                                              
    \  /   / /_                                              
     \/   |____|                                             
                                                             
    Door Sensor Board V2
    Pico 2 W
    Written by Russell MacGregor                     
*/



//*****************<Includes>***************** */
#include <stdio.h>
#include "pico/stdlib.h"

#include "pico/time.h"
#include "hardware/irq.h"

#include "hardware/spi.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"

// My code to include
#include "setup.h"
#include "peripherals/doorsense_gpio.h"
#include "peripherals/doorsense_tof.h"
#include "peripherals/doorsense_i2c.h"
#include "peripherals/doorsense_spi.h"
#include "peripherals/doorsense_uart.h"

//*****************</Includes>*****************

#define TARGET_REGISTER _u(0x0110)
int main() {
    // First, initialize peripherals
        stdio_init_all();
        init_doorsense_i2c();       // init i2c
        init_tof();                 // init ToF sensor
}
