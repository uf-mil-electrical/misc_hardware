#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#include "pico/stdlib.h"

#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/i2c.h"

#include "servo-pwm.h"

#include "ssd1306.h"

#include "mil-logo.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/* --------------------------------- LED PIN -------------------------------- */
#define LED_PIN 25  

/* ---------------------------------- SERVO --------------------------------- */

#define SERVO_PIN 8

/* ----------------------------------- I2C ---------------------------------- */

#define I2C_PORT i2c1
#define SDA_PIN 2
#define SCL_PIN 3
#define BAUD (400 * 1000)

#define ADDR 0x3C

/* -------------------------------------------------------------------------- */
/*                                 PROTOTYPES                                 */
/* -------------------------------------------------------------------------- */

/* ----------------------------------- I2C ---------------------------------- */

/**
 * @brief Initializes i2c based on passed i2c port, pins, and baud rate
 * 
 * @param i2c 
 * @param baud_rate 
 * @param sda 
 * @param scl 
 */
void i2c_pin_init(i2c_inst_t *i2c, const uint baud_rate, const uint8_t sda, const uint8_t scl);

/* --------------------------------- DRAWING -------------------------------- */

/**
 * @brief Draws pulse on screen
 * 
 * @param disp 
 * @param duty 
 */
void draw_pulse(ssd1306_t *disp, uint duty);

/* ---------------------------------- SERVO --------------------------------- */

void start_servo(const uint pin);

/* --------------------------------- BUTTON --------------------------------- */

void button_init(const uint pin);

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

        uint16_t duty = get_pwm_level(SERVO_PIN);

        draw_pulse(&disp, duty);

        duty = (duty > PWM_MAX_VAL) ? PWM_MIN_VAL : duty + 100;

        pwm_set_gpio_level(SERVO_PIN, duty);

        sleep_ms(1000);
        
        if (duty > PWM_MAX_VAL)
            duty = PWM_MIN_VAL;

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

/* --------------------------------- DRAWING -------------------------------- */

void draw_pulse(ssd1306_t *disp, uint duty) {
    if (!disp) return;
    if (duty > PWM_MAX_VAL) duty = PWM_MAX_VAL;
    if (duty < PWM_MIN_VAL) duty = PWM_MIN_VAL;

    int rising_x = 10;
    int falling_x = map(duty, PWM_MIN_VAL/2, PERIOD_US/2, rising_x, 127);
    int low_y = 40; 
    int high_y = 20;

    ssd1306_clear(disp);

    ssd1306_draw_line(disp, 0, low_y, rising_x, low_y);             // left part of low voltage
    ssd1306_draw_line(disp, rising_x, high_y, rising_x, low_y);     // rising edge (in order to work, you have to draw top to bottom, right to left)
    ssd1306_draw_line(disp, rising_x, high_y, falling_x, high_y);   // high voltage
    ssd1306_draw_line(disp, falling_x, high_y, falling_x, low_y);   // falling edge
    ssd1306_draw_line(disp, falling_x, low_y, 127, low_y);          // right part of low voltage

    char buf[32];
    snprintf(buf, sizeof(buf), "duty: %u us", duty);
    ssd1306_draw_string(disp, 0, 0, 1, buf);

    ssd1306_show(disp);
}


/* ---------------------------------- SERVO --------------------------------- */

void start_servo(const uint pin ) {
    pwm_set_gpio_level(pin, PWM_MID_VAL);

    // Sleep for 2 seconds to give the thrusters time to start
    sleep_ms(2000);
    return;
}

/* --------------------------------- BUTTON --------------------------------- */

void button_init(const uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}
