#ifndef PNEUMATICSLOGIC__H__
#define PNEUMATICSLOGIC__H__

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

// Above are redefinitions of the state macros from the pneumatics.h file. This
// is to provide them for testing without including the files that are used for
// data retrieval from the hardware

int getValveStateLogic(int oneAndTwo, int zeroAndThree);
// here the input, boolean anded integer values for two pairs of valves
// (v1 && v2, and v0 && v3), are cased to return known state identifiers
// depending on those valves
// these are VALVESOPEN, VALVESVACUUMOPEN, VALVESAIROPEN, VALVESCLOSED,
// and UNKNOWNVALVESTATE

#endif