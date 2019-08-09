#ifndef PNEUMATICS__H__
#define PNEUMATICS__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro
#include "pneumaticsLogic.h"

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
// given an input integer representing the valveset as a macro defined above,
// this retrieves data from the registers of the hardware (using 
// getValveStateValues) and returns the state value of the given valveset
// potential states are VALVESOPEN, VALVESCLOSED, VALVESVACUUMOPEN,
// VALVESAIROPEN, and UNKNOWNVALVESTATE
// Usage:
// getValveState(VALVESET0);
// returns:
// VALVESCLOSED

void getValveStateValues(int valveSet, int *oneAndTwo, int *zeroAndThree);
// given an input integer representing the valveset as a macro defined above,
// this retrieves the data from the registers and puts those values into
// memory addressed by pointers input to this function
// usage:
// int *oneAndTwo;
// int *zeroAndThree;
// getValveStateValues(VALVESET0, oneAndTwo, zeroAndThree);
// returns nothing, but places values at memory addressed by the two pointers

int getPumpState(int pump);
// given an input pump identifier, this returns the state of the pump
// as either PUMPON or PUMPOFF
// usage:
// getPumpState(PUMP1);
// returns:
// PUMPOFF

void switchState(int newState, int valveSet);
// given a desired new state for a given valveset, this changes the states
// of each of the four valves and the pump in the valveset to appropriately
// achieve the desired overall valveset state (such as VALVESCLOSED)
// usage:
// switchState(VALVESVACUUMOPEN, VALVESET2);

void allPowerOff();
// this cycles through all the valvesets 0-4 and uses allPowerOffValveset()
// to turn off all power to each valveset. No input or output values

void allPowerOffValveset(int valveSet);
// given an input valveset identifier, this cycles through the valves 0-3
// along with the pump and changes the digital I/O value to turn off power;
// if the power is already off on a valve or pump, nothing changes with that
// valve or pump; no return values
// usage:
// allPowerOffValveset(VALVESET0);

void valveToState(unsigned int valve, unsigned int state);
// given an input valve and an input state, this switches the given
// valve I/O port to the appropriate state value, no return value
// usage:
// pumpToState(VALVE3, VOPEN);

void pumpToState(unsigned int pump, unsigned int state);
// given an input pump and an input state, this switches the given
// pump I/O port to the appropriate state value, no return value
// usage:
// pumpToState(PUMP0, PUMPON);

#endif
