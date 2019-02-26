// Remote temperature sensor built with a Sparkfun BME280 breakout,
// an Adafruit Adalogger, and a RAKWireless WisNode LoRaWAN radio.

#include <RTClib.h>
#include <SparkFunBME280.h>
#include <Streaming.h>
#include <Wire.h>

struct {
  BME280        sensor;
  DateTime      last;
  float         t;
  float         h;
  float         p;
} temperature;

RTC_PCF8523 rtc;
char        eui[] = "353435315B376709";
char        aui[] = "70B3D57ED0017CA6";
char        key[] = "DADA9FE3E547607588AA4DAD97404386";

void distress() {
  pinMode(13, OUTPUT);
  
  while (true) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(700);
  }
}

bool updateTemperature() {
  DateTime updatedAt = rtc.now();

  if (temperature.last.unixtime() > 0 && ((updatedAt.unixtime() - temperature.last.unixtime()) < 30)) {
    // Only sample every 30s.
    return false;
  }

  temperature.t = temperature.sensor.readTempC();
  temperature.p = temperature.sensor.readFloatPressure() / 101325.0;
  temperature.h = temperature.sensor.readFloatHumidity();
  temperature.last = rtc.now();

  return true;
}


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  
  if (!temperature.sensor.beginI2C()) {
    Serial << "BME280 wasn't found via I2C..." << endl;
    distress();
  }

  Serial << "at+version\r\n";
  char buf[256];
  Serial.readBytesUntil('\r', buf, 255);
  Serial << (char *)buf << endl;

  Serial << "BOOT OK" << endl;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (updateTemperature()) {
    DateTime now = temperature.last;
    Serial << now.year() << "-" << now.month() << "-" << now.day() << " ";
    Serial << now.hour() << ":" << now.minute() << ":" << now.second() << endl;
    Serial << "T: " << temperature.t << "C" << endl;
    Serial << "H: " << temperature.h << "%" << endl;
    Serial << "P: " << temperature.p << "ATM" << endl;
  }
}
