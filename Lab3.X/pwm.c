/* 
 * File:   pwm.c
 * Author: Jesse Wolfel
 *
 * Created on 19 OCT 2015
 */

#include <xc.h>


void initPWM(){
    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1
    OC2CON = 0x0000; // Turn off OC1 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONSET = 0x8000; // Enable OC1
}
