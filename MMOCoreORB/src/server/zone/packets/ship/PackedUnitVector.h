/*
 * PackedUnitVector.h
 *
 *  Created on: Apr 4, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDUNITVECTOR_H_
#define SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDUNITVECTOR_H_

template<class T>inline const T clamp(const T &minT, const T &t, const T &maxT) {
	return (t < minT) ? minT : ((t > maxT) ? maxT : t);
}

class PackedUnitVector {
	enum
	{
		packedSize = 2,
		xSignMask = 0x8000u,
		ySignMask = 0x4000u,
		zSignMask = 0x2000u,
		componentMask = 0x003fu,
		componentMaskBits = 6
	};

	uint16 value;

public:
	PackedUnitVector() : value(0) {

	}

	PackedUnitVector(const Vector3& vector) {
		set(vector);
	}

	void parse(Message* message) {
		value = message->readShort();
	}

	void write(Message* message) {
		message->writeShort(value);
	}

	void set(const Vector3& v) {
		value = 0;
		float x = v.getX();

		if (x < 0.f) {
			x = -x; value |= xSignMask;
		}

		float y = v.getY();

		if (y < 0.f) {
			y = -y;
			value |= ySignMask;
		}

		float z = v.getZ();

		if (z < 0.f) {
			z = -z;
			value |= zSignMask;
		}

		float const w = static_cast<float>(componentMask - 1) / (x + y + z);
		value |= static_cast<uint16>(x * w) << componentMaskBits;
		value |= static_cast<uint16>(y*w);
	}

	Vector3 get() {
		float x = static_cast<float>((value >> componentMaskBits)
				& componentMask);
		float y = static_cast<float>(value & componentMask);
		float z = static_cast<float>(componentMask) - x - y;

		if (value & xSignMask)
			x = -x;

		if (value & ySignMask)
			y = -y;

		if (value & zSignMask)
			z = -z;

		Vector3 v(x, y, z);
		v.normalize();

		return v;
	}
};

#endif /* SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDUNITVECTOR_H_ */
