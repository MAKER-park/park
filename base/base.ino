/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
          == Base/ Master Node 00==
  by Dejan, www.HowToMechatronics.com
  Libraries:
  nRF24/RF24, https://github.com/nRF24/RF24
  nRF24/RF24Network, https://github.com/nRF24/RF24Network
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

#define button 2
#define led 3

RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;      // Address of the other node in Octal format
const uint16_t node012 = 012;
const uint16_t node022 = 022;

void setup() {
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
}

void loop() {
  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    unsigned long incomingData;
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    Serial.println(incomingData);
  }
  //===== Sending =====//
  // Servo control at Node 01
  unsigned long potValue = analogRead(A0);
  unsigned long angleValue = map(potValue, 0, 1023, 0, 180); // Suitable for servo control
  RF24NetworkHeader header2(node01);     // (Address where the data is going)
  bool ok = network.write(header2, &angleValue, sizeof(angleValue)); // Send the data

  // LED Control at Node 012
  unsigned long buttonState = digitalRead(button);
  RF24NetworkHeader header4(node012);    // (Address where the data is going)
  bool ok3 = network.write(header4, &buttonState, sizeof(buttonState)); // Send the data

  // LEDs control at Node 022
  unsigned long pot2Value = analogRead(A1);
  RF24NetworkHeader header3(node022);    // (Address where the data is going)
  bool ok2 = network.write(header3, &pot2Value, sizeof(pot2Value)); // Send the data
}
