#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "NU32.h"          // constants, funcs for startup and UART
//#include "./xbee_ansic_library/include/xbee/serial.h"

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

#define MAX_MESSAGE_LENGTH 200
#define WAITING 0
#define CORE_TICKS 40000000 // number of core ticks in 1 second, 80 MHz
#define MAXDIST 2.0

/*
define the x and y values of all 3 sensors here
then use them in calculation of distances

use a hash table for the node measurements?
*/

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

int32_t main(void) {

  NU32_Startup();

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
  __builtin_disable_interrupts();   // step 2: disable interrupts at CPU
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
  __builtin_enable_interrupts();    // step 7: CPU interrupts enabled

  //TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  LATDbits.LATD3 = 0;
  
  while (1) {
    
  }
  return 0;
}
