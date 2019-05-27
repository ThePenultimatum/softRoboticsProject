#ifndef PRESSURESENSOR__H__
#define PRESSURESENSOR__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro
#include "pneumatics.h"

#define usePressureSensor 1 // 1 = true, 0 = false

void enterMeasurementState(int sensor, int airOrVacState);
int takeMeasurement(int sensor);

#endif