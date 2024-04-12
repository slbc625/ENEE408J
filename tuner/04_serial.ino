#include <TimeLib.h>

constexpr int msgBufSize = 200;
bool fft_multi = 0;

void setup_serial() {
  Serial.begin(115200);
  serial = &Serial;
  sercmd.addCommand("pitch", set_pitch);
  sercmd.addCommand("rate", set_rate);
  sercmd.addCommand("prob", set_prob);
  sercmd.addCommand("on", set_on);
  sercmd.addCommand("off", set_off);
  sercmd.addCommand("yin", set_yin);
  sercmd.addCommand("fft", set_fft);
  sercmd.addCommand("yinalpha", set_yinalpha);
  sercmd.addCommand("fftalpha", set_fftalpha);
  sercmd.addCommand("ign", set_rectreshold);
  sercmd.addCommand("freqs", set_freqs);
  sercmd.addCommand("show", set_display);
  sercmd.addCommand("find", set_find);
  sercmd.addCommand("help", set_help);
  sercmd.addCommand("level", set_reclevel);
  sercmd.addCommand("gain", set_gain);
  sercmd.addCommand("filter", set_filter);
  sercmd.addCommand("save", set_save);
  sercmd.addCommand("recall", set_recall);
  sercmd.addCommand("defaults", set_defaults);
  sercmd.addDefaultHandler(read_err);
}

void stream_usage() {
  if (usage) {
    serial->print("memory usage: ");
    serial->print(AudioMemoryUsageMax());
    int cpuusage = AudioProcessorUsageMax();
    serial->print(" - cpu usage: ");
    serial->print(cpuusage);
    if (rec_level || output_serial) {serial->print(" - ");}
    else {serial->println();}
  }
}

void serial_info() {
  serial->println(" ");
  serial->println("make sure to have serial monitor set to send NL/CR");
  serial->println(" ");
#if defined(KINETISK)
  serial->println("streaming filtered and gained signal to left USB audio channel");
  serial->println("streaming unprocessed signal to right USB audio channel");
  //teensy 4.x uses 44100 Hz
  //teensy 3.x uses 44117 Hz
  serial->println("to record with audacity on linux use pulse and record at 44117Hz");
  serial->println(" ");
#endif
  serial->print("tuning pitch is set to: ");
  serial->print(pitch);
  serial->println("Hz");
  serial->println("type pitch#442 to change pitch to 442Hz");
  serial->println(" ");
  if (yin_add) {serial->println("yin algorithm is active");} else {serial->println("yin algorithm is off");}
  serial->println("type yin#1 or yin#0 to toggle yin");
  serial->println(" ");
  if (fft_add) {serial->println("fft analzer is active");} else {serial->println("fft analyzer is off");}
  serial->println("type fft#1 or fft#0 to toggle fft");
  serial->println(" ");
  serial->print("analyzing rate is set to: ");
  serial->print(1000 / tuner_rate);
  serial->println("Hz");
  serial->println("type rate#100 to change samplerate to 100Hz");
  serial->println(" ");
  serial->print("mic gain is set to: ");
  serial->println(gain, 1);
  serial->println("type gain#65 to change gain to 6.5");
  serial->println("(gain > 1.0: amplification)");
  serial->println("(gain < 1.0: attenuation)");
  serial->println("(gain = 0.0: mute)");
  serial->println("(gain = 1.0: pass through)");
  serial->println("(gain < 0.0: invert signal)");
  serial->println(" ");
  serial->print("mic highpass is set to: ");
  serial->println(highpass);
  serial->println("type filter#50 to filter out freqs below 50Hz");
  serial->println("(cleaner signal with highpass > 20)");
  serial->println(" ");
  serial->print("analyzing treshold is set to: ");
  serial->print(rec_treshold * 100, 0);
  serial->println("%");
  serial->println("type ign#15 to ignore sound quieter than 15%");
  serial->println(" ");
  serial->print("yin probability is set to: ");
  serial->print(yin_probability * 100, 1);
  serial->println("%");
  serial->println("type prob#995 to change yin probability to 99.5%");
  serial->println("(greater accuracy as probability -> 99.9%)");
  serial->println(" ");
  serial->print("yin smoothing filter constant alpha is set to: ");
  serial->println(yin_alpha * 10, 0);
  serial->println("type yinalpha#5 to change yin alpha to 5 (valid: 0-10)");
  serial->println("(smoother as alpha -> 10, but with alpha = 10 slow or no updating)");
  serial->println("(alpha 0 = smoothing off and averaging on)");
  serial->println("(smoothing = good for logging, averaging = good for tuning)");
  serial->println(" ");
  serial->print("fft smoothing filter constant alpha is set to: ");
  serial->println(fft_alpha * 10, 0);
  serial->println("type fftalpha#5 to change fft alpha to 5 (valid: 0-10)");
  serial->println("(smoother as alpha -> 10, but with alpha = 10 slow or no updating)");
  serial->println("(alpha 0 = smoothing off and averaging on)");
  serial->println("(smoothing = good for logging, averaging = good for tuning)");
  serial->println(" ");
  serial->print("fft number of freqs is set to: ");
  serial->println(number_of_freqs);
  serial->println("type freqs#5 to change number of freqs to 5 lines (valid: up to 10)");
  serial->println(" ");
  serial->print("find closest fft freq to yin tolerance is set to: ");
  serial->print(percent);
  serial->println("%");
  serial->println("type find#5 to set tolerance to +/- 5%");
  serial->println(" ");
  serial->print("fft output is set to: ");
  if (!fft_multi) {serial->println("single");}
  else {serial->println("multi");}
  serial->println("type show#0 to show only fundamental freq");
  serial->println("and show#1 to show all freqs");
  serial->println(" ");
  serial->println("type level#1 or level#0 to show/hide rec level");
  serial->println(" ");
  serial->println("type defaults# to set default settings");
  serial->println(" ");
  serial->println("type save# to save settings to eeprom");
  serial->println(" ");
  serial->println("type recall# to read settings from eeprom");
  serial->println(" ");
  serial->println("type on# or off# to toggle data stream of yin and fft");
  serial->println(" ");
  serial->println("type help# to show this info at any time");
  serial->println(" ");
}

void set_help() {
  serial->println(" ");
  output_serial = 0;
  rec_level = 0;
  serial_info();
}

void set_freqs() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {number_of_freqs = atol(arg);}
  fft.lines(number_of_freqs);
  serial->print("number of fft freqs = ");
  serial->println(number_of_freqs);
}

void set_display() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {fft_multi = atol(arg);}
  if (fft_multi) {
    serial->println("set to show full number of fft freqs");
  }
  else {
    serial->println("set to show only fundamental fft freq");
  }
}

void set_find() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {percent = atol(arg);}
  serial->print("new fft freq finding tolerance = ");
  serial->print(percent);
  serial->println("%");
}

void set_prob() {
  char *arg;
  int prob_temp;
  arg = sercmd.next(); if (arg != NULL) {prob_temp = atol(arg);}
  if (prob_temp >= 100 ) {yin_probability = 0.001 * prob_temp;}
  else {yin_probability = 0.01 * prob_temp;}
  serial->print("new yin_probability = ");
  serial->print(yin_probability * 100, 1);
  serial->println("%");
}

void set_rate() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {tuner_rate = 1000 / atol(arg);}
  serial->print("new samplerate = ");
  serial->print(1000 / tuner_rate);
  serial->println("Hz");
}

void set_on() {
  serial->println("stream turned on");
  setTime(0, 0, 0, 1, 1, 2020);
  output_serial = 1;
}

void set_off() {
  serial->println("stream turned off");
  output_serial = 0;
}

void stream_serial() {
  serial->print("time: ");
  time();
  serial->print(" - yin: ");
  if (yin_add) {
    serial->print(yin_serial, 2);
  }
  else {
    serial->print("-.--");
  }
  serial->print(" - fft: ");
  if (fft_add) {
    if (fft_multi) {for (int i = 0; i < number_of_freqs; i++) {serial->print(fft_output[i]); if (i < number_of_freqs - 1) {serial->print(" : ");}}}
    else {serial->print(fft_serial, 2);}
  }
  else {
    serial->print("-.--");
  }
  serial->println();
}

void set_yin() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {yin_add = atol(arg);}
  if (yin_add) {
    serial->println("yin turned on");
  }
  else {
    serial->println("yin turned off");
  }
}

void set_fft() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {fft_add = atol(arg);}
  if (fft_add) {
    serial->println("fft turned on");
  }
  else {
    serial->println("fft turned off");
  }
}

void set_fftalpha() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {fft_alpha = 0.1f * atol(arg);}
  fft.smoothing(fft_alpha);
  if (fft_alpha == 0) {serial->println("fft: smoothing off, averaging on");}
  else {
    serial->print("new fft alpha = ");
    serial->println(fft_alpha * 10, 0);
  }
}

void set_yinalpha() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {yin_alpha = 0.1f * atol(arg);}
  if (yin_alpha == 0) {serial->println("yin: smoothing off, averaging on");}
  else {
    serial->print("new yin alpha = ");
    serial->println(yin_alpha * 10, 0);
  }
}

void set_reclevel() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {rec_level = atol(arg);}
  if (rec_level) {serial->println("rec level turned on");}
  else {serial->println("rec level turned off");}
}

void set_rectreshold() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {rec_treshold = 0.01f * atol(arg);}
  serial->print("new rec treshold = ");
  serial->print(rec_treshold * 100, 0);
  serial->println("%");
}

void stream_reclevel() {
  if (rec_level) {
    serial->print("rec level in % : ");
    if (reclevel_float < 0.01f) {serial->print(reclevel_float * 100.0f, 1);}
    else {serial->print(reclevel_float * 100.0f, 0); if (reclevel_float >= 0.99f) {led.blink(30, 10);}}
    if (output_serial) {serial->print(" - ");}
    else {serial->println();}
  }
}

void set_gain() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {gain = 0.1f * atol(arg);}
  amp.gain(gain);
  serial->print("gain is set to ");
  serial->println(gain, 1);
}

void set_filter() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {highpass = atol(arg);}
  filter.frequency(highpass);
  serial->print("highpass is set to ");
  serial->print(highpass);
  serial->println("Hz");
}

void set_pitch() {
  char *arg;
  arg = sercmd.next(); if (arg != NULL) {pitch = atol(arg);}
  tuner_new_pitch();
}

void set_save() {eeprom_write(); serial->println("settings saved to eeprom"); led.blink(30, 10);}
void set_recall() {set_values_from_eeprom(); serial->println("settings recalled from eeprom");}
void set_defaults() {set_values_from_defaults(); serial->println("all settings set to default (but not saved to eeprom)");}

void read_err() {
  serial->println("unknown command");
}

void time() {
  printDigits(hour());
  serial->print(":");
  printDigits(minute());
  serial->print(":");
  printDigits(second());
}

void printDigits(int digits) {
  if (digits < 10) {serial->print('0');}
  serial->print(digits);
}
