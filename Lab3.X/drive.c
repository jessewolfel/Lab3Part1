#include <xc.h>
#include<string.h>
#include "drive.h"
#include "timer.h"

#define OUTPUT 0
#define INPUT 1
#define Button PORTDbits.RD6

typedef enum stateTypeEnum {
    idle1, idle2, forward, backward, idle
} stateType;

volatile stateType state = idle1;

void robotStateMachine(unsigned int val)
{
    
switch (state) {

    case idle1:
        while(Button != 1)
        {
           OC2RS = 0;
           OC4RS = 0;
           OC1RS = 0;
           OC3RS = 0;
        }
        if (Button == 1) {
            state = forward;
            break;
        }
        
    case forward:
        while (Button != 1);
        {
         if(analogVal >= 429 && analogVal <= 604)
            {
                OC2RS = 1023;
                OC4RS = 1023;
                OC1RS = 0;
                OC3RS = 0;
            }
         else if (analogVal == 1023)
         {
             OC4RS = analogVal;
             OC2RS = 0;
             OC1RS = 0;
             OC3RS = 0;
         }
         else if (analogVal == 0)
         {
             OC2RS = 1023;
             OC4RS = 0;
             OC1RS = 0;
             OC3RS = 0;
         }
         else if (analogVal > 614)
         {
             OC4RS = 1023;
             OC2RS = 1023 - analogVal;
             OC1RS = 0;
             OC3RS = 0;
         }
         else if (analogVal < 419)
         {
             OC2RS = 1023;
             OC4RS = analogVal;
             OC1RS = 0;
             OC3RS = 0;
         }
        }
        if (Button == 1) {
            state = idle2;
            break;
        }
        

    case idle2:
        while (Button != 1);
            {
                OC2RS = 0;
                OC4RS = 0;
                OC1RS = 0;
                OC3RS = 0;
            }
        if(Button == 1)
        {
            state = backward;
            break;
        }
       

    case backward:
       while (Button != 1);
        {
         if(analogVal >= 429 && analogVal <= 604)
            {
                OC1RS = 1023;
                OC3RS = 1023;
                OC2RS = 0;
                OC4RS = 0;
            }
         else if (analogVal == 1023)
         {
             OC3RS = analogVal;
             OC1RS = 0;
             OC2RS = 0;
             OC4RS = 0;
         }
         else if (analogVal == 0)
         {
             OC1RS = 1023;
             OC3RS = 0;
             OC2RS = 0;
             OC4RS = 0;
         }
         else if (analogVal > 614)
         {
             OC3RS = 1023;
             OC1RS = 1023 - analogVal;
             OC2RS = 0;
             OC4RS = 0;
         }
         else if (analogVal < 419)
         {
             OC1RS = 1023;
             OC3RS = analogVal;
             OC2RS = 0;
             OC4RS = 0;
         }
        }
        else if (Button == 1) {
            state = idle1;
            break;
        }
        
}
