#ifndef SPACETRANSFORM_H_
#define SPACETRANSFORM_H_

#include "engine/engine.h"

class SpaceTransform : public Object {
protected:
	Vector3 position;
	Vector3 rotation;
	Vector3 yprDelta;
	Vector3 velocity;
	float speed;

public:
	SpaceTransform() : Object() {
		speed = 0.f;
	}

	void setPosition(const Vector3& value) {
		position = value;
	}

	void setRotation(const Vector3& value) {
		rotation = value;
	}

	void setYprDelta(const Vector3& value) {
		yprDelta = value;
	}

	void setVelocity(const Vector3& value) {
		velocity = value;
	}

	void setSpeed(float value) {
		speed = value;
	}

	const Vector3& getPosition() const {
		return position;
	}

	const Vector3& getRotation() const {
		return rotation;
	}

	const Vector3& getYprDelta() const {
		return yprDelta;
	}

	const Vector3& getVelocity() const {
		return velocity;
	}

	float getSpeed() const {
		return speed;
	}

	String toDebugString() const {
		StringBuffer msg;
		msg << "SpaceTransform: " << endl
			<< "  position: " << position.toString() << endl
			<< "  rotation: " << rotation.toString() << endl
			<< "  yprDelta: " << yprDelta.toString() << endl
			<< "  velocity: " << velocity.toString() << endl
			<< "  speed:    " << speed;

		return msg.toString();
	}
};

#endif // SPACETRANSFORM_H_
