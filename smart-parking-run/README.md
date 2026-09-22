BẢN CHẠY WOKWI - SMART PARKING

1. Mở: https://wokwi.com/projects/new/st-nucleo-c031c6
2. Trong project mới, mở diagram.json và thay toàn bộ bằng file diagram.json trong thư mục này.
3. Mở sketch.ino và thay toàn bộ bằng file sketch.ino trong thư mục này.
4. Nhấn nút Play.

Sơ đồ mô phỏng:
- NUCLEO C031C6
- 3 module cảm biến 4 chân (mô phỏng bằng photoresistor sensor VCC/GND/DO/AO)
- 3 LED đỏ + R220
- 2 HC-SR04
- 2 servo
- LCD1602 16x2

Pin:
IR1 DO=PC6, IR2 DO=PC7, IR3 DO=PC8
LED1=PB0, LED2=PB1, LED3=PB2
HC-SR04 vào D2/D3
HC-SR04 ra D4/D5
Servo vào PA8
Servo ra PB8
LCD RS=PA6, E=PA7, D4=PB10, D5=PB4, D6=PB5, D7=PA5
