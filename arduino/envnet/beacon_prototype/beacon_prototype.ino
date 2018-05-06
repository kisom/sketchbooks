#include <beaconsense.h>

#include <bluefruit.h>

/*
 * EXPERIMENT 1
 * 
 * For reference, see https://dl.kyleisom.net/posts/2018/04/30/2018-04-30/. This
 * sketch is an implementation of 'Going Forward' #1. 
 * 
 * A beacon is defined as 
 *     + [4B] a header (the string ENVS)
 *     + [4B] a node identifier (an unsigned 32-bit integer)
 *     + [4B] a sensor reading (an unsigned 32-bit integer)
 *     + [4B] a CRC32 checksum
 * The major number isn't used, but the minor number is meant to be the sensor
 * ID (e.g. temperature, humidity, etc...).
 * 
 * In this first experiment, the beacon is updated every second.
 */

#define MANUFACTURER_ID	0x0059

uint8_t beaconID[16] = {
	0x68, 0x65, 0x6c, 0x6c,
	0x6f, 0x2c, 0x20, 0x77,
	0x6f, 0x72, 0x6c, 0x64,
	0x21, 0x6b, 0x64, 0x69
};


static uint16_t	major = 1;
static uint16_t minor = 0;
static uint32_t	sensors[] = {100, 1000, 10000};
static uint32_t id = 0x42;
BLEBeacon beacon(beaconID, major, minor, -45);

void setup() {
	Serial.begin(9600);
	Bluefruit.begin();
	Bluefruit.setTxPower(0);
	Bluefruit.setName("env-node-proto");
	beacon.setManufacturer(MANUFACTURER_ID);

	uint8_t	addr[6];
	uint8_t status = Bluefruit.Gap.getAddr(addr);
	Serial.print("Adapter address: ");
	for (uint8_t i = 0; i < 5; i++) {
		Serial.print(addr[i], HEX);
		Serial.print(":");
	}
	Serial.println(addr[5], HEX);


	setupBeacon();
}

void setupBeacon() {
	updateBeacon();
	Bluefruit.ScanResponse.addName();
	Bluefruit.Advertising.restartOnDisconnect(true);
	Bluefruit.Advertising.setInterval(160, 160); // in unit of 0.625ms
	Bluefruit.Advertising.setFastTimeout(30); // number of seconds in fast mode
	Bluefruit.Advertising.start(0);		  // stop advertising after n second (0=never stop)
}

void updateBeacon() {
	Bluefruit.Advertising.stop();
	logBeacon();
	beacon.setMajorMinor(major, minor);
	write_beacon(beaconID, id, sensors[minor]);
	sensors[minor]++;
	beacon.setUuid(beaconID);
	minor = (minor + 1) % 3;
	Bluefruit.Advertising.setBeacon(beacon);
	Bluefruit.Advertising.start(0);
}

void logBeacon() {
	Serial.print("major: ");
	Serial.print(major);
	Serial.print(", minor: ");
	Serial.print(minor);
	Serial.print(", id: ");
	Serial.println(sensors[minor]);

}

void loop() {
	delay(1000);
	updateBeacon();
}
