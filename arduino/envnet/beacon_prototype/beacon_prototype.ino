#include <bluefruit.h>

#define MANUFACTURER_ID	0x0059

uint8_t beaconID[16] = {
	0x68, 0x65, 0x6c, 0x6c,
	0x6f, 0x2c, 0x20, 0x77,
	0x6f, 0x72, 0x6c, 0x64,
	0x21, 0x6b, 0x64, 0x69
};

BLEBeacon beacon(beaconID, 1, 2, -45);

void setup() {
	Bluefruit.begin();
	Bluefruit.setTxPower(0);
	Bluefruit.setName("env-node-proto");
	beacon.setManufacturer(MANUFACTURER_ID);

	setupBeacon();
	suspendLoop();
}

void setupBeacon() {
	Bluefruit.Advertising.setBeacon(beacon);
	Bluefruit.ScanResponse.addName();
	Bluefruit.Advertising.restartOnDisconnect(true);
	Bluefruit.Advertising.setInterval(160, 160); // in unit of 0.625ms
	Bluefruit.Advertising.setFastTimeout(30); // number of seconds in fast mode
	Bluefruit.Advertising.start(0);		  // stop advertising after n second (0=never stop)
}

void loop() {}