void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  fundFreq=getFundamental
  //scale fundFreq from 0-1023 to real freq
  realFun=fundFreq*divPSec
  closestNote
}

//given an input of 1024 samples, finds fundametal frequency
  //uses yin
int getFundamental(){}

float pitchShift(oldFreq,newFreq, sample){
if (notefreq1.available()){
      waveform5.frequency(notefreq1.read()* newFreq/oldFreq); //1 octave down
      waveform5.amplitude(peak1.read());
}
