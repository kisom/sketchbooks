#include <SPI.h>
#include <Adafruit_GPS.h>
#include <Streaming.h>
#include <lmic.h>

#define GPSSerial Serial1
Adafruit_GPS GPS(&GPSSerial);

const lmic_pinmap lmic_pins = {
    .nss = 8,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 4,
    .dio = {3, LMIC_UNUSED_PIN, LMIC_UNUSED_PIN},
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (GPS.newNMEAreceived()) {
    Serial << "new sentence received" << endl;
    Serial << GPS.fix << " / " << GPS.fixquality << endl
  }
  delay(100);
}
