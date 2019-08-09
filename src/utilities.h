#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "NU32.h"          // constants, funcs for startup and UART
#include "pneumatics.h"

void setup_nu32_softrobotics(void);
// this runs the setup function in NU32 for the board with the PIC32
// and sets the TRIS and LAT register values appropriately to
// initialize the digital I/O for all pneumatic components to be
// turned off; then, a double-check functional state change
// to the off and closed states for all valves and pumps
// is run

void delayRough(void);
// given the initializations for the clock on the PIC32 in
// NU32.c, this delays the processing for about 0.5 seconds
// or 24 million clock cycles