#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

const int IR1_PIN = D2;
const int IR2_PIN = D3;
const int IR3_PIN = D4;
const int TRIG_IN = D5;
const int ECHO_IN = D6;
const int TRIG_OUT = D7;
const int ECHO_OUT = D8;
const int SERVO_IN_PIN = D9;
const int SERVO_OUT_PIN = D10;
const int LED1_PIN = PC6;
const int LED2_PIN = PA6;
const int LED3_PIN = PA7;

LiquidCrystal lcd(D11, D12, PA0, PA1, PA4, PB0);
Servo gateIn;
Servo gateOut;

long readDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH, 30000UL);
  if (duration == 0) return 999;
  return (long)(duration * 0.0343 / 2.0);
}

void setup() {
  pinMode(IR1_PIN, INPUT_PULLUP);
  pinMode(IR2_PIN, INPUT_PULLUP);
  pinMode(IR3_PIN, INPUT_PULLUP);
  pinMode(TRIG_IN, OUTPUT);
  pinMode(ECHO_IN, INPUT);
  pinMode(TRIG_OUT, OUTPUT);
  pinMode(ECHO_OUT, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  gateIn.attach(SERVO_IN_PIN);
  gateOut.attach(SERVO_OUT_PIN);
  gateIn.write(0);
  gateOut.write(0);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART PARKING");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1000);
}

void loop() {
  bool occ1 = digitalRead(IR1_PIN) == LOW;
  bool occ2 = digitalRead(IR2_PIN) == LOW;
  bool occ3 = digitalRead(IR3_PIN) == LOW;

  digitalWrite(LED1_PIN, occ1);
  digitalWrite(LED2_PIN, occ2);
  digitalWrite(LED3_PIN, occ3);

  int occupied = (int)occ1 + (int)occ2 + (int)occ3;
  int freeSlots = 3 - occupied;

  long distIn = readDistanceCM(TRIG_IN, ECHO_IN);
  long distOut = readDistanceCM(TRIG_OUT, ECHO_OUT);

  if (distIn < 15 && freeSlots > 0) gateIn.write(90);
  else if (distIn > 25) gateIn.write(0);

  if (distOut < 15) gateOut.write(90);
  else if (distOut > 25) gateOut.write(0);

  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(occ1 ? "FULL " : "FREE ");
  lcd.print("S2:");
  lcd.print(occ2 ? "FULL" : "FREE");

  lcd.setCursor(0, 1);
  lcd.print("S3:");
  lcd.print(occ3 ? "FULL " : "FREE ");
  lcd.print(" F:");
  lcd.print(freeSlots);
  lcd.print("   ");
  delay(100);
}