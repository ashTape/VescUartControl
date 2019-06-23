#include <Servo.h>
#include "footSensor.h"
#include "twoWheels.h"

footSensor front(0, 800), rear(1, 800); // footSensor(pin, threshold value)
twoWheels wheels(9,10); // twoWheels(right pin, left pin)

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (wheels.getStatus()){ // check connections of wheels
    int val = front.getValue() - rear.getValue(); 
    if (front.check()){ //whether its value is over its threshold
      if (val > 0){
        wheels.accel(val);    
      }else{
        wheels.brake(val);
      }
    }else if(!(front.check()) && rear.check()){
      wheels.reverse(val);
    }else{
      wheels.lock();
    }
  }else{
    Serial.println("Not Connected to Wheels!");
  }
  delay(10);
}
