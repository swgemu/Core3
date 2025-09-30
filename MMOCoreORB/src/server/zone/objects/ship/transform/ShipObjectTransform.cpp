#include "ShipObjectTransform.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/packets/ship/ShipUpdateTransformMessage.h"

ShipObjectTransform::ShipObjectTransform(ShipObject* ship) : Object() {
	initializeTransform(ship);
}

void ShipObjectTransform::initializeTransform(ShipObject* ship) {
	if (ship == nullptr) {
		return;
	}

	Locker lock(&mutex);

	setCurrentTransform(ship);
	previousTransform = currentTransform;
	nextTransform = currentTransform;

	transformType.initializeType(ship);
}

void ShipObjectTransform::setCurrentTransform(ShipObject* ship) {
	if (ship == nullptr) {
		return;
	}

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

	serverTime = System::getMiliTime();
	deltaTime = 0.f;
}

void ShipObjectTransform::setNextTransform(const Vector3& position, float speed, int type) {
	Locker lock(&mutex);

	transformType.setTransformType(type);

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

void ShipObjectTransform::setNextTransform(const SpaceTransform& transform, int type) {
	Locker lock(&mutex);

	Vector3 velocity = transform.getPosition() - currentTransform.getPosition();
	float distance = SpaceMath::qNormalize(velocity);

	nextTransform = transform;
	nextTransform.setVelocity(velocity);
	nextDistance = distance;
	transformType.setTransformType(type);

	if (transformType.getTransformType() != SpaceTransformType::DOCK) {
		auto rotation = SpaceMath::velocityToRotation(velocity);
		nextTransform.setRotation(rotation);
	}
}

void ShipObjectTransform::updateTransform(ShipObject* ship, bool lightUpdate, bool notifyClient) {
	if (ship == nullptr || !isScheduled()) {
		return;
	}

	Locker lock(&mutex);

	updateCurrentTransform(ship);
	setDeltaTime();

	if (isStaticUpdate()) {
		return;
	}

	if (notifyClient) {
		setSpeed(ship);
		setRotation(ship);
		setPosition(ship);
		setVelocity(ship);
	} else {
		setTransform(ship);
	}

	updateNextTransform(ship);
	updateShip(ship);

	if (lightUpdate && isInertiaUpdate()) {
		return;
	}

	if (notifyClient) {
		broadcastTransform(ship);
	}
}

void ShipObjectTransform::setTransform(ShipObject* ship) {
	float speed = Math::min(transformType.getThrottleMax() * ship->getActualMaxSpeed(), nextDistance);

	if (nextTransform.getSpeed() > 0.f) {
		speed = Math::min(nextTransform.getSpeed(), speed);
	}

	auto rotation = nextTransform.getRotation();
	auto velocity = nextTransform.getVelocity();
	auto position = (velocity * speed * deltaTime) + currentTransform.getPosition();

	position.setX(Math::clamp(-7999.f, position.getX(), 7999.f));
	position.setY(Math::clamp(-7999.f, position.getY(), 7999.f));
	position.setZ(Math::clamp(-7999.f, position.getZ(), 7999.f));

	SpaceTransform transform;
	transform.setPosition(position);
	transform.setVelocity(velocity);
	transform.setRotation(rotation);
	transform.setSpeed(speed);

	previousTransform = currentTransform;
	currentTransform = transform;
}

void ShipObjectTransform::setSpeed(ShipObject* ship) {
	float speedActual = ship->getActualMaxSpeed();
	float speedCurrent = ship->getCurrentSpeed();

	if (speedActual <= 0.f && speedCurrent <= 0.f) {
		return;
	}

	float throttleMax = transformType.getThrottleMax();
	float throttleMid = transformType.getThrottleMid();
	float throttleMin = transformType.getThrottleMin();

	throttleMid = Math::max(ship->getSpeedRotationFactorOptimal(), throttleMid);

	float speedMin = throttleMin * speedActual;
	float speedMid = throttleMid * speedActual;
	float speedMax = throttleMax * speedActual;

	if (nextTransform.getSpeed() != 0.f) {
		speedMax = Math::min(nextTransform.getSpeed(), speedMax);
	}

	float radius = (speedCurrent * deltaTime) + POSITION_EPSILON;
	float distance = Math::max(nextDistance - radius, 0.f);
	float speedNew = speedMin;

	if (distance > 0.f || speedCurrent > 0.f) {
		float accelRate = Math::max(ship->getActualAccelerationRate(), 1.f);
		float decelRate = Math::max(ship->getActualDecelerationRate(), 1.f);
		float decelDist = (speedMax * speedMax) / decelRate;

		if (distance < decelDist) {
			speedNew = (distance / decelDist) * speedMax;
		} else {
			speedNew = speedMax;
		}

		if (nextRotation > ROTATION_EPSILON) {
			float rotationTime = Math::clamp(0.f,SpaceMath::getRotationTime(nextTransform.getRotation(), currentTransform.getRotation(), ship->getActualYawRate(), ship->getActualPitchRate()), 5.f);
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
			speedNew = Math::clamp(speedMin, ceilf(speedNew), speedMax);
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
	Vector3 yprRates = Vector3::ZERO;

	if (currentRotation != nextRotation) {
		Vector3 accel = Vector3::ZERO;
		Vector3 actual = Vector3::ZERO;
		Vector3 delta = SpaceMath::getRotationRate(nextRotation, currentRotation);

		const auto& rateDamp = transformType.getRotationRate();
		Vector3 deltaRate = rateDamp * deltaTime;

		if (transformType.getTransformType() == SpaceTransformType::DOCK) {
			accel = Vector3(ship->getEngineYawAccelerationRate(), ship->getEnginePitchAccelerationRate(), ship->getEngineRollAccelerationRate()) * deltaRate;
			actual = Vector3(ship->getEngineYawRate(), ship->getEnginePitchRate(), ship->getEngineRollRate()) * deltaRate;
		} else {
			accel = Vector3(ship->getActualYawAccelerationRate(), ship->getActualPitchAccelerationRate(), ship->getActualRollAccelerationRate()) * deltaRate;
			actual = Vector3(ship->getActualYawRate(), ship->getActualPitchRate(), ship->getActualRollRate()) * deltaRate;

			delta[SpaceTransformType::ROLL] += (-delta[SpaceTransformType::YAW] * rateDamp[SpaceTransformType::ROLL]);
			delta[SpaceTransformType::ROLL] = SpaceMath::getRotationRate(delta[SpaceTransformType::ROLL]);
		}

		for (int axis = 0; axis < 3; ++axis) {
			if (fabs(delta[axis]) <= ROTATION_EPSILON) {
				rotation[axis] = nextRotation[axis];
				continue;
			}

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
	if (currentTransform.getRotation() == previousTransform.getRotation() && currentTransform.getVelocity() == previousTransform.getVelocity()) {
		return;
	}

	if (transformType.getTransformType() == SpaceTransformType::DOCK) {
		previousTransform.setVelocity(currentTransform.getVelocity());
		currentTransform.setVelocity(nextTransform.getVelocity());
		return;
	}

	Vector3 velocity = SpaceMath::rotationToVelocity(currentTransform.getRotation());

	if (currentTransform.getSpeed() > 1.f) {
		float t = Math::clamp(0.f, (currentTransform.getSpeed() / (float)VELOCITY_MAX) * ship->getSlip(), 1.f);
		velocity = Math::linearInterpolate(currentTransform.getVelocity(), velocity, 1.f - t);
		SpaceMath::qNormalize(velocity);
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
	float radius = (currentTransform.getSpeed() * deltaTime) + POSITION_EPSILON;

	if (nextDistance <= radius) {
		currentTransform.setPosition(nextTransform.getPosition());
		nextDistance = 0.f;
	} else {
		auto velocity = nextTransform.getPosition() - currentTransform.getPosition();
		nextDistance = SpaceMath::qNormalize(velocity);
		nextTransform.setVelocity(velocity);
	}

	if (nextTransform.getVelocity() != currentTransform.getVelocity()) {
		if (transformType.getTransformType() != SpaceTransformType::DOCK) {
			auto rotation = SpaceMath::velocityToRotation(nextTransform.getVelocity());
			nextTransform.setRotation(rotation);
		}

		nextRotation = SpaceMath::getRotationTime(nextTransform.getRotation(), currentTransform.getRotation()) * M_PI;;
	}
}

void ShipObjectTransform::updateShip(ShipObject* ship) {
	ship->setPosition(currentTransform.getPosition());

	if (currentTransform.getRotation() != previousTransform.getRotation()) {
		bool precision = ship->getBoundingRadius() >= 64.f || transformType.getTransformType() == SpaceTransformType::FAST;
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
		float rY = -yprRates[SpaceTransformType::YAW];
		float rP = -yprRates[SpaceTransformType::PITCH];
		float rR = yprRates[SpaceTransformType::ROLL];

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
