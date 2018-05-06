#include <blepp/lescan.h>

#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "beacon.h"

/*
 * MSD from a beacon:
 * 59 02 15 45  4e 56 53 42
 * 00 00 00 7b  02 00 00 54
 * 9c 4a 8d 01  00 00 00 d3
 *
 * Flag data:
 * 00 01 01 00  00 00 00 00
 * 10 12 d6 00  00 00 00 00
 * 11 12 d6 00  00 00 00 00
 * 11 12 d6 00  00 00 00
 */

void
dump_vector(const std::vector<uint8_t> &v)
{
	for (size_t i = 0; i < v.size(); i++) {
		std::setfill(0);
		std::cout << std::hex << std::setw(2) << static_cast<int>(v[i]) << " ";
		if (i == 0) {
			continue;
		}

		if ((i % 7) == 0) {
			std::cout << std::endl;
			continue;
		}

		if ((i % 3) == 0) {
			std::cout << " ";
		}
	}
}

static uint16_t
uint16_from_vector(const std::vector<uint8_t> &v, size_t from)
{
	uint8_t		buf[2];
	uint16_t	value;

	buf[0] = v[from];
	buf[1] = v[from+1];
	memcpy(&value, buf, 2);
	return value;
}

Beacon::Beacon(const BLEPP::AdvertisingResponse &ad)
{
	size_t	vec_off = 4;
	for (size_t i = vec_off; i < vec_off+16; i++) {
		this->uuid[i] = ad.manufacturer_specific_data[0][i];
	}
	vec_off += 16;

	this->major = uint16_from_vector(ad.manufacturer_specific_data[0], vec_off);
	vec_off += 2;
	this->minor = uint16_from_vector(ad.manufacturer_specific_data[0], vec_off);
}

bool
isBeacon(const BLEPP::AdvertisingResponse &ad)
{
	if ((ad.type != BLEPP::LeAdvertisingEventType::ADV_SCAN_IND) &&
	    (ad.type != BLEPP::LeAdvertisingEventType::ADV_IND)) {
		return false;	
	}

	return true;
}
