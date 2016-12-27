/*
 * PackedRotationRate.h
 *
 *  Created on: Apr 4, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDROTATIONRATE_H_
#define SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDROTATIONRATE_H_

float const PI_2 = 3.14159265358979323846f / 2.f;

class PackedRotationRate {
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
		rate = static_cast<int8>(clamp(-(PI_2), rate, (PI_2))*(127.f / (PI_2)));
	}

	float get() {
		return rate*((PI_2)/127.f);
	}

	void parse(Message* message) {
		rate = message->readSignedByte();
	}

	void write(Message* message) {
		message->writeSignedByte(rate);
	}
};

#endif /* SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDROTATIONRATE_H_ */
