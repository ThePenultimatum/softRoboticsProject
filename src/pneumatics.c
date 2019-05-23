#include "pneumatics.h"

int getValveState() {
	int oneAndTwo = ((LATBbits.LATB1 && LATBbits.LATB2) == VCLOSED); //VALVE1POWER && VALVE2POWER;
	int zeroAndThree = ((LATBbits.LATB0 && LATBbits.LATB3) == VCLOSED); //VALVE0POWER && VALVE3POWER;
	if (oneAndTwo && zeroAndThree) { //VALVE0POWER && VALVE1POWER && VALVE2POWER && VALVE3POWER) {
		return VALVESCLOSED;
	} else if (!(oneAndTwo || zeroAndThree)) {
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
	if (!(LATBbits.LATB5)) {//PUMP0POWER) {
		return PUMPON;
	} else {
		return PUMPOFF;
	}
	//else {
	//	return UNKNOWNPUMPSTATE;
	//}
}

void allPowerOff() {
	/*PUMP0POWER = 0;
	VALVE0POWER = 0;
	VALVE1POWER = 0;
	VALVE2POWER = 0;
	VALVE3POWER = 0;*/
	LATBbits.LATB0 = VOPEN;
	LATBbits.LATB1 = VOPEN;
	LATBbits.LATB2 = VOPEN;
	LATBbits.LATB3 = VOPEN;
	LATBbits.LATB5 = VOPEN;
}

void pumpToState(unsigned int pump, unsigned int state) {
	switch(pump){
		case PUMP0 :
		    //pump = state;
		    LATBbits.LATB5 = state;
		    break;
		default :
		    break;
	}
	return;
}

void valveToState(unsigned int valve, unsigned int state) {
	switch(valve){
		case VALVE0 :
		    //VALVE0POWER = state;
		    LATBbits.LATB0 = state;
		    break;
		case VALVE1 :
		    //VALVE1POWER = state;
		    LATBbits.LATB1 = state;
		    break;
		case VALVE2 :
		    //VALVE2POWER = state;
		    LATBbits.LATB2 = state;
		    break;
		case VALVE3 :
		    //VALVE3POWER = state;
		    LATBbits.LATB3 = state;
		    break;
		default :
		    break;
	}
	return;
}

void switchState(int newState) {
	// states are 0, 1, 2, 3
	// states correspond to valve configurations
	// 0 is all valves off, 3 is all valves on
	// 1 is valves 1 and 4 powered to close them and provide vacuum when pump is powered
	// 2 is valves 2 and 3 powered to close them and provide air when pump is powered
	int currValveState = getValveState();
	int currPumpState = getPumpState();

    if (currValveState == newState) {
    	return;
    }

	pumpToState(PUMP0, PUMPOFF);

	switch(currValveState) {
		case VALVESOPEN :
		    if (newState == VALVESVACUUMOPEN) {
		    	valveToState(VALVE3, VCLOSED);
		    	valveToState(VALVE0, VCLOSED);
		    } else if (newState == VALVESAIROPEN) {
		    	valveToState(VALVE1, VCLOSED);
		    	valveToState(VALVE2, VCLOSED);
		    } else if (newState == VALVESCLOSED) {
		    	valveToState(VALVE3, VCLOSED);
		    	valveToState(VALVE1, VCLOSED);
		    	valveToState(VALVE0, VCLOSED);
		    	valveToState(VALVE2, VCLOSED);
		    } else {
		    	return;
		    }
		    break;
		case VALVESVACUUMOPEN :
		    if (newState == VALVESOPEN) {
		    	valveToState(VALVE0, VOPEN);
		    	valveToState(VALVE3, VOPEN);
		    } else if (newState == VALVESAIROPEN) {
		    	valveToState(VALVE1, VCLOSED);
		    	valveToState(VALVE2, VCLOSED);
		    	valveToState(VALVE3, VOPEN);
		    	valveToState(VALVE0, VOPEN);
		    } else if (newState == VALVESCLOSED) {
		    	valveToState(VALVE1, VCLOSED);
		    	valveToState(VALVE2, VCLOSED);
		    } else {
		    	return;
		    }
		    break;
		case VALVESAIROPEN :
		    if (newState == VALVESOPEN) {
		    	valveToState(VALVE2, VOPEN);
		    	valveToState(VALVE1, VOPEN);
		    } else if (newState == VALVESVACUUMOPEN) {
		    	valveToState(VALVE3, VCLOSED);
		    	valveToState(VALVE0, VCLOSED);
		    	valveToState(VALVE2, VOPEN);
		    	valveToState(VALVE1, VOPEN);
		    } else if (newState == VALVESCLOSED) {
		    	valveToState(VALVE3, VCLOSED);
		    	valveToState(VALVE0, VCLOSED);
		    } else {
		    	return;
		    }
		    break;
		case VALVESCLOSED :
		    if (newState == VALVESOPEN) {
		    	valveToState(VALVE2, VOPEN);
		    	valveToState(VALVE0, VOPEN);
		    	valveToState(VALVE1, VOPEN);
		    	valveToState(VALVE3, VOPEN);
		    } else if (newState == VALVESVACUUMOPEN) {
		    	valveToState(VALVE2, VOPEN);
		    	valveToState(VALVE1, VOPEN);
		    } else if (newState == VALVESAIROPEN) {
		    	valveToState(VALVE0, VOPEN);
		    	valveToState(VALVE3, VOPEN);
		    } else {
		    	return;
		    }
		    break;
		default :
		    break;
	}
	return;
}