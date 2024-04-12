#include <EEPROM.h>

bool yin_add_temp;
bool fft_add_temp;
int pitch_temp;
float yin_probability_temp;
int tuner_rate_temp;
float fft_alpha_temp;
float yin_alpha_temp;
float rec_treshold_temp;
uint16_t number_of_freqs_temp;
int percent_temp;
int highpass_temp;
float gain_temp;
int index_of_beats_temp;

void eeprom_read() {
  EEPROM.get(0, yin_add_temp);
  EEPROM.get(5, fft_add_temp);
  EEPROM.get(10, pitch_temp);
  EEPROM.get(15, yin_probability_temp);
  EEPROM.get(20, tuner_rate_temp);
  EEPROM.get(25, fft_alpha_temp);
  EEPROM.get(30, yin_alpha_temp);
  EEPROM.get(35, rec_treshold_temp);
  EEPROM.get(40, number_of_freqs_temp);
  EEPROM.get(45, percent_temp);
  EEPROM.get(50, highpass_temp);
  EEPROM.get(55, gain_temp);
  EEPROM.get(60, index_of_beats_temp);
}

void set_values_from_eeprom() {
  eeprom_read();
  yin_add = yin_add_temp;
  fft_add = fft_add_temp;
  pitch = pitch_temp;
  yin_probability = yin_probability_temp;
  tuner_rate = tuner_rate_temp;
  fft_alpha = fft_alpha_temp;
  yin_alpha = yin_alpha_temp;
  rec_treshold = rec_treshold_temp;
  number_of_freqs = number_of_freqs_temp;
  percent = percent_temp;
  highpass = highpass_temp;
  gain = gain_temp;
  index_of_beats = index_of_beats_temp;
}

void eeprom_write() {
  if (yin_add != yin_add_temp) {EEPROM.put(0, yin_add);}
  if (fft_add != fft_add_temp) {EEPROM.put(5, fft_add);}
  if (pitch != pitch_temp) {EEPROM.put(10, pitch);}
  if (yin_probability != yin_probability_temp) {EEPROM.put(15, yin_probability);}
  if (tuner_rate != tuner_rate_temp) {EEPROM.put(20, tuner_rate);}
  if (fft_alpha != fft_alpha_temp) {EEPROM.put(25, fft_alpha);}
  if (yin_alpha != yin_alpha_temp) {EEPROM.put(30, yin_alpha);}
  if (rec_treshold != rec_treshold_temp) {EEPROM.put(35, rec_treshold);}
  if (number_of_freqs != number_of_freqs_temp) {EEPROM.put(40, number_of_freqs);}
  if (percent != percent_temp) {EEPROM.put(45, percent);}
  if (highpass != highpass_temp) {EEPROM.put(50, highpass);}
  if (gain != gain_temp) {EEPROM.put(55, gain);}
  if (index_of_beats != index_of_beats_temp) {EEPROM.put(60, index_of_beats);}
}

void set_values_from_defaults() {
  yin_add = yin_add_default;
  fft_add = fft_add_default;
  pitch = pitch_default;
  yin_probability = yin_probability_default;
  tuner_rate = tuner_rate_default;
  fft_alpha = fft_alpha_default;
  yin_alpha = yin_alpha_default;
  rec_treshold = rec_treshold_default;
  number_of_freqs = number_of_freqs_default;
  percent = percent_default;
  highpass = highpass_default;
  gain = gain_default;
  index_of_beats = index_of_beats_default;
}
