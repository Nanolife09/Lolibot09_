#include "auton.h"
#include "driver.h"
#include "debug.h"

void chassisfwd(int y, int power){
  while(std::abs(rotation_value(lf))<std::abs(y)){
   spin(lf,power);
   spin(lb,power);
   spin(rf,power);
   spin(rb,power); 
  }
  lf.resetRotation();
}

void chassisstop() {
  lf.stop();
  lb.stop();
  rf.stop();
  rb.stop();
}

void chassisturn(int y,int power){
  while (rotation_value(lf)<y){
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
    spin(clamp,-clamp_power);
  }
  clamp.stop();
}

void bklampup(){
  while(rotation_value(back)<back_max){
    spin(back,back_power);
  }
  back.stop();
}

void bklampdown(){
  while(rotation_value(back)>0){
    spin(back,-back_power);
  }
  back.stop();
}

void red_right(){
  klampup();
  task::sleep(20);
  chassisfwd(1000,20);
  task::sleep(20);
  chassisstop();
  task::sleep(20);
  klampdown();
  task::sleep(20);
  chassisfwd(800,-20);
  task::sleep(20);
  chassisstop();
}

void red_left(){
  lf.resetRotation();
  chassisfwd(3000,50);
  lf.resetRotation();
  klampdown();
  chassisfwd(-3000,50);
  klampup();
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

int option = 1;

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