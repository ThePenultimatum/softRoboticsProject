#include "pneumatics.h"

int getValveState(int valveSet) {
	int *oneAndTwo;
	int *zeroAndThree;
	getValveStateValues(valveSet, oneAndTwo, zeroAndThree);

	return getValveStateLogic(*oneAndTwo, *zeroAndThree);
}

void getValveStateValues(int valveSet, int *oneAndTwo, int *zeroAndThree) {
	*oneAndTwo = ((VALVE1POWER && VALVE2POWER) == VCLOSED); //VALVE1POWER && VALVE2POWER;
	*zeroAndThree = ((VALVE0POWER && VALVE3POWER) == VCLOSED); //VALVE0POWER && VALVE3POWER;
	switch(valveSet) {
		case VALVESET0 :
			*oneAndTwo = ((VALVE1POWER && VALVE2POWER) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			*zeroAndThree = ((VALVE0POWER && VALVE3POWER) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		case VALVESET1 :
			*oneAndTwo = ((VALVE5POWER && VALVE6POWER) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			*zeroAndThree = ((VALVE4POWER && VALVE7POWER) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		case VALVESET2 :
			*oneAndTwo = ((VALVE9POWER && VALVE10POWER) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			*zeroAndThree = ((VALVE8POWER && VALVE11POWER) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		case VALVESET3 :
			*oneAndTwo = ((VALVE13POWER && VALVE14POWER) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			*zeroAndThree = ((VALVE12POWER && VALVE15POWER) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		case VALVESET4 :
			*oneAndTwo = ((VALVE17POWER && VALVE18POWER) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			*zeroAndThree = ((VALVE16POWER && VALVE19POWER) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		default :
		    break; //return UNKNOWNVALVESTATE;
	}
	return;
}

int getPumpState(int pump) {
	switch(pump) {
		case PUMP0 :
			if (!(PUMP0POWER)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		case PUMP1 :
			if (!(PUMP1POWER)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		case PUMP2 :
			if (!(PUMP2POWER)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		case PUMP3 :
			if (!(PUMP3POWER)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		case PUMP4 :
			if (!(PUMP4POWER)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		default :
		    return UNKNOWNPUMPSTATE;
	}
	//else {
	//	return UNKNOWNPUMPSTATE;
	//}
}

void allPowerOff() {
	allPowerOffValveset(VALVESET0);
	allPowerOffValveset(VALVESET1);
	allPowerOffValveset(VALVESET2);
	allPowerOffValveset(VALVESET3);
	allPowerOffValveset(VALVESET4);
}

void allPowerOffValveset(int valveSet) {
	switch(valveSet) {
		case VALVESET0 :
			VALVE0POWER = VCLOSED;
			VALVE1POWER = VCLOSED;
			VALVE2POWER = VCLOSED;
			VALVE3POWER = VCLOSED;
			PUMP0POWER = PUMPOFF;
			break;
		case VALVESET1 :
			VALVE4POWER = VCLOSED;
			VALVE5POWER = VCLOSED;
			VALVE6POWER = VCLOSED;
			VALVE7POWER = VCLOSED;
			PUMP1POWER = PUMPOFF;
			break;
		case VALVESET2 :
			VALVE8POWER = VCLOSED;
			VALVE9POWER = VCLOSED;
			VALVE10POWER = VCLOSED;
			VALVE11POWER = VCLOSED;
			PUMP2POWER = PUMPOFF;
			break;
		case VALVESET3 :
			VALVE12POWER = VCLOSED;
			VALVE13POWER = VCLOSED;
			VALVE14POWER = VCLOSED;
			VALVE15POWER = VCLOSED;
			PUMP3POWER = PUMPOFF;
			break;
		case VALVESET4 :
			VALVE16POWER = VCLOSED;
			VALVE17POWER = VCLOSED;
			VALVE18POWER = VCLOSED;
			VALVE19POWER = VCLOSED;
			VALVE16POWER = PUMPOFF;
			break;
		default :
		    break;
	}
}

void pumpToState(unsigned int pump, unsigned int state) {
	switch(pump){
		case PUMP0 :
		    //pump = state;
		    PUMP0POWER = state;
		    break;
		case PUMP1 :
		    //pump = state;
		    PUMP1POWER = state;
		    break;
		case PUMP2 :
		    //pump = state;
		    PUMP2POWER = state;
		    break;
		case PUMP3 :
		    //pump = state;
		    PUMP3POWER = state;
		    break;
		case PUMP4 :
		    //pump = state;
		    PUMP4POWER = state;
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
		    VALVE0POWER = state;
		    break;
		case VALVE1 :
		    //VALVE1POWER = state;
		    VALVE1POWER = state;
		    break;
		case VALVE2 :
		    //VALVE2POWER = state;
		    VALVE2POWER = state;
		    break;
		case VALVE3 :
		    //VALVE3POWER = state;
		    VALVE3POWER = state;
		    break;
		case VALVE4 :
		    //VALVE0POWER = state;
		    VALVE4POWER = state;
		    break;
		case VALVE5 :
		    //VALVE1POWER = state;
		    VALVE5POWER = state;
		    break;
		case VALVE6 :
		    //VALVE2POWER = state;
		    VALVE6POWER = state;
		    break;
		case VALVE7 :
		    //VALVE3POWER = state;
		    VALVE7POWER = state;
		    break;
		case VALVE8 :
		    //VALVE0POWER = state;
		    VALVE8POWER = state;
		    break;
		case VALVE9 :
		    //VALVE1POWER = state;
		    VALVE9POWER = state;
		    break;
		case VALVE10 :
		    //VALVE2POWER = state;
		    VALVE10POWER = state;
		    break;
		case VALVE11 :
		    //VALVE3POWER = state;
		    VALVE11POWER = state;
		    break;
		case VALVE12 :
		    //VALVE0POWER = state;
		    VALVE12POWER = state;
		    break;
		case VALVE13 :
		    //VALVE1POWER = state;
		    VALVE13POWER = state;
		    break;
		case VALVE14 :
		    //VALVE2POWER = state;
		    VALVE14POWER = state;
		    break;
		case VALVE15 :
		    //VALVE3POWER = state;
		    VALVE15POWER = state;
		    break;
		case VALVE16 :
		    //VALVE0POWER = state;
		    VALVE16POWER = state;
		    break;
		case VALVE17 :
		    //VALVE1POWER = state;
		    VALVE17POWER = state;
		    break;
		case VALVE18 :
		    //VALVE2POWER = state;
		    VALVE18POWER = state;
		    break;
		case VALVE19 :
		    //VALVE3POWER = state;
		    VALVE19POWER = state;
		    break;
		default :
		    break;
	}
	return;
}

void switchState(int newState, int valveSet) {
	// states are 0, 1, 2, 3
	// states correspond to valve configurations
	// 0 is all valves off, 3 is all valves on
	// 1 is valves 1 and 4 powered to close them and provide vacuum when pump is powered
	// 2 is valves 2 and 3 powered to close them and provide air when pump is powered
	int currValveState = getValveState(valveSet);
	//int currPumpState = getPumpState(pump);

    if (currValveState == newState) {
    	return;
    }

	//pumpToState(PUMP0, PUMPOFF);

	int valve0 = VALVE0;
	int valve1 = VALVE1;
	int valve2 = VALVE2;
	int valve3 = VALVE3;

	switch(valveSet) {
		case 0 :
			valve0 = VALVE0;
			valve1 = VALVE1;
			valve2 = VALVE2;
			valve3 = VALVE3;
			break;
		case 1 :
			valve0 = VALVE4;
			valve1 = VALVE5;
			valve2 = VALVE6;
			valve3 = VALVE7;
			break;
		case 2 :
			valve0 = VALVE8;
			valve1 = VALVE9;
			valve2 = VALVE10;
			valve3 = VALVE11;
			break;
		case 3 :
			valve0 = VALVE12;
			valve1 = VALVE13;
			valve2 = VALVE14;
			valve3 = VALVE15;
			break;
		case 4 :
			valve0 = VALVE16;
			valve1 = VALVE17;
			valve2 = VALVE18;
			valve3 = VALVE19;
			break;
		default :
		    break;
	}

	switch(currValveState) {
		case VALVESOPEN :
		    if (newState == VALVESVACUUMOPEN) {
		    	valveToState(valve3, VCLOSED);
		    	valveToState(valve0, VCLOSED);
		    } else if (newState == VALVESAIROPEN) {
		    	valveToState(valve1, VCLOSED);
		    	valveToState(valve2, VCLOSED);
		    } else if (newState == VALVESCLOSED) {
		    	valveToState(valve3, VCLOSED);
		    	valveToState(valve1, VCLOSED);
		    	valveToState(valve0, VCLOSED);
		    	valveToState(valve2, VCLOSED);
		    } else {
		    	return;
		    }
		    break;
		case VALVESVACUUMOPEN :
		    if (newState == VALVESOPEN) {
		    	valveToState(valve0, VOPEN);
		    	valveToState(valve3, VOPEN);
		    } else if (newState == VALVESAIROPEN) {
		    	valveToState(valve1, VCLOSED);
		    	valveToState(valve2, VCLOSED);
		    	valveToState(valve3, VOPEN);
		    	valveToState(valve0, VOPEN);
		    } else if (newState == VALVESCLOSED) {
		    	valveToState(valve1, VCLOSED);
		    	valveToState(valve2, VCLOSED);
		    } else {
		    	return;
		    }
		    break;
		case VALVESAIROPEN :
		    if (newState == VALVESOPEN) {
		    	valveToState(valve2, VOPEN);
		    	valveToState(valve1, VOPEN);
		    } else if (newState == VALVESVACUUMOPEN) {
		    	valveToState(valve3, VCLOSED);
		    	valveToState(valve0, VCLOSED);
		    	valveToState(valve2, VOPEN);
		    	valveToState(valve1, VOPEN);
		    } else if (newState == VALVESCLOSED) {
		    	valveToState(valve3, VCLOSED);
		    	valveToState(valve0, VCLOSED);
		    } else {
		    	return;
		    }
		    break;
		case VALVESCLOSED :
		    if (newState == VALVESOPEN) {
		    	valveToState(valve2, VOPEN);
		    	valveToState(valve0, VOPEN);
		    	valveToState(valve1, VOPEN);
		    	valveToState(valve3, VOPEN);
		    } else if (newState == VALVESVACUUMOPEN) {
		    	valveToState(valve2, VOPEN);
		    	valveToState(valve1, VOPEN);
		    } else if (newState == VALVESAIROPEN) {
		    	valveToState(valve0, VOPEN);
		    	valveToState(valve3, VOPEN);
		    } else {
		    	return;
		    }
		    break;
		default :
		    break;
	}
	return;
}
