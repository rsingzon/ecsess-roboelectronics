/* Source File
 * File:   main.c
 * Author: Joshua David Alfaro
 *
 * Created on July 23, 2014, 6:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f88.h>

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

#define _XTAL_FREQ 4000000
#define STATUS_LED PORTBbits.RB4

#define LEFT_IR PORTBbits.RB2
#define RIGHT_IR PORTAbits.RA7

// Left Motor (1 is forward, 2 is backward)
#define H_1A PORTAbits.RA2
#define H_2A PORTAbits.RA3

// Right Motor (4 is forward, 3 is backward)
#define H_3A PORTAbits.RA4
#define H_4A PORTBbits.RB0

// Prototypes
void motorStop();
void motorLeft();
void motorRight();
void motorForward();
void motorBackward();

void init();
int onRamp(int port);
//int findDistance();

// Main Program
void main() {

    // Initialization
    init();
    //adcInit(0);   // analog input
    STATUS_LED = 1;
    H_2A = 0;
    H_4A = 0;

    while(1)
    {
        // Testing IR
        if(LEFT_IR == 1)
        {
            H_1A = 1;
        }
        else
        {
            H_1A = 0;
        }

        if(RIGHT_IR == 1)
        {
            H_3A = 1;
        }
        else
        {
                H_3A = 0;
        }
    }
}

// Function for Initialising IOs
void init ()
{
    OSCCON = 0b01101110;    // set clock

    TRISA = 0b10000000;
    TRISB = 0b00000100;
    ANSEL = 0;
    PORTA = 0;
    PORTB = 0;
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

///Finds the distance in cm
/*int findDistance()
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

}*/

void motorStop()
{
    // Left Motor
    H_1A = 0;
    H_2A = 0;

    // Right Motor
    H_3A = 0;
    H_4A = 0;
}

void motorForward()
{
    //Left motor
    H_1A = 1;
    H_2A = 0;

    //Right motor
    H_3A = 0;
    H_4A = 1;
}

void motorBackward()
{
    //Left motor
    H_1A = 0;
    H_2A = 1;

    //Right motor
    H_3A = 1;
    H_4A = 0;
}

void motorRight()
{
    //Left motor
    H_1A = 1;
    H_2A = 0;

    //Right motor
    H_3A = 1;
    H_4A = 0;
}

void motorLeft()
{
    // Left Motor
    H_1A = 1;
    H_2A = 0;

    // Right Motor
    H_3A = 0;
    H_4A = 1;
}