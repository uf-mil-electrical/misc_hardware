#include "servo-pwm.h"

#include "hardware/pwm.h"
#include "pico/stdlib.h"

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
    pwm_config_set_wrap(&cfg, 19999);

    gpio_set_function(pin, GPIO_FUNC_PWM);

    uint8_t slice = pwm_gpio_to_slice_num(pin);
    pwm_init(slice, &cfg, true);
    pwm_set_enabled(slice, true);
}

int map(int x,  int in_min, int in_max, int out_min, int out_max){
    return ((x-in_min)*(out_max-out_min)/ (in_max-in_min) + out_min);
}

uint servo_effort_to_duty(float effort) {
    // Bound it just incase
    if (effort > 1)
        effort = 1;
    if (effort < -1)
        effort = -1;

    // Stopped, prob unnecessry
    if (effort == 0)
        return STOP_VAL;

    // Explicit type casting just to be safe, with 2 decimal point precision
    int effort_int = (int)(effort*100);

    return map(effort_int, -100, 100, MAX_REV_VAL, MAX_FWR_VAL);
}