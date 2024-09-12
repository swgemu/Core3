#ifndef PACKEDQUATERNION_H_
#define PACKEDQUATERNION_H_

#include "engine/engine.h"

class PackedQuaternion : public Object {
private:
	static constexpr float directionScale = 127.f;
	static constexpr float directionScaleInv = 1.f / directionScale;

protected:
	int8 w;
	int8 x;
	int8 y;
	int8 z;

public:
	PackedQuaternion() {
		w = 127;
		x = 0;
		y = 0;
		z = 0;
	}

	PackedQuaternion(const Quaternion& value) {
		set(value);
	}

	void set(const Quaternion& value) {
		w = Math::clamp(-1.f, value.getW(), 1.f) * directionScale;
		x = Math::clamp(-1.f, value.getX(), 1.f) * directionScale;
		y = Math::clamp(-1.f, value.getY(), 1.f) * directionScale;
		z = Math::clamp(-1.f, value.getZ(), 1.f) * directionScale;
	}

	void parse(Message* message) {
		w = message->readSignedByte();
		x = message->readSignedByte();
		y = message->readSignedByte();
		z = message->readSignedByte();
	}

	void write(Message* message) const {
		message->writeSignedByte(w);
		message->writeSignedByte(x);
		message->writeSignedByte(y);
		message->writeSignedByte(z);
	}

	Quaternion get() const {
		Quaternion direction(w, x, y, z);
		direction.normalize();

		return direction;
	}
};


#endif // PACKEDQUATERNION_H_
