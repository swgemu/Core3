/*
 * PackedPosition.h
 *
 *  Created on: Aug 22, 2017
 *	  Author: TheAnswer
 */

#ifndef PACKEDPOSITION_H_
#define PACKEDPOSITION_H_

#include "PackedUnitVector.h"
#include "engine/util/u3d/Vector3.h"

class PackedPosition {
public:
	static const constexpr float positionScale = 32767.f / 8000.f;
	static const constexpr float inversePositionScale = 8000.f / 32767.f;

protected:
	int16 x;
	int16 y;
	int16 z;

public:
	PackedPosition() {
		x = 0;
		y = 0;
		z = 0;
	}

	PackedPosition(const Vector3& vector) {
		set(vector);
	}

	void parse(Message* message) {
		x = message->readSignedShort();
		z = message->readSignedShort();
		y = message->readSignedShort();
	}

	void write(Message* message) {
		message->writeSignedShort(x);
		message->writeSignedShort(z);
		message->writeSignedShort(y);
	}

	void set(const Vector3& vector) {
		x = (int16)(Math::clamp(-8000.0f, vector.getX(), 8000.f) * positionScale);
		y = (int16)(Math::clamp(-8000.0f, vector.getY(), 8000.f) * positionScale);
		z = (int16)(Math::clamp(-8000.0f, vector.getZ(), 8000.f) * positionScale);
	}

	Vector3 get() {
		return Vector3(x,y,z) * inversePositionScale;
	}
};

#endif /* PACKEDPOSITION_H_ */
