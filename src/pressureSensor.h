#ifndef PRESSURESENSOR__H__
#define PRESSURESENSOR__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro
#include "pneumatics.h"

#define usePressureSensor 1 // 1 = true, 0 = false
// this macro defines a usage state for using the pressure sensor

void enterMeasurementState(int sensor, int airOrVacState);
// this is designed to send the appropriate signal through hardware,
// a digital high signal for greater than 10 ms, to the pressure
// sensor through the appropriate output pin

int takeMeasurement(int sensor);
// this is designed to read back the appropriate information
// from the sensor and process it into a pressure value
// from the ADC

#endif