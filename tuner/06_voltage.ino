
int pin_voltage = A1;

float aref = 3.27;
int voltage_devider_R1 = 331; // 331k
int voltage_devider_R2 = 70;  // 220k

int analogread_value;
float V_out;
float V_in;

elapsedMillis stopwatch_voltage = 1000;

void setup_voltage() {
  pinMode(pin_voltage, INPUT_PULLDOWN);
  int x = analogRead(pin_voltage); //discard this reading
}

void start_voltage() {
  mode_voltage = 1;
  stopwatch_voltage = 1000;
  value_old = 0;
}

void voltage() {
  analogread_value = analogRead(pin_voltage);
  V_out = (analogread_value / pow(2, analogread_res)) * aref;
  V_in = V_out / voltage_devider_R2 * (voltage_devider_R1 + voltage_devider_R2);
  if (V_in < 3.3) {power_loss();}
  if (stopwatch_voltage >= 1000) {
    if (V_in < 3.6) {voltage_alarm = 1; bubble_voltage(V_in); stopwatch_tuner = 1200; tuner_stop = 1;}
    else if (mode_voltage) {if (voltage_alarm) {voltage_alarm = 0;} bubble_voltage(V_in);}
    stopwatch_voltage = 0;
  }
}

void power_loss() {
  eeprom_write();
}
