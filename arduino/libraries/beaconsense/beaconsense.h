#ifndef __BEACONSENSE_H__
#define __BEACONSENSE_H__

#include <stdint.h>

// The SENSOR_TYPE enums are for my environmental sensors, but any value can be
// used.
typedef enum {
	SENSOR_TEMPERATURE,
	SENSOR_HUMIDITY,
	SENSOR_SOIL_MOISTURE,
} SENSOR_TYPE;

const uint8_t	header[4] = {0x45, 0x4e, 0x56, 0x53};

bool	write_beacon(char *beacon, uint32_t id, uint32_t sensor);

#endif // __BEACON_SENSE_H__