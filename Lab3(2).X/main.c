#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "config.h"
#include "lcd.h"
#include "adc.h"

volatile unsigned int analogVal = 0;

void getAnalogVoltage (unsigned int val)
{
    unsigned char F1;
    unsigned char F10;
    unsigned char S1;
    unsigned char S10;
    unsigned char analogVoltage[5];
    
    
    

    
    //Set the 1's term
    F1 = val % 1;
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
    /*
    F1 = '1';
    F10 = '0';
    S1 = '2';
    S10 = '3';
    */
    
    
    analogVoltage[0] = F1;
    analogVoltage[1] = F10;
    analogVoltage[2] = S1;
    analogVoltage[3] = S10;
    analogVoltage[4] = '\0';
    
    printStringLCD(analogVoltage);
    //printStringLCD("1234");
}

int main (void) {
    // SYSTEMConfigPerformance(40000000);
    initTMR();
    initLCD();
    initADC();
    
    int i;
    while(1) {
        if (IFS0bits.AD1IF == 1)
        {
            analogVal = ADC1BUF0;
            IFS0bits.AD1IF = 0;
            getAnalogVoltage(analogVal);
        }
        //moveCursorLCD(1,1);
        //printCharLCD('c');
        //getAnalogVoltage(analogVal);
        
    }
}