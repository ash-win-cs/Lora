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

// these are just dummy variables, replace with your own
struct DATA {
  char names;
  String input;
};

int Chan;
DATA MyData;

// you will need to define the pins to create the serial port
SoftwareSerial ESerial(PIN_RX, PIN_TX);


// create the transceiver object, passing in the serial and pins
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {

  Serial.begin(9600);

  // start the transceiver serial port--i have yet to get a different
  // baud rate to work--data sheet says to keep on 9600
  ESerial.begin(9600);

  Serial.println("Starting Sender");

  // this init will set the pinModes for you
  Transceiver.init();
  MyData.names = "RR";

}

void loop() {
  if (Serial.available()) {
    MyData.input = Serial.readString();
    Transceiver.SendStruct(&MyData, sizeof(MyData));
    Serial.print("Sending: "); Serial.println(MyData.input);
  }


}
