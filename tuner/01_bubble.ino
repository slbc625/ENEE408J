#include "SevSeg.h"

SevSeg display;

void setup_bubble() {
  byte numDigits = 4;
  byte digitPins[] = {0, 10, 3, 5};
  byte segmentPins[] = {12, 11, 2, 7, 1, 9, 6, 4};
  bool resistorsOnSegments = true; // 'true' means resistors are on segment pins
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  display.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  display.setBrightness(10);
}

void bubble() {
  display.refreshDisplay();
}

float value_old;
bool blink_batt = 0;

void bubble_voltage(float value) {
  if (voltage_alarm) {value_old = 0;}
  if (blink_batt) {display.setChars("bAtt");}
  else {
    value = value + 0.05;
    value = (int)(value * 10);
    value = value / 10;
    if (value_old != value) {
      value_old = value;
      uint8_t first_digit = value;
      uint8_t second_digit = compare(value, 1) - first_digit * 10;
      first_digit = convert_digit(first_digit, 1);
      second_digit = convert_digit(second_digit, 0);
      const uint8_t U[] = {B00111110, B01001000, first_digit, second_digit};
      display.setSegments(U);
    }
  }
  if (voltage_alarm) {blink_batt = !blink_batt;}
}

uint8_t convert_digit(int input, bool dec) {
  uint8_t digit;
  if (input == 0) {digit = B00111111;}
  else if (input == 1) {digit = B00000110;}
  else if (input == 2) {digit = B01011011;}
  else if (input == 3) {digit = B01001111;}
  else if (input == 4) {digit = B01100110;}
  else if (input == 5) {digit = B01101101;}
  else if (input == 6) {digit = B01111101;}
  else if (input == 7) {digit = B00000111;}
  else if (input == 8) {digit = B01111111;}
  else if (input == 9) {digit = B01101111;}
  if (dec == 1) {digit = digit | B10000000;}
  return digit;
}

long long compare(double number, int decplaces) {
  int dp = pow(10, decplaces);
  return (long long)((number + (0.5 / dp)) * dp);
}
