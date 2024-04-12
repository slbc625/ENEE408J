
#include <debouncetm.h>

#define buttonpin       18  // button pin
#define samplerate    0.75  // poll interval for update() in msec (a safe starting point would be samplerate = 0.1 * bounce-duration in msec)
#define longpress     0.90  // longpress duration in sec
#define doubleclick   0.50  // doubleclick window in sec

Button button1(buttonpin, INPUT_PULLUP, LOW, samplerate, longpress, doubleclick);  // specify pin, pinMode, polarity, samplerate, longpress duration, doubleclick window

void button() {
  button1.update();
  if (button1.pressed()) {}
  if (button1.released()) {}
  if (button1.longpressed()) {change_mode();}
  if (button1.clicked()) {button_clicked();}
  if (button1.doubleclicked()) {}
}

void change_mode() {
  if (!runonce && mode_tuner) {mode_tuner = 0; start_metronome();}
  else if (!runonce && mode_metronome) {mode_metronome = 0; start_voltage();}
  else if (!runonce && mode_voltage) {mode_voltage = 0; start_tuner();}
}

void button_clicked() {
  if (mode_metronome) {metronome_beep = !metronome_beep;}
  else if (mode_tuner) {tuner_sound();}
}
