/*

  This example shows how to connect to an EBYTE transceiver
  using an Arduino Nano

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
  unsigned long Count;
  int Bits;
  float Volts;
  float Amps;  
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
  Serial.println("Starting Reader");

  // this init will set the pinModes for you
  Transceiver.init();

  // all these calls are optional but shown to give examples of what you can do

  // Serial.println(Transceiver.GetAirDataRate());
  // Serial.println(Transceiver.GetChannel());

  // Transceiver.SetAddressH(1);
  // Transceiver.SetAddressL(0);
  // Chan = 5;
  // Transceiver.SetChannel(Chan);
  // save the parameters to the unit,
  // Transceiver.SaveParameters(PERMANENT);

  // you can print all parameters and is good for debugging
  // if your units will not communicate, print the parameters
  // for both sender and receiver and make sure air rates, channel
  // and address is the same
  // Transceiver.PrintParameters();


}

void loop() {

  // if the transceiver serial is available, proces incoming data
  // you can also use Transceiver.available()


  if (ESerial.available()) {

    // i highly suggest you send data using structures and not
    // a parsed data--i've always had a hard time getting reliable data using
    // a parsing method

    Transceiver.GetStruct(&MyData, sizeof(MyData));

    // dump out what was just received
    Serial.print("Message: "); Serial.println(MyData.input);
//    Serial.print("Bits: "); Serial.println(MyData.Bits);
//    Serial.print("Volts: "); Serial.println(MyData.Volts);

  }
}
