#ifndef SHIPPROJECTILE_H_
#define SHIPPROJECTILE_H_

//#define SHIPPROJECTILE_DEBUG

#include "server/zone/objects/ship/ShipObject.h"

#ifdef SHIPPROJECTILE_DEBUG
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#endif // SHIPPROJECTILE_DEBUG

class ShipProjectile: public Object, public Logger {
public:
	const static constexpr float positionScale = 7800.f;
	const static constexpr float invPositionScale = 1.f / positionScale;

protected:
	ManagedWeakReference<ShipObject*> shipRef;

	uint8 weaponSlot;
	uint8 projectileType;
	uint8 componentSlot;

	Vector3 thisPosition;
	Vector3 lastPosition;
	Vector3 direction;

	float distance;
	float speed;
	float range;
	float radius;

	uint64 deltaMax;
	uint64 firstUpdate;
	uint64 lastUpdate;

public:
	ShipProjectile() {
		setLoggingName("ShipProjectile");

		weaponSlot = 0;
		projectileType = 0;
		componentSlot = 0;

		distance = 0.f;
		speed = 0.f;
		range = 0.f;
		radius = 0.f;

		deltaMax = 0;
		firstUpdate = 0;
		lastUpdate = 0;
	}

	ShipProjectile(ShipObject* ship, uint8 weapon, uint8 projectile, uint8 component, Vector3 start, Vector3 end, float projectileSpeed, float projectileRange, float projectileRadius, uint64 miliTime) {
		this->shipRef = ship;

		weaponSlot = weapon;
		projectileType = projectile;
		componentSlot = component;

		thisPosition = start;
		lastPosition = start;
		direction = end * invPositionScale;

		distance = 0.f;
		speed = projectileSpeed;
		range = projectileRange;
		radius = projectileRadius;

		deltaMax = (projectileRange / projectileSpeed) * 1000.f;
		firstUpdate = miliTime - 200; //SpaceCombatManager::CheckProjectilesTask::INTERVAL;
		lastUpdate = firstUpdate;
	}

// get
	ManagedWeakReference<ShipObject*> getShip() const {
		return shipRef;
	}

	uint8 getWeaponSlot() const {
		return weaponSlot;
	}

	uint8 getProjectileType() const {
		return projectileType;
	}

	uint8 getComponentSlot() const {
		return componentSlot;
	}

	const Vector3& getThisPosition() const {
		return thisPosition;
	}

	const Vector3& getLastPosition() const {
		return lastPosition;
	}

	const Vector3& getDirection() const {
		return direction;
	}

	float getDistance() const {
		return distance;
	}

	float getSpeed() const {
		return speed;
	}

	float getRange() const {
		return range;
	}

	float getRadius() const {
		return radius;
	}

	uint64 getDeltaMax() const {
		return deltaMax;
	}

	uint64 getFirstUpdateTime() const {
		return firstUpdate;
	}

	uint64 getLastUpdateTime() const {
		return lastUpdate;
	}

	void setLastUpdateTime(uint64 miliTime) {
		lastUpdate = miliTime;
	}

	void updatePosition(uint64 deltaTime) {
		distance = deltaTime * speed * 0.001f;

		lastPosition = thisPosition;
		thisPosition = thisPosition + (distance * direction);
	}

	bool validatePosition() {
		if (thisPosition.getX() > 7999.f || thisPosition.getX() < -7999.f
		 || thisPosition.getY() > 7999.f || thisPosition.getY() < -7999.f
		 || thisPosition.getZ() > 7999.f || thisPosition.getZ() < -7999.f) {
			return false;
		}

		return distance > 0.f;
	}

#ifdef SHIPPROJECTILE_DEBUG
	void debugProjectile(ShipObject* ship) {
		auto pilot = ship->getPilot();
		if (pilot == nullptr) {
			return;
		}

		StringBuffer msg;

		msg << " thisPosition " << thisPosition.toString() << endl
			<< " lastPosition " << lastPosition.toString() << endl
			<< " direction    " << direction.toString() << endl
			<< " distance     " << distance << endl
			<< " speed        " << speed << endl
			<< " range        " << range << endl
			<< " radius       " << radius << endl
			<< " deltaTime    " << (System::getMiliTime() - lastUpdate) << endl
			<< " totalTime    " << (System::getMiliTime() - firstUpdate) << endl
			<< " deltaMax     " << deltaMax << endl
			<< "--------------------------------";

		pilot->sendSystemMessage(msg.toString());

		auto path = new CreateClientPathMessage();
		path->addCoordinate(lastPosition);
		path->drawBoundingSphere(thisPosition, Matrix4(), Sphere(Vector3::ZERO, radius));
		path->addCoordinate(thisPosition);
		ship->broadcastMessage(path, true);
	}
#endif //SHIPPROJECTILE_DEBUG
};

#endif // SHIPPROJECTILE_H_
