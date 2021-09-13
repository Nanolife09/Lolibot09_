#include "auton.h"

std::vector <int> target;
std::vector <int> direction;

void auton () {
  PID_ODORMETRY pid;
  for (int i = 0; i < target.size(); i++) {
    pid.PID_CONTROL(target[i], direction[i]);
  }
}