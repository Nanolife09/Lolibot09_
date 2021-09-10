#ifndef PID_ODORFILE
#define PID_ODORFILE

#include "vex.h"
#include "robot-config.h"
#include <chrono>

class PID_ODORMETRY {
  const float KP = 0;
  const float KI = 0;
  const float KD = 0;
  float power;
  float prev_position;
  float prev_velocity;
  float velocity;
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  std::chrono::duration <float> time_change;
  int error;
  public:
  PID_ODORMETRY();
  int value(encoder name, int target);
};

#endif