#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=409,144
AudioOutputI2S2          i2s2_1;         //xy=658,153
AudioConnection          patchCord1(i2s1, 0, i2s2_1, 0);
AudioConnection          patchCord2(i2s1, 1, i2s2_1, 1);
// GUItool: end automatically generated code
void setup() {
  AudioMemory(10);
}

void loop() {
}