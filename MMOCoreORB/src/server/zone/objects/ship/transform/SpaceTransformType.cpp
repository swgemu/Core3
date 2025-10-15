#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/transform/SpaceTransformType.h"

SpaceTransformType::SpaceTransformType(ShipObject* ship, int type) : Object() {
	initializeType(ship, type);
}

void SpaceTransformType::initializeType(ShipObject* ship, int type) {
	if (ship == nullptr) {
		return;
	}

	setRotationDamp(ship->getBoundingRadius());
	setTransformType(type);
}

void SpaceTransformType::setThrottleRate() {
	switch (transformType) {
		case Type::SLOW: {
			throttleMin = 0.25f;
			throttleMax = 0.5f;
			break;
		}
		case Type::DOCK: {
			throttleMin = 0.f;
			throttleMax = 0.5f;
			break;
		}
		case Type::FAST: {
			throttleMin = 0.5f;
			throttleMax = 1.f;
			break;
		}
		case Type::AUTO:
		case Type::FORM:
		default: {
			throttleMin = 0.f;
			throttleMax = 1.f;
		}
	}
}

void SpaceTransformType::setRotationRate() {
	switch (transformType) {
		case Type::SLOW:
		case Type::DOCK:
		case Type::FORM: {
			rotationRate[Rotation::YAW] = 0.5f;
			rotationRate[Rotation::PITCH] = 0.5f;
			rotationRate[Rotation::ROLL] = 0.5f;
			break;
		}
		case Type::FAST:
		case Type::AUTO:
		default: {
			rotationRate[Rotation::YAW] = 1.f;
			rotationRate[Rotation::PITCH] = 1.f;
			rotationRate[Rotation::ROLL] = 0.5f;
		}
	}

	rotationRate = rotationRate * rotationDamp;
}

void SpaceTransformType::setRotationDamp(float radius) {
	if (radius <= DAMP_RADIUS_MIN) {
		return;
	}

	float rotationMass = Math::clamp(0.f, (float)((radius - DAMP_RADIUS_MIN) / DAMP_RADIUS_MAX), 1.f);

	rotationDamp[Rotation::YAW] = 1.f - (rotationMass * 0.25f);
	rotationDamp[Rotation::PITCH] = 1.f - (rotationMass * 0.5f);
	rotationDamp[Rotation::ROLL] = 1.f - rotationMass;
}
