#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "examples.h"
#include "NU32.h"          // constants, funcs for startup and UART
#include "pneumatics.h"
#include "testing.h"
#include "utilities.h"

#define CORE_TICKS 40000000 // number of core ticks in 1 second, 80 MHz

/*
define the x and y values of all 3 sensors here
then use them in calculation of distances

use a hash table for the node measurements?
*/

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

int32_t main(void) {
  setup_nu32_softrobotics();

  unsigned int i = 0;//, data = 0;
  //unsigned int buflen = 20;
  //char buffer[buflen];

  //float midval = 1.8;

  //int valvesetInUse = VALVESET0;
  //int pumpInUse = PUMP0;

  /*_CP0_SET_COUNT(0);
  while (_CP0_GET_COUNT() < 80000000) {
    Nop();
  } */
  //switchState(VALVESET0, VALVESAIROPEN);
  //valveToState(VALVE0, VOPEN);
  //switchState(VALVESAIROPEN, VALVESET0);
  while (1) {

    //cyclePumps();
    //cycleValves();

    cycleAllComponents();
    
    //switchState(VALVESET0, VALVESAIROPEN);
    //switchState(VALVESET2, VALVESAIROPEN);
    //pumpToState(PUMP0, PUMPON);
    //delayRough();
    //pumpToState(PUMP0, PUMPOFF);
    //switchState(VALVESET0, VALVESCLOSED);
    //pumpToState(PUMP2, PUMPON);
    //delayRough();
    //pumpToState(PUMP2, PUMPOFF);
    //switchState(VALVESET2, VALVESCLOSED);
    //switchState(VALVESET0, VALVESVACUUMOPEN);
    //pumpToState(PUMP0, PUMPON);
    //delayRough();
    //pumpToState(PUMP0, PUMPOFF);
    //switchState(VALVESET0, VALVESCLOSED);
    //switchState(VALVESET2, VALVESVACUUMOPEN);
    //pumpToState(PUMP2, PUMPON);
    //delayRough();
    //pumpToState(PUMP2, PUMPOFF);
    //switchState(VALVESET2, VALVESCLOSED);
    //switchState(VALVESET0, VALVESOPEN);
    //switchState(VALVESET2, VALVESOPEN);
    //delayRough();
    //switchState(VALVESET0, VALVESCLOSED);
    //switchState(VALVESET2, VALVESCLOSED);
    //allPowerOff();
    //delayRough();
  }
  return 0;
}
