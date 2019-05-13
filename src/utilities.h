#include "NU32.h"

#define IDLE_MODE_VAL 1
#define PWM_MODE_VAL 2
#define ITEST_MODE_VAL 3
#define HOLD_MODE_VAL 4
#define TRACK_MODE_VAL 5

volatile int controlsModeMSD;

void setMode(int);
int queryMode(void);
void initPositionTiming(void);
void initPeriphs(void);
void initADC(void);
unsigned int adc_sample_convert(int);
unsigned int adcGetAvgVal(int);
float getMeasuredValInMilliAmps(unsigned int);