#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "AudioStream_F32.h"
#include "OpenAudio_ArduinoLibrary.h"
#include "AudioEffectFormantShiftFD_OA_F32.h"  //the local file holding your custom function

//set the sample rate and block size
const float sample_rate_Hz = 44117.f; ; // other frequencies in the table in AudioOutputI2S_F32 for T3.x only
const int audio_block_samples = 128;     //for freq domain processing, a power of 2: 16, 32, 64, 128
AudioSettings_F32 audio_settings(sample_rate_Hz, audio_block_samples);

//create audio library objects for handling the audio
AudioInputI2S                 i2sIn;   // input signal
AudioConvert_I16toF32         cnvrt1;  // Converts to float
AudioEffectFormantShiftFD_OA_F32 formantShift(audio_settings); // the frequency-domain processing block
AudioEffectGain_F32           gain1; //Applies digital gain to audio data.
AudioConvert_F32toI16         cnvrt2; //output signal, f32
AudioOutputI2S                i2sOut; //output signal, i16

AudioAnalyzeNoteFrequency  notefreq;
//Make all of the audio connections
AudioConnection       patchCord1(i2sIn,        0, cnvrt1, 0); // connect to input
AudioConnection_F32   patchCord2(cnvrt1,       0, formantShift, 0);//converts to float
AudioConnection_F32   patchCord3(formantShift, 0, gain1, 0); //connect to gain
AudioConnection_F32   patchCord4(gain1,        0, cnvrt2, 0); //connect to the left output
AudioConnection       patchCord6(cnvrt2,       0, i2sOut, 0);
AudioConnection_F32  connx(i2sIn, 0, notefreq, 0); //connects to peak analyzer

//inputs and levels
float input_gain_dB = 0.0f; //gain on the microphone
float formant_shift_gain_correction_dB = 0.0;  //will be used to adjust for gain in formant shifter

// ****************************  SETUP  **********************
void setup() {
  Serial.begin(1); delay(1000);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(10);            // I16 type
  AudioMemory_F32(40, audio_settings);

  // Configure the frequency-domain algorithm
  int overlap_factor = 8;  //set to 4 or 8 or either 75% overlap (4x) or 87.5% overlap (8x)
  int N_FFT = audio_block_samples * overlap_factor;
  formantShift.setup(audio_settings, N_FFT); //do after AudioMemory_F32();
  formantShift.setScaleFactor(1.0f); //1.0 is no formant shifting.
  if (overlap_factor == 4) {
    formant_shift_gain_correction_dB = -3.0;
  } else if (overlap_factor == 8) {
    formant_shift_gain_correction_dB = -9.0;
  }
}

// *************************  LOOP  *********************
void loop() {
  if (notefreq.available()) {
      float note = notefreq.read();
      //float prob = notefreq.probability();
      float rounded = nearestFreq(note);
      float ratio=rounded/note;
      Serial.printf("Note: %3.2f | Rounded: %3.2f | %1.3f\n", note, rounded,ratio);
      
      formantShift.setScaleFactor(ratio);
  }
} 

// ********************************************************

float nearestFreq(float measured){
  float rounded= log(measured/440.0)/log(2);
  rounded=round(12*rounded)/12;//round to nearest 12th
  rounded=exp(log(2)*rounded)*440.0;
  return rounded;
}