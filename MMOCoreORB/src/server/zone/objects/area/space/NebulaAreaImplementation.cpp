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

	// Update the nebula to delay for next lightning
	lastLightning.updateToCurrentTime();
	lastLightning.addMiliTime((1 + System::random(LIGHTNINGDELAY + 1)) * 1000);

	// Incrememnt the lightning count
	lightningCount.increment();

	// Calculate the lightning size
	float sphereRadius = getRadius();
	float radiusFactor = sphereRadius * 0.3;
	Vector3 areaCenter = getAreaCenter();

	Vector3 startPoint = areaShape->getRandomPosition();
	Vector3 endPoint = areaShape->getRandomPosition(startPoint, radiusFactor * 0.75, radiusFactor);

#ifdef DEBUG_NEBULA_AREAS
	info(true) << "\n";
	info(true) << " Sending lightning! -- Lightning Count: " << lightningCount << " Nebula ID: " << getNebulaID() << " Start Time: " << startTime << " End Time: " << randomMaxDuration << " Radius Factor: " << radiusFactor << " Start: " << startPoint.toString() << " End Point: " << endPoint.toString();
#endif

	// Broadcast message in space manager to nearby ships and their players
	spaceManager->broadcastNebulaLightning(ship, areaCenter, lightningCount, getNebulaID(), startTime, randomMaxDuration, startPoint, endPoint);

	shipLightningDamage(ship, startPoint, endPoint, radiusFactor);
}

void NebulaAreaImplementation::shipLightningDamage(ShipObject* ship, const Vector3& startPoint, const Vector3& endPoint, float range) {
	if (ship == nullptr)
		return;

	auto pilot = ship->getPilot();

	if (pilot == nullptr)
		return;

	CloseObjectsVector* closeVector = (CloseObjectsVector*)pilot->getCloseObjects();

	if (closeVector == nullptr)
		return;

	SortedVector<TreeEntry*> closeObjects;
	closeVector->safeCopyTo(closeObjects);

#ifdef DEBUG_NEBULA_AREAS
	info(true) << "shipLightningDamage -- Total Nearby Objects: " << closeObjects.size() << " Start Point: " << startPoint.toString() << " Range: " << range;
#endif

	Vector3 direction = endPoint - startPoint;
	float lightningMin = getLightningDamageMin();
	float lightningMax = getLightningDamageMax();

	for (int i = 0; i < closeObjects.size(); i++) {
		SceneObject* object = static_cast<SceneObject*>(closeObjects.get(i));

		if (object == nullptr || !object->isShipObject())
			continue;

		Reference<ShipObject*> targetShip = object->asShipObject();

		if (targetShip == nullptr)
			continue;

#ifdef DEBUG_NEBULA_AREAS
		info(true) << "Valid Ship: " << targetShip->getDisplayedName();
#endif

		float targetRadius = targetShip->getBoundingRadius() + LIGHTNING_DAMAGE_RAD;
		Vector3 difference = targetShip->getPosition() - startPoint;

		float intersection = SpaceCollisionManager::getPointIntersection(direction, difference, targetRadius, range);

		if (intersection == SpaceCollisionManager::MISS) {
			continue;
		}

		float damage = lightningMin + System::frandom(lightningMax - lightningMin);

		Core::getTaskManager()->scheduleTask([targetShip]{
			Locker locker(targetShip);

			//shield damage

		}, "LightningDamageTask", 100);
	}
}
