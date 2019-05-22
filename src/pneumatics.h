#ifndef PNEUMATICS__H__
#define PNEUMATICS__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

#define PUMPPOWER LATBbits.LATB0
#define VALVE1POWER LATBbits.LATB1
#define VALVE2POWER LATBbits.LATB2
#define VALVE3POWER LATBbits.LATB3
#define VALVE4POWER LATBbits.LATB4

#define VALVESOPEN 0
#define VALVESVACUUMOPEN 1
#define VALVESAIROPEN 2
#define VALVESCLOSED 3
#define UNKNOWNSTATE 100


int getState();
void switchState();
void allPowerOff();
void valvesToState();

#endif