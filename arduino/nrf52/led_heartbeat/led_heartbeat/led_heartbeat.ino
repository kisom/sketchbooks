const int ledPin = 17;

void blink(int spacing) {
  digitalWrite(ledPin, HIGH);
  delay(spacing);
  digitalWrite(ledPin, LOW);
}

void setup() {
  pinMode(ledPin, OUTPUT);

}

const int short_space = 100;
constexpr int long_space = 1000 - (3 * short_space);

void loop() {
  blink(short_space);
  delay(short_space);
  blink(short_space);
  delay(long_space);
}
