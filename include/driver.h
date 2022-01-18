#ifndef DRIVER_HFILE
#define DRIVER_HFILE
#include "vex.h"

extern int change_sens;
extern int dead_zone;
extern int lift_power_limit;
extern int lift_rotation_error;
extern int lift_max;
extern int lift_power_up;
extern int lift_power_down;
extern int clamp_max;
extern int clamp_power;
extern int back_max;
extern int back_power;

extern void spin(motor name, int power);
extern void driver_ctrl();

extern int left_power;
extern int right_power;

#endif