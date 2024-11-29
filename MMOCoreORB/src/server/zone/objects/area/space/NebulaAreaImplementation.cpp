/*
 * NebulaAreaImplementation.cpp
 *
 * Created on: 01/05/2024
 * Author: Hakry
 */

#include "server/zone/objects/area/space/NebulaArea.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/packets/jtl/CreateNebulaLightningMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/spacecollision/SpaceCollisionManager.h"
#include "server/zone/managers/spacecombat/SpaceCombatManager.h"
#include "server/zone/packets/ship/OnShipHit.h"

// #define DEBUG_NEBULA_AREAS

void NebulaAreaImplementation::notifyPositionUpdate(TreeEntry* entry) {
	if (numberOfShipsInRange <= 0)
		return;

	// Some nebulas have no lightning
	if (lightningAppearance.isEmpty() || getNebulaDensity() < 0) {
		return;
	}

	if (!lastLightning.isPast())
		return;

	if (entry == nullptr)
		return;

	SceneObject* sceneObject = cast<SceneObject*>(entry);

	if (sceneObject == nullptr || !sceneObject->isShipObject())
		return;

	auto ship = sceneObject->asShipObject();

	if (ship == nullptr)
		return;

	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer != nullptr && (zoneServer->isServerLoading() || zoneServer->isServerShuttingDown()))
		return;

#ifdef DEBUG_NEBULA_AREAS
	info(true) << getAreaName() << " -- NebulaAreaImplementation::notifyPositionUpdate called";
#endif // DEBUG_NEBULA_AREAS

	// Create lightning based of the ship in the nebula
	createNewLightning(ship);
}

void NebulaAreaImplementation::notifyEnter(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject())
		return;

#ifdef DEBUG_NEBULA_AREAS
	info(true) << getAreaName() << " -- NebulaAreaImplementation::notifyEnter called for: " << sceneO->getDisplayedName();
#endif // DEBUG_NEBULA_AREAS

	SpaceActiveAreaImplementation::notifyEnter(sceneO);

	auto shipObject = sceneO->asShipObject();

	if (shipObject == nullptr)
		return;

	numberOfShipsInRange.increment();
}

void NebulaAreaImplementation::notifyExit(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject())
		return;

	SpaceActiveAreaImplementation::notifyExit(sceneO);

	auto shipObject = sceneO->asShipObject();

	if (shipObject == nullptr)
		return;

	numberOfShipsInRange.decrement();

	if (numberOfShipsInRange <= 0) {
		numberOfShipsInRange.set(0);
	}
}

void NebulaAreaImplementation::createNewLightning(ShipObject* ship) {
	if (ship == nullptr)
		return;

	auto zone = getZone();

	if (zone == nullptr)
		return;

	auto spaceManager = zone->getSpaceManager();

	if (spaceManager == nullptr)
		return;

	Locker locker(_this.getReferenceUnsafeStaticCast());

	// Handle start time and end time
	int startTime = 1000;

	int maxTimeMs = getMaxLightningDuration() * 1000;
	int randomMaxDuration = startTime + ((maxTimeMs / 2) + System::random(maxTimeMs - (maxTimeMs / 2)));
	int lightningInterval = (System::random(LIGHTNINGDELAY - 1) + 1) * 1000;

	// Update the nebula to delay for next lightning
	lastLightning.updateToCurrentTime();
	lastLightning.addMiliTime(lightningInterval);

	// Incrememnt the lightning count
	lightningCount.increment();

	// Calculate the lightning size
	float sphereRadius = getRadius();
	float radiusFactor = sphereRadius * 0.3;
	Vector3 areaCenter = getAreaCenter();

	// Precalculate the lightning distance
	float minDistance = radiusFactor * 0.75;
	float maxDistance = radiusFactor;
	float randomDistance = System::frandom(maxDistance - minDistance) + minDistance;

	Vector3 startPoint = areaShape->getRandomPosition();
	Vector3 endPoint = areaShape->getRandomPosition(startPoint, randomDistance, randomDistance);

#ifdef DEBUG_NEBULA_AREAS
	info(true) << "\n";
	info(true) << " Sending lightning! -- Lightning Count: " << lightningCount << " Nebula ID: " << getNebulaID() << " Start Time: " << startTime << " End Time: " << randomMaxDuration << " Radius Factor: " << radiusFactor << " Start: " << startPoint.toString() << " End Point: " << endPoint.toString();
#endif

	// Broadcast message in space manager to nearby ships and their players
	spaceManager->broadcastNebulaLightning(ship, areaCenter, lightningCount, getNebulaID(), startTime, randomMaxDuration, startPoint, endPoint);

	shipLightningDamage(ship, startPoint, endPoint, randomDistance, startTime, randomMaxDuration);
}

void NebulaAreaImplementation::shipLightningDamage(ShipObject* ship, const Vector3& startPoint, const Vector3& endPoint, float distance, int startTime, int endTime) {
	if (ship == nullptr)
		return;

	auto spaceManager = zone->getSpaceManager();

	if (spaceManager == nullptr)
		return;

	CloseObjectsVector* closeObjects = (CloseObjectsVector*)ship->getCloseObjects();

	if (closeObjects == nullptr)
		return;

	SortedVector<ManagedReference<TreeEntry*> > closeCopy;
	closeObjects->safeCopyReceiversTo(closeCopy, CloseObjectsVector::SHIPTYPE);

#ifdef DEBUG_NEBULA_AREAS
	info(true) << "shipLightningDamage -- Total Nearby Objects: " << closeObjects->size() << " Start Point: " << startPoint.toString() << " Distance: " << distance;
#endif

	Vector3 direction = endPoint - startPoint;
	float lightningMin = getLightningDamageMin();
	float lightningMax = getLightningDamageMax();

	for (int i = 0; i < closeCopy.size(); i++) {
		SceneObject* object = static_cast<SceneObject*>(closeCopy.get(i).get());

		if (object == nullptr || !object->isShipObject())
			continue;

		Reference<ShipObject*> targetShip = object->asShipObject();

		if (targetShip == nullptr || (targetShip->getOptionsBitmask() & OptionBitmask::INVULNERABLE))
			continue;

#ifdef DEBUG_NEBULA_AREAS
		info(true) << "Valid Ship: " << targetShip->getDisplayedName();
#endif

		const Vector3& targetPosition = targetShip->getPosition();
		Vector3 difference = targetPosition - startPoint;
		float targetRadius = targetShip->getBoundingRadius() + LIGHTNING_DAMAGE_RAD;

		float intersection = SpaceCollisionManager::instance()->getPointIntersection(direction, difference, targetRadius, distance);

		if (intersection == SpaceCollisionManager::MISS) {
			continue;
		}

		// Calculate the global and local collision points and orientation
		Vector3 collisionPoint = ((endPoint - startPoint) * intersection) + startPoint;

		const Matrix4& targetRotation = *targetShip->getRotationMatrix();
		Vector3 localPosition = (collisionPoint - targetPosition);
		localPosition = Vector3(localPosition.getX(), localPosition.getZ(), localPosition.getY()) * targetRotation;

		bool hitFront = localPosition.getZ() >= 0.f;

		spaceManager->broadcastNebulaLightning(targetShip, getAreaCenter(), lightningCount, getNebulaID(), startTime, endTime, collisionPoint, targetPosition);

		float damage = lightningMin + System::frandom(lightningMax - lightningMin);

#ifdef DEBUG_NEBULA_AREAS
		info(true) << "shipLightningDamage -- Collision with targetShip: " << targetShip->getDisplayedName() << " at position: " << collisionPoint.toString() << " hitFront: " << hitFront;
#endif

		Core::getTaskManager()->scheduleTask([targetShip, collisionPoint, hitFront, damage]{
			Locker locker(targetShip);
			auto deltaVector = targetShip->getDeltaVector();

			float shieldCurrent = hitFront ? targetShip->getFrontShield() : targetShip->getRearShield();
			float shieldMaximum = hitFront ? targetShip->getMaxFrontShield() : targetShip->getMaxRearShield();

			if (shieldCurrent == 0.f || shieldMaximum == 0.f) {
				return;
			}

			float percentageOld = shieldCurrent / shieldMaximum;

			shieldCurrent = Math::max(0.f, shieldCurrent - damage);

			float percentageNew = shieldCurrent / shieldMaximum;

			if (percentageNew != percentageOld) {
				if (hitFront) {
					targetShip->setFrontShield(shieldCurrent, false, nullptr, deltaVector);
				} else {
					targetShip->setRearShield(shieldCurrent, false, nullptr, deltaVector);
				}

				auto shipHit = new OnShipHit(targetShip, collisionPoint, SpaceCombatManager::ShipHitType::HITSHIELD, percentageNew, percentageOld);
				targetShip->broadcastMessage(shipHit, true);
			}

			if (deltaVector != nullptr) {
				deltaVector->sendMessages(targetShip);
			}

		}, "LightningDamageTask", 1000);
	}
}
