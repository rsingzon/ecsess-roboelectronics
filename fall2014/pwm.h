/* 
 * File:   pwm.h
 * Author: Dirk
 *
 * Created on June 26, 2013, 8:45 PM
 */
#ifndef PWM_H
#define PWM_H

#define TIM2_PRESCALE 1 /**<Sets the Timer 2 prescale value, only 1, 4, and 16 are valid values*/
/**
 * @brief Sets the period of the PWM based on the following formula,
 * PWM Period = (period+1)*4*(1/_XTAL_FREQ)* TIM2_PRESCALE
 * @param period The period set in the TIM2 peripheral that controls the period of the pwm.
 * @warning period must not exceed 255
 * @note The duty cycle is set to 50% by default
 * @retval EXIT_SUCCESS is returned if PWM was activated
 */
int openPWM(unsigned int period);

void closePWM(void);

/**
 * @brief A function that sets the duty cycle of the PWM
 * @param dutyCycle Sets the period of the duty cycle for the PWM
 * @warning dutyCycle is not a percentage, but a period value,
 * and should be computed based on the value of period set in openPWM.
 * @return
 */
int setDCPWM(unsigned int dutyCycle);

#endif