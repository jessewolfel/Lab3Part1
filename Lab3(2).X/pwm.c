/* 
 * File:   pwm.c
 * Author: Jesse Wolfel
 *
 * Created on 19 OCT 2015
 */

#include <xc.h>


void initPWM()
{
    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1 J11 PIN20
    RPC2Rbits.RPC2R = 0b1100; // map OC1 to RC2 J10 PIN19
    RPF1Rbits.RPF1R = 0b1011; // map OC3 to RF1 J11 P8
    RPD3Rbits.RPD3R = 0b1011; // map OC4 to RD3 J11 P18
    
    OC2CON = 0x0000; // Turn off OC2 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006;  // Configure for PWM mode
    OC2CONbits.OCTSEL = 1;  // Oscillator
    OC2CONbits.ON = 1;  // Enable OC2
    
    OC1CON = 0x0000; // Turn off OC1 while doing setup.
    OC1R = 0x0000; // Initialize primary Compare Register
    OC1RS = 0x0800; // Initialize secondary Compare Register
    OC1CON = 0x0006;// Configure for PWM mode
    OC1CONbits.OCTSEL = 1; // Oscillator
    OC1CONbits.ON = 1; // Enable OC1
    
    OC3CON = 0x0000; // Turn off OC3 while doing setup.
    OC3R = 0x0000; // Initialize primary Compare Register
    OC3RS = 0x0800; // Initialize secondary Compare Register
    OC3CON = 0x0006;  // Configure for PWM mode
    OC3CONbits.OCTSEL = 1; // Oscillator
    OC3CONbits.ON = 1; // Enable OC3
    
    OC4CON = 0x0000; // Turn off OC4 while doing setup.
    OC4R = 0x0000; // Initialize primary Compare Register
    OC4RS = 0x0800; // Initialize secondary Compare Register
    OC4CON = 0x0006;// Configure for PWM mode
    OC4CONbits.OCTSEL = 1; // Oscillator
    OC4CONbits.ON = 1; // Enable OC4
}

