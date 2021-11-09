#include "debug.h"

float rotation_value (motor name) {
  return name.rotation(rotationUnits::raw);
}

void debug() {
  while(true){
    if(ctrl.ButtonA.pressing()){
      spin(liftl,30);
      spin(liftr, 30);
    }
  }
}

