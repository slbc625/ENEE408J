
#include "Audio.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "AudioStream_F32.h"
#include "OpenAudio_ArduinoLibrary.h"

//set the sample rate and block size
const float sample_rate_Hz = 44117.f; //standt 44.1 kHz
const int audio_block_samples = 128;
AudioSettings_F32 audio_settings(sample_rate_Hz, audio_block_samples);

//create audio library objects for handling the audio
AudioInputI2S            i2sIn;     // input
AudioConvert_I16toF32    cnvrt1;    // Convert to float
RadioIQMixer_F32         iqmixer1;
AudioFilter90Deg_F32     hilbert1;
AudioMixer4_F32          sum1;      // Summing node for the SSB receiver
AudioConvert_F32toI16    cnvrt2;
AudioOutputI2S           i2sOut;

//Make all of the audio connections
AudioConnection       patchCord0(i2sIn,    0, cnvrt1,   0); // connect to Left codec, 16-bit
AudioConnection_F32   patchCord1(cnvrt1,   0, iqmixer1, 0); // Input to 2 mixers
AudioConnection_F32   patchCord2(cnvrt1,   0, iqmixer1, 1);
AudioConnection_F32   patchCord3(iqmixer1, 0, hilbert1, 0); // Broadband 90 deg phase
AudioConnection_F32   patchCord4(iqmixer1, 1, hilbert1, 1);
AudioConnection_F32   patchCord5(hilbert1, 0, sum1,     0); // Sideband select
AudioConnection_F32   patchCord6(hilbert1, 1, sum1,     1);
AudioConnection_F32   patchCord9(sum1,     0, cnvrt2,   0); // connect to the left output
AudioConnection       patchCordB(cnvrt2,   0, i2sOut,   0);

// Filter for AudioFilter90Deg_F32 hilbert1
#include "hilbert251A.h"

//inputs and levels
float gain_dB = -15.0f;
float gain = 0.177828f;  // Same as -15 dB
float sign = 1.0f;
float deltaGain_dB = 2.5f;
float frequencyLO = 100.0f;
float delayms = 1.0f;

// ***************   SETUP   **********************************
void setup() {
  Serial.begin(1); delay(1000);

  AudioMemory(10);            // I16 type
  AudioMemory_F32(200, audio_settings);


  iqmixer1.frequency(frequencyLO);   // Frequency shift, Hz
  deltaFrequency(0.0f);              // Print freq
  hilbert1.begin(hilbert251A, 251);  // Set the Hilbert transform FIR filter
  sum1.gain(0, gain*sign);           // Set gains
  sum1.gain(1, gain);
  
}

// *************************   LOOP    ****************************

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
  }
}
float nearestFreq(float measured){
  float rounded= log(measured/440.0)/log(2);
  rounded=round(12*rounded)/12;//round to nearest 12th
  rounded=exp(log(2)*rounded)*440.0;
  return rounded;
}
