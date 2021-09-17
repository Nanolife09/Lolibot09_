#ifndef PID_ODORFILE
#define PID_ODORFILE

#include "vex.h"
#include "robot-config.h"
#include "driver.h"

class PID_ODORMETRY {
  const double KP = 0;
  const double KD = 0;
  float average_position = 0;
  int error = 0;
  int prev_error = 0;
  int total_error = 0;
  int derivative = error - prev_error;
  double motor_power;
  //------------------------------
  const double turn_KP = 0;
  const double turn_KD = 0;
  float turn_difference;
  int turn_error = 0;
  int turn_prev_error = 0;
  int turn_total_error = 0;
  int turn_derivative = error - prev_error;
  double turn_motor_power;
  public:
  enum position {lateral, turn};
  int PID_CONTROL(int target, int pos);
};

#endif