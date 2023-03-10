/*
* ESP32 CO2 Meter - MH-Z14A + 1602 RGB LCD 동작 예제
* CO2센서의 측정값을 LCD로 출력하는 예제입니다.
* 
* CO2 ppm - LCD 색상 (Lv 1~7)
* 0~450,  ~700, ~1000,  ~1500, ~2000,  ~3000, ~10000(MAX)
* 파랑색, 하늘색,  녹색, 노랑색, 주황색, 빨간색, 보라색
*
* MH-Z14A : ESP32
* VCC     : 5V
* GND     : GND
* UART(Rx): Pin 17 (Tx2 - UART2) 
* UART(Tx): Pin 16 (Rx2 - UART2) 
* 
* 1602 LCD: ESP32
* VCC     : 5V / 3.3V
* GND     : GND
* SCL     : GPIO 22 (I2C_SCL)
* SDA     : GPIO 21 (I2C_SDA)
*
* 엘레파츠 - MH-Z14A NDIR 방식 CO2 센서 모듈
* https://www.eleparts.co.kr/EPXF8W33
*
* 엘레파츠 - LCD1602 RGB Module 
* https://www.eleparts.co.kr/EPXVXRJH
* 
* 엘레파츠 - ESP32 개발보드
* https://www.eleparts.co.kr/EPXRVLBX
*/
#include <MHZ.h>
#include "Waveshare_LCD1602_RGB.h"

MHZ co2(Serial2, MHZ14A);         // MHZ14A Hw serial 설정
Waveshare_LCD1602_RGB lcd(16,2);  // 1602 I2C LCD 설정 / I2C Pin - SCL: 22 / SDA: 21

int co2_ppm = 0;
char co2_ppm_str[100] = {0,};
int co2_level = 0, print_co2_level = 0;

void setup() 
{
  Serial.begin(115200);                 // PC 시리얼 통신 설정 / 보드레이트: 115200
  Serial.println("Enable UATRT0 (PC)");   
  delay(200); 
  
  Serial2.begin(9600);                  // MHZ14A 시리얼 통신 / 보드레이트: 9600
  // co2.setDebug(true);                // 디버그 정보 표시
  Serial.println("Enable UATRT2 (MHZ14A)");
  delay(200);

  lcd.init();                           // LCD 설정, 화면 출력
  lcd.setColorWhite();
  Serial.println("Enable 1608 RGB LCD");
  delay(200);

  // 센서 예열 대기 - MHZ14A 1분
  if (co2.isPreHeating()) {
    Serial.print("Preheating 60s");
    lcd.setCursor(0,0);
    lcd.send_string("Preheating");
    lcd.setCursor(0,1);
    lcd.send_string("Wait 60s");
    while (co2.isPreHeating()) {
      Serial.print(".");
      delay(1000);
    }
    Serial.println();
  } // 삭제 하면 바로 센서 데이터 수신 가능 (단, 예열 시간 동안 측정 정확도가 보장되지 않음)

  // 설정 및 초기화, 센서 예열 종료, 반복 측정 시작
  Serial.println("Start CO2 Sensor!!!");
  lcd.clear();
}

void loop() {

  // CO2 값 읽어오기 
  co2_ppm = co2.readCO2UART();  // CO2 센서 값 읽어오기

  co2_level = AlarmLevelSet(co2_ppm);       // CO2 레벨 계산
  AlarmLcdColorSet(co2_level);              // LCD 색상 설정

  print_co2_level = co2_level + 1;          // 출력용 레벨 수정 0~6 -> 1~7;

  // LCD에 ppm 값 출력 - 1열
  lcd.setCursor(0,0);
  lcd.send_string("CO2 :");
  lcd.setCursor(13,0);
  lcd.send_string("ppm");
  sprintf(co2_ppm_str, " %d ", co2_ppm);    // ppm 수치 문자열로 변경, 앞 뒤 공백 추가
  lcd.setCursor(6,0);
  lcd.send_string(co2_ppm_str);
  
  // LCD에 레벨 값 출력 - 2열
  lcd.setCursor(0,1);
  lcd.send_string("CO2 LEVEL : ");
  lcd.write_char((print_co2_level+'0'));          // char 출력 아스키 코드 변환(int to char): ('0'== 48)+(int 0~9) = '0'~'9' 

  // PC에 CO2 값 전송
  Serial.println("CO2 : " + String(co2_ppm) + " ppm | Level : " + String(print_co2_level));  
  
  // 5초 지연
  delay(5000);  
}



// CO2 LEVEL 계산 함수 (7단계 (0~6)) 
int AlarmLevelSet(int CO2ppm){

  // 각 농도 범위 (0~450, 450~700, 700~1000, 1000~1500...)설정을 위한 배열
  int alarmLevel[8]={0,450,700,1000,1500,2000,3000,10000};

  // CO2 ppm 값에따라 낮은 ppm부터 검사하여 범위에 해당하면 레벨 리턴 후 종료
  for(int alarmLevelCnt = 0; alarmLevelCnt < 7; alarmLevelCnt++){
    if(alarmLevel[alarmLevelCnt] <= CO2ppm && CO2ppm < alarmLevel[(alarmLevelCnt+1)]){

      return alarmLevelCnt; 
    }
  }
  return -1;
}

// LCD 색상 설정 함수
int AlarmLcdColorSet(int co2_level){

  // 파랑색,하늘색,녹색,노랑색,주황색,빨간색,보라색
  int alarmColor[7][3]={{0,0,255},{0,255,255},{0,255,0},{255,255,0},{255,128,0},{255,0,0},{255,0,255}};

  lcd.setRGB(alarmColor[co2_level][0],alarmColor[co2_level][1],alarmColor[co2_level][2]); 

  return 0;
}



