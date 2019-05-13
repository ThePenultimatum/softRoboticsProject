
#include "utilities.h"

#define SAMPLE_TIME 10

volatile int controlsModeMSD = IDLE_MODE_VAL;

void setMode(int mode) {
  controlsModeMSD = mode;
}
int queryMode(void) {
  return controlsModeMSD;
}

void initADC(void) {
  __builtin_disable_interrupts();
  AD1PCFGbits.PCFG0 = 0;
  AD1CON3bits.ADCS = 2;
  AD1CON1bits.ADON = 1;                   // turn on A/D converter
  __builtin_enable_interrupts(); 
}

void initPositionTiming(void) {
  __builtin_disable_interrupts();   // step 2: disable interrupts at CPU
  T4CONbits.TCKPS = 0b110;     // Timer4 prescaler N=64
  PR4 = 6249;              // period = (PR4+1) * N * 12.5 ns = 200 us, 5 kHz
  TMR4 = 0;                // initial TMR4 count is 0
  IPC4bits.T4IP = 4;                // step 4: interrupt priority
  IFS0bits.T4IF = 0;                // step 5: clear T4 interrupt flag
  IEC0bits.T4IE = 1;                // step 6: enable timer4 interrupt
  T4CONbits.ON = 1;        // turn on Timer4
  __builtin_enable_interrupts();    // step 7: CPU interrupts enabled
}

void initPeriphs(void) {
  __builtin_disable_interrupts();   // step 2: disable interrupts at CPU
  T2CONbits.TCKPS = 0b100;     // Timer2 prescaler N=16 (1:1)
  PR2 = 999;              // period = (PR2+1) * N * 12.5 ns = 200 us, 5 kHz
  TMR2 = 0;                // initial TMR2 count is 0
  IPC2bits.T2IP = 3;                // step 4: interrupt priority
  IFS0bits.T2IF = 0;                // step 5: clear T2 interrupt flag
  IEC0bits.T2IE = 1;                // step 6: enable timer2 interrupt
  T2CONbits.ON = 1;        // turn on Timer2

  T3CONbits.TCKPS = 0b101;     // Timer3 prescaler N=1 (1:1)
  PR3 = 124;              // period = (PR3+1) * N * 12.5 ns = 50 us, 20 kHz
  TMR3 = 0;                // initial TMR3 count is 0
  //IPC3bits.T3IP = 6;                // step 4: interrupt priority
  //IFS0bits.T3IF = 0;                // step 5: clear T2 interrupt flag
  //IEC0bits.T3IE = 1;                // step 6: enable timer3 interrupt
  T3CONbits.ON = 1;        // turn on Timer3

  OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
  OC1RS = 31;             // duty cycle = OC1RS/(PR3+1) = 25%
  OC1R = 31;              // initialize before turning OC1 on; afterward it is read-only
  OC1CONbits.OCTSEL = 1;   // use timer 3
  OC1CONbits.ON = 1;       // turn on OC1

  TRISDbits.TRISD8 = 0; // configuring RD8 as buffered digital output
  ODCDbits.ODCD8 = 0;
  __builtin_enable_interrupts();    // step 7: CPU interrupts enabled
  // interrupt stuff above



  /*AD1PCFGbits.PCFG0 = 0;
  AD1CON3bits.ADCS = 2;
  AD1CON1bits.ADON = 1;                   // turn on A/D converter*/

}

unsigned int adc_sample_convert(int pin) { // sample & convert the value on the given 
                                           // adc pin the pin should be configured as an 
                                           // analog input in AD1PCFG
    unsigned int elapsed = 0, finish_time = 0;
    AD1CHSbits.CH0SA = pin;                // connect chosen pin to MUXA for sampling
    AD1CON1bits.SAMP = 1;                  // start sampling
    elapsed = _CP0_GET_COUNT();
    finish_time = elapsed + SAMPLE_TIME;
    while (_CP0_GET_COUNT() < finish_time) {
      ;                                   // sample for more than 250 ns
    }
    AD1CON1bits.SAMP = 0;                 // stop sampling and start converting
    while (!AD1CON1bits.DONE) {
      ;                                   // wait for the conversion process to finish
    }
    return ADC1BUF0;                      // read the buffer with the result
}

unsigned int adcGetAvgVal(int pin) {
	unsigned int vals = 0;
	int numVals = 5;
	int i = 0;
	for (i = 0; i < numVals; i++) {
		vals += adc_sample_convert(pin);
	}
	return (vals/numVals);
}

float getMeasuredValInMilliAmps(unsigned int counts) {
	// measured from calibration
	return (2.09 * counts - 1064);
}