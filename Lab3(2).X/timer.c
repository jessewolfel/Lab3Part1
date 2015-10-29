/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "lcd.h"


void initTMR() {
    //Initialize Timer 1 for debounce and LCD delays
    TMR1 = 0;// clear TMR1
    PR1 = 6;// Initialize PR1 to 6 (corresponds to 1us)
    T1CONbits.TCKPS = 0; // Initialize pre-scalar to 1
    T1CONbits.TCS = 0; // Use internal peripheral clock
    IFS0bits.T1IF = 0; //lower interrupt flag
    
    //Initialize Timer 2 for message delay
    TMR2 = 0;
    PR2 = 26041;
    T2CONbits.TCKPS = 7; //Initialize PreScalar to 256
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
   }
void delayUs(unsigned int delay){
    TMR1 = 0; //clear timer 1
    PR1 = 6*delay - 1; // set PR equal to a 1us * delay
    IFS0bits.T1IF = 0; //lower interrupt flag
    T1CONbits.TON =  1;
    while(IFS0bits.T1IF == 0); 
    T1CONbits.TON = 0; //disable timer 1
}

void delaySec() {
    TMR2 = 0;
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.TON = 0;
}