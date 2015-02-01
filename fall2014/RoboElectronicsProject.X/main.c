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

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

#define _XTAL_FREQ 4000000

/*
 *
 */

void main() {

    initPIC16F88();

    while(1)
    {

    }
    return;
}

