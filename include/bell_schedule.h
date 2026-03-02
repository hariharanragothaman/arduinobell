#ifndef BELL_SCHEDULE_H
#define BELL_SCHEDULE_H

#include <stdint.h>

struct BellEvent {
  uint8_t hour;
  uint8_t minute;
  uint8_t duration_seconds;
};

// Default school bell schedule (24-hour format).
// Edit this array to customize bell times for your institution.
static const BellEvent BELL_SCHEDULE[] = {
  { 8, 10, 40},  // Morning assembly
  { 8, 30, 20},  // Period 1 start
  { 9, 30, 20},  // Period 2 start
  {10, 30, 20},  // Period 3 start
  {11, 30, 20},  // Period 4 start
  {12, 10, 20},  // Lunch break
  {13, 10, 20},  // Period 5 start
  {14, 10, 20},  // Period 6 start
  {14, 30, 20},  // Short break
  {15, 30, 20},  // Period 7 start
  {16, 30, 20},  // Dismissal
};

static const uint8_t BELL_SCHEDULE_COUNT =
    sizeof(BELL_SCHEDULE) / sizeof(BELL_SCHEDULE[0]);

// Returns true if the bell should be ringing at the given time.
inline bool shouldRingBell(uint8_t hour, uint8_t minute, uint8_t second) {
  for (uint8_t i = 0; i < BELL_SCHEDULE_COUNT; i++) {
    const BellEvent &ev = BELL_SCHEDULE[i];
    if (hour == ev.hour && minute == ev.minute &&
        second < ev.duration_seconds) {
      return true;
    }
  }
  return false;
}

#endif
