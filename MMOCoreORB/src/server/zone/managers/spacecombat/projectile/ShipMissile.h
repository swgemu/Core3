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

		timeToHit = Math::clamp(timeMin, (int(distance / clientSpeed) * 1000), timeMax);
	}

// update
	void updatePosition(int deltaTime, int totalTime) {
		auto target = targetRef.get();
		if (target == nullptr) {
			return;
		}

		Vector3 targetDirection = getTargetPosition(target) - thisPosition;

		float tMinus = Math::max(timeToHit - totalTime, deltaTime) * 0.001f;
		float sqrLength = targetDirection.squaredLength();
		float range = serverSpeed * tMinus;

		if (sqrLength > (range * range)) {
			float length = sqrt(sqrLength);
			speed = length / tMinus;
			direction = targetDirection * (1.f / length);
		} else {
			speed = serverSpeed / tMinus;
		}

		distance = deltaTime * speed * 0.001f;

		lastPosition = thisPosition;
		thisPosition = thisPosition + (distance * direction);
	}

	Vector3 getTargetPosition(ShipObject* target) const {
		Vector3 targetPosition = target->getPosition();

		if (hardpointTranslate != Vector3::ZERO) {
			Matrix4 targetRotation = *target->getRotationMatrix();
			targetRotation.transpose();

			Vector3 position = hardpointTranslate * targetRotation;
			targetPosition = targetPosition + Vector3(position.getX(), position.getZ(), position.getY());
		}

		return targetPosition;
	}

#ifdef SHIPPROJECTILE_DEBUG
	void debugProjectile(ShipObject* ship, int hitResult) {
		ShipProjectile::debugProjectile(ship, hitResult);

		auto pilot = ship->getPilot();
		if (pilot == nullptr) {
			return;
		}

		auto target = targetRef.get();
		if (target == nullptr) {
			return;
		}

		Vector3 targetDirection = target->getPosition() - thisPosition;

		StringBuffer msg;

		msg << "Missile: " << endl
			<< " hardpoint  " << hardpointTranslate.toString() << endl
			<< " timeMin    " << timeMin << endl
			<< " timeMax    " << timeMax << endl
			<< " timeToHit  " << timeToHit << endl
			<< " difficulty " << difficulty << endl
			<< " distance   " << targetDirection.length() << endl
			<< "--------------------------------";

		pilot->sendSystemMessage(msg.toString());
	}
#endif //SHIPPROJECTILE_DEBUG
};

#endif // SHIPMISSILE_H_
