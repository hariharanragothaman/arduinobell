#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include <stdint.h>

static const uint8_t LCD_RS = 4;
static const uint8_t LCD_EN = 7;
static const uint8_t LCD_D4 = 8;
static const uint8_t LCD_D5 = 9;
static const uint8_t LCD_D6 = 12;
static const uint8_t LCD_D7 = 13;

static const uint8_t LCD_COLS = 16;
static const uint8_t LCD_ROWS = 2;

inline void displayInit(LiquidCrystal &lcd) {
  lcd.begin(LCD_COLS, LCD_ROWS);
}

inline void displayTime(LiquidCrystal &lcd,
                        uint8_t hour, uint8_t minute, uint8_t second) {
  lcd.setCursor(0, 0);

  if (hour < 10) lcd.print('0');
  lcd.print(hour, DEC);
  lcd.print(':');
  if (minute < 10) lcd.print('0');
  lcd.print(minute, DEC);
  lcd.print(':');
  if (second < 10) lcd.print('0');
  lcd.print(second, DEC);
}

inline void displayStatus(LiquidCrystal &lcd, bool ringing) {
  lcd.setCursor(0, 1);
  if (ringing) {
    lcd.print("BELL RINGING    ");
  } else {
    lcd.print("                ");
  }
}

#endif
