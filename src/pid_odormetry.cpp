#include "pid_odormetry.h"

int PID_ODORMETRY::PID_CONTROL (int target, int pos) {
  while (true) {
    average_position = (encoderL.position(rotationUnits::deg) + encoderR.position(rotationUnits::deg))/2;
    error = target - average_position;
    derivative = error - prev_error;

    turn_difference = encoderL.position(rotationUnits::deg) - encoderR.position(rotationUnits::deg);
    turn_error = target - turn_difference;
    turn_derivative = turn_error - turn_prev_error;

    total_error += error;
    turn_total_error += turn_error;

    motor_power = error * KP + derivative * KD + total_error * KI;
    turn_motor_power = turn_error * turn_KP + turn_derivative * turn_KD + turn_total_error * turn_KI;
    prev_error = error;
    turn_prev_error = turn_error;
    task::sleep(20);
    switch (pos) {
      case lateral:
        return motor_power;
        break;
      case turn:
        return turn_motor_power;
        break;
    }
  }
}