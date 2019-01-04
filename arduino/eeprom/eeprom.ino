#include <Wire.h>

const int eeprom = 0x50;

const uint8_t data[] = {
  0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77,
  0x6f, 0x72, 0x6c, 0x64
};

void
write_eeprom(uint8_t *data, uint8_t datalen, uint8_t start)
{
  for (uint8_t i = 0; i < datalen; i++) {
    Serial.print("writing byte ");
    Serial.print(i);
    Serial.print("... ");
    Serial.flush();
    Wire.beginTransmission(eeprom + 1);
    Serial.print("[ transmission began ] ");
    Serial.flush();
    Wire.write(0);
    Wire.write(start+i);
    Serial.print("[ wrote address ] ");
    Serial.flush();
    Wire.write(data[i]);
    Serial.print("[ wrote data ] ");
    Serial.flush();
    Wire.endTransmission();
    Serial.print(" [ transmission ended ] ");
    Serial.flush();
    delay(5);
    Serial.println("ok!");
  }
}

void
storeHello()
{
  Serial.println("writing EEPROM");
  write_eeprom(data, 12, 0);
  Serial.println("complete");
}

void
dumpEEPROM(uint8_t start, uint8_t len)
{
  char data;

  Serial.println("reading from EEPROM");

  for (uint8_t i = 0; i < len; i++) {
    Wire.beginTransmission(eeprom);
    Wire.write(0);
    Wire.write(start + i);
    Wire.endTransmission();

    Wire.requestFrom(eeprom, 1);
    while (!Wire.available()) {
      delay(5);
    }
    data = Wire.read();
    Serial.print(data, HEX); Serial.flush();
  }
  Serial.println();
}

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(115200);
  dumpEEPROM(0, 12);
  // storeHello();
}

void loop() {

}
