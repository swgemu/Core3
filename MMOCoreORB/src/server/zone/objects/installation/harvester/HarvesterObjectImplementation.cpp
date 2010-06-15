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

	activateUiSync();
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

	for (int i = 0; i < resourceHopper.size(); ++i) {
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

	//lets delete the containers from db

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* container = resourceHopper.get(i);

		container->destroyObjectFromDatabase(true);
	}

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateHopper();
	inso7->startUpdate(0x0D);

	resourceHopper.removeAll(inso7);

	inso7->updateActiveResourceSpawn(getActiveResourceSpawnID());
	inso7->updateHopperSize(getHopperSize());
	inso7->updateExtractionRate(getActualRate());

	inso7->close();

	broadcastToOperators(inso7);

	/*while (resourceHopper.size() > 0) {
		ResourceContainer* container = resourceHopper.get(0);

		removeResourceFromHopper(container);
	}*/

	setOperating(false);
}

void HarvesterObjectImplementation::removeResourceFromHopper(ResourceContainer* container) {
	int index = resourceHopper.find(container);

	if (index == -1)
		return;

	container->destroyObjectFromDatabase(true);

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateHopper();
	inso7->startUpdate(0x0D);

	resourceHopper.remove(index, inso7, 1);

	inso7->updateActiveResourceSpawn(getActiveResourceSpawnID());
	inso7->updateHopperSize(getHopperSize());
	inso7->updateExtractionRate(getActualRate());

	inso7->close();

	broadcastToOperators(inso7);

	if (resourceHopper.size() == 0)
		setOperating(false);
}

void HarvesterObjectImplementation::addResourceToHopper(ResourceContainer* container) {
	if (resourceHopper.contains(container))
		return;

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateHopper();
	inso7->startUpdate(0x0D);

	resourceHopper.add(container, inso7, 1);
	inso7->close();

	broadcastToOperators(inso7);
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

			InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
			inso7->updateHopper();
			inso7->startUpdate(0x0D);

			resourceHopper.set(0, container, inso7, 2);
			resourceHopper.set(i, oldEntry, inso7, 0);

			inso7->close();

			broadcastToOperators(inso7);
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

	resourceHopperTimestamp.updateToCurrentTime();

	ManagedReference<ResourceContainer*> container = getContainerFromHopper(newSpawn);

	if (container == NULL) {
		container = newSpawn->createResource(0);

		addResourceToHopper(container);
		setActiveResource(container);
	} else {
		setActiveResource(container);
	}

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateExtractionRate(getActualRate());
	inso7->updateActiveResourceSpawn(getActiveResourceSpawnID());
	inso7->close();

	broadcastToOperators(inso7);
}

void HarvesterObjectImplementation::updateResourceContainerQuantity(ResourceContainer* container, int newQuantity, bool notifyClient) {
	container->setQuantity(newQuantity);

	if (!notifyClient)
		return;

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* cont = resourceHopper.get(i);

		if (cont == container) {
			InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
			inso7->updateHopper();
			inso7->startUpdate(0x0D);
			resourceHopper.set(i, container, inso7, 1);
			inso7->updateHopperSize(getHopperSize());
			inso7->updateExtractionRate(getActualRate());
			inso7->close();

			broadcastToOperators(inso7);
		}
	}
}

void HarvesterObjectImplementation::updateMaintenance() {
	Time currentTime;

	float elapsedTime = (currentTime.getTime() - lastMaintenanceTime.getTime());

	float payAmount = (elapsedTime / 3600.0) * baseMaintenanceRate;

	if (payAmount > surplusMaintenance) {
		payAmount = surplusMaintenance;
		setOperating(false);
	}

	addMaintenance(-1.0f * payAmount);

	float enegeryAmount = (elapsedTime / 3600.0) * basePowerRate;

	if (enegeryAmount > surplusPower) {
		enegeryAmount = surplusPower;
		setOperating(false);
	}

	addPower(-1.0f * enegeryAmount);

	lastMaintenanceTime.updateToCurrentTime();
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

	if (harvestAmount > 0) {
		spawn->extractResource(zone->getZoneID(), harvestAmount);

		updateResourceContainerQuantity(container, currentQuantity + harvestAmount, true);
		//container->setQuantity(currentQuantity + harvestAmount);
	}
	// Update Timestamp
	resourceHopperTimestamp.updateToCurrentTime();

	updateToDatabaseAllObjects(false);

	/*InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->startUpdate(0x0D);
	resourceHopper.set(0, container, inso7, 1);
	inso7->updateHopperSize(getHopperSize());
	inso7->close();

	broadcastToOperators(inso7);*/

}

void HarvesterObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	InstallationObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	if (!destroyContainedObjects)
		return;

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* container = resourceHopper.get(i);

		container->destroyObjectFromDatabase(true);
	}
}

float HarvesterObjectImplementation::getActualRate() {
	if (!isOperating())
		return 0.0f;

	if (resourceHopper.size() == 0)
		return 0;

	ResourceContainer* container = resourceHopper.get(0);
	ResourceSpawn* spawn = container->getSpawnObject();

	return extractionRate * (spawn->getDensityAt(zone->getZoneID(), positionX, positionY));
}

void HarvesterObjectImplementation::setOperating(bool value, bool notifyClient) {
	if (value == operating)
		return;

	if (value) {
		resourceHopperTimestamp.updateToCurrentTime();
	}

	InstallationObjectImplementation::setOperating(value, notifyClient);

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this);
	inso7->updateExtractionRate(getActualRate());
	inso7->close();

	broadcastToOperators(inso7);

	updateToDatabaseAllObjects(false);
}

float HarvesterObjectImplementation::getHopperSize() {
	float hopperSize = 0.0f;

	for (int i = 0; i < resourceHopper.size(); i++) {
		ResourceContainer* entry = resourceHopper.get(i);
		hopperSize += entry->getQuantity();
	}

	return hopperSize;
}
