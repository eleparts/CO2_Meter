/*
* ESP32 CO2 Meter - 1602 RGB LCD 동작 예제
* 1602 RGB LCD의 간단한 기능 테스트 예제입니다.
* 
* 1602 LCD: ESP32
* VCC     :   5V / 3.3V
* GND     :   GND
* SCL     :   GPIO 22 (I2C_SCL)
* SDA     :   GPIO 21 (I2C_SDA)
* 
* 엘레파츠 - LCD1602 RGB Module 
* https://www.eleparts.co.kr/EPXVXRJH
* 
* 엘레파츠 - ESP32 개발보드
* https://www.eleparts.co.kr/EPXRVLBX
*/
#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"

Waveshare_LCD1602_RGB lcd(16,2);  // 1602 I2C LCD 설정 / I2C Pin - SCL: 22 / SDA: 21 

// 색상 값 지정 - 파랑색,하늘색,녹색,노랑색,주황색,빨간색,보라색
int Color[7][3]={{0,0,255},{0,255,255},{0,255,0},{255,255,0},{255,128,0},{255,0,0},{255,0,255}};

void setup() {

  lcd.init();
  
  // 첫째줄 문자 출력
  lcd.setCursor(0,0);
  lcd.send_string("Hello World!!!");

  // 둘째줄 문자 출력
  lcd.setCursor(0,1);
  lcd.send_string("1602 RGB LCD");
  
  // 1초씩 R/G/B/W 색상 출력
  lcd.setRGB(255,0,0);      // Red
  delay(1000);
  lcd.setRGB(0,255,0);      // Blue
  delay(1000);
  lcd.setRGB(0,0,255);      // Green
  delay(1000);
  lcd.setRGB(255,255,255);  // White
  delay(1000);
  
}

void loop() {

  // 파랑색,하늘색,녹색,노랑색,주황색,빨간색,보라색 - 1초 마다 변경
  for(int i = 0; i<7; i++)
  {
    lcd.setRGB(Color[i][0],Color[i][1],Color[i][2]);
    delay(1000);
  }

  delay(1000);  // 7번 변경 완료 후 1초 추가 지연

}
