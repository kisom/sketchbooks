#ifndef __BEACON_H__
#define __BEACON_H__

#include <blepp/lescan.h>
#include <vector>

class Beacon {
public:
	Beacon(const BLEPP::AdvertisingResponse&);
	uint16_t	major_dev(void) { return this->major; }
	uint16_t	minor_dev(void) { return this->minor; }
private:
	uint8_t	uuid[16];
	uint16_t major;
	uint16_t minor;
};

bool	isBeacon(const BLEPP::AdvertisingResponse &);
void	dump_vector(const std::vector<uint8_t> &);

#endif
