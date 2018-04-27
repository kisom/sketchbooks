const int ledPin = 17;

void blink(int spacing) {
  digitalWrite(ledPin, HIGH);
  delay(spacing);
  digitalWrite(ledPin, LOW);
}

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  blink(500);
  delay(500);
}
