const int buzzer = 9;
const int speaker = A0;
const int mic = A1;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(mic, INPUT);

}

#define MINFREQ 1000
#define MAXFREQ 5000
int freq = MINFREQ*2;
int delta = 100;

void loop() {
  tone(speaker, freq, 50);
  delay(50);
  tone(speaker, freq+100, 50);
  delay(50);
  tone(speaker, freq, 50);
  delay(50);
  tone(speaker, freq-100, 50);
  delay(50);

  //freq += delta;
  if ((freq >= MAXFREQ) || (freq <= MINFREQ)) {
    delta = -delta;
  }

}
