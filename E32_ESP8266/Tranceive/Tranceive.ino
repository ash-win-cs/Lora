/*

  This example shows how to connect to an EBYTE transceiver
  using an ESP8266

  This code for for the sender


  connections
  Module      Teensy
  M0          4
  M1          5
  Rx          2 (MCU Tx line)
  Tx          3 (MCU Rx line)
  Aux         6
  Vcc         3V3
  Gnd         Gnd

*/

#include <SoftwareSerial.h>
#include "EBYTE.h"

#define PIN_RX D3
#define PIN_TX D2
#define PIN_M0 D7
#define PIN_M1 D6
#define PIN_AX D5


// i recommend putting this code in a .h file and including it
// from both the receiver and sender modules
struct DATA {
  String names;  
  String input;
};

// these are just dummy variables, replace with your own
int Chan;
DATA MyData;
unsigned long Last;

// connect to any digital pin to connect to the serial port
// don't use pin 01 and 1 as they are reserved for USB communications
SoftwareSerial ESerial(PIN_RX, PIN_TX);

// create the transceiver object, passing in the serial and pins
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  Serial.begin(9600);
  ESerial.begin(9600);

  // this init will set the pinModes for you
  Transceiver.init();
//  MyData.names = 'CS';
//  
//  MyData.names += ':';
}

void loop() {

  // if the transceiver serial is available, proces incoming data
  // you can also use Transceiver.available()


  if (ESerial.available()) {
    Transceiver.GetStruct(&MyData, sizeof(MyData));

    // dump out what was just received
    Serial.print("RR: "); Serial.println(MyData.input);
  }
 else if(Serial.available()){
    MyData.input = Serial.readString();
    Transceiver.SendStruct(&MyData, sizeof(MyData));
    Serial.print("ME:"); Serial.println(MyData.input);
 }
}
