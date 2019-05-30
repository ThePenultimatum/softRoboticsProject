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
  LATB &= 0x8000; // for five pump setup
  TRISD &= 0xFC00; // for five pump setup
  LATD &= 0xFC00; // for five pump setup

  __builtin_enable_interrupts();
}


int32_t main(void) {
  setup_nu32_softrobotics();

  allPowerOff();

  unsigned int i = 0;
  
  while (1) {

    if (i < 2) {
      if (getValveState(VALVESET0) == VALVESOPEN) {

        switchState(VALVESCLOSED, VALVESET0);
      } else {
        switchState(VALVESOPEN, VALVESET0);
      }

      switchState(VALVESAIROPEN, VALVESET0);

      pumpToState(PUMP0, PUMPON);

      _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
      _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }

      pumpToState(PUMP0, PUMPOFF);
      switchState(VALVESOPEN, VALVESET0);

      //////////////////////////////////////////

      if (getValveState(VALVESET0) == VALVESOPEN) {

        switchState(VALVESCLOSED, VALVESET0);
      } else {
        switchState(VALVESOPEN, VALVESET0);
      }
      //VALVE0POWER = 1;
      //LATBbits.LATB0 = 1;
      //valveToState(VALVE0, VCLOSED);

      switchState(VALVESVACUUMOPEN, VALVESET0);

      pumpToState(PUMP0, PUMPON);

      _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }

      pumpToState(PUMP0, PUMPOFF);
      switchState(VALVESOPEN, VALVESET0);

    }

    i++;
  }
  return 0;
}
