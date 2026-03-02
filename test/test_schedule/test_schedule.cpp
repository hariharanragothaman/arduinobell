#include <unity.h>
#include <stdint.h>

// Standalone copy of the schedule types and logic for native testing
// (avoids pulling in Arduino.h)

struct BellEvent {
  uint8_t hour;
  uint8_t minute;
  uint8_t duration_seconds;
};

static const BellEvent BELL_SCHEDULE[] = {
  { 8, 10, 40},
  { 8, 30, 20},
  { 9, 30, 20},
  {10, 30, 20},
  {11, 30, 20},
  {12, 10, 20},
  {13, 10, 20},
  {14, 10, 20},
  {14, 30, 20},
  {15, 30, 20},
  {16, 30, 20},
};

static const uint8_t BELL_SCHEDULE_COUNT =
    sizeof(BELL_SCHEDULE) / sizeof(BELL_SCHEDULE[0]);

static bool shouldRingBell(uint8_t hour, uint8_t minute, uint8_t second) {
  for (uint8_t i = 0; i < BELL_SCHEDULE_COUNT; i++) {
    const BellEvent &ev = BELL_SCHEDULE[i];
    if (hour == ev.hour && minute == ev.minute &&
        second < ev.duration_seconds) {
      return true;
    }
  }
  return false;
}

// --- Schedule hit tests ---

void test_morning_assembly_start(void) {
  TEST_ASSERT_TRUE(shouldRingBell(8, 10, 0));
}

void test_morning_assembly_mid(void) {
  TEST_ASSERT_TRUE(shouldRingBell(8, 10, 20));
}

void test_morning_assembly_end(void) {
  TEST_ASSERT_TRUE(shouldRingBell(8, 10, 39));
}

void test_morning_assembly_just_after(void) {
  TEST_ASSERT_FALSE(shouldRingBell(8, 10, 40));
}

void test_period1_start(void) {
  TEST_ASSERT_TRUE(shouldRingBell(8, 30, 0));
}

void test_period2_start(void) {
  TEST_ASSERT_TRUE(shouldRingBell(9, 30, 0));
}

void test_period3_start(void) {
  TEST_ASSERT_TRUE(shouldRingBell(10, 30, 5));
}

void test_period4_start(void) {
  TEST_ASSERT_TRUE(shouldRingBell(11, 30, 10));
}

void test_lunch_break(void) {
  TEST_ASSERT_TRUE(shouldRingBell(12, 10, 0));
}

void test_period5_start(void) {
  TEST_ASSERT_TRUE(shouldRingBell(13, 10, 0));
}

void test_period6_start(void) {
  TEST_ASSERT_TRUE(shouldRingBell(14, 10, 0));
}

void test_short_break(void) {
  TEST_ASSERT_TRUE(shouldRingBell(14, 30, 0));
}

void test_period7_start(void) {
  TEST_ASSERT_TRUE(shouldRingBell(15, 30, 0));
}

void test_dismissal(void) {
  TEST_ASSERT_TRUE(shouldRingBell(16, 30, 0));
}

void test_dismissal_end(void) {
  TEST_ASSERT_TRUE(shouldRingBell(16, 30, 19));
}

void test_dismissal_just_after(void) {
  TEST_ASSERT_FALSE(shouldRingBell(16, 30, 20));
}

// --- Schedule miss tests ---

void test_midnight_silent(void) {
  TEST_ASSERT_FALSE(shouldRingBell(0, 0, 0));
}

void test_early_morning_silent(void) {
  TEST_ASSERT_FALSE(shouldRingBell(6, 0, 0));
}

void test_between_periods_silent(void) {
  TEST_ASSERT_FALSE(shouldRingBell(9, 0, 0));
}

void test_late_evening_silent(void) {
  TEST_ASSERT_FALSE(shouldRingBell(22, 0, 0));
}

void test_wrong_minute_silent(void) {
  TEST_ASSERT_FALSE(shouldRingBell(8, 11, 0));
}

void test_just_before_period_silent(void) {
  TEST_ASSERT_FALSE(shouldRingBell(8, 29, 59));
}

// --- Boundary tests ---

void test_all_events_second_zero(void) {
  for (uint8_t i = 0; i < BELL_SCHEDULE_COUNT; i++) {
    TEST_ASSERT_TRUE_MESSAGE(
        shouldRingBell(BELL_SCHEDULE[i].hour, BELL_SCHEDULE[i].minute, 0),
        "Second 0 should always ring");
  }
}

void test_all_events_last_valid_second(void) {
  for (uint8_t i = 0; i < BELL_SCHEDULE_COUNT; i++) {
    uint8_t lastSec = BELL_SCHEDULE[i].duration_seconds - 1;
    TEST_ASSERT_TRUE_MESSAGE(
        shouldRingBell(BELL_SCHEDULE[i].hour, BELL_SCHEDULE[i].minute, lastSec),
        "Last valid second should ring");
  }
}

void test_all_events_first_invalid_second(void) {
  for (uint8_t i = 0; i < BELL_SCHEDULE_COUNT; i++) {
    uint8_t firstInvalid = BELL_SCHEDULE[i].duration_seconds;
    TEST_ASSERT_FALSE_MESSAGE(
        shouldRingBell(BELL_SCHEDULE[i].hour, BELL_SCHEDULE[i].minute, firstInvalid),
        "First second past duration should not ring");
  }
}

void test_every_hour_without_event_silent(void) {
  for (uint8_t h = 0; h < 24; h++) {
    bool isScheduledHour = false;
    for (uint8_t i = 0; i < BELL_SCHEDULE_COUNT; i++) {
      if (BELL_SCHEDULE[i].hour == h) {
        isScheduledHour = true;
        break;
      }
    }
    if (!isScheduledHour) {
      TEST_ASSERT_FALSE(shouldRingBell(h, 0, 0));
      TEST_ASSERT_FALSE(shouldRingBell(h, 30, 0));
    }
  }
}

int main(int argc, char **argv) {
  UNITY_BEGIN();

  RUN_TEST(test_morning_assembly_start);
  RUN_TEST(test_morning_assembly_mid);
  RUN_TEST(test_morning_assembly_end);
  RUN_TEST(test_morning_assembly_just_after);
  RUN_TEST(test_period1_start);
  RUN_TEST(test_period2_start);
  RUN_TEST(test_period3_start);
  RUN_TEST(test_period4_start);
  RUN_TEST(test_lunch_break);
  RUN_TEST(test_period5_start);
  RUN_TEST(test_period6_start);
  RUN_TEST(test_short_break);
  RUN_TEST(test_period7_start);
  RUN_TEST(test_dismissal);
  RUN_TEST(test_dismissal_end);
  RUN_TEST(test_dismissal_just_after);

  RUN_TEST(test_midnight_silent);
  RUN_TEST(test_early_morning_silent);
  RUN_TEST(test_between_periods_silent);
  RUN_TEST(test_late_evening_silent);
  RUN_TEST(test_wrong_minute_silent);
  RUN_TEST(test_just_before_period_silent);

  RUN_TEST(test_all_events_second_zero);
  RUN_TEST(test_all_events_last_valid_second);
  RUN_TEST(test_all_events_first_invalid_second);
  RUN_TEST(test_every_hour_without_event_silent);

  return UNITY_END();
}
