#ifndef SERVO_PWM_H
#define SERVO_PWM_H

#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include <stdint.h>

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

/* ----------------------------- ESC PWM VALUES ----------------------------- */
#define PWM_MAX_VAL 1900 // us, max forward pwm value in microseconds
#define PWM_MIN_VAL 1100 // us, max reverse pwm value in microseconds
#define PWM_MID_VAL 1500 // us, nuetral/starting pwm value in microseconds

#define ANGLE_MAX_VAL 180       // unit: deg | Servo Max Angle Value
#define ANGLE_MIN_VAL 0         // unit: deg | Servo Minimum Angle Value
#define ANGLE_MID_VAL 90        // unit: deg | Servo Angle at Neutral PWM

#define PERIOD_US 20000 // us, period of servo PWM
#define FREQUENCY 50 // Hz, frequency of servo PWM

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
 * @brief Get the pwm level of the gpio, bc there is no official function idk why
 * 
 * @param pin GPIO pin to get PWM level from
 * @return uint16_t level of pwm
 */
uint16_t get_pwm_level(const uint8_t pin );


/* --------------------------------- EFFORT --------------------------------- */

/**
 * @brief Function that converts effort value [-1,1] to a PWM duty value
 * 
 * @param effort [float] A value between [-1,1] to convert to servo duty values
 * @return uint frequency value for the servo
 */
uint servo_effort_to_duty(float effort);

/**
 * @brief Get the servo effort [-1,1] from PWM duty value
 * 
 * @param duty 
 * @return float 
 */
float servo_effort_from_duty(uint duty);


/* --------------------------------- ANGLES --------------------------------- */

/**
 * @brief Converts angle into duty pulse width according to the DB
 * 
 * @param angle angle to convert to servo duty values
 * @return uint frequency value for the servo
 */
uint16_t servo_duty_from_angle(const int angle);

/**
 * @brief Converts duty pulse width into converts it to an angle according to the DB
 * 
 * @param pulse_width pulse width of the servo
 * @return int16_t  angle it corresponds to 
 */
int16_t servo_angle_from_duty(uint pulse_width);

/**
 * @brief Fucntion that moves pwm from current angle to a new angle incrementally
 * 
 * @param pin GPIO pin to write to 
 * @param final_angle final angle you want to move to 
 * @param increment ABSOLUTE Value of how much you want to increment the angle
 * @param delay_ms how many ms to delay per increment
 */
void increment_servo_angle(const uint8_t pin, const int final_angle, const uint increment, const uint delay_ms);

#endif //SERVO_PWM_H