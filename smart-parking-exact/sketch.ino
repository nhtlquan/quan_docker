#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

const int IR1_DO = D2, IR2_DO = D3, IR3_DO = D4;
const int IR1_AO = A0, IR2_AO = A1, IR3_AO = A2;
const int LED1 = D5, LED2 = D6, LED3 = D7;
const int TRIG_IN = D8, ECHO_IN = D9, TRIG_OUT = D10, ECHO_OUT = D11;
const int SERVO_IN = D12, SERVO_OUT = D13;

LiquidCrystal lcd(A3, A4, A5, D0, D1, D14);
Servo gateIn, gateOut;

long distanceCm(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long t = pulseIn(echoPin, HIGH, 30000UL);
  if (!t) return -1;
  return (long)(t / 58UL);
}

bool occupied(int pin) { return digitalRead(pin) == LOW; }

void updateDisplay(bool s1, bool s2, bool s3) {
  int freeSlots = (!s1) + (!s2) + (!s3);
  lcd.setCursor(0,0);
  lcd.print("S1:"); lcd.print(s1 ? "FULL " : "FREE ");
  lcd.print("S2:"); lcd.print(s2 ? "FULL" : "FREE");
  lcd.setCursor(0,1);
  lcd.print("S3:"); lcd.print(s3 ? "FULL " : "FREE ");
  lcd.print("F:"); lcd.print(freeSlots);
  lcd.print("    ");
}

void setup() {
  pinMode(IR1_DO, INPUT); pinMode(IR2_DO, INPUT); pinMode(IR3_DO, INPUT);
  pinMode(LED1, OUTPUT); pinMode(LED2, OUTPUT); pinMode(LED3, OUTPUT);
  pinMode(TRIG_IN, OUTPUT); pinMode(ECHO_IN, INPUT);
  pinMode(TRIG_OUT, OUTPUT); pinMode(ECHO_OUT, INPUT);

  gateIn.attach(SERVO_IN); gateOut.attach(SERVO_OUT);
  gateIn.write(0); gateOut.write(0);

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("SMART PARKING");
  lcd.setCursor(0,1); lcd.print("SYSTEM READY");
  delay(1200);
}

void loop() {
  bool s1 = occupied(IR1_DO), s2 = occupied(IR2_DO), s3 = occupied(IR3_DO);

  digitalWrite(LED1, s1);
  digitalWrite(LED2, s2);
  digitalWrite(LED3, s3);
  updateDisplay(s1,s2,s3);

  long dIn = distanceCm(TRIG_IN,ECHO_IN);
  long dOut = distanceCm(TRIG_OUT,ECHO_OUT);
  int freeSlots = (!s1) + (!s2) + (!s3);

  if (dIn > 0 && dIn < 20 && freeSlots > 0) gateIn.write(90);
  else if (dIn < 0 || dIn > 30) gateIn.write(0);

  if (dOut > 0 && dOut < 20) gateOut.write(90);
  else if (dOut < 0 || dOut > 30) gateOut.write(0);

  delay(100);
}