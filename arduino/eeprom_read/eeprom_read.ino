#include <Wire.h>

#define EEPROM_ADR 0x50

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(100000);
  Wire.beginTransmission(EEPROM_ADR);
  Wire.write(0);
  Wire.write(1);
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ADR, 1);
  if (Wire.available())
    Serial.println(Wire.read());
}

void loop() {
  // put your main code here, to run repeatedly:

}
