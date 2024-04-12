
int index_of_beats_default = 10;
int index_of_beats;

int beats[40] = {40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 63, 66, 69, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 126, 132, 138, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216};
int metronome_ms[40];
bool metronome_beep = 0;

elapsedMillis stopwatch_beat;

void setup_metronome() {
  pinMode(pin_speaker, OUTPUT);
  for (int k = 0; k < 40; k++) {
    metronome_ms[k] = round((float)60000 / beats[k]);
  }
}

void start_metronome() {
  mode_metronome = 1;
  metronome_beep = 0;
  display.setChars("bEAt");
  stopwatch_metronome = 0;
  metronome_started = 1;
}

void metronome() {
  if (stopwatch_beat >= metronome_ms[index_of_beats]) {
    led.blink(40, 1);
    if (metronome_beep) {tone(pin_speaker, 1100, 40);}
    stopwatch_beat = 0;
  }
}

void metronome_plus() {
  if (index_of_beats < 39) {
    index_of_beats++;
    metronome_beats();
  }
}

void metronome_minus() {
  if (index_of_beats > 0) {
    index_of_beats--;
    metronome_beats();
  }
}

void metronome_beats() {
  char buf[5];
  memset(buf, 0, sizeof(buf));
  snprintf(buf, sizeof(buf), "%4d", beats[index_of_beats]);
  display.setChars(buf);
}
