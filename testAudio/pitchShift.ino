#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <math.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=409,144
AudioOutputI2S2          i2s2_1;         //xy=658,153
AudioAnalyzeNoteFrequency notefreq;       //xy=789,437
AudioEffectGranular      granular1;      //xy=504,155
AudioConnection          patchCord1(i2s1, 0, i2s2_1, 0);
AudioConnection          patchCord2(i2s1, 0, notefreq, 0);
AudioConnection          patchCord3(i2s1, 1, i2s2_1, 1);
AudioConnection          patchCord4(i2s1, 0, granular1, 0);
// GUItool: end automatically generated code
#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];

void setup() {
  Serial.begin(115200);
  AudioMemory(30);
  notefreq.begin(.15);  //yin threshold
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  granular1.beginPitchShift(100);
}

void loop() {
    if (notefreq.available()) {
        float note = notefreq.read();
        float prob = notefreq.probability();
        Serial.printf("Note: %3.2f | Probability: %.2f\n", note, prob);
        granular1.setSpeed(nearestFreq(note)/note);
    }
}
float nearestFreq(float measured){
  float rounded= log(measured/440.0)/log(2);
  rounded=round(12*rounded)/12;//round to nearest 12th
  rounded=exp(log(2)*rounded);
  return rounded;
}