#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <math.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=318.16668701171875,157
AudioEffectGranular      granular1;      //xy=546.1666870117188,149
AudioEffectGranular      granular2;      //xy=572.1666717529297,206.1666717529297
AudioAnalyzeNoteFrequency notefreq;       //xy=698.1666870117188,450
AudioMixer4              mixer1;         //xy=746.1666717529297,146.1666717529297
AudioOutputI2S           i2s2_1;         //xy=894.1666870117188,148
AudioConnection          patchCord1(i2s1, 0, notefreq, 0);
AudioConnection          patchCord2(i2s1, 0, granular1, 0);
AudioConnection          patchCord3(i2s1, 0, granular2, 0);
AudioConnection          patchCord4(granular1, 0, mixer1, 0);
AudioConnection          patchCord5(granular2, 0, mixer1, 1);
AudioConnection          patchCord6(mixer1, 0, i2s2_1, 0);
// GUItool: end automatically generated code

// GUItool: end automatically generated code
#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory1[GRANULAR_MEMORY_SIZE];
int16_t granularMemory2[GRANULAR_MEMORY_SIZE];

void setup() {
  Serial.begin(115200);
  AudioMemory(30);
  notefreq.begin(.15);  //yin threshold
  granular1.begin(granularMemory1, GRANULAR_MEMORY_SIZE);
  granular1.beginPitchShift(13);
  granular2.begin(granularMemory2, GRANULAR_MEMORY_SIZE);
  granular2.beginPitchShift(17);
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
}

void loop() {
  //granular1.setSpeed(2.0);
  //granular2.setSpeed(2.0);
  if (notefreq.available()) {
      float note = notefreq.read();
      //float prob = notefreq.probability();
      float rounded = nearestFreq(note);
      float ratio=rounded/note;
      Serial.printf("Note: %3.2f | Rounded: %3.2f | %1.3f\n", note, rounded,ratio);
      
      granular1.setSpeed(ratio);
      granular2.setSpeed(ratio);
  }
}
float nearestFreq(float measured){
  float rounded= log(measured/440.0)/log(2);
  rounded=round(12*rounded)/12;//round to nearest 12th
  rounded=exp(log(2)*rounded)*440.0;
  return rounded;
}