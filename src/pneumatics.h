#ifndef PNEUMATICS__H__
#define PNEUMATICS__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

#define PUMP0POWER LATDbits.LATD2
#define VALVE0POWER LATBbits.LATB3
#define VALVE1POWER LATBbits.LATB5
#define VALVE2POWER LATBbits.LATB4
#define VALVE3POWER LATBbits.LATB8

#define PUMP1POWER LATDbits.LATD3
#define VALVE4POWER LATBbits.LATB7
#define VALVE5POWER LATBbits.LATB11
#define VALVE6POWER LATBbits.LATB6
#define VALVE7POWER LATBbits.LATB10

#define PUMP2POWER LATDbits.LATD4
#define VALVE8POWER LATBbits.LATB2
#define VALVE9POWER LATDbits.LATD1
#define VALVE10POWER LATBbits.LATB9
#define VALVE11POWER LATBbits.LATB14

#define PUMP3POWER LATDbits.LATD5
#define VALVE12POWER LATBbits.LATB13
#define VALVE13POWER LATDbits.LATD8
#define VALVE14POWER LATBbits.LATB12
#define VALVE15POWER LATDbits.LATD9

#define PUMP4POWER LATDbits.LATD6
#define VALVE16POWER LATDbits.LATD0
#define VALVE17POWER LATBbits.LATB0
#define VALVE18POWER LATBbits.LATB1
#define VALVE19POWER LATDbits.LATD7

#define VALVESET0 0
#define PUMP0  50
#define VALVE0  0
#define VALVE1  1
#define VALVE2  2
#define VALVE3  3

#define VALVESET1 1
#define PUMP1  51
#define VALVE4  4
#define VALVE5  5
#define VALVE6  6
#define VALVE7  7

#define VALVESET2 2
#define PUMP2  52
#define VALVE8  8
#define VALVE9  9
#define VALVE10 10
#define VALVE11 11

#define VALVESET3 3
#define PUMP3  53
#define VALVE12 12
#define VALVE13 13
#define VALVE14 14
#define VALVE15 15

#define VALVESET4 4
#define PUMP4  54
#define VALVE16 16
#define VALVE17 17
#define VALVE18 18
#define VALVE19 19

#define VCLOSED  1 // 1 is unconnected state because of hex inverter circuit
#define VOPEN  0

#define VALVESOPEN 0
#define VALVESVACUUMOPEN 1
#define VALVESAIROPEN 2
#define VALVESCLOSED 3
#define UNKNOWNVALVESTATE 100

#define PUMPON 0
#define PUMPOFF 1 // 1 is unconnected state because of hex inverter circuit
#define UNKNOWNPUMPSTATE 200


int getValveState(int valveSet);
int getPumpState(int pump);
void switchState(int newState, int valveSet);
void allPowerOff();
void allPowerOffValveset(int valveSet);
void valveToState(unsigned int valve, unsigned int state);
void pumpToState(unsigned int pump, unsigned int state);

#endif
