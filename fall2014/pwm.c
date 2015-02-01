/**
 * @file pwm.c A source file for a pwm library
 * @author Dirk Dubois
 * @date June 26, 2013
 */
#include <xc.h>
#include <stdlib.h>
#include "pwm.h"

/**
 * @brief Sets the period of the PWM based on the following formula,
 * PWM Period = (period+1)*4*(1/_XTAL_FREQ)* TIM2_PRESCALE
 * @param period The period set in the TIM2 peripheral that controls the period of the pwm.
 * @warning period must not exceed 255
 * @note The duty cycle is set to 50% by default
 * @retval EXIT_SUCCESS is returned if PWM was activated
 */
int openPWM(unsigned int period)
{
    if(period > 255)
    {
        return EXIT_FAILURE;
    }
    else
    {
        PR2 = period;   //Setup timer 2 period

        //Duty Cycle Register CCPR1L:CCP1X:CCP1Y
        CCPR1L = period/2; //PWM Duty Cycle MSBs
        CCP1X = 0; //PWM LSBSs
        CCP1Y = 0; //PWM LSBs

        TRISBbits.TRISB3 = 0; //Ensure CCP1 is output

        //Set the TIM2 Prescaler based on the define in the pwm.h
        switch(TIM2_PRESCALE)
        {
            case 1: T2CKPS0 = 0; //Set up Timer 2 PreScaler
                    T2CKPS1 = 0;
                    break;
            case 4: T2CKPS0 = 1; //Set up Timer 2 PreScaler
                    T2CKPS1 = 0;
                    break;
            case 16:T2CKPS1 = 1;
                    break;
            default:T2CKPS0 = 0; //Set up Timer 2 PreScaler
                    T2CKPS1 = 0;
                    break;
        }

        TMR2ON = 1; //Enable Timer 2

        CCP1M2 = 1; //Enable PWM
        CCP1M3 = 1;
        return EXIT_SUCCESS;
    }
}

void closePWM(void)
{
    //Disabled PWM
    CCP1M0 = 0;
    CCP1M1 = 0;
    CCP1M2 = 0;
    CCP1M3 = 0;
}
/**
 * @brief A function that sets the duty cycle of the PWM
 * @param dutyCycle Sets the period of the duty cycle for the PWM
 * @warning dutyCycle is not a percentage, but a period value,
 * and should be computed based on the value of period set in openPWM.
 * @return
 */
int setDCPWM(unsigned int dutyCycle)
{
    if(dutyCycle>255)
    {
        return EXIT_FAILURE;
    }
    else
    {
        CCPR1L = dutyCycle;
        return EXIT_SUCCESS;
    }
}