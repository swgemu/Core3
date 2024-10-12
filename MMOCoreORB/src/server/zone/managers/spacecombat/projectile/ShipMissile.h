#ifndef SHIPMISSILE_H_
#define SHIPMISSILE_H_

#include "ShipProjectile.h"
#include "server/zone/objects/ship/ShipMissileData.h"
#include "server/zone/packets/jtl/UpdateMissileMessage.h"

class ShipMissile : public ShipProjectile {
protected:
	ManagedWeakReference<ShipObject*> targetRef;
	Vector3 hardpointTranslate;

	int timeMin;
	int timeMax;
	int timeToHit;
	int difficulty;

	float clientSpeed;
	float serverSpeed;

public:
	ShipMissile(ShipObject* ship, uint8 weapon, uint8 projectile, uint8 component, Vector3 start, Vector3 end, float projectileSpeed, float projectileRange, float projectileRadius, uint64 miliTime)
	: ShipProjectile(ship, weapon, projectile, component, start, end, projectileSpeed, projectileRange, projectileRadius, miliTime) {
		setLoggingName("ShipMissile");

		uniqueID = (System::getMikroTime() << 16) | ship->getUniqueID();

		timeMin = 0;
		timeMax = 0;
		timeToHit = 0;
		difficulty = 0;

		clientSpeed = 0.f;
		serverSpeed = 0.f;
	}

	bool isMissile() const {
		return true;
	}

// get
	ManagedWeakReference<ShipObject*> getTarget() const {
		return targetRef;
	}

	const Vector3& getHardpointTranslation() const {
		return hardpointTranslate;
	}

	int getTimeMin() const {
		return timeMin;
	}

	int getTimeMax() const {
		return timeMax;
	}

	int getTimeToHit() const {
		return timeToHit;
	}

	int getDifficulty() const {
		return difficulty;
	}

	float getServerSpeed() const {
		return serverSpeed;
	}

	float getClientSpeed() const {
		return clientSpeed;
	}

// set
	void setTarget(ShipObject* ship) {
		targetRef = ship;
	}

	void setHardpointTranslation(const Vector3& value) {
		hardpointTranslate = value;
	}

	void readMissileData(const ShipMissileData* data) {
		timeMin = data->getMinTime() * 1000.f;
		timeMax = data->getMaxTime() * 1000.f;
		clientSpeed = data->getClientSpeed();
		serverSpeed = data->getServerSpeed();
		difficulty = data->getCounterDifficulty();

		projectileType = data->getMissileType();
		range = data->getMaxTime() * serverSpeed;
		radius = serverSpeed * 0.1f;
		speed = serverSpeed;
		deltaMax = timeMax;
	}

	void calculateTimeToHit() {
		auto target = targetRef.get();
		if (target == nullptr) {
			return;
		}

		Vector3 targetDirection = getTargetPosition(target) - thisPosition;
		float distance = targetDirection.length() - radius;

		timeToHit = Math::clamp(timeMin, (int(distance / serverSpeed) * 1000), timeMax);
	}

// update
	void updatePosition(int deltaTime, int totalTime) {
		auto target = targetRef.get();
		if (target == nullptr) {
			return;
		}

		float timeRemaining = Math::max(timeToHit - totalTime, deltaTime) * 0.001f;
		float deltaRate = deltaTime * 0.001f;

		Vector3 targetDirection = getTargetPosition(target) - thisPosition;
		float targetRadius = target->getBoundingRadius() + radius;
		float targetDistance = Math::max(targetDirection.normalize() - targetRadius, 0.f);

		speed = Math::max(targetDistance / timeRemaining, serverSpeed);
		distance = speed * deltaRate;
		direction = (targetDirection + direction) * 0.5f;

		lastPosition = thisPosition;
		thisPosition = thisPosition + (distance * direction);
	}

	Vector3 getTargetPosition(ShipObject* target, float deltaTime = 0.f) const {
		const Matrix4& targetRotation = *target->getConjugateMatrix();
		Vector3 targetPosition = target->getWorldPosition();

		if (hardpointTranslate != Vector3::ZERO) {
			Vector3 position = hardpointTranslate * targetRotation;
			targetPosition = Vector3(position.getX(), position.getZ(), position.getY()) + targetPosition;
		}

		Vector3 targetDirection = Vector3(targetRotation[2][0], targetRotation[2][2], targetRotation[2][1]);
		float targetSpeed = target->getCurrentSpeed();

		return (targetDirection * targetSpeed * deltaTime) + targetPosition;
	}

#ifdef SHIPPROJECTILE_DEBUG
	void debugProjectile(ShipObject* ship, int hitResult) {
		debugProjectileMessage(ship, hitResult);
		debugProjectilePath(ship);
	}

	void debugProjectileMessage(ShipObject* ship, int hitResult) {
		ShipProjectile::debugProjectileMessage(ship, hitResult);

		auto target = targetRef.get();
		if (target == nullptr) {
			return;
		}

		Vector3 targetPosition = target->getWorldPosition();
		Vector3	targetDirection = targetPosition - thisPosition;

		StringBuffer msg;

		msg << "Missile: " << endl
			<< " hardpoint  " << hardpointTranslate.toString() << endl
			<< " timeMin    " << timeMin << endl
			<< " timeMax    " << timeMax << endl
			<< " timeToHit  " << timeToHit << endl
			<< " difficulty " << difficulty << endl
			<< " distance   " << targetDirection.length() << endl
			<< "--------------------------------";

		auto smsg = new ChatSystemMessage(msg.toString());
		ship->broadcastMessage(smsg, true);
	}

	void debugProjectilePath(ShipObject* ship) {
		auto target = targetRef.get();
		if (target == nullptr) {
			return;
		}

		const Vector3& targetPosition = target->getWorldPosition();
		const Matrix4& targetRotation = *target->getConjugateMatrix();
		float targetRadius = target->getBoundingRadius();

		auto path = new CreateClientPathMessage();

		path->addCoordinate(lastPosition);
		path->drawBoundingSphere(thisPosition, Matrix4(), Sphere(Vector3::ZERO, radius));
		path->addCoordinate(thisPosition);
		path->addCoordinate(targetPosition);
		path->drawBoundingSphere(targetPosition, targetRotation, Sphere(Vector3::ZERO, targetRadius));
		path->addCoordinate(targetPosition);

		ship->broadcastMessage(path, true);
	}
#endif //SHIPPROJECTILE_DEBUG
};

#endif // SHIPMISSILE_H_
