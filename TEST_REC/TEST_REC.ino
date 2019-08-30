//recvier

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// define the pins
#define CE_PIN   9
#define CSN_PIN 10
 
// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); 
 
// Single radio pipe address for the 2 nodes to communicate.
//const byte rxAddr[6] = "00001";
const uint64_t pipe = 0xF0F0F0F011LL;
const uint64_t pipe1 = 0xF0F0F0F011AA;
float incomedata[2];
 
void setup()
{
  // Start the serial
  Serial.begin(9600);
  Serial.println("NRF24L01P Receiver Starting...");
  
  // Start the radio.
  radio.begin();
  // Power setting
  radio.setPALevel(RF24_PA_HIGH);   // RF24_PA_MIN ,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  
  // Set the reading pipe and start listening
  radio.openReadingPipe(0, pipe);
  radio.openReadingPipe(1, pipe1);

  radio.startListening();
  
}
 
void loop()
{
  if (radio.available())
  {

    // the buffer to store the received message in
//    char senderId[10] = {0};
    
    radio.read(incomedata,sizeof(incomedata));

    /*// Print the message out to the COM window
    Serial.print("id: ");
    Serial.println(incomedata[0]);
    Serial.print("data: ");
    Serial.println(incomedata[1]);*/
    if(incomedata[0] == 1){
      Serial.print ("node 01 data : ");
      Serial.println(incomedata[1]); 
    }
    if(incomedata[0] == 2){
      Serial.print ("node 02 data : ");
      Serial.println(incomedata[1]); 
    }
  }
}
