#include <SoftwareSerial.h>

const int rxPin = 3;
const int txPin = 2;

SoftwareSerial  s(rxPin, txPin);

void setup() {
  pinMode(txPin, OUTPUT);
  pinMode(rxPin, INPUT);
  s.begin(9600);

}

const int pinLED = 13;
bool ledState = false;

void loop() {
  if (ledState) {
    digitalWrite(pinLED, LOW);
  } else {
    digitalWrite(pinLED, HIGH);
  }
  ledState = !ledState;
  s.println("hello, world");
  delay(1000);
}
