#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// Set the CE & CSN pins
#define CE_PIN   9
#define CSN_PIN 10
 
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xF0F0F0F011LL;
 
// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); 
 
// CHANGE THIS PER EACH TRANSMITTER, from 0 to 2
float transmitterId[2];

 
void setup() {
 

  // Start up the Serial connection
  while (!Serial);
  Serial.begin(9600);
  
  // Start the Radio!
  radio.begin();
  
  // Power setting
  radio.setPALevel(RF24_PA_HIGH); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  
  // Slower data rate for better range
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  
  // Stop listening, so we can send!
  radio.stopListening();
  
  // Number of retries
  radio.setRetries(15, 15);
 
  radio.openWritingPipe(pipe);
 
}
 
void loop() {

  transmitterId[0] = 2;//id
  transmitterId[1] = 150;//data

    radio.write(transmitterId, sizeof(transmitterId));
    Serial.println(transmitterId[0]);
    Serial.println(transmitterId[1]);
  // Wait a short while before sending the other one
  delay(100);
 
}
