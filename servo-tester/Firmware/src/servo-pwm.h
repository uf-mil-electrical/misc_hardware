#ifndef SERVO_PWM_H
#define SERVO_PWM_H

#include "stdint.h"
#include "pico/stdlib.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/* ----------------------------- ESC PWM VALUES ----------------------------- */
#define MAX_FWR_VAL 1900 // us, max forward pwm value in microseconds
#define MAX_REV_VAL 1100 // us, max reverse pwm value in microseconds
#define STOP_VAL    1500 // us, nuetral/starting pwm value in microseconds

/* -------------------------------------------------------------------------- */
/*                                 PROTOTYPES                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initializes PWM for the input pin to be 50 Hz with 1us resolution
 * 
 * @param pin (const int) Pin number (typically 1-30, check with what your 2040 board allows)
 */
void servo_pwm_init(const int pin);

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
 * @brief Function that converts effort value [-1,1] to a PWM duty value
 * 
 * @param effort [float] A value between [-1,1] to convert to servo duty values
 * @return uint frequency value for the servo
 */
uint servo_effort_to_duty(float effort);


#endif //SERVO_PWM_H