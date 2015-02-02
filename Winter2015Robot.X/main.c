/* 
 * File:   main.c
 * Author: ddubois
 *
 * Created on February 1, 2015, 8:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <pic16f88.h>
#include "pic16f88init.h"
#include "adc.h"

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

#define _XTAL_FREQ 4000000
#define STATUS_LED PORTBbits.RB4
#define TRUE 1
#define FALSE 0

#define LEFT_IR_SENSOR 0
#define RIGHT_IR_SENSOR 0

#define H_1A PORTAbits.RA2
#define H_2A PORTAbits.RA3
#define H_3A PORTAbits.RA4
#define H_4A PORTBbits.RB0

#define ACCELEROMETER_X 0
#define ACCELEROMETER_Y 1
#define ACCELEROMETER_Z 2

/*Function prototypes*/
void motorStop();
void motorLeft();
void motorRight();
void motorForward();
void motorReverse();

int onRamp(int port);

#define CONVERSION_TO_DEG 57.29577951308233 /**<The scalling factor from radians to degrees*/
#define FORWARD_THRESHOLD 5
#define REVERSE_THRESHOLD 5
float computePitch(int accelerometerX, int accelerometerY, int accelerometerZ);

int checkIfBalanced();
/*
 * 
 */
void main() {
    initPIC16F88();

    STATUS_LED = 1;
    __delay_ms(500); //Required delay before startup

    motorForward();

    while(1){

        if(checkIfBalanced() == TRUE)
        {
            //Stop processing
            while(1){
                __delay_ms(250);
                STATUS_LED = 1;
                __delay_ms(250);
                STATUS_LED = 0;
            }
        }
        
        /*Check if we are still on the ramp*/
        if(!onRamp(LEFT_IR_SENSOR)){
            motorRight();
        }else if(!onRamp(RIGHT_IR_SENSOR))
        {
            motorLeft();
        }
        else{
            motorForward();
        }

        
    }

    return;
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

void motorReverse()
{
    //Left motor
    H_1A = 1;
    H_2A = 0;

    //Right motor
    H_3A = 1;
    H_4A = 0;
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
        motorReverse();
        return FALSE;
    }else{
        motorStop();
        return TRUE;
    }
}