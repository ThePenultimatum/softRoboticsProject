#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "NU32.h"          // constants, funcs for startup and UART
#include "pneumatics.h"
#include "utilities.h"

void cyclePumps(void);
// this cycles through power on and off with all the pumps
// by flipping digital I/O on the appropriate pins
// no input is required

void cycleValves(void);
// this cycles through power on and off with all the pumps
// by flipping digital I/O on the appropriate pins
// no input is required