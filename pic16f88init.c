#include "pic16f88Init.h"
#include <pic16f88.h>
#include "pwm.h"
void initPIC16F88()
{
    OSCCON = 0b01101110;
    TRISA = 0;
    TRISB = 0;
    ANSEL = 0;
    PORTA = 0;
    PORTB = 0;

    openPWM(25); //Sets the pwm to 38kHz
}

