/* 
 * File:   pwm.c
 * Author: Jesse Wolfel
 *
 * Created on 19 OCT 2015
 */

#include <xc.h>


void initPWM()
{
    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1
    RPD5Rbits.RPD5R = 0b1100; // map OC1 to RD5
    OC2CON = 0x0000; // Turn off OC1 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006;// Configure for PWM mode
    OC2CONbits.OCTSEL = 1; // Oscillator
    OC2CONbits.ON = 1; // Enable OC1
}

