#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <math.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=171.1666717529297,146
AudioAnalyzeNoteFrequency notefreq;       //xy=267.16668701171875,550.9999694824219
AudioEffectDelay         delay1;         //xy=359.16668701171875,212.16665649414062
AudioEffectGranular      granular4;      //xy=506.16668701171875,574.1666870117188
AudioEffectGranular      granular3;      //xy=542.1666870117188,430.16668701171875
AudioEffectGranular      granular1;      //xy=544.1666870117188,155.00000762939453
AudioEffectGranular      granular2;      //xy=578.1666870117188,298.1666564941406
AudioEffectDelay         delay3;         //xy=750.1666870117188,283.16668701171875
AudioEffectDelay         delay4;         //xy=750.1666870117188,428.16668701171875
AudioEffectDelay         delay2;         //xy=752.1666870117188,143.16665649414062
AudioEffectDelay         delay5;         //xy=752.1666870117188,578.1666870117188
AudioMixer4              mixer1;         //xy=1034.1666870117188,163.16665649414062
AudioOutputI2S           i2s2_1;         //xy=1169.1665649414062,168
AudioConnection          patchCord1(i2s1, 0, notefreq, 0);
AudioConnection          patchCord2(i2s1, 0, delay1, 0);
AudioConnection          patchCord3(delay1, 0, granular1, 0);
AudioConnection          patchCord4(delay1, 1, granular2, 0);
AudioConnection          patchCord5(delay1, 2, granular3, 0);
AudioConnection          patchCord6(delay1, 3, granular4, 0);
AudioConnection          patchCord7(granular4, delay5);
AudioConnection          patchCord8(granular3, delay4);
AudioConnection          patchCord9(granular1, delay2);
AudioConnection          patchCord10(granular2, delay3);
AudioConnection          patchCord11(delay3, 0, mixer1, 1);
AudioConnection          patchCord12(delay4, 0, mixer1, 2);
AudioConnection          patchCord13(delay2, 0, mixer1, 0);
AudioConnection          patchCord14(delay5, 0, mixer1, 3);
AudioConnection          patchCord15(mixer1, 0, i2s2_1, 0);
// GUItool: end automatically generated code

#define GRANULAR_MEMORY_SIZE 25600  // enough for 290 ms at 44.1 kHz
int16_t granularMemory1[GRANULAR_MEMORY_SIZE];
int16_t granularMemory2[GRANULAR_MEMORY_SIZE];
int16_t granularMemory3[GRANULAR_MEMORY_SIZE];
int16_t granularMemory4[GRANULAR_MEMORY_SIZE];

void setup() {
  Serial.begin(115200);
  AudioMemory(256);
  notefreq.begin(.15);  //yin threshold

  //set up the freqshifts
  granular1.begin(granularMemory1, GRANULAR_MEMORY_SIZE);
  granular1.beginPitchShift(12);
  granular2.begin(granularMemory2, GRANULAR_MEMORY_SIZE);
  granular2.beginPitchShift(12);
  granular3.begin(granularMemory3, GRANULAR_MEMORY_SIZE);
  granular3.beginPitchShift(12);
  granular4.begin(granularMemory4, GRANULAR_MEMORY_SIZE);
  granular4.beginPitchShift(12);
  //merge together signals
  mixer1.gain(0, 0.25);
  mixer1.gain(1, 0.25);
  mixer1.gain(2, 0.25);
  mixer1.gain(3, 0.25);
  //add delay
  delay1.delay(0,0);
  delay1.delay(1,3);
  delay1.delay(2,6);
  delay1.delay(3,9);
  delay2.delay(0,9);
  delay3.delay(0,6);
  delay4.delay(0,3);
  delay5.delay(0,0);
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
      granular3.setSpeed(ratio);
      granular4.setSpeed(ratio);
  }
}
float nearestFreq(float measured){
  float rounded= log(measured/440.0)/log(2);//divide by 440, then take log2
  rounded=round(12*rounded)/12;//round to nearest 12th
  rounded=exp(log(2)*rounded)*440.0;
  return rounded;
}