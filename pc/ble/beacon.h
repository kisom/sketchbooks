#ifndef __BEACON_H__
#define __BEACON_H__

#include <blepp/lescan.h>

class Beacon {
public:
	Beacon(BLEPP::AdvertisingResponse&);
private:
	uint8_t	uuid[16];
	uint16_t major;
	uint16_t minor;
};

#endif
