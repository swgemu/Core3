#include "ShipObjectTransform.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/packets/ship/ShipUpdateTransformMessage.h"

ShipObjectTransform::ShipObjectTransform(ShipObject* ship) : Object() {
	initializeTransform(ship);
}

void ShipObjectTransform::initializeTransform(ShipObject* ship) {
	Locker lock(&mutex);

	setCurrentTransform(ship);
	previousTransform = currentTransform;
	nextTransform = currentTransform;

	serverTime = System::getMiliTime();
	deltaTime = 0.f;
}

void ShipObjectTransform::setCurrentTransform(ShipObject* ship) {
	Locker lock(&mutex);

	const auto& matrix = *ship->getConjugateMatrix();
	const auto& position = ship->getPosition();
	auto velocity = SpaceMath::matrixToVelocity(matrix);
	auto rotation = SpaceMath::matrixToRotation(matrix);
	float speed = ship->getCurrentSpeed();

	SpaceTransform transform;
	transform.setPosition(position);
	transform.setVelocity(velocity);
	transform.setRotation(rotation);
	transform.setSpeed(speed);

	previousTransform = currentTransform;
	currentTransform = transform;
}

void ShipObjectTransform::setNextTransform(const Vector3& position, float speed, int model) {
	Locker lock(&mutex);

	flightModel = model;

	if (nextTransform.getPosition() == position && nextTransform.getSpeed() == speed) {
		return;
	}

	auto velocity = position - currentTransform.getPosition();
	float distance = SpaceMath::qNormalize(velocity);
	auto rotation = SpaceMath::velocityToRotation(velocity);

	SpaceTransform transform;
	transform.setPosition(position);
	transform.setVelocity(velocity);
	transform.setRotation(rotation);
	transform.setSpeed(speed);

	nextTransform = transform;
	nextDistance = distance;
}

void ShipObjectTransform::setNextTransform(const SpaceTransform& transform, int model) {
	Locker lock(&mutex);

	Vector3 velocity = transform.getPosition() - currentTransform.getPosition();
	float distance = SpaceMath::qNormalize(velocity);

	nextTransform = transform;
	nextTransform.setVelocity(velocity);
	nextDistance = distance;
	flightModel = model;

	if (flightModel != FlightModel::DOCK) {
		auto rotation = SpaceMath::velocityToRotation(velocity);
		nextTransform.setRotation(rotation);
	}
}

void ShipObjectTransform::updateTransform(ShipObject* ship, bool lightUpdate, bool notifyClient) {
	Locker lock(&mutex);

	updateCurrentTransform(ship);
	setDeltaTime();

	if (lightUpdate && isStaticUpdate()) {
		return;
	}

	setSpeed(ship);
	setRotation(ship);
	setPosition(ship);
	setVelocity(ship);

	updateNextTransform(ship);
	updateShip(ship);

	if (lightUpdate && isInertiaUpdate()) {
		return;
	}

	if (notifyClient) {
		broadcastTransform(ship);
	}
}

void ShipObjectTransform::setSpeed(ShipObject* ship) {
	float speedActual = ship->getActualMaxSpeed();
	float speedCurrent = ship->getCurrentSpeed();

	if (speedActual <= 0.f && speedCurrent <= 0.f) {
		return;
	}

	float throttleMax = getThrottleMax();
	float throttleMin = getThrottleMin();
	float throttleMid = ship->getSpeedRotationFactorOptimal();

	throttleMid = Math::max((throttleMin + throttleMax) * 0.5f, throttleMid);

	float speedMin = throttleMin * speedActual;
	float speedMid = throttleMid * speedActual;
	float speedMax = throttleMax * speedActual;

	speedMax = Math::min(nextTransform.getSpeed(), speedMax);

	float radius = (speedActual * deltaTime * 2.f) + 1.f;
	float distance = nextDistance - radius;
	float speedNew = speedMin;

	if (distance > radius || speedCurrent > 0.f) {
		float accelRate = ship->getActualAccelerationRate();
		float decelRate = ship->getActualDecelerationRate();
		float decelDist = (speedMax * speedMax) / decelRate;

		speedNew = Math::min(distance, speedMax);

		if (speedNew > speedMin) {
			float rotationTime = Math::clamp(0.f,SpaceMath::getRotationTime(ship, nextTransform.getRotation()), 5.f);
			float distanceTime = distance / Math::max(speedMax, 1.f);
			float speedTurn = speedMax;

			if (rotationTime > 0.f && distanceTime <= rotationTime) {
				float t = Math::clamp(0.f, distanceTime / rotationTime, 1.f);
				speedTurn = Math::linearInterpolate(speedMin, speedMax, t);
			} else if (rotationTime > 1.f) {
				float t = Math::clamp(0.f, 1.f / rotationTime, 1.f);
				speedTurn = Math::linearInterpolate(speedMin, speedMid, t);
			} else if (rotationTime > 0.f) {
				float t = Math::clamp(0.f, 1.f - rotationTime, 1.f);
				speedTurn = Math::linearInterpolate(speedMid, speedMax, t);
			}

			speedNew = Math::min(speedTurn, speedNew);
		}

		if (speedNew != speedCurrent) {
			speedNew = Math::clamp(-decelRate * deltaTime, speedNew - speedCurrent, accelRate * deltaTime) + speedCurrent;
			speedNew = Math::clamp(speedMin, speedNew, speedMax);
		}
	}

	previousTransform.setSpeed(currentTransform.getSpeed());
	currentTransform.setSpeed(speedNew);
}

void ShipObjectTransform::setRotation(ShipObject* ship) {
	const auto& previousRotation = previousTransform.getRotation();
	const auto& previousYprRates = previousTransform.getYprDelta();
	const auto& currentRotation = currentTransform.getRotation();
	const auto& currentYprRates = currentTransform.getYprDelta();
	const auto& nextRotation = nextTransform.getRotation();

	Vector3 rotation = currentRotation;
	Vector3 yprRates = currentYprRates;

	if (currentRotation != nextRotation) {
		float rollRadius = Math::clamp(0.f, ship->getBoundingRadius() / 128.f, 1.f);
		float rollSpeed = Math::clamp(0.f, ship->getCurrentSpeed() / ship->getEngineMaxSpeed(), 1.f);
		float rollDamp =  (1.f - rollRadius) * rollSpeed;

		Vector3 accel = Vector3(ship->getActualYawAccelerationRate(), ship->getActualPitchAccelerationRate(), ship->getActualRollAccelerationRate() * rollDamp) * deltaTime;
		Vector3 actual = Vector3(ship->getActualYawRate(), ship->getActualPitchRate(), ship->getActualRollRate() * rollDamp) * deltaTime;
		Vector3 delta = SpaceMath::getRotationRate(nextRotation, currentRotation);

		if (flightModel != FlightModel::DOCK && fabs(delta[RotationAxis::YAW]) >= 0.01f) {
			delta[RotationAxis::ROLL] = SpaceMath::getRotationRate(delta[RotationAxis::ROLL] + (-delta[RotationAxis::YAW] * 0.5f));
		}

		for (int axis = 0; axis < 3; ++axis) {
			float lastDelta = currentYprRates[axis] * deltaTime;
			float thisDelta = Math::clamp(lastDelta - accel[axis], delta[axis], lastDelta + accel[axis]);
			rotation[axis] = SpaceMath::getRotationRate(Math::clamp(-actual[axis], thisDelta, actual[axis]) + currentRotation[axis]);
		}

		if (rotation != currentRotation) {
			yprRates = SpaceMath::getRotationRate(rotation, currentRotation) * (1.f / deltaTime);
		}
	}

	previousTransform.setRotation(currentRotation);
	currentTransform.setRotation(rotation);

	previousTransform.setYprDelta(currentYprRates);
	currentTransform.setYprDelta(yprRates);
}

void ShipObjectTransform::setPosition(ShipObject* ship) {
	const auto& currentPosition = currentTransform.getPosition();
	const auto& currentVelocity = currentTransform.getVelocity();
	float currentSpeed = currentTransform.getSpeed();

	Vector3 position = (currentVelocity * currentSpeed * deltaTime) + currentPosition;

	position.setX(Math::clamp(-7999.f, position.getX(), 7999.f));
	position.setY(Math::clamp(-7999.f, position.getY(), 7999.f));
	position.setZ(Math::clamp(-7999.f, position.getZ(), 7999.f));

	if (position == currentPosition) {
		return;
	}

	previousTransform.setPosition(currentPosition);
	currentTransform.setPosition(position);
}

void ShipObjectTransform::setVelocity(ShipObject* ship) {
	Vector3 velocity = flightModel == FlightModel::DOCK ? nextTransform.getVelocity() : SpaceMath::rotationToVelocity(currentTransform.getRotation());

	if (ship->getCurrentSpeed() >= 1.f) {
		float slipRate = Math::clamp(0.f, (ship->getCurrentSpeed() / (float)VELOCITY_MAX) * ship->getSlip(), 1.f);
		velocity = Math::linearInterpolate(currentTransform.getVelocity(), velocity, 1.f - slipRate);
	}

	previousTransform.setVelocity(currentTransform.getVelocity());
	currentTransform.setVelocity(velocity);
}

void ShipObjectTransform::updateCurrentTransform(ShipObject* ship) {
	if (ship->getPosition() != currentTransform.getPosition()) {
		previousTransform.setPosition(currentTransform.getPosition());
		currentTransform.setPosition(ship->getPosition());
		updateNextTransform(ship);
	}

	if (ship->getCurrentSpeed() != currentTransform.getSpeed()) {
		previousTransform.setSpeed(currentTransform.getSpeed());
		currentTransform.setSpeed(ship->getCurrentSpeed());
	}
}

void ShipObjectTransform::updateNextTransform(ShipObject* ship) {
	Vector3 velocity = nextTransform.getPosition() - currentTransform.getPosition();
	float distance = SpaceMath::qNormalize(velocity);
	float radius = (currentTransform.getSpeed() * deltaTime) + 1.f;

	if (distance <= radius) {
		nextTransform.setPosition(currentTransform.getPosition());
		nextDistance = 0.f;
		return;
	}

	nextTransform.setVelocity(velocity);
	nextDistance = distance;

	if (flightModel != FlightModel::DOCK) {
		auto rotation = SpaceMath::velocityToRotation(velocity);
		nextTransform.setRotation(rotation);
	}
}

void ShipObjectTransform::updateShip(ShipObject* ship) {
	ship->setPosition(currentTransform.getPosition());

	if (currentTransform.getRotation() != previousTransform.getRotation()) {
		bool precision = ship->getBoundingRadius() >= 64.f || flightModel == FlightModel::FAST;
		auto direction = SpaceMath::rotationToQuaternion(currentTransform.getRotation(), precision);
		ship->setDirection(direction);
		ship->setRotationMatrix(direction);
	}

	if (currentTransform.getSpeed() != previousTransform.getSpeed()) {
		ship->setCurrentSpeed(currentTransform.getSpeed());
		ship->updateSpeedRotationValues(false);
	}
}

void ShipObjectTransform::broadcastTransform(ShipObject* ship) {
	auto shipCov = ship->getCloseObjects();

	if (shipCov == nullptr) {
		return;
	}

	PackedVelocity velocity;
	PackedRotationRate rateY;
	PackedRotationRate rateP;
	PackedRotationRate rateR;

	if (currentTransform.getSpeed() > 0.f) {
		Vector3 deltaV = currentTransform.getVelocity() * currentTransform.getSpeed();
		velocity.set(Vector3(deltaV.getX(), deltaV.getZ(), deltaV.getY()));

		const auto& yprRates = currentTransform.getYprDelta();
		float rY = -yprRates[RotationAxis::YAW];
		float rP = -yprRates[RotationAxis::PITCH];
		float rR = yprRates[RotationAxis::ROLL];

		rateY.set(rY);
		rateP.set(rP);
		rateR.set(rR);
	}

	SortedVector<ManagedReference<TreeEntry*>> closeObjects;
	shipCov->safeCopyReceiversTo(closeObjects, CloseObjectsVector::PLAYERTYPE);

	const auto& currentPosition = currentTransform.getPosition();

	for (int i = 0; i < closeObjects.size(); ++i) {
		auto playerEntry = closeObjects.get(i).castTo<SceneObject*>();

		if (playerEntry == nullptr) {
			continue;
		}

		uint32 syncStamp = playerEntry->getSyncStamp();

		auto data = new ShipUpdateTransformMessage(ship, currentPosition, velocity, rateY, rateP, rateR, syncStamp);
		playerEntry->sendMessage(data);
	}
}
