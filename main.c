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
/*
 * 
 */
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
    int distance = 12000/voltage;
    return distance;
}
