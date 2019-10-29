/*
 * This is an experiment to verify a question I had about
 * deep sleep on the SAMD boards; it seemed like peripherals
 * would remain powered during sleep (e.g. so as to not have
 * to reinit sensors), but I wanted to be sure. I connected
 * a multimeter to an Adafruit Feather M4 Express's 3V3 and GND pins
 * and ran this code. At no point did the voltage drop :)
 */
#include <Adafruit_SleepyDog.h>


void
setup()
{
	Serial.begin(9600);	
	while (!Serial) ;
	Serial.println("BOOTING");
}


void
loop()
{
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.println("Sleeping...");
	delay(5000);

	// Sleep for 60 seconds.
	digitalWrite(LED_BUILTIN, LOW);
	int	slept = Watchdog.sleep(60000);
#if defined(USBCON) && !defined(USE_TINYUSB)
	USBDevice.attach();
#endif

	digitalWrite(LED_BUILTIN, HIGH);
	Serial.print("Slept for ");
	Serial.print(slept);
	Serial.println(" us.");
}
