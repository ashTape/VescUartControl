#ifndef twoWheels_H
#define twoWheels_H

#include <Servo.h>

class twoWheels{
  Servo right,left;
  int goalSpeed[2];
  int currentSpeed[2];
//  float P, I, D, preP, Time, preTime, dt;
 public:
  twoWheels(const int, const int);
  ~twoWheels();
  bool getStatus();
  int* getCurrentSpeedPtr(){return currentSpeed;};
  void writeGoalSpeed(const int (&)[2]);
  void writeGoalSpeedSine(const int (&)[2]);
  void accel(const int&);  
  void brake(const int&);
  void reverse(const int&);
  void lock();
};

#endif
