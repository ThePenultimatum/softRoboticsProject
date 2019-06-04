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


int32_t main(void) {
  setup_nu32_softrobotics();

  unsigned int i = 0;

  /*_CP0_SET_COUNT(0);
  while (_CP0_GET_COUNT() < 80000000) {
    Nop();
  } */
  //switchState(VALVESET0, VALVESAIROPEN); 
  //valveToState(VALVE0, VOPEN);
  //switchState(VALVESAIROPEN, VALVESET0); 
  while (1) {

    /*if (i < 3) {

      switchState(VALVESAIROPEN, VALVESET0);
      pumpToState(PUMP0, PUMPON);

      _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }

      pumpToState(PUMP0, PUMPOFF);

      switchState(VALVESVACUUMOPEN, VALVESET0);
      pumpToState(PUMP0, PUMPON);

      _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }

      pumpToState(PUMP0, PUMPOFF);

      switchState(VALVESCLOSED, VALVESET0);
    }
    i++;*/

    valveToState(VALVE0, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE1, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE2, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE3, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE4, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE5, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE6, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE7, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE8, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE9, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE10, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE11, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE12, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE13, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE14, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE15, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE16, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE17, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE18, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    valveToState(VALVE19, VCLOSED);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    pumpToState(PUMP0, PUMPOFF);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    pumpToState(PUMP1, PUMPOFF);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    pumpToState(PUMP2, PUMPOFF);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    pumpToState(PUMP3, PUMPOFF);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }
    pumpToState(PUMP4, PUMPOFF);
    _CP0_SET_COUNT(0);
      while (_CP0_GET_COUNT() < 80000000) {
        Nop();
      }  

    /*if (getValveState(VALVESET0) == VALVESVACUUMOPEN) {
      valveToState(VALVE15, VCLOSED);
    }*/







    //pumpToState(PUMP0, PUMPON);
    //if (i < 2) {
    /*if (getValveState(VALVESET0) == VALVESOPEN) {

      switchState(VALVESCLOSED, VALVESET0);
    } else {
      switchState(VALVESOPEN, VALVESET0);
    }*/

    //switchState(VALVESAIROPEN, VALVESET0);


    //pumpToState(PUMP0, PUMPOFF);
    //switchState(VALVESOPEN, VALVESET0);

      //////////////////////////////////////////

      /*if (getValveState(VALVESET0) == VALVESOPEN) {

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
      switchState(VALVESOPEN, VALVESET0);*/

    //}

    //i++;
  }
  return 0;
}
