/*
 Name:		VescUartSample.ino
 Created:	9/26/2015 10:12:38 PM
 Author:	AC
*/

// the setup function runs once when you press reset or power the board
// To use VescUartControl stand alone you need to define a config.h file, that should contain the Serial or you have to comment the line
// #include Config.h out in VescUart.h
// This lib version tested with vesc fw 3.38 and 3.40 on teensy 3.2 and arduino uno

//Include libraries copied from VESC
#include "VescUart.h"

#define DEBUG 
#define SERIALIO SoftwareSerial(8,7) 
#define DEBUGSERIAL Serial // usb serial

unsigned long count;
struct bldcMeasure measuredVal;

void setup() {

  DDRB |= _BV(5);
	
	//Setup UART port
	SERIALIO.begin(115200);
	SetSerialPort(&SERIALIO);
	SERIALIO.listen();

	//Setup debug port
	#ifdef DEBUG
		DEBUGSERIAL.begin(115200);
		SetDebugSerialPort(&DEBUGSERIAL);
	#endif

  PORTB |= _BV(5);
}

void loop() {
	DEBUGSERIAL.print("Loop: "); DEBUGSERIAL.println(count++);
  DEBUGSERIAL.flush();
	if (VescUartGetValue(measuredVal)) {
		//SerialPrint(measuredVal, &DEBUGSERIAL);
		VescUartSetDuty(0.3, &SERIALIO);
    PORTB |= _BV(5);
	}else{
		DEBUGSERIAL.println("Failed to get data!");
    PORTB &= ~_BV(5);
	}
	delay(250);
}
