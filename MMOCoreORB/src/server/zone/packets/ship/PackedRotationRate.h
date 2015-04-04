/*
 * PackedRotationRate.h
 *
 *  Created on: Apr 4, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDROTATIONRATE_H_
#define SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDROTATIONRATE_H_

#include "engine/engine.h"

#include "PackedUnitVector.h"

class PackedRotationRate {
	float const PI = 3.14159265358979323846f;

	enum
	{
		packedSize = 1
	};

	int8 rate;
public:
	PackedRotationRate() : rate(0) {

	}

	PackedRotationRate(float rate) {
		set(rate);
	}


	void set(float rate) {
		rate = static_cast<int8>(clamp(-(PI/2), rate, (PI/2))*(127.f / (PI/2)));
	}

	float get() {
		return rate*((PI/2)/127.f);
	}

	void parse(Message* message) {
		rate = message->readSignedByte();
	}

	void write(Message* message) {
		message->writeSignedByte(rate);
	}
};

#endif /* SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDROTATIONRATE_H_ */
