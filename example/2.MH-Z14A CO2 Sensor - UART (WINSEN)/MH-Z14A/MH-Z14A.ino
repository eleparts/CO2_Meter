/*
* ESP32 CO2 Meter - MH-Z14A 동작 예제
* MH-Z14A의 간단한 기능 테스트 예제입니다.
* 
* MH-Z14A : ESP32
* VCC     : 5V
* GND     : GND
* UART(Rx): Pin 17 (Tx2 - UART2) 
* UART(Tx): Pin 16 (Rx2 - UART2) 
* 
* 엘레파츠 - MH-Z14A NDIR 방식 CO2 센서 모듈
* https://www.eleparts.co.kr/EPXF8W33
* 
* 엘레파츠 - ESP32 개발보드
* https://www.eleparts.co.kr/EPXRVLBX
*/
#include <MHZ.h>

MHZ co2(Serial2, MHZ14A);   // MHZ14A Hw serial 설정

void setup() {
  Serial.begin(115200);
  
  // Use HW serial - UART2
  Serial2.begin(9600);  // ESP32 uart2 - Pin Rx: 16 / Tx: 17  

  // 센서 측정 범위 변경 (2k, 5k, 10k)
  // co2.setRange(RANGE_5K);

  delay(100);
  Serial.println("MHZ 14A");

  // 디버그 정보 표시
  // co2.setDebug(true);
 
  // 센서 예열 대기 - MHZ14A 1분
  if (co2.isPreHeating()) {
    Serial.print("Preheating");
    while (co2.isPreHeating()) {
      Serial.print(".");
      delay(2000);
    }
    Serial.println();
  } // 주석(삭제) 하면 바로 센서 데이터 수신 가능 (단, 예열 시간동안 측정 정확도가 보장되지 않음)
}

void loop() {
  Serial.print("Time from start: ");
  Serial.print(millis() / 1000);
  Serial.println(" s");

  // UART
  int ppm_uart = co2.readCO2UART();
  Serial.print("CO2 : ");

  if (ppm_uart > 0) {
    Serial.println(String(ppm_uart) + "ppm");
  } else {
    Serial.println("n/a");
  }

  delay(2000);
}
