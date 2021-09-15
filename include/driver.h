#ifndef DRIVER_HFILE
#define DRIVER_HFILE
#include "vex.h"

extern void spin(motor name, int power);
extern void tank_ctrl();
extern void piston_ctrl();
extern void driver_ctrl();
extern void mogo_lift_ctrl();

#endif