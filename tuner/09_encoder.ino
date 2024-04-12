
const uint8_t pinA = 19;
const uint8_t pinB = 17;

boolean chanA;
boolean chanB;

int8_t oldstate = 3;
int enc = 0;
int val = 0;
int old = 0;

const uint8_t detents = 3;

const int8_t enctable[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

// table for noisy buttons with half resolution:
// const int8_t enctable[] = {0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, -1, 0, 0};

void setup_encoder() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
}

void encoder() {
  chanA = digitalReadFast(pinA);
  chanB = digitalReadFast(pinB);
  int8_t state = chanA | (chanB << 1);
  if (oldstate != state) {
    enc += enctable[state | (oldstate << 2)];
    if (state == detents)
      val = enc >> 2;
    oldstate = state;
  }
  if (val > old) {
    enc_plus();
    old = val;
  }
  else if (val < old) {
    enc_minus();
    old = val;
  }
}

void enc_plus() {
  if (mode_metronome) {metronome_plus();}
  else if (mode_tuner) {tuner_plus();}
}

void enc_minus() {
  if (mode_metronome) {metronome_minus();}
  else if (mode_tuner) {tuner_minus();}
}
