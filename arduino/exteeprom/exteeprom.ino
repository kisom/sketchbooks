#include <extEEPROM.h>
#include <Wire.h>

extEEPROM mem(kbits_512, 1, 128);

void setup() {
  Serial.begin(115200);
  uint8_t memStatus = mem.begin(extEEPROM::twiClock400kHz); //go fast!
  if (memStatus) {
    Serial.print("setup failed with code ");
    Serial.println(memStatus);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
