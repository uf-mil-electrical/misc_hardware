#include "servo-pwm.h"

#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */

void servo_pwm_init(const int pin) {
    pwm_config cfg = pwm_get_default_config();

    // The ESC on the car needs a PWM signal. Most servos and ESCs
    // run at 50 Hz (20 ms) and need a pulse of around 1.0 - 2.0 ms.

    // The formula for pwm frequency is f = clock_freq / (divider * (TOP + 1))
    // divider is the clock divider. TOP is the count value before overflow.

    // The pico has a clock of about 125 MHz and if we use a divider of 125,
    // we can set top to be 19999 for a resolution of 1us so that the PWM values
    // we need are 1000 (1 ms) and 2000 (2 ms) at 50 Hz.
    pwm_config_set_clkdiv(&cfg, 125.0f);
    pwm_config_set_wrap(&cfg, PERIOD_US-1);

    gpio_set_function(pin, GPIO_FUNC_PWM);

    uint8_t slice = pwm_gpio_to_slice_num(pin);
    pwm_init(slice, &cfg, true);
    pwm_set_enabled(slice, true);
}

int map(int x,  int in_min, int in_max, int out_min, int out_max){
    return ((x-in_min)*(out_max-out_min)/ (in_max-in_min) + out_min);
}

uint16_t get_pwm_level(const uint8_t pin ) {

    uint8_t slice = pwm_gpio_to_slice_num(pin);
    uint8_t channel = pwm_gpio_to_channel(pin);

    // Get the PWM slice and compare value
    if (channel == PWM_CHAN_A) {
        return pwm_hw->slice[slice].cc & PWM_CH0_CC_A_BITS;
    } else {
        return (pwm_hw->slice[slice].cc & PWM_CH0_CC_B_BITS) >> PWM_CH0_CC_B_LSB;
    }
}

/* --------------------------------- EFFORT --------------------------------- */

uint servo_effort_to_duty(float effort) {
    if (effort > 1)
        effort = 1;
    if (effort < -1)
        effort = -1;
    if (effort == 0)
        return PWM_MID_VAL;

    // Explicit type casting just to be safe, with 2 decimal point precision
    int effort_int = (int)(effort*100);

    return map(effort_int, -100, 100, PWM_MIN_VAL, PWM_MAX_VAL);
}


float servo_effort_from_duty(uint duty) {
    if (duty > PWM_MAX_VAL)
        duty = PWM_MAX_VAL;
    if (duty < PWM_MIN_VAL)
        duty = PWM_MIN_VAL;
    if (duty == PWM_MID_VAL)
        return 0;

    int effort_int = map(duty, PWM_MIN_VAL, PWM_MAX_VAL, -100, 100);

    return (float)effort_int / 100.0f;
}


/* ---------------------------------- ANGLE --------------------------------- */

uint16_t servo_duty_from_angle(int angle){
    if (angle > ANGLE_MAX_VAL)
        angle = ANGLE_MAX_VAL;
    if (angle < ANGLE_MIN_VAL)
        angle = ANGLE_MIN_VAL;

    if (angle == ANGLE_MID_VAL)
        return PWM_MID_VAL;

    return map(angle, ANGLE_MIN_VAL, ANGLE_MAX_VAL, PWM_MIN_VAL, PWM_MAX_VAL);
}


int16_t servo_angle_from_duty(uint pulse_width) {
    if (pulse_width > PWM_MAX_VAL)
        pulse_width = PWM_MAX_VAL;
    if (pulse_width < PWM_MIN_VAL)
        pulse_width = PWM_MIN_VAL;

    if (pulse_width == PWM_MID_VAL)
        return ANGLE_MID_VAL;

    return map(pulse_width, PWM_MIN_VAL, PWM_MAX_VAL, ANGLE_MIN_VAL, ANGLE_MAX_VAL);
}


void increment_servo_angle(const uint8_t pin, const int final_angle, const uint increment, const uint delay_ms) {
    int current_angle = servo_angle_from_duty(get_pwm_level(pin));
    int step = (final_angle > current_angle) ? increment : -increment;

    while(abs(final_angle - current_angle) > increment) {
        current_angle += step;
        pwm_set_gpio_level(pin, servo_duty_from_angle(current_angle));
        sleep_ms(delay_ms);
    }

    // case when  the remaining angle difference if it's less than the increment
    pwm_set_gpio_level(pin, servo_duty_from_angle(final_angle));

}