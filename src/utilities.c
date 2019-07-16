#include "utilities.h"

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