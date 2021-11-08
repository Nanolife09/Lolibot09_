#include "auton.h"
#include "driver.h"
#include "debug.h"
using namespace std;

void chassisfwd(int y, int power){
  while(abs(rotation_value(lf))<abs(y)){
   spin(lf,power);
   spin(lb,power);
   spin(rf,power);
   spin(rb,power); 
 }
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
  chassisfwd(10000,50);
  lf.resetRotation();
  klampdown();
  chassisfwd(-10000,50);
  lf.resetRotation();
  chassisfwd(50000,50);
  lf.resetRotation();
}

void red_left(){
  chassisfwd(3000,50);
  lf.resetRotation();
  klampdown();
  chassisfwd(3000,50);
  klampup();
}

void blue_left(){
  chassisfwd(3000,50);
  lf.resetRotation();
  klampdown();
  chassisfwd(3000,50);
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