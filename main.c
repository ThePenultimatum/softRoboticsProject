#include "NU32.h" 									// constants, functions for startup and UART
#define VOLTS_PER_COUNT (3.3/1024)
#define CORE_TICK_TIME 25 							// nanoseconds between core ticks
#define SAMPLE_TIME 10 // 10 core timer ticks = 250 ns
#define DELAY_TICKS 20000000 // delay 1/2 sec, 20 M core ticks, between messages

unsigned int adc_sample_convert(int pin) { // sample & convert the value on the given
// adc pin the pin should be configured as an
// analog input in AD1PCFG
unsigned int elapsed = 0, finish_time = 0;
AD1CHSbits.CH0SA = pin; // connect chosen pin to MUXA for sampling
AD1CON1bits.SAMP = 1; // start sampling
elapsed = _CP0_GET_COUNT();
finish_time = elapsed + SAMPLE_TIME;

while (_CP0_GET_COUNT() < finish_time) {
	; // sample for more than 250 n
}

AD1CON1bits.SAMP = 0; // stop sampling and start converting
while (!AD1CON1bits.DONE) {
; // wait for the conversion process to finish
}

return ADC1BUF0; // read the buffer with the result
}

int main(void) {
	unsigned int sample14 = 0, sample15 = 0, elapsed = 0;
	char msg[100] = {};
	NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
	//AD1PCFGbits.PCFG14 = 0; // AN14 is an adc pin
	AD1PCFGbits.PCFG15 = 0; // AN15 is an adc pin
	AD1CON3bits.ADCS = 2; // ADC clock period is Tad = 2*(ADCS+1)*Tpb =
	// 2*3*12.5ns = 75ns
	AD1CON1bits.ADON = 1; // turn on A/D converter
	
	while (1) {
		_CP0_SET_COUNT(0); // set the core timer count to zero
		//sample14 = adc_sample_convert(14); // sample and convert pin 14
		sample15 = adc_sample_convert(15); // sample and convert pin 15
		elapsed = _CP0_GET_COUNT(); // how long it took to do two samples
		// send the results over serial
		sprintf(msg, "Time elapsed: %5u ns AN14: %4u (%5.3f volts)"
		" AN15: %4u (%5.3f volts) \r\n",
		elapsed * CORE_TICK_TIME,
		//sample14, sample14 * VOLTS_PER_COUNT,
		sample15, sample15 * VOLTS_PER_COUNT);
		NU32_WriteUART3(msg);
		_CP0_SET_COUNT(0); // delay to prevent a flood of messages
		while(_CP0_GET_COUNT() < DELAY_TICKS) {
			;
		}
	}
return 0;
}