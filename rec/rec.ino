// RF 통신을 위한 라이브러리 추가
#include <SPI.h>
#include <RF24.h>
 
// 핀 번호 설정
#define PIN_CE 9
#define PIN_CSN 10
 
// myRF24 이름으로 RF24 클래스 생성
RF24 myRF24(PIN_CE, PIN_CSN);
const uint64_t pipe = 0x0000000000000001;
 
void setup() {
  // 시리얼 통신 초기화
  Serial.begin(9600);
  // RF24 초기화 및 수신기능으로 설정
  myRF24.begin();
  myRF24.openReadingPipe(0, pipe);
  myRF24.setPALevel(RF24_PA_MIN);
  myRF24.startListening();
}

void loop() {
  // 모듈로부터 데이터가 수신되면
  if(myRF24.available()) {
    int data;
    myRF24.read(&data, sizeof(data));
    Serial.println(data);
  }
}
