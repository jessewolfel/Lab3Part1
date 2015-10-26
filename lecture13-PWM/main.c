/* 
 * File:   main.c
 * Author: Jesse Wolfel
 *
 * Created on 19 OCT 2015
 */
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"

volatile unsigned int analogVal = 0;

int main(void){
    SYSTEMConfigPerformance(40000000);
    
    initTimer2();
    initPWM();
    initADC();
    enableInterrupts();
    
    while(1){   
        getAnalogVoltage(analogVal);
    }
    
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    analogVal = ADC1BUF0;
}

// Want to read the voltage from the analog input pin and return it
void getAnalogVoltage (unsigned int val)
{
    unsigned char F1;
    unsigned char F10;
    unsigned char S1;
    unsigned char S10;
    unsigned char analogVoltage[5];
    
    
    analogVoltage[0] = F1;
    analogVoltage[1] = F10;
    analogVoltage[2] = S1;
    analogVoltage[3] = S10;
    analogVoltage[4] = '\0';
    
    //Set the 1's term
    F1 = val % 10;
    //Removes the 1's term and divides by ten
    val = (val - val%10)/10;
    //Set the 10's term
    F10 = val % 10;
    //Removes the 10's term and divides by ten
    val = (val - val%10)/10;
    //Set the 100's term
    S1 = val % 10;
    //Removes the 100's term and divides by ten
    val = (val - val%10)/10;
    //Set the 1000's term
    S10 = val%10;
    printStringLCD(analogVoltage);
}