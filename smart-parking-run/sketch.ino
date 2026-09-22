#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

const uint8_t S1 = PC6;
const uint8_t S2 = PC7;
const uint8_t S3 = PC8;

const uint8_t LED1 = PB0;
const uint8_t LED2 = PB1;
const uint8_t LED3 = PB2;

const uint8_t TRIG_IN = D2;
const uint8_t ECHO_IN = D3;
const uint8_t TRIG_OUT = D4;
const uint8_t ECHO_OUT = D5;

const uint8_t SERVO_IN = PA8;
const uint8_t SERVO_OUT = PB8;

LiquidCrystal lcd(PA6, PA7, PB10, PB4, PB5, PA5);
Servo gateIn, gateOut;

long distanceCM(uint8_t trig, uint8_t echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  unsigned long t = pulseIn(echo, HIGH, 30000UL);
  if (!t) return 999;
  return t / 58;
}

void setup() {
  Serial.begin(115200);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(TRIG_IN, OUTPUT);
  pinMode(ECHO_IN, INPUT);
  pinMode(TRIG_OUT, OUTPUT);
  pinMode(ECHO_OUT, INPUT);

  gateIn.attach(SERVO_IN);
  gateOut.attach(SERVO_OUT);
  gateIn.write(0);
  gateOut.write(0);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART PARKING");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM READY");
  delay(1200);
}

void loop() {
  // DO of the simulated LM393/LDR module is LOW when active.
  bool slot1 = digitalRead(S1) == LOW;
  bool slot2 = digitalRead(S2) == LOW;
  bool slot3 = digitalRead(S3) == LOW;

  digitalWrite(LED1, slot1 ? HIGH : LOW);
  digitalWrite(LED2, slot2 ? HIGH : LOW);
  digitalWrite(LED3, slot3 ? HIGH : LOW);

  int freeSlots = (!slot1) + (!slot2) + (!slot3);

  long dIn = distanceCM(TRIG_IN, ECHO_IN);
  long dOut = distanceCM(TRIG_OUT, ECHO_OUT);

  if (dIn < 20 && freeSlots > 0) gateIn.write(90);
  else if (dIn > 30) gateIn.write(0);

  if (dOut < 20) gateOut.write(90);
  else if (dOut > 30) gateOut.write(0);

  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(slot1 ? "FULL " : "FREE ");
  lcd.print("S2:");
  lcd.print(slot2 ? "FULL" : "FREE");

  lcd.setCursor(0, 1);
  lcd.print("S3:");
  lcd.print(slot3 ? "FULL " : "FREE ");
  lcd.print("F:");
  lcd.print(freeSlots);
  lcd.print("   ");

  delay(100);
}