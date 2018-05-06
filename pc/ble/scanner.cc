#include <blepp/lescan.h>
#include <blepp/pretty_printers.h>
#include <blepp/blestatemachine.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

static bool
isBeacon(const BLEPP::AdvertisingResponse &ad)
{
	if ((ad.type != BLEPP::LeAdvertisingEventType::ADV_SCAN_IND) &&
	    (ad.type != BLEPP::LeAdvertisingEventType::ADV_IND)) {
		return false;	
	}

	return true;
}

int
main(void)
{
	BLEPP::log_level = BLEPP::LogLevels::Error;
	BLEPP::HCIScanner scanner;

	while (true) {
		std::vector<BLEPP::AdvertisingResponse> ads =
		    scanner.get_advertisements();
		for (const auto &ad : ads) {
			if (!isBeacon(ad)) {
				continue;
			}
			cout << "Beacon: " << ad.address << endl;
			for (const auto &uuid : ad.UUIDs) {
				cout << "\tUUID: " << to_str(uuid) << endl;
			}
		}
	sleep(1);
	}
}
