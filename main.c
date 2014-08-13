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
#include "pic16f88Init.h"
#include "adc.h"

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

#define _XTAL_FREQ 4000000
#define LED PORTBbits.RB4
#define IR_LED PORTBbits.RB3
#define PHOTO_DIODE PORTBbits.RB2
#define IR_TRANSMITTER PORTBbits.RB1

#define H_1A PORTAbits.RA2
#define H_2A PORTAbits.RA3
#define H_3A PORTAbits.RA4
#define H_4A PORTBbits.RB0
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
    IR_LED = 1;
    while(1)
    {
        //motorLeft();
        transmitPattern();
        if(onRamp(PHOTO_DIODE))
        {
            LED = 1;
            //do something
        }
        else
        {
            LED = 0;
            //do something else
        }
        
        int distance = findDistance();

        int time = distance*50;

    }
    return;
}

int onRamp(int port)
{
    if(port)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int findDistance()
{
    int adcValue = adcRead();
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
    H_1A = 1;
    H_2A  = 0;

    H_3A = 0;
    H_4A = 1;
    return;
}

void motorLeft()
{
    H_1A = 0;
    H_2A = 1;

    H_3A = 1;
    H_4A = 0;

    return;
}

void transmitPattern()
{
    transmitBit(1);
    transmitBit(1);

    transmitBit(0);
    transmitBit(1);
    transmitBit(0);
    transmitBit(1);
    transmitBit(1);
    transmitBit(0);
    transmitBit(1);
    transmitBit(0);

    transmitBit(0);
    transmitBit(0);
}

void transmitBit(int bitValue)
{
    IR_TRANSMITTER = bitValue;
    __delay_us(250);
    return;
}