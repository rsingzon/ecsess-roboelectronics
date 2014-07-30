/* Header file
 * File:   pic16f88Init.h
 * Author: Raluca
 *
 * Created on July 23, 2014, 7:04 PM
 */

#ifndef PIC16F88INIT_H
#define	PIC16F88INIT_H

/*
 * @summary A function that inits the pic16f88
 * @retval none
 */
void initPIC16F88();

#endif	/* PIC16F88INIT_H */

//*****************
#include "pic16f88Init.h"
#include <pic16f88.h>
void initPIC16F88()
{
    OSCCON = 0b01101110;
    TRISA = 0;
    TRISB = 0;
    ANSEL = 0;
    PORTA = 0;
    PORTB = 0;
}


