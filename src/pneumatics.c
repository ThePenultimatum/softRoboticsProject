#include "pneumatics.h"

int getValveState() {
	int oneAndTwo = VALVE1POWER && VALVE2POWER;
	int zeroAndThree = VALVE0POWER && VALVE3POWER;
	if (oneAndTwo && zeroAndThree) { //VALVE0POWER && VALVE1POWER && VALVE2POWER && VALVE3POWER) {
		return VALVESCLOSED;
	} else if (!(oneAndTwo && zeroAndThree)) {
		return VALVESOPEN;
	} else if (oneAndTwo && (!zeroAndThree)) {
		return VALVESAIROPEN;
	} else if ((!oneAndTwo) && zeroAndThree) {
		return VALVESVACUUMOPEN;
	} else {
		return UNKNOWNVALVESTATE;
	};
}

int getPumpState() {
	if (PUMP0POWER) {
		return PUMP0ON;
	} else {
		return PUMP0OFF;
	}
	//else {
	//	return UNKNOWNPUMPSTATE;
	//}
}

void allPowerOff() {
	PUMPPOWER = 0;
	VALVE1POWER = 0;
	VALVE2POWER = 0;
	VALVE3POWER = 0;
	VALVE4POWER = 0;
}

void pumpToState(unsigned int pump, unsigned int state) {
	switch(pump){
		case PUMP0 :
		    PUMPPOWER = state;
		default :
		    ;
	}	
}

void valveToState(unsigned int valve, unsigned int state) {
	switch(valve){
		case VALVE0 :
		    VALVE0POWER = state;
		case VALVE1 :
		    VALVE1POWER = state;
		case VALVE2 :
		    VALVE2POWER = state;
		case VALVE3 :
		    VALVE3POWER = state;
		default :
		    ;
	}
}

void switchState(int stateval) {
	// states are 0, 1, 2, 3
	// states correspond to valve configurations
	// 0 is all valves off, 3 is all valves on
	// 1 is valves 1 and 4 powered to close them and provide vacuum when pump is powered
	// 2 is valves 2 and 3 powered to close them and provide air when pump is powered
	int currValveState = getValveState();
	int currPumpState = getPumpState();

	pumpToState(PUMP0, PUMPOFF);

	
}