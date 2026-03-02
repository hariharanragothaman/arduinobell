#include <Arduino.h>
#include <LiquidCrystal.h>
#include "rtc.h"
#include "display.h"
#include "bell_schedule.h"

static const uint8_t BELL_PIN = A0;  // Pin 14 (analog 0) drives the relay

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  pinMode(BELL_PIN, OUTPUT);
  digitalWrite(BELL_PIN, LOW);

  Serial.begin(9600);
  rtcInit();
  displayInit(lcd);
}

void loop() {
  uint8_t second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  rtcGetDateTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth,
                 &month, &year);

  displayTime(lcd, hour, minute, second);

  Serial.print(hour, DEC);
  Serial.print(':');
  Serial.print(minute, DEC);
  Serial.print(':');
  Serial.print(second, DEC);
  Serial.print(' ');
  Serial.print(month, DEC);
  Serial.print('/');
  Serial.print(dayOfMonth, DEC);
  Serial.print('/');
  Serial.println(year, DEC);

  bool ringing = shouldRingBell(hour, minute, second);
  digitalWrite(BELL_PIN, ringing ? HIGH : LOW);
  displayStatus(lcd, ringing);

  delay(1000);
}
