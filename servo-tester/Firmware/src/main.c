#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#include "pico/stdlib.h"

#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/i2c.h"

#include "MIL_USB2CAN.h"
#include "MIL_electrical_message_system.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/* --------------------------------- LED PIN -------------------------------- */
#define LED_PIN 25  

/* ------------------------------ THRUSTER PINS ----------------------------- */

#define SERVO_PIN 2

/* ----------------------------- ESC PWM VALUES ----------------------------- */

#define MAX_FWR_VAL 2200 // us, max forward pwm value in microseconds
#define MAX_REV_VAL 800 // us, max reverse pwm value in microseconds
#define STOP_VAL    1500 // us, nuetral/starting pwm value in microseconds

/* -------------------------------------------------------------------------- */
/*                                 GLOBAL VARS                                */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                   STRUCTS                                  */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                 PROTOTYPES                                 */
/* -------------------------------------------------------------------------- */

/* -------------------------------- THRUSTER -------------------------------- */

/**
 * @brief Function that initalizes a pin to have PWM (50 Hz)
 * 
 * @param pin 
 */
void servo_init(const uint pin);

/**
 * @brief Function that re-maps a number from one range to another \
 *          Based off arduino map function, which is just y-y1 = m(x-x1)
 * 
 * @param x input value
 * @param in_min minimum value of the input range
 * @param in_max maximum value of the input range
 * @param out_min minimum value of the output range
 * @param out_max maximum value of the output range

 * @return [int] output value based on in and out
 */
int map(int x,  int in_min, int in_max, int out_min, int out_max);

/**
 * @brief 
 * 
 * @param speed float value [-1,1] to convert to servo duty values
 * @return uint frequency value for the servo
 */
uint servo_duty(float speed);

/**
 * @brief Set Pwm of pass pin to 1500 us, typical 0deg position
 * 
 * @param pin 
 */
void start_servo(const uint pin );

/* ----------------------------------- MSG ---------------------------------- */

/**
 * @brief Qunction to read usb packets
 * 
 * @param msg 
 * @return usb_errcode_t 
 */

usb_errcode_t read_message(usb_message_t *msg);

/* -------------------------------------------------------------------------- */
/*                                    MAIN                                    */
/* -------------------------------------------------------------------------- */

int main() {
    stdio_init_all();

    // LED to indicate the board is flashed
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    
    // Intialize pwm pins
    servo_init(SERVO_PIN);
    start_servo(SERVO_PIN);

    while (1) {
        
        usb_message_t msg;
        usb_errcode_t parse_status = parse_message(&msg);
        // printf("Parse Status: %d\n", parse_status);

        if(parse_status == SUCCESS) 
            read_message(&msg);

        tight_loop_contents();
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                                 DEFINITIONS                                */
/* -------------------------------------------------------------------------- */

/* -------------------------------- THRUSTERS ------------------------------- */

void servo_init(const uint pin){

    // Set up a pwm config
    pwm_config cfg = pwm_get_default_config();

    // Set the PWM frequency to 50 Hz
    // The formula for PWM frequency is: f = clock_freq / (divider * (TOP + 1))
    // For a 50 Hz frequency with a 125 MHz base clock, and assuming a TOP value of 
    // 19999 (for a resolution of 1us),
    // the divider should be approximately 125.
    pwm_config_set_clkdiv(&cfg, 125.0f);
    pwm_config_set_wrap(&cfg, 19999); // Set the TOP value for 1us resolution

    gpio_set_function(pin, GPIO_FUNC_PWM);

    uint8_t slice = pwm_gpio_to_slice_num(pin);

    pwm_init(slice, &cfg, true);
    pwm_set_enabled(slice, true);

    return;
}

int map(int x,  int in_min, int in_max, int out_min, int out_max){
    return ((x-in_min)*(out_max-out_min)/ (in_max-in_min) + out_min);
}

uint servo_duty(float speed){
    // Bound it just incase
    if (speed > 1)
        speed = 1;
    if (speed < -1)
        speed = -1;

    // Stopped, prob unnecessry
    if (speed == 0)
        return STOP_VAL;

    // Explicit type casting just to be safe, with 2 decimal point precision
    int speed_int = (int)(speed*100);

    return map(speed_int, -100, 100, MAX_REV_VAL, MAX_FWR_VAL);
}

void start_servo(const uint pin ) {
    pwm_set_gpio_level(pin, STOP_VAL);

    // Sleep for 2 seconds to give the thrusters time to start
    sleep_ms(2000);
    return;
}

/* ----------------------------------- MSG ---------------------------------- */

usb_errcode_t read_message(usb_message_t *msg) {

    if (msg == NULL)
        return FAILURE;

    uint8_t classID = msg->class_id;
    uint8_t subClassID = msg->subclass_id;
    
    float speed;

    bool kill;

    // Check if message is for thrusters
    if (classID != SUB9TK_CLASSID)
        return WRONG_CLASS;

    switch (subClassID) {
        // Thrust Set
        case SUB9TK_SUBID_THR_SETPACK:

            // In order to get the float, we will need to do 
            // memcpy and sizeof instead of doing:
            // speed = msg->payload[1];
            memcpy(&speed, &msg->payload[1], sizeof(float)); 

            // Calculate pmw, set the thruster
            uint pmwVal = servo_duty(speed);
            // printf("Got %f from msg, converted it to %d\n", speed, pmwVal);
            pwm_set_gpio_level(SERVO_PIN, pmwVal);

            // Return Ack
            send_ACK();

            return SUCCESS;
    
        default:
            return FAILURE;
        }
}
