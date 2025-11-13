#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#include "pico/stdlib.h"

#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/i2c.h"

#include "MIL_electrical_protocol_macros.h"
#include "MIL_electrical_protocol_msg.h"

#include "servo-pwm.h"

#include "ssd1306.h"

#include "mil-logo.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/* --------------------------------- LED PIN -------------------------------- */
#define LED_PIN 25  

/* ------------------------------ THRUSTER PINS ----------------------------- */

#define SERVO_PIN 8

/* ----------------------------------- I2C ---------------------------------- */

#define I2C_PORT i2c1
#define SDA_PIN 2
#define SCL_PIN 3
#define BAUD (400 * 1000)

#define ADDR 0x3C

/* -------------------------------------------------------------------------- */
/*                                 GLOBAL VARS                                */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                   STRUCTS                                  */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                 PROTOTYPES                                 */
/* -------------------------------------------------------------------------- */

/* ----------------------------------- I2C ---------------------------------- */

/**
 * @brief 
 * 
 * @param i2c 
 * @param baud_rate 
 * @param sda 
 * @param scl 
 */
void i2c_pin_init(i2c_inst_t *i2c, const uint baud_rate, const uint8_t sda, const uint8_t scl);

static void i2c_scan(i2c_inst_t *port) {
    printf("I2C scan:\n");
    for (int addr = 0x08; addr < 0x78; addr++) {
        uint8_t rxdata;
        int ret = i2c_read_blocking(port, addr, &rxdata, 1, false);
        if (ret >= 0) printf(" - found device at 0x%02X\n", addr);
        sleep_ms(5);
    }
}

/* ---------------------------------- SERVO --------------------------------- */

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

    // ---- On Board LED ----
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    
    // ---- PWM -----
    servo_pwm_init(SERVO_PIN);
    start_servo(SERVO_PIN);

    // ---- I2C -----
    char *loading = "Loading...";
    char *words = "Hello, World!";

    i2c_pin_init(I2C_PORT, BAUD, SDA_PIN, SCL_PIN);
    ssd1306_t disp;
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, ADDR, I2C_PORT);

    // Fake loading bc I hate mechanical team
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 32, 56, 1, loading);
    ssd1306_bmp_show_image(&disp, mil_logo_bmp_data, mil_logo_bmp_size);
    ssd1306_show(&disp);
    sleep_ms(2000);



    while (1) {

        // usb_message_t msg;
        // usb_errcode_t parse_status = parse_message(&msg);
        // // printf("Parse Status: %d\n", parse_status);

        // if(parse_status == SUCCESS) 
        //     read_message(&msg);

        for (int y = 8; y < 56; y++) {
            ssd1306_clear(&disp);
            ssd1306_draw_string(&disp, 8, y, 1, words);
            ssd1306_show(&disp);
            sleep_ms(100);   
        }

        for (int y = 56; y > 8; y--) {
            ssd1306_clear(&disp);
            ssd1306_draw_string(&disp, 8, y, 1, words);
            ssd1306_show(&disp);
            sleep_ms(100);   
        }
        
        tight_loop_contents();
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                                 DEFINITIONS                                */
/* -------------------------------------------------------------------------- */

/* ----------------------------------- I2C ---------------------------------- */
void i2c_pin_init(i2c_inst_t *i2c, const uint baud_rate, const uint8_t sda, const uint8_t scl){
    i2c_init(i2c, baud_rate);

    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);

    gpio_pull_up(sda);
    gpio_pull_up(scl);
}

/* -------------------------------- THRUSTERS ------------------------------- */

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
            uint pmwVal = servo_effort_to_duty(speed);
            // printf("Got %f from msg, converted it to %d\n", speed, pmwVal);
            pwm_set_gpio_level(SERVO_PIN, pmwVal);

            // Return Ack
            send_ACK();

            return SUCCESS;
    
        default:
            return FAILURE;
        }
}
