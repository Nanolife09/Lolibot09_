#ifndef DRIVER_HFILE
#define DRIVER_HFILE
#include "vex.h"

extern void spin(motor name, int power);
extern void driver_ctrl();

extern int left_power;
extern int right_power;

#endif