/*
 * HarvesterObjectImplementation.cpp
 *
 *  Created on: 10/06/2010
 *      Author: victor
 */

#include "HarvesterObject.h"
#include "server/zone/packets/harvester/HarvesterObjectMessage7.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage7.h"
#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/harvester/ResourceHarvesterActivatePageMessage.h"
#include "server/zone/managers/resource/ResourceManager.h"

void HarvesterObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	//info("atrasdasd", true);

	InstallationObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	if (!isOnAdminList(player))
		return;

	menuResponse->addRadialMenuItemToRadialID(122, 78, 3, "@harvester:manage");
	menuResponse->addRadialMenuItemToRadialID(122, 77, 3, "@player_structure:management_power");
}

void HarvesterObjectImplementation::synchronizedUIListen(SceneObject* player, int value) {
	if (!player->isPlayerCreature() || !isOnAdminList((CreatureObject*)player))
		return;

	addOperator((PlayerCreature*) player);

	updateHopper();

	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this);
	player->sendMessage(msg);
}

void HarvesterObjectImplementation::updateOperators() {
	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this);
	broadcastToOperators(msg);
}

void HarvesterObjectImplementation::synchronizedUIStopListen(SceneObject* player, int value) {
	if (!player->isPlayerCreature())
		return;

	removeOperator((PlayerCreature*) player);
}

int HarvesterObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	switch (selectedID) {
	/*case 122:
		sendPermissionListTo(player, "ADMIN");
		break;*/
	case 78: {
		ResourceHarvesterActivatePageMessage* rhapm = new ResourceHarvesterActivatePageMessage(getObjectID());
		player->sendMessage(rhapm);
		break;
	}
	case 77:
		break;

	default:
		return InstallationObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}

void HarvesterObjectImplementation::updateToDatabaseAllObjects(bool startTask) {
	InstallationObjectImplementation::updateToDatabaseAllObjects(startTask);

	for (int i = 0; resourceHopper.size(); ++i) {
		resourceHopper.get(i)->updateToDatabaseAllObjects(false);
	}
}

int HarvesterObjectImplementation::getHopperItemQuantity(ResourceSpawn* spawn) {
	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry->getSpawnObject() == spawn)
			return entry->getQuantity();
	}

	return -1;
}

void HarvesterObjectImplementation::verifyOperators() {
	if (operatorList.size() <= 0)
		return;

	// won't fully clean up at once because indexes would change once you remove one - but should clean up
	for (int i = 0; i < operatorList.size(); i++) {
		ManagedReference<PlayerCreature*> obj = operatorList.get(i);

		if (!obj->isOnline()) {
			operatorList.remove(i);

			--i;
		}
	}

}

uint64 HarvesterObjectImplementation::getActiveResourceSpawnID() {
	if (resourceHopper.size() == 0) {
		return 0;
	} else {
		ResourceContainer* entry = resourceHopper.get(0);

		return entry->getSpawnObject()->getObjectID();
	}
}

void HarvesterObjectImplementation::clearResourceHopper() {
	if (resourceHopper.size() == 0)
		return;


	InstallationObjectDeltaMessage7* dtano6 = new InstallationObjectDeltaMessage7( _this);
	dtano6->startUpdate(0x0D);

	resourceHopper.removeAll(dtano6);

	dtano6->updateActiveResourceSpawn(getActiveResourceSpawnID());

	dtano6->close();

	broadcastToOperators(dtano6);
}

void HarvesterObjectImplementation::removeResourceFromHopper(ResourceContainer* container) {
	int index = resourceHopper.find(container);

	if (index == -1)
		return;

	InstallationObjectDeltaMessage7* dtano6 = new InstallationObjectDeltaMessage7( _this);
	dtano6->startUpdate(0x0D);

	resourceHopper.remove(index, dtano6, 1);

	dtano6->updateActiveResourceSpawn(getActiveResourceSpawnID());

	dtano6->close();

	broadcastToOperators(dtano6);
}

void HarvesterObjectImplementation::addResourceToHopper(ResourceContainer* container) {
	if (resourceHopper.contains(container))
		return;

	InstallationObjectDeltaMessage7* dtano6 = new InstallationObjectDeltaMessage7( _this);
	dtano6->startUpdate(0x0D);

	resourceHopper.add(container, dtano6, 1);
	dtano6->close();

	broadcastToOperators(dtano6);
}

void HarvesterObjectImplementation::setActiveResource(ResourceContainer* container) {
	if (resourceHopper.size() == 0) {
		addResourceToHopper(container);

		return;
	}

	int i = 0;
	for (; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry == container) {
			if (i == 0)
				return;

			ManagedReference<ResourceContainer*> oldEntry = resourceHopper.get(0);

			InstallationObjectDeltaMessage7* dtano6 = new InstallationObjectDeltaMessage7( _this);
			dtano6->startUpdate(0x0D);

			resourceHopper.set(0, container, dtano6, 2);
			resourceHopper.set(i, oldEntry, dtano6, 0);

			dtano6->close();

			broadcastToOperators(dtano6);
		}
	}
}

ResourceContainer* HarvesterObjectImplementation::getContainerFromHopper(ResourceSpawn* spawn) {
	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry->getSpawnObject() == spawn)
			return entry;
	}

	return NULL;
}

void HarvesterObjectImplementation::changeActiveResourceID(uint64 spawnID) {

	// Logic:
	// 1) If operating, and already has an active resource ID - make sure the hopper gets updated
	// 2) Get the spawn information & set the active resource id
	// 3) If hopper size is zero for the resource + is operating, send a packet to the operators to add a zero element for delta packets

	info("updating active ");

	if (isOperating()) {
		updateHopper();
	}

	ManagedReference<ResourceSpawn*> newSpawn = dynamic_cast<ResourceSpawn*>(getZoneServer()->getObject(spawnID));
	if (newSpawn == NULL) {
		error("new spawn null");
		return;
	}

	Time currentTime;

	resourceHopperTimestamp = currentTime;

	ManagedReference<ResourceContainer*> container = getContainerFromHopper(newSpawn);

	if (container == NULL) {
		container = newSpawn->createResource(0);

		addResourceToHopper(container);
		setActiveResource(container);
	} else {
		setActiveResource(container);
	}

	InstallationObjectDeltaMessage7* dtano6 = new InstallationObjectDeltaMessage7( _this);
	dtano6->updateExtractionRate(getActualRate());
	dtano6->updateActiveResourceSpawn(getActiveResourceSpawnID());
	dtano6->close();

	broadcastToOperators(dtano6);

	//setResourceHopperTimestamp(currentTime.getTime()); // ReInit

	//ResourceManager* resourceManager = getZoneServer()->getResourceManager();
}

void HarvesterObjectImplementation::updateHopper() {
	// Nothing to update if we're not operating
	if (!isOperating())
		return;

	if (resourceHopper.size() == 0) // no active spawn
		return;

	ResourceContainer* container = resourceHopper.get(0);
	ResourceSpawn* spawn = container->getSpawnObject();

	// the spawn expired before we updated hopper last - don't update the hopper
	/*if (spawnExpireTimestamp.compareTo(resourceHopperTimestamp) > 0) { // if (t1 < t2) return 1;
		StringBuffer msg;
		msg << "HarvesterObjectImplementation::updateHopper(" << hex << activeResourceID << dec << ") resource expired!! (why do we have expired resources in the list?) spawnExpireTimestamp: " << dec << spawnExpireTimestamp.getTime() << "  resourceHopperTimestamp: " << resourceHopperTimestamp.getTime() << endl;
		info(msg);
		return;
	}*/

	Time currentTime;

	Time spawnExpireTimestamp(spawn->getDespawned());
	// if (t1 < t2) return 1 - if spawnTime is sooner currentTime, use spawnTime, else use spawn time
	Time harvestUntil = (spawnExpireTimestamp.compareTo(currentTime) > 0) ? spawnExpireTimestamp : currentTime;

	float elapsedTime = (harvestUntil.getTime() - resourceHopperTimestamp.getTime());
	float spawnDensity = spawn->getDensityAt(getZone()->getZoneID(), positionX, positionY);

	float harvestAmount = (elapsedTime / 60.0) * (spawnDensity * getExtractionRate());

	int availableCapacity = (int)(getHopperSizeMax() - getHopperSize());
	harvestAmount = harvestAmount > availableCapacity ? availableCapacity : harvestAmount;

	float currentQuantity = container->getQuantity();

	container->setQuantity(currentQuantity + harvestAmount);
	// Update Timestamp
	resourceHopperTimestamp = currentTime;
}

float HarvesterObjectImplementation::getActualRate() {
	if (!isOperating())
		return 0.0f;

	if (resourceHopper.size() == 0)
		return 0;

	ResourceContainer* container = resourceHopper.get(0);
	ResourceSpawn* spawn = container->getSpawnObject();

	return extractionRate * (spawn->getDensityAt(zone->getZoneID(), positionX, positionY) / 100.f);
}


float HarvesterObjectImplementation::getHopperSize() {
	float hopperSize = 0.0f;

	for (int i = 0; i < resourceHopper.size(); i++) {
		ResourceContainer* entry = resourceHopper.get(i);
		hopperSize += entry->getQuantity();
	}

	return hopperSize;
}
