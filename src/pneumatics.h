#ifndef PNEUMATICS__H__
#define PNEUMATICS__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

#define PUMP0POWER LATBbits.LATB5
#define VALVE0POWER LATBbits.LATB0
#define VALVE1POWER LATBbits.LATB1
#define VALVE2POWER LATBbits.LATB2
#define VALVE3POWER LATBbits.LATB3

#define VALVE0  0
#define VALVE1  1
#define VALVE2  2
#define VALVE3  3

#define PUMP0  50
//#define PUMP1 = 51

#define VCLOSED  1
#define VOPEN  0

#define VALVESOPEN 0
#define VALVESVACUUMOPEN 1
#define VALVESAIROPEN 2
#define VALVESCLOSED 3
#define UNKNOWNVALVESTATE 100

#define PUMPON 1
#define PUMPOFF 0
#define UNKNOWNPUMPSTATE 200


int getValveState();
int getPumpState();
void switchState(int newState);
void allPowerOff();
void valveToState(unsigned int valve, unsigned int state);
void pumpToState(unsigned int pump, unsigned int state);

#endif