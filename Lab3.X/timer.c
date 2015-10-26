/*
 * File:   timer.c
 * Author: Jesse Wolfel
 *
 * Created on 19 OCT 2015
 */

#include <xc.h>
#include "timer.h"
#include "interrupt.h"

void initTimer2(){
    TMR2 = 0;
    PR2 = 1023;
    T2CONbits.TCKPS = 0;
    T2CONbits.TCS = 0;
    T2CONbits.ON = 1;
}

//Uses timer 2
void delayUs(unsigned int delay){
    TMR2 = 0;
    PR2 = 5*delay;
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 1;
    disableInterrupts();
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.TON = 0;
    enableInterrupts();
}