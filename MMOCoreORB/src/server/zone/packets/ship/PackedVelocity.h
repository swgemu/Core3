/*
 * PackedVelocity.h
 *
 *  Created on: Apr 4, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDVELOCITY_H_
#define SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDVELOCITY_H_

#include "PackedUnitVector.h"

class PackedVelocity {
	int16 speed;
	PackedUnitVector direction;

public:
	PackedVelocity() : speed(0) {

	}

	PackedVelocity(const Vector3& vector) {
		set(vector);
	}

	void parse(Message* message) {
		speed = message->readSignedShort();
		direction.parse(message);
	}

	void write(Message* message) {
		message->writeShort(speed);

		direction.write(message);
	}

	void set(const Vector3& v) {
		float const mag = v.length();

		speed = static_cast<int16>(clamp(-512.f, mag, 512.f)*(32767.f / 512.f));

		direction.set(mag ? v/mag : Vector3(0, 0, 1));
	}

	Vector3 get() {
		return direction.get() * (speed*(512.f / 32767.f));
	}
};


#endif /* SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDVELOCITY_H_ */
