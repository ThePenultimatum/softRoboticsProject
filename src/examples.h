#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "NU32.h"          // constants, funcs for startup and UART
#include "pneumatics.h"
#include "testing.h"
#include "utilities.h"

void cycleAllComponents(void);
	// here all the components are cycled through power on and then power off
	// using the cyclePumps first and then cycleValves. They are cycled
	// in numeric order according to their definitions in pneumatics.h

void rollMMVS(void);
	// here all the mmvs components would simultaneously actuate
	// in one direction and then alternate to the next over and over
	// this will be something like the following depending on which
	// valvesets are connected to which cavities and potentially in a while loop to repeat:
	//   switchState(VALVESAIROPEN, VALVESET0);
	//   pumpToState(PUMPON, PUMP0);
	//   delayRough();
	//   pumpToState(PUMPOFF, PUMP0);
	//   switchState(VALVESAIROPEN, VALVESET1);
	//   pumpToState(PUMPON, PUMP1);
	//   delayRough();
	//   pumpToState(PUMPOFF, PUMP1);
	//   switchState(VALVESAIROPEN, VALVESET2);
	//   pumpToState(PUMPON, PUMP2);
	//   delayRough();
	//   pumpToState(PUMPOFF, PUMP2);

void shrinkMcKibbens(void);
	// here all the mckibben muscles would actuate at the same time and then de-actuate
	// this will be something like the following depending on which
	// valvesets are connected to which cavities and potentially in a while loop to repeat:
	//   switchState(VALVESAIROPEN, VALVESET3);
	//   pumpToState(PUMPON, PUMP3);
	//   delayRough();
	//   pumpToState(PUMPOFF, PUMP3);