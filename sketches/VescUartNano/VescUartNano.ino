/*
 Name:        VescUartSample.ino
 Created:    9/26/2015 10:12:38 PM
 Author:    AC
*/

// the setup function runs once when you press reset or power the board
// To use VescUartControl stand alone you need to define a config.h file, that
// should contain the Serial or you have to comment the line
// #include Config.h out in VescUart.h
// This lib version tested with vesc fw 3.38 and 3.40 on teensy 3.2 and arduino
// uno

// Include libraries copied from VESC
#include "VescUart.h"

#define DEBUG
#define S_SERIAL SoftwareSerial(8, 7)
#define H_SERIAL Serial  // usb serial

unsigned long count;
struct bldcMeasure measuredVal;

void setup()
{
    DDRB |= _BV(5);  // Setup LED I/O

    // Setup UART port
    S_SERIAL.begin(115200);
    SetSerialPort(&S_SERIAL);
    S_SERIAL.listen();

// Setup debug port
#ifdef DEBUG
    H_SERIAL.begin(115200);
    SetDebugSerialPort(&H_SERIAL);
#endif

    PORTB |= _BV(5);  // LED On
}

void loop()
{
    H_SERIAL.print("Loop: ");
    H_SERIAL.println(count++);
    H_SERIAL.flush();
    if (VescUartGetValue(measuredVal))
    {
        // SerialPrint(measuredVal, &H_SERIAL);
        VescUartSetDuty(0.3, &S_SERIAL);
        PORTB |= _BV(5);
    }
    else
    {
        H_SERIAL.println("Failed to get data!");
        PORTB &= ~_BV(5);  // LED Off
    }
    delay(250);
}
