#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "NU32.h"          // constants, funcs for startup and UART
#include "pneumatics.h"

#define CORE_TICKS 40000000 // number of core ticks in 1 second, 80 MHz

/*
define the x and y values of all 3 sensors here
then use them in calculation of distances

use a hash table for the node measurements?
*/

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

void setup_nu32_softrobotics() {
  NU32_Startup();
  __builtin_disable_interrupts();
  //TRISB &= 0xFFD0; // for one pump setup
  //LATB &= 0xFFD0; // for one pump setup

  TRISB &= 0x8000; // for five pump setup
  LATB &= 0xFFFF; // for five pump setup, 1's because of hex inverter
  TRISD &= 0xFC00; // for five pump setup
  LATD &= 0xFFFF; // for five pump setup, 1's because of hex inverter

  __builtin_enable_interrupts();

  allPowerOff();

  pumpToState(PUMP0, PUMPOFF);
  pumpToState(PUMP1, PUMPOFF);
  pumpToState(PUMP2, PUMPOFF);
  pumpToState(PUMP3, PUMPOFF);
  pumpToState(PUMP4, PUMPOFF);
  valveToState(VALVE0, VCLOSED);
  valveToState(VALVE1, VCLOSED);
  valveToState(VALVE2, VCLOSED);
  valveToState(VALVE3, VCLOSED);
  valveToState(VALVE4, VCLOSED);
  valveToState(VALVE5, VCLOSED);
  valveToState(VALVE6, VCLOSED);
  valveToState(VALVE7, VCLOSED);
  valveToState(VALVE8, VCLOSED);
  valveToState(VALVE9, VCLOSED);
  valveToState(VALVE10, VCLOSED);
  valveToState(VALVE11, VCLOSED);
  valveToState(VALVE12, VCLOSED);
  valveToState(VALVE13, VCLOSED);
  valveToState(VALVE14, VCLOSED);
  valveToState(VALVE15, VCLOSED);
  valveToState(VALVE16, VCLOSED);
  valveToState(VALVE17, VCLOSED);
  valveToState(VALVE18, VCLOSED);
  valveToState(VALVE19, VCLOSED);
}

void delayRough() {
  _CP0_SET_COUNT(0);
  while (_CP0_GET_COUNT() < 240000000) {
    Nop();
  } 
}

void cyclePumps() {
  pumpToState(PUMP0, PUMPON);
  delayRough();
  pumpToState(PUMP1, PUMPON);
  delayRough();
  pumpToState(PUMP2, PUMPON);
  delayRough();
  pumpToState(PUMP3, PUMPON);
  delayRough();
  pumpToState(PUMP4, PUMPON);
  delayRough();
  pumpToState(PUMP0, PUMPOFF);
  delayRough();
  pumpToState(PUMP1, PUMPOFF);
  delayRough();
  pumpToState(PUMP2, PUMPOFF);
  delayRough();
  pumpToState(PUMP3, PUMPOFF);
  delayRough();
  pumpToState(PUMP4, PUMPOFF);
  delayRough();
}

void cycleValves() {
  valveToState(VALVE0, VOPEN);
  delayRough();
  valveToState(VALVE0, VCLOSED);
  delayRough();
  valveToState(VALVE1, VOPEN);
  delayRough();
  valveToState(VALVE1, VCLOSED);
  delayRough();
  valveToState(VALVE2, VOPEN);
  delayRough();
  valveToState(VALVE2, VCLOSED);
  delayRough();
  valveToState(VALVE3, VOPEN);
  delayRough();
  valveToState(VALVE3, VCLOSED);
  delayRough();
  valveToState(VALVE4, VOPEN);
  delayRough();
  valveToState(VALVE4, VCLOSED);
  delayRough();
  valveToState(VALVE5, VOPEN);
  delayRough();
  valveToState(VALVE5, VCLOSED);
  delayRough();
  valveToState(VALVE6, VOPEN);
  delayRough();
  valveToState(VALVE6, VCLOSED);
  delayRough();
  valveToState(VALVE7, VOPEN);
  delayRough();
  valveToState(VALVE7, VCLOSED);
  delayRough();
  valveToState(VALVE8, VOPEN);
  delayRough();
  valveToState(VALVE8, VCLOSED);
  delayRough();
  valveToState(VALVE9, VOPEN);
  delayRough();
  valveToState(VALVE9, VCLOSED);
  delayRough();
  valveToState(VALVE10, VOPEN);
  delayRough();
  valveToState(VALVE10, VCLOSED);
  delayRough();
  valveToState(VALVE11, VOPEN);
  delayRough();
  valveToState(VALVE11, VCLOSED);
  delayRough();
  valveToState(VALVE12, VOPEN);
  delayRough();
  valveToState(VALVE12, VCLOSED);
  delayRough();
  valveToState(VALVE13, VOPEN);
  delayRough();
  valveToState(VALVE13, VCLOSED);
  delayRough();
  valveToState(VALVE14, VOPEN);
  delayRough();
  valveToState(VALVE14, VCLOSED);
  delayRough();
  valveToState(VALVE15, VOPEN);
  delayRough();
  valveToState(VALVE15, VCLOSED);
  delayRough();
  valveToState(VALVE16, VOPEN);
  delayRough();
  valveToState(VALVE16, VCLOSED);
  delayRough();
  valveToState(VALVE17, VOPEN);
  delayRough();
  valveToState(VALVE17, VCLOSED);
  delayRough();
  valveToState(VALVE18, VOPEN);
  delayRough();
  valveToState(VALVE18, VCLOSED);
  delayRough();
  valveToState(VALVE19, VOPEN);
  delayRough();
  valveToState(VALVE19, VCLOSED);
  delayRough();
}

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

    cyclePumps();
    cycleValves();


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
