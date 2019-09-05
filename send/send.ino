// RF 통신을 위한 라이브러리 추가
#include <SPI.h>
#include <RF24.h>

// 핀 번호 설정
#define PIN_CE 9
#define PIN_CSN 10

RF24 myRF24(PIN_CE, PIN_CSN);
const uint64_t pipe = 0x0000000000000001;

void setup() {
  myRF24.begin();
  // RF24 초기화 및 송신기능으로 설정
  myRF24.openWritingPipe(pipe);
  myRF24.setPALevel(RF24_PA_MIN);
  myRF24.stopListening();
}

void loop() {
  int data = analogRead(A0);
  myRF24.write(&data, sizeof(data));
}
