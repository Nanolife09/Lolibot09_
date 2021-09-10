#include "pid_odormetry.h"

PID_ODORMETRY::PID_ODORMETRY(){
  start = std::chrono::high_resolution_clock::now();
}

int PID_ODORMETRY::value (encoder name, int target) {
  prev_position = name.rotation(rotationUnits::raw);
  end = std::chrono::high_resolution_clock::now();
  time_change = end - start;
  prev_velocity = prev_position / time_change.count();
  error = prev_position - name.rotation(rotationUnits::raw);
  power = (name.rotation(rotationUnits::raw) - prev_position) * (error * KP);
  return power;
}