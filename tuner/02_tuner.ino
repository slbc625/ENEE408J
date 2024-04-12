#include <Audio.h>
#include "AudioFFTInterp1024.h"

int pin_speaker = 14;

// Teensy 4.0:
// INMP441 gain 3.5 and highpass 20 // WS to pin 20, SCK to pin 21, SD to pin 8, LR to GND, don't wire MCLK pin 23
// SPH0645 gain 8.5 and highpass 20 // LRCLK to pin 20, BCLK to pin 21, DOUT to pin 8, SEL to GND, don't wire MCLK pin 23
// #define mic_pin A6               // connect mic to analog pin (teensy 4.0: A6 = pin 20)
// #define mic_pin 21               // connect mic to analog pin (teensy 4.0: A7 = pin 21)
// #define mic_pin A8               // connect mic to analog pin (teensy 4.0: A8 = pin 22)

// Teensy 3.6:
// PDM     gain 2.5 and highpass 20 // CLK to pin 9, DATA to pin 13, SEL to GND
// MAX9814 gain 1.5 and highpass 20 // mic out to ADC analog pin
// INMP441 gain 3.5 and highpass 20 // WS to pin 23, SCK to pin 9, SD to pin 13, LR to GND, don't wire MCLK pin 11
// #define mic_pin A2                  // connect mic to analog pin (teensy 3.6: A2 = pin 16)

AudioInputI2S input;
//AudioInputAnalog        input(mic_pin);
//AudioInputPDM           input;
AudioAnalyzePeak peak;
AudioFilterStateVariable filter;
AudioAmplifier amp;
AudioAnalyzeNoteFrequency yin;
AudioFFTInterp1024 fft;
//AudioOutputUSB          usb;

AudioConnection patchCord1(input, 0, filter, 0);
AudioConnection patchCord2(filter, 2, amp, 0);
AudioConnection patchCord3(amp, 0, yin, 0);
AudioConnection patchCord4(amp, 0, fft, 0);
AudioConnection patchCord5(amp, 0, peak, 0);
//AudioConnection         patchCord6(amp, 0, usb, 0);
//AudioConnection         patchCord7(input, 0, usb, 1);

// default settings:                   // in analyze_notefreq.h adjust AUDIO_GUITARTUNER_BLOCKS

bool yin_add_default = 1;               // set yin on/off
bool fft_add_default = 1;               // set fft on/off
float yin_probability_default = 0.95f;  // update only if higher than propability
int tuner_rate_default = 500;           // sampling interval in ms to analyze and display data
float yin_alpha_default = 0.0f;         // IIR smoothing filter smoothing constant - greater smoothing as alpha -> 1
float fft_alpha_default = 0.0f;         // IIR smoothing filter smoothing constant - greater smoothing as alpha -> 1
float rec_treshold_default = 0.1f;      // ignore sound below this level
uint16_t number_of_freqs_default = 3;   // Number of spectral lines to detect (<11) (in order of magnitude)
int percent_default = 5;                // tolerance for finding closeest freq
int highpass_default = 20;              // high pass filter
float gain_default = 35.0f;             // digitally amplify signal
const int memory = 100;                 // use AudioMemoryUsageMax()
float yin_treshold = 0.15f;             // yin probability treshold

float yin_probability;
int tuner_rate;
float fft_alpha;
float yin_alpha;
float rec_treshold;
uint16_t number_of_freqs;
int percent;
int highpass;
float gain;

bool yin_add;
int yin_int;
float yin_serial;
float yin_bubble = 0;
float yin_smoothed;
float yin_averaged;

bool fft_add;
int fft_int;
float fft_serial;
float fft_bubble = 0;
float fft_output[10];
float fft_averaged[10];

float reclevel_float;
int freq_int;
bool output_serial;
bool rec_level;

int pitch;
int pitch_default = 443.0f;
int pitch_array[9];
float pitch_factor[9] = { 8, 4, 20, 10, 5, 2.5, 12.5, 6.25, 3.125 };
byte decpoint;
bool led_oldstate;
elapsedMillis stopwatch_sampling;

void setup_tuner() {
  AudioMemory(memory);         // use AudioMemoryUsageMax() +2
  filter.frequency(highpass);  // filter out DC & extremely low frequencies
  amp.gain(gain);              // amplify signal
  yin.begin(yin_treshold);     // initialize the yin algorithm's threshold, set the detection threshold: the amount of allowed uncertainty in %
  fft.lines(number_of_freqs);  // number of fft freqs
  fft.smoothing(fft_alpha);    // smoothed = alpha * smoothed + (1.0 - alpha) * new_value
  pitch_calc();
  display.setNumber(pitch * 10, 1);
}

void start_tuner() {
  float temp = peak.read();  // dummy read
  mode_tuner = 1;
  stopwatch_tuner = 0;
  tuner_stop = 1;
  display_pitch();
}

void display_pitch() {
  display.setNumber(pitch * 10, 1);
}

void pitch_calc() {
  for (int i = 0; i < 9; i++) {
    pitch_array[i] = round((float)pitch * pitch_factor[i]);
  }
}

void tuner() {
  tuner_collect();
  if (stopwatch_sampling >= tuner_rate) {
    stream_usage();
    stream_reclevel();
    tuner_analyze();
    stopwatch_sampling = 0;
  }
}

int yin_counter = 0;
int fft_counter[10];

void tuner_collect() {
  if (peak.available()) {
    reclevel_float = peak.read();
    if (reclevel_float >= rec_treshold) {
      if (yin_add && yin.available() && yin.probability() > yin_probability) {
        float yin_float = yin.read();
        if (yin_alpha == 0.0f) {
          yin_counter++;
          yin_averaged += yin_float;
        } else {
          yin_smoothed = yin_alpha * yin_smoothed + (1.0 - yin_alpha) * yin_float;
          yin_serial = yin_smoothed;
        }
      }
      if (fft.available()) {
        float fft_float[10];
        for (int i = 0; i < number_of_freqs; i++) {
          fft_float[i] = fft.read(i);
          if (fft_alpha == 0.0f) {
            fft_counter[i]++;
            fft_averaged[i] += fft_float[i];
          } else {
            fft_output[i] = fft_float[i];
          }
        }
      }
    }
  }
}

void tuner_analyze() {
  if (yin_alpha == 0) {
    if (yin_counter == 0) {
      yin_serial = 0;
    } else {
      yin_serial = yin_averaged / yin_counter;
    }
  }
  if (fft_alpha == 0) {
    for (int i = 0; i < number_of_freqs; i++) {
      if (fft_counter[i] == 0) {
        fft_output[i] = 0;
      } else {
        fft_output[i] = fft_averaged[i] / fft_counter[i];
      }
    }
  }

  if (yin_add && yin_serial > highpass) {
    find_nearest_fft();
    yin_bubble = yin_serial;
  } else {
    find_lowest_fft();
    fft_bubble = fft_serial;
  }
  if (output_serial) { stream_serial(); }

  int divider = 0;
  float freq_float = 0;
  if (yin_add && yin_bubble > highpass) {
    freq_float += yin_bubble;
    divider++;
  }
  if (fft_add && fft_bubble > highpass) {
    freq_float += fft_bubble;
    divider++;
  }
  if (divider == 0) {
    freq_int = 0;
  } else {
    freq_int = round((float)freq_float * 1000.0f / divider);
  }
  if (freq_int < 100000) {
    freq_int = round((float)freq_int / 10);
    decpoint = 2;
  } else if (freq_int < 1000000) {
    freq_int = round((float)freq_int / 100);
    decpoint = 1;
  } else if (freq_int < 10000000) {
    freq_int = round((float)freq_int / 1000);
    decpoint = 4;
  }
  bool led_state;
  for (int j = 0; j < 9; j++) {
    if (freq_int == pitch_array[j]) {
      led_state = 1;
      break;
    } else {
      led_state = 0;
    }
  }
  if (led_oldstate != led_state) {
    if (led_state) {
      led.on();
    } else {
      led.off(500);
    }
    led_oldstate = led_state;
  }
  if (freq_int != 0) { display.setNumber(freq_int, decpoint); }

  yin_averaged = 0;
  yin_counter = 0;
  yin_serial = 0;
  yin_bubble = 0;
  fft_serial = 0;
  fft_bubble = 0;
  for (int i = 0; i < number_of_freqs; i++) {
    fft_output[i] = 0;
    fft_averaged[i] = 0;
    fft_counter[i] = 0;
  }
}

void find_nearest_fft() {
  float yin_percent = yin_serial / 100.0f * percent;
  bool success = 0;
  for (int i = 0; i < number_of_freqs; i++) {
    if (fft_output[i] < (yin_serial + yin_percent) && fft_output[i] > (yin_serial - yin_percent)) {
      fft_serial = fft_output[i];
      success = 1;
      break;
    }
  }
  if (success) {
    fft_bubble = fft_serial;
  } else {
    find_lowest_fft();
  }
}

void find_lowest_fft() {
  float fft_temp = 15000.0f;
  for (int i = 0; i < number_of_freqs; i++) {
    if (fft_output[i] < fft_temp) { fft_temp = fft_output[i]; }
  }
  fft_serial = fft_temp;
}

void tuner_sound() {
  if (tuner_tone) {
    tuner_tone = 0;
    noTone(pin_speaker);
    tuner_stop = 1;
    stopwatch_tuner = 0;
    float temp = peak.read();
  }  // dummy read
  else {
    display_pitch();
    tuner_tone = 1;
    tone(pin_speaker, pitch);
  }
}

void tuner_plus() {
  if (pitch < 500) {
    pitch++;
    tuner_new_pitch();
  }
}

void tuner_minus() {
  if (pitch > 300) {
    pitch--;
    tuner_new_pitch();
  }
}

void tuner_new_pitch() {
  pitch_calc();
  tuner_stop = 1;
  display_pitch();
  if (tuner_tone) {
    noTone(pin_speaker);
    tone(pin_speaker, pitch);
  } else {
    stopwatch_tuner = 0;
  }
  serial->print("new pitch = ");
  serial->print(pitch);
  serial->println("Hz");
}
