#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <math.h>


// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=55,600.2083129882812
AudioAnalyzeNoteFrequency notefreq;       //xy=137.45834350585938,270.874924659729
AudioFilterStateVariable           filter1;           //xy=195.2083396911621,745.2083396911621
AudioEffectDelay         delay1;         //xy=322.3750457763672,613.7082748413086
AudioEffectDelay         delay10; //xy=360.5555725097656,1790.5555419921875
AudioEffectGranular      granular4;      //xy=543.9583435058594,570.7083282470703
AudioEffectGranular      granular8;      //xy=549.7916259765625,1121.8750190734863
AudioEffectGranular      granular5;      //xy=557.7083129882812,677.7083129882812
AudioEffectGranular      granular3;      //xy=579.9583435058594,426.7083282470703
AudioEffectGranular      granular1;      //xy=581.9583435058594,151.7083282470703
AudioEffectGranular      granular6;      //xy=580.2083129882812,840.2082862854004
AudioEffectGranular      granular7;      //xy=589.375,965.6249561309814
AudioEffectGranular      granular16; //xy=587.9721527099609,2298.7222862243652
AudioEffectGranular      granular13; //xy=595.8888397216797,1854.5555801391602
AudioEffectGranular      granular9; //xy=608.8055419921875,1287.5556163787842
AudioEffectGranular      granular2;      //xy=615.9583435058594,294.7083282470703
AudioEffectGranular      granular14; //xy=618.3888397216797,2017.0555534362793
AudioEffectGranular      granular15; //xy=627.5555267333984,2142.4722232818604
AudioEffectGranular      granular10; //xy=641.4721908569336,1476.8888959884644
AudioEffectGranular      granular12; //xy=644.1388168334961,1741.555477142334
AudioEffectGranular      granular11; //xy=651.8055267333984,1603.5555152893066
AudioEffectDelay         delay3;         //xy=787.9583435058594,279.7083282470703
AudioEffectDelay         delay4;         //xy=787.9583435058594,424.7083282470703
AudioEffectDelay         delay5;         //xy=787.4584350585938,572.2083129882812
AudioEffectDelay         delay2;         //xy=789.9583435058594,139.7083282470703
AudioEffectDelay         delay6;         //xy=791.0415725708008,715.2083129882812
AudioEffectDelay         delay9;         //xy=790.6249237060547,1123.1250839233398
AudioEffectDelay         delay7;         //xy=793.9582786560059,843.1249771118164
AudioEffectDelay         delay8;         //xy=803.9582595825195,973.5416488647461
AudioEffectDelay         delay12; //xy=822.8055877685547,1448.2222061157227
AudioEffectDelay         delay11; //xy=826.1388206481934,1283.2222290039062
AudioEffectDelay         delay14; //xy=825.6389617919922,1749.0555801391602
AudioEffectDelay         delay13; //xy=828.1389389038086,1598.2221450805664
AudioEffectDelay         delay15;   //xy=829.2220993041992,1892.0555801391602
AudioEffectDelay         delay18; //xy=828.8054504394531,2299.9723510742188
AudioEffectDelay         delay16; //xy=832.1388053894043,2019.9722442626953
AudioEffectDelay         delay17; //xy=842.138786315918,2150.388916015625
AudioMixer4              mixer1;         //xy=1071.9583435058594,159.7083282470703
AudioMixer4              mixer4; //xy=1110.1388702392578,1336.5555953979492
AudioMixer4              mixer2;         //xy=1255.208339691162,896.4583396911621
AudioMixer4              mixer5; //xy=1293.3888664245605,2073.305606842041
AudioMixer4              mixer3;         //xy=1550.208339691162,1138.5417079925537
AudioFilterStateVariable           filter2;           //xy=1794.333343505859,1150.3333435058591
AudioOutputI2S           i2s2_1;         //xy=1959.2083740234375,1168.9583129882812
AudioConnection          patchCord1(i2s1, 0, notefreq, 0);
AudioConnection          patchCord2(i2s1, 0, filter1, 0);
AudioConnection          patchCord3(filter1, delay1);
AudioConnection          patchCord4(filter1, delay10);
AudioConnection          patchCord5(delay1, 0, granular1, 0);
AudioConnection          patchCord6(delay1, 1, granular2, 0);
AudioConnection          patchCord7(delay1, 2, granular3, 0);
AudioConnection          patchCord8(delay1, 3, granular4, 0);
AudioConnection          patchCord9(delay1, 4, granular5, 0);
AudioConnection          patchCord10(delay1, 5, granular6, 0);
AudioConnection          patchCord11(delay1, 6, granular7, 0);
AudioConnection          patchCord12(delay1, 7, granular8, 0);
AudioConnection          patchCord13(delay10, 0, granular9, 0);
AudioConnection          patchCord14(delay10, 1, granular10, 0);
AudioConnection          patchCord15(delay10, 2, granular11, 0);
AudioConnection          patchCord16(delay10, 3, granular12, 0);
AudioConnection          patchCord17(delay10, 4, granular13, 0);
AudioConnection          patchCord18(delay10, 5, granular14, 0);
AudioConnection          patchCord19(delay10, 6, granular15, 0);
AudioConnection          patchCord20(delay10, 7, granular16, 0);
AudioConnection          patchCord21(granular4, delay5);
AudioConnection          patchCord22(granular8, delay9);
AudioConnection          patchCord23(granular5, delay6);
AudioConnection          patchCord24(granular3, delay4);
AudioConnection          patchCord25(granular1, delay2);
AudioConnection          patchCord26(granular6, delay7);
AudioConnection          patchCord27(granular7, delay8);
AudioConnection          patchCord28(granular16, delay18);
AudioConnection          patchCord29(granular13, delay15);
AudioConnection          patchCord30(granular9, delay11);
AudioConnection          patchCord31(granular2, delay3);
AudioConnection          patchCord32(granular14, delay16);
AudioConnection          patchCord33(granular15, delay17);
AudioConnection          patchCord34(granular10, delay12);
AudioConnection          patchCord35(granular12, delay14);
AudioConnection          patchCord36(granular11, delay13);
AudioConnection          patchCord37(delay3, 0, mixer1, 1);
AudioConnection          patchCord38(delay4, 0, mixer1, 2);
AudioConnection          patchCord39(delay5, 0, mixer1, 3);
AudioConnection          patchCord40(delay2, 0, mixer1, 0);
AudioConnection          patchCord41(delay6, 0, mixer2, 0);
AudioConnection          patchCord42(delay9, 0, mixer2, 3);
AudioConnection          patchCord43(delay7, 0, mixer2, 1);
AudioConnection          patchCord44(delay8, 0, mixer2, 2);
AudioConnection          patchCord45(delay12, 0, mixer4, 1);
AudioConnection          patchCord46(delay11, 0, mixer4, 0);
AudioConnection          patchCord47(delay14, 0, mixer4, 3);
AudioConnection          patchCord48(delay13, 0, mixer4, 2);
AudioConnection          patchCord49(delay15, 0, mixer5, 0);
AudioConnection          patchCord50(delay18, 0, mixer5, 3);
AudioConnection          patchCord51(delay16, 0, mixer5, 1);
AudioConnection          patchCord52(delay17, 0, mixer5, 2);
AudioConnection          patchCord53(mixer1, 0, mixer3, 0);
AudioConnection          patchCord54(mixer4, 0, mixer3, 2);
AudioConnection          patchCord55(mixer2, 0, mixer3, 1);
AudioConnection          patchCord56(mixer5, 0, mixer3, 3);
AudioConnection          patchCord57(mixer3, filter2);
AudioConnection          patchCord58(filter2, 0, i2s2_1, 0);
// GUItool: end automatically generated code

#define GRANULAR_MEMORY_SIZE 6400  // enough for 290 ms at 44.1 kHz
int16_t granularMemory1[GRANULAR_MEMORY_SIZE];
int16_t granularMemory2[GRANULAR_MEMORY_SIZE];
int16_t granularMemory3[GRANULAR_MEMORY_SIZE];
int16_t granularMemory4[GRANULAR_MEMORY_SIZE];
int16_t granularMemory5[GRANULAR_MEMORY_SIZE];
int16_t granularMemory6[GRANULAR_MEMORY_SIZE];
int16_t granularMemory7[GRANULAR_MEMORY_SIZE];
int16_t granularMemory8[GRANULAR_MEMORY_SIZE];
int16_t granularMemory9[GRANULAR_MEMORY_SIZE];
int16_t granularMemory10[GRANULAR_MEMORY_SIZE];
int16_t granularMemory11[GRANULAR_MEMORY_SIZE];
int16_t granularMemory12[GRANULAR_MEMORY_SIZE];
int16_t granularMemory13[GRANULAR_MEMORY_SIZE];
int16_t granularMemory14[GRANULAR_MEMORY_SIZE];
int16_t granularMemory15[GRANULAR_MEMORY_SIZE];
int16_t granularMemory16[GRANULAR_MEMORY_SIZE];

void setup() {
  Serial.begin(115200);
  AudioMemory(512);
  notefreq.begin(.15);  //yin threshold

  //filters
  filter1.frequency(3000);
  filter2.frequency(3000);

  //set up the freqshifts
  granular1.begin(granularMemory1, GRANULAR_MEMORY_SIZE);
  granular1.beginPitchShift(12);
  granular2.begin(granularMemory2, GRANULAR_MEMORY_SIZE);
  granular2.beginPitchShift(12);
  granular3.begin(granularMemory3, GRANULAR_MEMORY_SIZE);
  granular4.beginPitchShift(12);
  granular4.begin(granularMemory4, GRANULAR_MEMORY_SIZE);
  granular4.beginPitchShift(12);
  granular5.begin(granularMemory5, GRANULAR_MEMORY_SIZE);
  granular5.beginPitchShift(12);
  granular6.begin(granularMemory6, GRANULAR_MEMORY_SIZE);
  granular6.beginPitchShift(12);
  granular7.begin(granularMemory7, GRANULAR_MEMORY_SIZE);
  granular7.beginPitchShift(12);
  granular8.begin(granularMemory8, GRANULAR_MEMORY_SIZE);
  granular8.beginPitchShift(12);
  granular9.begin(granularMemory9, GRANULAR_MEMORY_SIZE);
  granular9.beginPitchShift(12);
  granular10.begin(granularMemory10, GRANULAR_MEMORY_SIZE);
  granular10.beginPitchShift(12);
  granular11.begin(granularMemory11, GRANULAR_MEMORY_SIZE);
  granular11.beginPitchShift(12);
  granular12.begin(granularMemory12, GRANULAR_MEMORY_SIZE);
  granular12.beginPitchShift(12);
  granular13.begin(granularMemory13, GRANULAR_MEMORY_SIZE);
  granular14.beginPitchShift(12);
  granular14.begin(granularMemory14, GRANULAR_MEMORY_SIZE);
  granular14.beginPitchShift(12);
  granular15.begin(granularMemory15, GRANULAR_MEMORY_SIZE);
  granular15.beginPitchShift(12);
  granular16.begin(granularMemory16, GRANULAR_MEMORY_SIZE);
  granular16.beginPitchShift(12);
  //merge together signals
  mixer1.gain(0, 0.25);
  mixer1.gain(1, 0.25);
  mixer1.gain(2, 0.25);
  mixer1.gain(3, 0.25);
  mixer2.gain(0, 0.25);
  mixer2.gain(1, 0.25);
  mixer2.gain(2, 0.25);
  mixer2.gain(3, 0.25);
  mixer3.gain(0, 0.25);
  mixer3.gain(1, 0.25);
  mixer3.gain(2, 0.25);
  mixer3.gain(3, 0.25);
  mixer4.gain(0, 0.25);
  mixer4.gain(1, 0.25);
  mixer4.gain(2, 0.25);
  mixer4.gain(3, 0.25);
  mixer5.gain(0, 0.25);
  mixer5.gain(1, 0.25);
  mixer5.gain(2, 0.25);
  mixer5.gain(3, 0.25);
  //add delay
  //first delay
  delay1.delay(0,0);
  delay1.delay(1,3);
  delay1.delay(2,6);
  delay1.delay(3,9);
  delay1.delay(4,12);
  delay1.delay(5,15);
  delay1.delay(6,18);
  delay1.delay(7,21);
  delay10.delay(0,24);
  delay10.delay(1,27);
  delay10.delay(2,30);
  delay10.delay(3,33);
  delay10.delay(4,36);
  delay10.delay(5,39);
  delay10.delay(6,42);
  delay10.delay(7,45);
  //second delay
  delay2.delay(0,45);
  delay3.delay(0,42);
  delay4.delay(0,39);
  delay5.delay(0,36);
  delay6.delay(0,33);
  delay7.delay(0,30);
  delay8.delay(0,27);
  delay9.delay(0,24);
  delay11.delay(0,21);
  delay12.delay(0,18);
  delay13.delay(0,15);
  delay14.delay(0,12);
  delay15.delay(0,9);
  delay16.delay(0,6);
  delay17.delay(0,3);
  delay18.delay(0,0);
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
      granular5.setSpeed(ratio);
      granular6.setSpeed(ratio);
      granular7.setSpeed(ratio);
      granular8.setSpeed(ratio);
      granular9.setSpeed(ratio);
      granular10.setSpeed(ratio);
      granular11.setSpeed(ratio);
      granular12.setSpeed(ratio);
      granular13.setSpeed(ratio);
      granular14.setSpeed(ratio);
      granular15.setSpeed(ratio);
      granular16.setSpeed(ratio);
  }
}
float nearestFreq(float measured){
  float rounded= log(measured/440.0)/log(2);//divide by 440, then take log2
  rounded=round(12*rounded)/12;//round to nearest 12th
  rounded=exp(log(2)*rounded)*440.0;
  return rounded;
}