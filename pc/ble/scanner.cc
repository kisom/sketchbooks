#include <blepp/lescan.h>
#include <blepp/pretty_printers.h>
#include <blepp/blestatemachine.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

static const string bluefruit = "f1:02:0a:f4:64:34";

static bool
isBeacon(const BLEPP::AdvertisingResponse &ad)
{
	if ((ad.type != BLEPP::LeAdvertisingEventType::ADV_SCAN_IND) &&
	    (ad.type != BLEPP::LeAdvertisingEventType::ADV_IND)) {
		return false;	
	}

	return true;
}

static void
showBeacon(const BLEPP::AdvertisingResponse &ad)
{
	struct BLEPP::AdvertisingResponse::Name	name;	

	cout << "Beacon: " << ad.address << endl;
	abort();
	if (ad.local_name) {	
		name = *ad.local_name;
		cout << name.name << endl;
	}
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
