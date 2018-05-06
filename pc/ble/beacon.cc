#include <blepp/lescan.h>
#include <string.h>
#include "beacon.h"

Beacon::Beacon(BLEPP::AdvertisingResponse &ad)
{
	for (int i = 0; i < 16; i++) {
		this->uuid[i] = ad.manufacturer_specific_data[0][i];
	}
	this->major = 0;
	this->minor = 0;
}
