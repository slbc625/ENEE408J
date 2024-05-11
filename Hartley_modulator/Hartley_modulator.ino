
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "AudioStream_F32.h"
#include "OpenAudio_ArduinoLibrary.h"

//set the sample rate and block size
const float sample_rate_Hz = 44117.f; //standard 44.1 kHz
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

AudioAnalyzeNoteFrequency     notefreq;  //analyzes frequency of note

//Make all of the audio connections
AudioConnection       patchCord1(i2sIn, 0, notefreq, 0); //connects to peak analyzer
AudioConnection       patchCord2(i2sIn,    0, cnvrt1,   0); // connect to 32 bit
AudioConnection_F32   patchCord3(cnvrt1,   0, iqmixer1, 0); // Input to 2 mixers
AudioConnection_F32   patchCord4(cnvrt1,   0, iqmixer1, 1);
AudioConnection_F32   patchCord5(iqmixer1, 0, hilbert1, 0); // these two lines multiply by sin,cos
AudioConnection_F32   patchCord6(iqmixer1, 1, hilbert1, 1);
AudioConnection_F32   patchCord7(hilbert1, 0, sum1,     0); // Sideband select
AudioConnection_F32   patchCord8(hilbert1, 1, sum1,     1);
AudioConnection_F32   patchCord9(sum1,     0, cnvrt2,   0); // connect to the left output
AudioConnection       patchCord10(cnvrt2,   0, i2sOut,   0);


// Filter for AudioFilter90Deg_F32 hilbert1
#include "hilbert251A.h"

//inputs and levels
float gain = 1.0f;
float sign = 1.0f;
float delayms = 1.0f;

// ***************   SETUP   **********************************
void setup() {
  Serial.begin(115200); delay(1000);

  AudioMemory(30);            // I16 type
  AudioMemory_F32(200, audio_settings);
  notefreq.begin(.15);  //yin threshold


  iqmixer1.frequency(0);   // initialize frequency shift
  hilbert1.begin(hilbert251A, 251);  // Set the Hilbert transform FIR filter
  sum1.gain(0, gain*sign);           // Set gains
  sum1.gain(1, gain);
  Serial.printf("Everything setup");
  
}

// *************************   LOOP    ****************************

void loop() {
  //iqmixer1.frequency(400);

  if (notefreq.available()) {
      float note = notefreq.read();
      //float prob = notefreq.probability();
      float rounded = nearestFreq(note);
      float diff=note-rounded;
      Serial.printf("Note: %3.2f | Rounded: %3.2f | %3.2f\n", note, rounded,diff);
      
      iqmixer1.frequency(diff);
  }
}
float nearestFreq(float measured){
  float rounded= log(measured/440.0)/log(2);
  rounded=round(12*rounded)/12;//round to nearest 12th
  rounded=exp(log(2)*rounded)*440.0;
  return rounded;
}
