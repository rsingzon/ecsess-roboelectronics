/* Source File
 * File:   main.c
 * Author: Dirk, Joshua
 * Source File
 *
 * Created on August 16, 2014
 */



#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f88.h>

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

#define _XTAL_FREQ 4000000
#define TIM2_PRESCALE 16 /**<Sets the Timer 2 prescale value, only 1, 4, and 16 are valid values*/

#define SWITCH_1 PORTBbits.RB2
#define SWITCH_2 PORTBbits.RB1

#define MOTOR_PWM PORTBbits.RB3

#define H1_A PORTAbits.RA2
#define H2_A PORTAbits.RA3

#define IR_RECEIVER PORTBbits.RB0

void init();
int openPWM(unsigned int);
void closePWM();
int setDCPWM(unsigned int);
int readReciever(unsigned int port);
void openGate();
//Global values
int values[8];
int expectedValues[8] = {0,1,0,1,0,1,0,1};


int main() {
    init();
    openPWM(255);
    OPTION_REG = 0;
    int foundPattern = 0;
    while(1) {
        /*if(readReciever(IR_RECEIVER));
        {
            for(int i = 0; i < 8; i++)
            {
                if(values[i] != expectedValues[i])
                {
                    foundPattern = 0;
                    break;
                }
                else
                {
                    foundPattern = 1;
                }
            }
        }
        if(foundPattern)
        {
            openGate();
        }*/
	
        openGate();




    }
    return (EXIT_SUCCESS);
}



/*
 * Initialisation Code
 *
 */
void init()
{
    OSCCON = 0b01101110;
    TRISA = 0b11110011;
    TRISB = 0b00000111;
    ANSEL = 0;
    PORTA = 0;
    PORTB = 0;
    OPTION_REG = 0;
}

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
        CCPR1L = 0x80; //PWM Duty Cycle MSBs
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

int readReciever(unsigned int port)
{
    int value1 = port;
    __delay_us(250);
    int value2 = port;
    if(value1 ==1 && value2 == 1)
    {
        for(int i = 0; i < 8; i++)
        {
            values[i] = port;
        }
        return 1;
    }
    else
    {
        return 0;
    }
    
}

void openGate()
{
    //Turn motor in the open direction
    H1_A = 1;
    H2_A = 0;

    //check that open switch isn't pressed
    while(!SWITCH_1);
    //turn off motor
    H1_A = 0;
    H2_A = 0;

    //Wait before closing gate
    for(int i = 0; i < 10; i++)
    {
        __delay_ms(1000);
    }

    //Turn motor in the close direction
    H1_A = 0;
    H2_A = 1;

    //Check that the close switch isn't pressed
    while(!SWITCH_2);
    //turn off motor
    H1_A = 0;
    H2_A = 0;

    return;
}
