#include <unity.h>
#include <stdint.h>

// Standalone copies of the BCD functions for native testing
// (avoids pulling in Wire.h which requires Arduino runtime)

static uint8_t decToBcd(uint8_t val) {
  return (val / 10 * 16) + (val % 10);
}

static uint8_t bcdToDec(uint8_t val) {
  return (val / 16 * 10) + (val % 16);
}

void test_decToBcd_zero(void) {
  TEST_ASSERT_EQUAL_HEX8(0x00, decToBcd(0));
}

void test_decToBcd_single_digit(void) {
  TEST_ASSERT_EQUAL_HEX8(0x05, decToBcd(5));
  TEST_ASSERT_EQUAL_HEX8(0x09, decToBcd(9));
}

void test_decToBcd_double_digit(void) {
  TEST_ASSERT_EQUAL_HEX8(0x10, decToBcd(10));
  TEST_ASSERT_EQUAL_HEX8(0x23, decToBcd(23));
  TEST_ASSERT_EQUAL_HEX8(0x30, decToBcd(30));
  TEST_ASSERT_EQUAL_HEX8(0x59, decToBcd(59));
}

void test_decToBcd_rtc_values(void) {
  TEST_ASSERT_EQUAL_HEX8(0x12, decToBcd(12));
  TEST_ASSERT_EQUAL_HEX8(0x31, decToBcd(31));
  TEST_ASSERT_EQUAL_HEX8(0x99, decToBcd(99));
}

void test_bcdToDec_zero(void) {
  TEST_ASSERT_EQUAL_UINT8(0, bcdToDec(0x00));
}

void test_bcdToDec_single_digit(void) {
  TEST_ASSERT_EQUAL_UINT8(5, bcdToDec(0x05));
  TEST_ASSERT_EQUAL_UINT8(9, bcdToDec(0x09));
}

void test_bcdToDec_double_digit(void) {
  TEST_ASSERT_EQUAL_UINT8(10, bcdToDec(0x10));
  TEST_ASSERT_EQUAL_UINT8(23, bcdToDec(0x23));
  TEST_ASSERT_EQUAL_UINT8(59, bcdToDec(0x59));
}

void test_bcdToDec_rtc_values(void) {
  TEST_ASSERT_EQUAL_UINT8(12, bcdToDec(0x12));
  TEST_ASSERT_EQUAL_UINT8(31, bcdToDec(0x31));
  TEST_ASSERT_EQUAL_UINT8(99, bcdToDec(0x99));
}

void test_roundtrip_all_valid_values(void) {
  for (uint8_t i = 0; i <= 99; i++) {
    uint8_t bcd = decToBcd(i);
    uint8_t back = bcdToDec(bcd);
    TEST_ASSERT_EQUAL_UINT8(i, back);
  }
}

void test_roundtrip_seconds(void) {
  for (uint8_t s = 0; s <= 59; s++) {
    TEST_ASSERT_EQUAL_UINT8(s, bcdToDec(decToBcd(s)));
  }
}

void test_roundtrip_hours(void) {
  for (uint8_t h = 0; h <= 23; h++) {
    TEST_ASSERT_EQUAL_UINT8(h, bcdToDec(decToBcd(h)));
  }
}

int main(int argc, char **argv) {
  UNITY_BEGIN();

  RUN_TEST(test_decToBcd_zero);
  RUN_TEST(test_decToBcd_single_digit);
  RUN_TEST(test_decToBcd_double_digit);
  RUN_TEST(test_decToBcd_rtc_values);

  RUN_TEST(test_bcdToDec_zero);
  RUN_TEST(test_bcdToDec_single_digit);
  RUN_TEST(test_bcdToDec_double_digit);
  RUN_TEST(test_bcdToDec_rtc_values);

  RUN_TEST(test_roundtrip_all_valid_values);
  RUN_TEST(test_roundtrip_seconds);
  RUN_TEST(test_roundtrip_hours);

  return UNITY_END();
}
