# CO2_Meter  

[ESP32](https://www.eleparts.co.kr/EPXRVLBX) 개발보드와 [MH-Z14A](https://www.eleparts.co.kr/goods/view?no=3186568) CO2 센서, [LCD1602 RGB Module](https://www.eleparts.co.kr/goods/view?no=10488490)를 사용해 CO2 측정기를 제작하는 예제입니다.  

[![샘플 이미지+유튜브 바로가기](https://raw.githubusercontent.com/eleparts/CO2_Meter/main/img/CO2_meter_sampel.jpg)](https://www.youtube.com/watch?v=iwCHd-AVvbM)  
(이미지를 누르면 유튜브로 이동됩니다)  

※ 위 샘플 이미지의 LCD는 대체품 [DFR0464](https://www.eleparts.co.kr/EPXV6B3U)을 사용하였습니다.  

## 사용법  

1. 아두이노 IDE에 ESP32 보드를 추가  
**환경설정** 메뉴의 보드매니저 URL 추가를 이용해 ESP32 보드를 추가해 줍니다.
```https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json```

2. 라이브러리 설치하기  
Library 경로 내부에 있는 두개의 라이브러리 파일 (각 경로 내부의 압축된 zip 파일)을 아두이노 IDE에 추가 해 줍니다.  

3. 회로 연결하기  
![회로도](https://raw.githubusercontent.com/eleparts/CO2_Meter/main/img/CO2_Meter.png)  
※ CO2센서의 UART핀을 사용하며, 센서에 핀헤더를 납땜해 주어야 합니다.  

4. example 내부의 예제 코드를 ESP32 보드에 업로드 해 줍니다.  

## 참고자료  

### 엘레파츠 블로그  

[ESP32와 CO2 센서로 이산화탄소 농도 측정기 만들기](https://blog.naver.com/elepartsblog/223046208897)  

### 구성품 BOM  

[기본 구성: Waveshare 1602 RGB LCD 사용](https://www.eleparts.co.kr/bom/share?pj_seq=5CGDR8JY5&hseq=0OKBT2Y2)  

[대체 LCD 구성: DFR0464 LCD 사용](https://www.eleparts.co.kr/bom/share?pj_seq=U1ZRM5JY5&hseq=PTGMB8Y2)  
