#include <blepp/lescan.h>
#include <blepp/pretty_printers.h>
#include <blepp/blestatemachine.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "beacon.h"

using namespace std;

/*
 * from the prototype at one point:
 * f1:02:0a:f4:64:34 is not a valid iBeacon.
 * Manufacturer data: 
 * 59  0  2 15 45  4e 56 53 42 
 *  0  0  0 33   5  0  0 6e 
 * 25 cb d8  1   0  1  0 d3 
 *
 * I *think* that the 0x0059 is a uint16_t containing the Nordic
 * manufacturer ID.
 *
 * Now, what's confusing me is 
 */

static const string bluefruit = "f1:02:0a:f4:64:34";

static void
showBeacon(const BLEPP::AdvertisingResponse &ad)
{
	Beacon beacon(ad);
	cout << "Beacon: " << ad.address << endl;
	cout << "\tMajor: " << beacon.major_dev() << endl;
	cout << "\tMinor: " << beacon.minor_dev() << endl;
}

int
main(void)
{
	BLEPP::log_level = BLEPP::LogLevels::Error;
	BLEPP::HCIScanner scanner(true, BLEPP::HCIScanner::FilterDuplicates::Off,
	    BLEPP::HCIScanner::ScanType::Passive, "");

	while (true) {
		std::vector<BLEPP::AdvertisingResponse> ads =
		    scanner.get_advertisements();
		for (const auto &ad : ads) {
			if (!isBeacon(ad)) {
				continue;
			}

			if (ad.address != bluefruit) {
				continue;
			}
			showBeacon(ad);
		}
	sleep(1);
	}
}
