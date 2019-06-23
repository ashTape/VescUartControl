#include <Arduino.h>

class footSensor{
  int pin, threshold, value, count;
public:
  footSensor(int p,int t):pin(p),threshold(t),value(0){};
  footSensor(int p):pin(p),threshold(0),value(0){};
  footSensor(){Serial.println("Need to Set the Pin Number of Foot Sensor!!!");};
  void setThreshold(int t){threshold = t;};
  void readValue();
  int getValue(){readValue();return value;};
  bool check();
};

void footSensor::readValue(){
  int totalValue = 0;
  for (count=0;count<100;count++){
    totalValue += analogRead(pin);
  }
  value = (int)totalValue/(count + 1);
};

bool footSensor::check(){
  if (value >= threshold){
    return true;
  }else{
    return false;
  }
};
