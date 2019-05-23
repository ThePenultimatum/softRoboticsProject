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
  TRISB &= 0xFFD0;
  LATB &= 0xFFD0;
  TRISD &= 0xFFFB;
  __builtin_enable_interrupts();
}


int32_t main(void) {
  setup_nu32_softrobotics();

  //LATBbits.LATB0 = 1;
  //LATBbits.LATB1 = 0;
  //LATBbits.LATB2 = 1;
  //LATBbits.LATB3 = 0;
  //LATBbits.LATB5 = 1;

  //LATDbits.LATD3 = 0;

/*  __builtin_disable_interrupts();   // step 2: disable interrupts at CPU
  T2CONbits.TCKPS = 0b111;     // Timer2 prescaler N=64
  PR2 = 31249;              // period = (PR2+1) * N * 12.5 ns = 100 Hz
  TMR2 = 0;                // initial TMR2 count is 0
  IPC2bits.T2IP = 6;                // step 4: interrupt priority
  IFS0bits.T2IF = 0;                // step 5: clear T2 interrupt flag
  IEC0bits.T2IE = 1;                // step 6: enable timer2 interrupt
  T2CONbits.ON = 1;        // turn on Timer2
  __builtin_enable_interrupts();    // step 7: CPU interrupts enabled*/
  // interrupt stuff above

  // use at command +++ and get the remote id and then attach that to the
  // message written to the uart here with the distance
  //__builtin_disable_interrupts();   // step 2: disable interrupts at CPU
/*  T2CONbits.TCKPS = 0b111;     // Timer2 prescaler N=64
  PR2 = 31249;              // period = (PR2+1) * N * 12.5 ns = 100 Hz
  TMR2 = 0;                // initial TMR2 count is 0
  IPC2bits.T2IP = 6;                // step 4: interrupt priority
  IFS0bits.T2IF = 0;                // step 5: clear T2 interrupt flag
  IEC0bits.T2IE = 1;                // step 6: enable timer2 interrupt
  T2CONbits.ON = 1;        // turn on Timer2*/
  /*IEC1bits.U2RXIE = 1;
  IEC1bits.U2TXIE = 0;
  U2STAbits.UTXEN = 0;
  IFS1bits.U2RXIF = 0;
  IFS1bits.U2TXIF = 0;
  IFS1bits.U2EIF = 0;
  IPC8bits.U2IP = 6;*/
  //__builtin_enable_interrupts();    // step 7: CPU interrupts enabled

  //TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  //LATDbits.LATD3 = 0;

  allPowerOff();
  
  while (1) {

    /*if (LATBbits.LATB0) {
      LATBbits.LATB0 = 0;
    } else {
      LATBbits.LATB0 = 1;
    }


    if (LATBbits.LATB1) {
      LATBbits.LATB1 = 0;
    } else {
      LATBbits.LATB1 = 1;
    }

    if (LATDbits.LATD3) {
      LATDbits.LATD3 = 0;
    } else {
      LATDbits.LATD3 = 1;
    }


    if (LATBbits.LATB2) {
      LATBbits.LATB2 = 0;
    } else {
      LATBbits.LATB2 = 1;
    }


    if (LATBbits.LATB3) {
      LATBbits.LATB3 = 0;
    } else {
      LATBbits.LATB3 = 1;
    }


    if (LATBbits.LATB5) {
      LATBbits.LATB5 = 0;
    } else {
      LATBbits.LATB5 = 1;
    }*/

    if (getValveState() == VALVESOPEN) {
      switchState(VALVESCLOSED);
    } else {
      switchState(VALVESOPEN);
    }
    //VALVE0POWER = 1;
    //LATBbits.LATB0 = 1;
    //valveToState(VALVE0, VCLOSED);

    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 80000000) {
      Nop();
    }
    //VALVE0POWER = 0;
    //LATBbits.LATB0 = 0;
    // _CP0_SET_COUNT(0);
    // while (_CP0_GET_COUNT() < 80000000) {
    //   Nop();
    // }
  }
  return 0;
}
