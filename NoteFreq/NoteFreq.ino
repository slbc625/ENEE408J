#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=409,144
AudioOutputI2S          i2s2_1;         //xy=658,153
AudioAnalyzeNoteFrequency notefreq;       //xy=789,437
AudioConnection          patchCord1(i2s1, 0, i2s2_1, 0);
AudioConnection          patchCord2(i2s1, 0, notefreq, 0);
AudioConnection          patchCord3(i2s1, 1, i2s2_1, 1);
// GUItool: end automatically generated code

void setup() {
  Serial.begin(115200);
  AudioMemory(30);
  notefreq.begin(.15);  //yin threshold
}

void loop() {
    if (notefreq.available()) {
        float note = notefreq.read();
        float prob = notefreq.probability();
        Serial.printf("Note: %3.2f | Probability: %.2f\n", note, prob);
    }
}