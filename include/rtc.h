#ifndef RTC_H
#define RTC_H

#include <Wire.h>
#include <stdint.h>

#define DS1307_I2C_ADDRESS 0x68

inline uint8_t decToBcd(uint8_t val) {
  return (val / 10 * 16) + (val % 10);
}

inline uint8_t bcdToDec(uint8_t val) {
  return (val / 16 * 10) + (val % 16);
}

inline void rtcInit() {
  Wire.begin();
}

inline void rtcStop() {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((uint8_t)0);
  Wire.write((uint8_t)0x80);
  Wire.endTransmission();
}

inline void rtcSetDateTime(uint8_t second, uint8_t minute, uint8_t hour,
                           uint8_t dayOfWeek, uint8_t dayOfMonth,
                           uint8_t month, uint8_t year) {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((uint8_t)0);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

inline void rtcGetDateTime(uint8_t *second, uint8_t *minute, uint8_t *hour,
                           uint8_t *dayOfWeek, uint8_t *dayOfMonth,
                           uint8_t *month, uint8_t *year) {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((uint8_t)0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  *second     = bcdToDec(Wire.read() & 0x7F);
  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3F);
  *dayOfWeek  = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month      = bcdToDec(Wire.read());
  *year       = bcdToDec(Wire.read());
}

#endif
