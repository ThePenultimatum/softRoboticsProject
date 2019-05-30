#include "pneumatics.h"

int getValveState(int valveSet) {
	int oneAndTwo = ((LATBbits.LATB1 && LATBbits.LATB2) == VCLOSED); //VALVE1POWER && VALVE2POWER;
	int zeroAndThree = ((LATBbits.LATB0 && LATBbits.LATB3) == VCLOSED); //VALVE0POWER && VALVE3POWER;
	switch(valveSet) {
		case VALVESET0 :
			oneAndTwo = ((LATBbits.LATB1 && LATBbits.LATB2) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			zeroAndThree = ((LATBbits.LATB0 && LATBbits.LATB3) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		case VALVESET1 :
			oneAndTwo = ((LATBbits.LATB6 && LATBbits.LATB7) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			zeroAndThree = ((LATBbits.LATB5 && LATBbits.LATB8) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		case VALVESET2 :
			oneAndTwo = ((LATBbits.LATB11 && LATBbits.LATB12) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			zeroAndThree = ((LATBbits.LATB10 && LATBbits.LATB13) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		case VALVESET3 :
			oneAndTwo = ((LATDbits.LATD1 && LATDbits.LATD2) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			zeroAndThree = ((LATDbits.LATD0 && LATDbits.LATD3) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		case VALVESET4 :
			oneAndTwo = ((LATDbits.LATD6 && LATDbits.LATD7) == VCLOSED); //VALVE1POWER && VALVE2POWER;
			zeroAndThree = ((LATDbits.LATD5 && LATDbits.LATD8) == VCLOSED); //VALVE0POWER && VALVE3POWER;
			break;
		default :
		    break; //return UNKNOWNVALVESTATE;
	}

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
	}		
}

int getPumpState(int pump) {
	switch(pump) {
		case PUMP0 :
			if (!(LATBbits.LATB4)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		case PUMP1 :
			if (!(LATBbits.LATB9)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		case PUMP2 :
			if (!(LATBbits.LATB14)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		case PUMP3 :
			if (!(LATDbits.LATD4)) {//PUMP0POWER) {
				return PUMPON;
			} else {
				return PUMPOFF;
			}
			break;
		case PUMP4 :
			if (!(LATDbits.LATD9)) {//PUMP0POWER) {
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
			LATBbits.LATB0 = VCLOSED;
			LATBbits.LATB1 = VCLOSED;
			LATBbits.LATB2 = VCLOSED;
			LATBbits.LATB3 = VCLOSED;
			LATBbits.LATB4 = PUMPOFF;
			break;
		case VALVESET1 :
			LATBbits.LATB5 = VCLOSED;
			LATBbits.LATB6 = VCLOSED;
			LATBbits.LATB7 = VCLOSED;
			LATBbits.LATB8 = VCLOSED;
			LATBbits.LATB9 = PUMPOFF;
			break;
		case VALVESET2 :
			LATBbits.LATB10 = VCLOSED;
			LATBbits.LATB11 = VCLOSED;
			LATBbits.LATB12 = VCLOSED;
			LATBbits.LATB13 = VCLOSED;
			LATBbits.LATB14 = PUMPOFF;
			break;
		case VALVESET3 :
			LATDbits.LATD0 = VCLOSED;
			LATDbits.LATD1 = VCLOSED;
			LATDbits.LATD2 = VCLOSED;
			LATDbits.LATD3 = VCLOSED;
			LATDbits.LATD4 = PUMPOFF;
			break;
		case VALVESET4 :
			LATDbits.LATD5 = VCLOSED;
			LATDbits.LATD6 = VCLOSED;
			LATDbits.LATD7 = VCLOSED;
			LATDbits.LATD8 = VCLOSED;
			LATDbits.LATD9 = PUMPOFF;
			break;
		default :
		    break;
	}
}

void pumpToState(unsigned int pump, unsigned int state) {
	switch(pump){
		case PUMP0 :
		    //pump = state;
		    LATBbits.LATB4 = state;
		    break;
		case PUMP1 :
		    //pump = state;
		    LATBbits.LATB9 = state;
		    break;
		case PUMP2 :
		    //pump = state;
		    LATBbits.LATB14 = state;
		    break;
		case PUMP3 :
		    //pump = state;
		    LATDbits.LATD4 = state;
		    break;
		case PUMP4 :
		    //pump = state;
		    LATDbits.LATD9 = state;
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
		case VALVE4 :
		    //VALVE0POWER = state;
		    LATBbits.LATB5 = state;
		    break;
		case VALVE5 :
		    //VALVE1POWER = state;
		    LATBbits.LATB6 = state;
		    break;
		case VALVE6 :
		    //VALVE2POWER = state;
		    LATBbits.LATB7 = state;
		    break;
		case VALVE7 :
		    //VALVE3POWER = state;
		    LATBbits.LATB8 = state;
		    break;
		case VALVE8 :
		    //VALVE0POWER = state;
		    LATBbits.LATB10 = state;
		    break;
		case VALVE9 :
		    //VALVE1POWER = state;
		    LATBbits.LATB11 = state;
		    break;
		case VALVE10 :
		    //VALVE2POWER = state;
		    LATBbits.LATB12 = state;
		    break;
		case VALVE11 :
		    //VALVE3POWER = state;
		    LATBbits.LATB13 = state;
		    break;
		case VALVE12 :
		    //VALVE0POWER = state;
		    LATDbits.LATD0 = state;
		    break;
		case VALVE13 :
		    //VALVE1POWER = state;
		    LATDbits.LATD1 = state;
		    break;
		case VALVE14 :
		    //VALVE2POWER = state;
		    LATDbits.LATD2 = state;
		    break;
		case VALVE15 :
		    //VALVE3POWER = state;
		    LATDbits.LATD3 = state;
		    break;
		case VALVE16 :
		    //VALVE0POWER = state;
		    LATDbits.LATD5 = state;
		    break;
		case VALVE17 :
		    //VALVE1POWER = state;
		    LATDbits.LATD6 = state;
		    break;
		case VALVE18 :
		    //VALVE2POWER = state;
		    LATDbits.LATD7 = state;
		    break;
		case VALVE19 :
		    //VALVE3POWER = state;
		    LATDbits.LATD8 = state;
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