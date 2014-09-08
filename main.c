/* Source File
 * File:   main.c
 * Author: Raluca
 * Source File
 * File:   main.c
 * Author: Raluca
 *
 * Created on July 23, 2014, 6:39 PM
 */



#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f88.h>
#include "pic16f88init.h"
#include "adc.h"
#include "pwm.h"

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

#define _XTAL_FREQ 4000000
#define STATUS_LED PORTBbits.RB4

#define LEFT_IR_LED PORTBbits.RB5
#define LEFT_PHOTO_DIODE PORTBbits.RB2
#define RIGHT_IR_LED PORTAbits.RA6
#define RIGHT_PHOTO_DIODE PORTAbits.RA7

//Note, the IR carrier must be on PORTBbits.RB3
#define IR_CARRIER PORTBbits.RB3

#define H_1A PORTAbits.RA2
#define H_2A PORTAbits.RA3
#define H_3A PORTAbits.RA4
#define H_4A PORTBbits.RB0

#define DISTANCE_POWER PORTAbits.RA1
/*
 * 
 */
void motorStop();
void motorLeft();
void motorRight();
void motorForward();

void transmitPattern();
void transmitBit(int bitValue);

int onRamp(int port);
///Finds the distance in cm
int findDistance();
void main() {

    initPIC16F88();
    adcInit(0);
    TRISBbits.TRISB2 = 1;
    TRISAbits.TRISA7 = 1;
    STATUS_LED = 1;
    LEFT_IR_LED = 1;
    RIGHT_IR_LED = 1;
    __delay_ms(500);
    motorForward();
    

    while(1)
    {
        int distance = findDistance();
        if(distance<=15){
            motorStop();
            transmitPattern();
            transmitPattern();
            transmitPattern();
        }

        else if(!onRamp(LEFT_PHOTO_DIODE))
            motorRight();

        else if(!onRamp(RIGHT_PHOTO_DIODE))
            motorLeft();

        else
            motorForward();
    }
    return;
}

int onRamp(int port)
{
    if(port)
    {
        return 0;
    }
    else
    {
        return 1;
    }
} 

int findDistance()
{
    DISTANCE_POWER = 1;
    __delay_ms(50);
    int adcValue = adcRead();
    DISTANCE_POWER = 0;
    int voltage = 20*adcValue;

    if(voltage <= 400)
    {
        return 30;
    }
    else if(voltage >= 3000)
    {
        return 3;
    }
    else
    {
      int distance = 12000/voltage;
      return distance;
    }
    
}

void motorStop()
{
    H_1A = 0;
    H_2A = 0;
    H_3A = 0;
    H_4A = 0;
    return;
}

void motorForward()
{
    //Left motor
    H_1A = 0;
    H_2A = 1;

    //Right motor
    H_3A = 0;
    H_4A = 1;
    return;
}

void motorRight()
{
    H_1A = 0;
    H_2A = 1;

    H_3A = 1;
    H_4A = 0;
    return;
}

void motorLeft()
{
    H_1A = 1;
    H_2A = 0;

    H_3A = 0;
    H_4A = 1;

    return;
}

void transmitPattern()
{
    LEFT_IR_LED = 0;
    RIGHT_IR_LED = 0;
    DISTANCE_POWER = 0;

    transmitBit(1);
    transmitBit(1);

    transmitBit(0);
    transmitBit(1);
    transmitBit(0);
    transmitBit(1);
    transmitBit(0);
    transmitBit(1);
    transmitBit(0);
    transmitBit(1);

    transmitBit(0);
    transmitBit(0);

    LEFT_IR_LED = 1;
    RIGHT_IR_LED = 1;
}

void transmitBit(int bitValue)
{
    CCP1M2 = bitValue; //Enable or disable PWM
    CCP1M3 = bitValue;
    __delay_us(1000); //Data rate
    return;
}
