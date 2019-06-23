#include "twoWheels.h"
#include "twoWheelsDefs.h"
#include <Arduino.h>
#include <math.h>

twoWheels::twoWheels(const int rightPin, const int leftPin){
  right.attach(rightPin);
  left.attach(leftPin);
};

twoWheels::~twoWheels(){
  lock();
}

bool twoWheels::getStatus(){
  if (right.attached() && left.attached()){
    return true;
  }else{
    return false;
  }
};

void twoWheels::writeGoalSpeed(const int (&array)[2]){
  right.write(array[0]);
  left.write(array[1]);
  memcpy(currentSpeed, array, sizeof(array));
};

void twoWheels::accel(const int &val){
  goalSpeed[0] = map(val, 0, 1023, 90, 0);
  goalSpeed[1] = map(val, 0, 1023, 90, 180);
  writeGoalSpeed(goalSpeed);
};

void twoWheels::brake(const int &val){
  int brake = map(val, 0, -1023, 0, 90);
  for(int i=0;i>2;i++){
    goalSpeed[i] = currentSpeed[i] - val;
  }

  goalSpeed[0] = 90;
  goalSpeed[1] = 90;
  writeGoalSpeed(goalSpeed);
};

void twoWheels::reverse(const int &val){ // Not used
  goalSpeed[0] = map(val, 0, 1023, 90, 130);
  goalSpeed[1] = map(val, 0, 1023, 90, 50);
  writeGoalSpeed(goalSpeed);
};

void twoWheels::lock(){
  goalSpeed[0] = 90;
  goalSpeed[1] = 90;
  writeGoalSpeed(goalSpeed);
};
