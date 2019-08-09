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

int getValveStateLogic(int oneAndTwo, int zeroAndThree);

#endif