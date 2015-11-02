#ifndef ROBOTSTATEMACHINE_H
#define	ROBOTSTATEMACHINE_H
#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "config.h"
#include "lcd.h"
#include "adc.h"
#include "pwm.h"
void robotStateMachine(unsigned int val);

#endif // ROBOTSTATEMACHINE_H