#include <SerialCommand.h>
// some modifications were done to the cpp file:
//  + configured to use only hardware serial ports
//  + changed default delimiter to "#"
//  + modified line "if(isprint(inChar))" to "if(isprint(inChar) || inChar == 0xC3 || inChar == 0x84 || inChar == 0xA4 || inChar == 0x96 || inChar == 0xB6 || inChar == 0x9C || inChar == 0xBC || inChar == 0x9F)"

Stream* serial;
SerialCommand sercmd;

#include <LEDsimple.h>
LEDsimple led(LED_BUILTIN);

bool usage = 0;   // set to 1 to dispaly memory and cpu usage on serial output, adjust cpu speed accordingly

bool runonce = 1;
int analogread_res = 12;
bool mode_tuner = 0;
bool tuner_stop = 0;
bool tuner_tone = 0;
bool mode_metronome = 0;
bool metronome_started = 0;
bool mode_voltage = 1;
bool voltage_alarm = 0;

elapsedMillis stopwatch_boot;
elapsedMillis stopwatch_tuner;
elapsedMillis stopwatch_metronome;

void setup() {
  analogReadResolution(analogread_res); // don't set when using AudioInputAnalog
  set_values_from_eeprom();
  setup_bubble();
  setup_tuner();
  setup_serial();
  setup_voltage();
  setup_encoder();
  setup_metronome();
  stopwatch_boot = 0;
}

void loop() {
  if (runonce && stopwatch_boot >= 1000) {runonce = 0; mode_voltage = 0; start_tuner(); serial_info();}
  if (tuner_stop && stopwatch_tuner >= 1000) {tuner_stop = 0;}
  if (mode_tuner && !tuner_tone && !tuner_stop) tuner();
  if (metronome_started && stopwatch_metronome >= 1000) {metronome_started = 0; metronome_beats();}
  if (mode_metronome) metronome();
  button();
  encoder();
  voltage();
  bubble();
  sercmd.readSerial();
  led.update();
}
