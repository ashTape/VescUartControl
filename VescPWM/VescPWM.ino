/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo motorRight, motorLeft;  // create servo object to control a servo

int footSensorFront_pin = 0;  // analog pin used to connect the potentiometer
int footSensorRear_pin = 1;
int footSensorFront_value, footSensorRear_value;    // variable to read the value from the analog pin
int val = 0;
int threshold = 800 ;

void setup() {
  motorRight.attach(9);  // attaches the servo on pin 9 to the servo object
  motorLeft.attach(10);
}

void loop() {
  footSensorFront_value = analogRead(footSensorFront_pin);  // reads the value of the potentiometer (value between 0 and 1023)
  footSensorRear_value = analogRead(footSensorRear_pin);
  if(footSensorFront_value >= threshold || footSensorRear_value >=threshold){
    val = footSensorFront_value - footSensorRear_value;
    if (val > 0){
      val = map(val, 0, 1023, 90, 0);     // scale it to use it with the servo (value between 0 and 180)
      motorRight.write(val);                  // sets the servo position according to the scaled value
      motorLeft.write(-val);     
    }else{
      val = map(val, 0, 1023, 180, 90);     // scale it to use it with the servo (value between 0 and 180)
      motorRight.write(val);                  // sets the servo position according to the scaled value
      motorLeft.write(-val); 
    }
  }
  delay(15);                           // waits for the servo to get there
}
