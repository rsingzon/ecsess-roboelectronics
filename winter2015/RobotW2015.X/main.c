/* Source File
 * File:   main.c
 * Author: Joshua David Alfaro
 *
 * Created on July 23, 2014, 6:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <pic16f88.h>
#include "../adc.h"

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

#define TRUE 1
#define FALSE 0

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

#define ACCELEROMETER_X 0
#define ACCELEROMETER_Y 1
#define ACCELEROMETER_Z 2

#define CONVERSION_TO_DEG 57.29577951308233 /**<The scalling factor from radians to degrees*/
#define FORWARD_THRESHOLD 5
#define REVERSE_THRESHOLD 5

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
   /*
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
    */

    adcRead();
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

float computePitch(int xValue, int yValue, int zValue){
    float pitch = 0;

    pitch = xValue*xValue + zValue*zValue; //sqaure denominator
    pitch = sqrt(pitch); //Square root denominator
    pitch = yValue / pitch; //Divide by numerator
    pitch = atan(pitch); //Take arctan

    pitch = (float)(pitch * CONVERSION_TO_DEG);
    return pitch;
}

int checkIfBalanced(){

    int xValue, yValue, zValue;
    float angle;
    //Read the X axis
    adcInit(ACCELEROMETER_X);
    xValue = adcRead();

    //Read the Y axis
    adcInit(ACCELEROMETER_Y);
    yValue = adcRead();

    //Read the Z axis
    adcInit(ACCELEROMETER_Z);
    zValue = adcRead();

    angle = computePitch(xValue, yValue, zValue);

    //check what the angle is and if we need to go forward or backward
    if(angle > FORWARD_THRESHOLD){
        motorForward();
        return FALSE;
    }else if(angle < REVERSE_THRESHOLD){
        motorBackward();
        return FALSE;
    }else{
        motorStop();
        return TRUE;
    }
}