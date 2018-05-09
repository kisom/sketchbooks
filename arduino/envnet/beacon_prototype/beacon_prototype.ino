#include <string.h>

#include <beaconsense.h>

#include <bluefruit.h>
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>

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
 *
 * EXPERIMENT 2
 *
 * How long does the 500 mAh battery last? Every second, we'll write the
 * log with the current power level and the RTC. Then, I'll let it
 * sit overnight.
 */

#define MANUFACTURER_ID	0x0059

// These pins come from AdaFruit and are valid for the nRF52 board.
static const int	batteryVoltage = 7;
static const int	cardSelect = 11;
static const char	logFilename[] = "voltage.log";
RTC_PCF8523		rtc;

uint8_t beaconID[16] = {
	0x68, 0x65, 0x6c, 0x6c,
	0x6f, 0x2c, 0x20, 0x77,
	0x6f, 0x72, 0x6c, 0x64,
	0x21, 0x6b, 0x64, 0x69
};


static uint16_t	major = 1;
static uint16_t minor = 0;
static uint16_t	sensors[] = {100, 1000, 10000};
// static uint32_t id = 0x42;
BLEBeacon beacon(beaconID, major, minor, -45);

static constexpr int ledPin = 17;

void sos() {
	while (true) {
		for (int i = 0; i < 3; i++) {
			digitalWrite(ledPin, HIGH);
			delay(100);
			digitalWrite(ledPin, LOW);
			delay(100);
		}

		delay(200);

		for (int i = 0; i < 3; i++) {
			digitalWrite(ledPin, HIGH);
			delay(300);
			digitalWrite(ledPin, LOW);
			delay(100);
		}

		delay(200);

		for (int i = 0; i < 3; i++) {
			digitalWrite(ledPin, HIGH);
			delay(100);
			digitalWrite(ledPin, LOW);
			delay(100);
		}

		delay(700);
	}
}

void setup() {
	Bluefruit.begin();
	Bluefruit.setTxPower(0);
	beacon.setManufacturer(MANUFACTURER_ID);
	setupBeacon();

	pinMode(batteryVoltage, INPUT);
	if (!SD.begin(cardSelect)) {
		sos();
	}

	if (!rtc.begin()) {
		sos();
	}

	// Set the analog reference to 3.0V (default = 3.6V)
	analogReference(AR_INTERNAL_3_0);

	// Set the resolution to 12-bit (0..4095)
	analogReadResolution(12);
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
	minor = sensors[major];
	beacon.setMajorMinor(major, minor);
	sensors[minor]++;
	beacon.setUuid(beaconID);
	major = (major + 1) % 3;
	Bluefruit.Advertising.setBeacon(beacon);
	Bluefruit.Advertising.start(0);
}

// From https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/master/libraries/Bluefruit52Lib/examples/Hardware/adc_vbat/adc_vbat.ino
#define VBAT_MV_PER_LSB   (0.73242188F)   // 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
#define VBAT_DIVIDER      (0.71275837F)   // 2M + 0.806M voltage divider on VBAT = (2M / (0.806M + 2M))
#define VBAT_DIVIDER_COMP (1.403F)        // Compensation factor for the VBAT divider

int mvToPercent(float mvolts) {
    uint8_t battery_level;

    if (mvolts >= 3000)
    {
        battery_level = 100;
    }
    else if (mvolts > 2900)
    {
        battery_level = 100 - ((3000 - mvolts) * 58) / 100;
    }
    else if (mvolts > 2740)
    {
        battery_level = 42 - ((2900 - mvolts) * 24) / 160;
    }
    else if (mvolts > 2440)
    {
        battery_level = 18 - ((2740 - mvolts) * 12) / 300;
    }
    else if (mvolts > 2100)
    {
        battery_level = 6 - ((2440 - mvolts) * 6) / 340;
    }
    else
    {
        battery_level = 0;
    }

    return battery_level;
}

static constexpr int	formatStringLength = 22;
static constexpr char	formatString[] = "%04d-%02d-%02d %02d:%02d %03d%%\n";
static uint32_t		last_update = 0;

void writeLogfile() {
	int voltage = analogRead(batteryVoltage);
	uint8_t vbat_per = mvToPercent(voltage * VBAT_MV_PER_LSB);

	DateTime now = rtc.now();
	char	line[formatStringLength];
	bool	ok = false;

	snprintf(line, formatStringLength, formatString, now.year(),
	    now.month(), now.day(), now.hour(), now.minute(), voltage);
		
	File log = SD.open(logFilename, FILE_WRITE);
	if (!log) {
		goto exit;
	}

	if (!log.seek(log.size())) {
		goto exit;
	}

	log.write(line);
	ok = true;

exit:
	log.close();
	if (!ok) {
		sos();
	}

	digitalWrite(ledPin, HIGH);
	delay(100);
	digitalWrite(ledPin, LOW);
	delay(100);
	digitalWrite(ledPin, HIGH);
	delay(100);
	digitalWrite(ledPin, LOW);
	last_update = rtc.now().unixtime();
}

void loop() {
	delay(1000);
	updateBeacon();
	if ((rtc.now().unixtime() - last_update) >= 3600) {
		writeLogfile();
	}
}
