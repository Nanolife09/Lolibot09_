#include "auton.h"
#include "driver.h"
#include "debug.h"

void chassisfwd(int y, int power){
  lf.resetRotation();
  while(std::abs(rotation_value(lf))<std::abs(y)){
   spin(lf,power);
   spin(lb,power);
   spin(rf,power);
   spin(rb,power); 
  }
}

void chassisstop() {
  lf.stop();
  lb.stop();
  rf.stop();
  rb.stop();
}

void chassisturn(int y,int power){
  while (rotation_value(lf)<std::abs(y)){
   spin(lf,power);
   spin(lb,power);
   spin(rf,-power);
   spin(rb,-power);
  }
  lf.stop();
  lb.stop();
  rf.stop();
  rb.stop();
  
}

void liftup(){
  while (rotation_value(liftl)<lift_max){
    spin(liftl,lift_power);
    spin(liftr,lift_power);    
  }
  liftl.stop();
  liftr.stop();
}

void liftdown(){
  while(rotation_value(liftl)>0){
    spin(liftl,-lift_power);
    spin(liftr,-lift_power);
  }
  liftl.stop();
  liftr.stop();
}

void klampup(){
  while(rotation_value(clamp)<clamp_max){
    spin(clamp,clamp_power);
  }
  clamp.stop();
  clamp.setBrake(brakeType::hold);
}

void klampdown(){
  while(rotation_value(clamp)>0){
    spin(clamp,-100);
  }
  clamp.stop();
  clamp.setBrake(brakeType::hold);
}

void bklamp(bool x){
  if (x) {
    while(rotation_value(back)<back_max){
      spin(back,back_power);
    }
  }
  else {
    while(rotation_value(back)>0){
      spin(back,-back_power);
    }
  }
  back.stop();
  back.setBrake(brakeType::hold);
}

void red_right(){
  chassisfwd(4000,-80);
  chassisfwd(500,50);
}

void red_left(){
  clamp.spin(directionType::fwd, 100, percentUnits::pct);
  chassisfwd(1350,100);
  chassisstop();
  klampdown();
  chassisfwd(1500,-100);
  chassisstop();
}

void blue_left(){
  chassisfwd(3000,50);
  lf.resetRotation();
  klampdown();
  chassisfwd(-3000,50);
  klampup();
}

void blue_right(){
  chassisfwd(10000,50);
  lf.resetRotation();
  klampdown();
  chassisfwd(-10000,50);
  lf.resetRotation();
  chassisfwd(50000,50);
  lf.resetRotation();
}

void skills(){
  chassisfwd(3000,50);
  lf.resetRotation();
  klampdown();
  chassisturn(500,20);
  lf.resetRotation();
  chassisfwd(-3000,50);
  lf.resetRotation();
  chassisturn(-500,20);
  lf.resetRotation();
  chassisfwd(1000,30);
  lf.resetRotation();
  liftup();
  klampup();
}

int option = 0;

void auton_ctrl(){
  switch(option){
    case 0:
    red_left();
    break;
    case 1:
    red_right();
    break;
    case 2:
    blue_left();
    break;
    case 3:
    blue_right();
    break;
    case 4:
    skills();
    break;
  }
}