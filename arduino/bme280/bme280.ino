
#include <SparkFunBME280.h>

BME280  bme280;

void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  // put your setup code here, to run once:
  bme280.settings.commInterface = I2C_MODE;
  bme280.settings.I2CAddress = 0x77;
  bme280.settings.runMode = 3; //  3, Normal mode
  bme280.settings.tStandby = 0; //  0, 0.5ms
  bme280.settings.filter = 0; //  0, filter off

  //tempOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  bme280.settings.tempOverSample = 1;

  //pressOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  bme280.settings.pressOverSample = 1;

  //humidOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  bme280.settings.humidOverSample = 1;

  if (bme280.begin() != 0x60) {
    Serial.println("BME280 failed");
    while (1);
  }

  Serial.println("OK");
}

void loop() {
  // put your main code here, to run repeatedly:

}
