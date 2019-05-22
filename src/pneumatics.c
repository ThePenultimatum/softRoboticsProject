#include "pneumatics.h"

int getValveState() {
	int twoAndThree = VALVE2POWER && VALVE3POWER;
	int oneAndFour = 
	if (VALVE1POWER && VALVE2POWER && VALVE3POWER && VALVE4POWER) {
		return VALVESCLOSED
	} else if (!)
	return 1;
}

void allPowerOff() {
	PUMPPOWER = 0;
	VALVE1POWER = 0;
	VALVE2POWER = 0;
	VALVE3POWER = 0;
	VALVE4POWER = 0;
}

void valvesToState() {

}

void switchState(int stateval) {
	// states are 0, 1, 2, 3
	// states correspond to valve configurations
	// 0 is all valves off, 3 is all valves on
	// 1 is valves 1 and 4 powered to close them and provide vacuum when pump is powered
	// 2 is valves 2 and 3 powered to close them and provide air when pump is powered

}