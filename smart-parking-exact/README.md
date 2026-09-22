# He thong bai do xe thong minh - redraw theo anh tham chieu

Bo linh kien va bo tri duoc ve lai theo anh: NUCLEO-C031C6, 3 module cam bien 4 chan, 3 LED + R 220R, 2 HC-SR04, 2 servo, LCD1602 va breadboard.

Wokwi hien khong co part FC-51/LM393 dung hinh dang module trong anh; phan cam bien duoc mo phong bang wokwi-photoresistor-sensor 4 chan (VCC/GND/DO/AO), giu dung kieu ket noi 4 chan va giao dien module gan tuong tu.

Pin map:
IR1 DO=D2 AO=A0
IR2 DO=D3 AO=A1
IR3 DO=D4 AO=A2
LED1/2/3=D5/D6/D7
ENTRY HC-SR04=D8/D9
EXIT HC-SR04=D10/D11
SERVO IN/OUT=D12/D13
LCD1602: RS=A3, E=A4, D4=A5, D5=D0, D6=D1, D7=D14
