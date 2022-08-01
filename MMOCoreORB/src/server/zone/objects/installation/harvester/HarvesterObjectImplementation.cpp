/*
 * HarvesterObjectImplementation.cpp
 *
 *  Created on: 10/06/2010
 *      Author: victor
 */

#include "../../../packets/harvester/HarvesterObjectMessage7.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/harvester/ResourceHarvesterActivatePageMessage.h"
#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/packets/object/GenericResponse.h"
#include "server/zone/objects/scene/variables/DeltaVectorMap.h"
#include "server/zone/objects/installation/InstallationTickTask.h"

void HarvesterObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!isOnAdminList(player))
		return;

	InstallationObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItemToRadialID(118, 78, 3, "@harvester:manage"); //Operate Machinery
}

void HarvesterObjectImplementation::initializeTransientMembers() {
	InstallationObjectImplementation::initializeTransientMembers();

	if (resourceHopper.size() > 0) {
		for (int i = resourceHopper.size() - 1; i >= 0; i--) {
			ResourceContainer* entry = resourceHopper.get(i);
			int quantity = entry->getQuantity();
			ManagedReference<ResourceSpawn*> entryResource = entry->getSpawnObject();

			if (entryResource == nullptr) {
				entry->destroyObjectFromWorld(true);
				entry->destroyObjectFromDatabase();
				continue;
			}

			uint64 resourceID = entryResource->getObjectID();

			addResource(resourceID, quantity);

			entry->destroyObjectFromWorld(true);
			entry->destroyObjectFromDatabase();
		}
	}
}

int HarvesterObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!isOnAdminList(player))
		return 1;

	switch (selectedID) {
	case 78: {
		ResourceHarvesterActivatePageMessage* rhapm = new ResourceHarvesterActivatePageMessage(getObjectID());
		player->sendMessage(rhapm);
		break;
	}
	case 77:
		//handleStructureAddEnergy(player);
		break;

	default:
		return InstallationObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}

void HarvesterObjectImplementation::scheduleTickTask(bool immediate) {
	if (tickTask == nullptr) {
		tickTask = new InstallationTickTask(_this.getReferenceUnsafeStaticCast());
	}

	if (immediate) {
		tickTask->execute();
		return;
	}

	uint64 tickTimer = 30 * 60 * 1000; // 30 min default

	if (getOperatorCount() > 0) {
		tickTimer = 10 * 1000; // 10 seconds to update the real time synchronized ui
	}

	if (tickTask->isScheduled()) {
		if (tickTask->getNextExecutionTime().miliDifference() > tickTimer) {
			tickTask->reschedule(tickTimer);
		}
	} else {
		tickTask->schedule(tickTimer);
	}
}

void HarvesterObjectImplementation::doTick() {
	if (isActive())
		harvest();

	InstallationSynchronizedUi* ui = getSynchronizedUi();

	if (ui)
		ui->refresh();

	scheduleTickTask();
}

void HarvesterObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	InstallationObjectImplementation::fillAttributeList(alm, object);

	if(isSelfPowered()){
		alm->insertAttribute("@veteran_new:harvester_examine_title", "@veteran_new:harvester_examine_text");
	}

}

ResourceSpawn* HarvesterObjectImplementation::getSelectedResourcePool() {
	if (resourceType == 0)
		return nullptr;

	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr)
		return nullptr;

	Reference<ResourceSpawn*> resourceSpawn = zoneServer->getObject(resourceType).castTo<ResourceSpawn*>();

	return resourceSpawn;
}

float HarvesterObjectImplementation::getHopperContents(DeltaVectorMap<uint64, float>* hopperList) {
	int hopperAmount = 0;

	for (int i = 0; i < hopperList->size(); i++) {
		uint64 entryKey = hopperContents->getKeyAt(i);
		float entryValue = hopperContents->getValueAt(i);

		hopperAmount += entryValue;

		if (hopperList)
			hopperList->set(entryKey, entryValue);
	}

	return hopperAmount;
}

void HarvesterObjectImplementation::activate(CreatureObject* player) {
	int hopperAmount = getHopperContents();

	if (hopperAmount >= maxHopperAmount) {
		if (player != nullptr)
			player->sendSystemMessage("@shared:harvester_hopper_full"); // Output hopper full. Shutting down.

		return;
	}

	bool active = isActive();
	InstallationObjectImplementation::activate(player);

	if (!active && isActive()) {
		Reference<ResourceSpawn*> selectedResource = getSelectedResourcePool();

		if (selectedResource == nullptr) {
			if (player != nullptr)
				player->sendSystemMessage("@shared:harvester_no_resource"); // No resource selected. Shutting down.

			deactivate();
			return;
		}

		if (!selectedResource->inShift()) {
			if (player != nullptr)
				player->sendSystemMessage("@shared:harvester_resource_depleted"); // Resource has been depleted. Shutting down.

			deactivate();
			return;
		}

		float conditionDamage = getConditionDamage();

		if (conditionDamage > 0) {
			if (player != nullptr) {
				float maxCondition = getMaxCondition();
				float damage = conditionDamage / maxCondition;

				if (damage < 0.25)
					player->sendSystemMessage("@shared:harvester_no_maint_1"); // Electrical short detected. Shutting down. (Choose "pay maintenance" to repair.)
				else if (damage < 0.5)
					player->sendSystemMessage("@shared:harvester_no_maint_2"); // Cooling system failure detected. Shutting down. (Choose "pay maintenance" to repair.)
				else if (damage < 0.75)
					player->sendSystemMessage("@shared:harvester_no_maint_3"); // Hopper mechanism jam detected. Shutting down. (Choose "pay maintenance" to repair.)
				else
					player->sendSystemMessage("@shared:harvester_no_maint_4"); // Major system failure detected. Shutting down. (Choose "pay maintenance" to repair.)
			}

			deactivate();
			return;
		}

		float spawnDensity = selectedResource->getDensityAt(getZone()->getZoneName(), getPositionX(), getPositionY());
		installedExtractionRate = currentExtractionRate * spawnDensity;
		updateLastTickTime();
	}
}

void HarvesterObjectImplementation::deactivate() {
	bool active = isActive();
	InstallationObjectImplementation::deactivate();

	if (active && !isActive()) {
		installedExtractionRate = 0.f;
		roundHopperContents();
	}
}

void HarvesterObjectImplementation::roundHopperContents() {
	for (int i = hopperContents->size() - 1; i >= 0; i--) {
		uint64 entryKey = hopperContents->getKeyAt(i);
		int entryValue = (int)hopperContents->getValueAt(i);

		if (entryValue == 0)
			hopperContents->drop(entryKey);
		else
			hopperContents->set(entryKey, (float)entryValue);
	}
}

void HarvesterObjectImplementation::setCurrentExtractionRate(float newRate) {
	if (newRate >= maxExtractionRate)
		return;

	if (isActive()) {
		harvest();
		deactivate();

		currentExtractionRate = newRate;
		activate(nullptr);
	} else {
		currentExtractionRate = newRate;
	}
}

void HarvesterObjectImplementation::harvest() {
	if (!isActive() || installedExtractionRate == 0.f)
		return;

	if (getConditionDamage() > 0) {
		deactivate();
		return;
	}

	Reference<ResourceSpawn*> resourceSpawn = getSelectedResourcePool();

	if (resourceSpawn == nullptr || !resourceSpawn->inShift()) {
		deactivate();
		return;
	}

	Time now;
	uint64 curTime = now.getTime();

	uint64 tickDiff = lastTickTime.miliDifference() / 1000;
	uint64 tickTime = lastTickTime.getTime();
	float amountCollected = tickDiff * installedExtractionRate;
	uint64 powerTime = getOutOfPowerTime();
	updateLastTickTime();

	// Adjust for the harvester running out of power prior to the harvest tick
	if (powerTime > 0 && powerTime < curTime) {
		// Out of power before last tick
		if (powerTime < tickTime) {
			amountCollected = 0;
		} else {
			// Adjust by how much power was available
			float collectAdjust = (powerTime - tickTime) / (curTime - tickTime);
			amountCollected *= collectAdjust;
		}
	}

	float curMax = getHopperContents();

	if (curMax + amountCollected > maxHopperAmount) {
		float newAmount = maxHopperAmount - curMax;
		addResource(resourceSpawn->getObjectID(), newAmount);
		deactivate();
	} else {
		addResource(resourceSpawn->getObjectID(), amountCollected);
	}
}

void HarvesterObjectImplementation::addResource(uint64 resourceID, float amount) {
	float curAmount = hopperContents->get(resourceID);
	float newAmount = curAmount + amount;

	if (amount < 0)
		amount = 0;

	hopperContents->set(resourceID, newAmount);
}

void HarvesterObjectImplementation::selectResource(uint64 resourceID, CreatureObject* player) {
	bool found = false;

	if (surveyList.size() == 0)
		takeSurvey();

	for (int i = 0; i < surveyList.size(); i++) {
		Reference<ResourceSpawn*> spawn = surveyList.get(i);

		if (spawn == nullptr)
			continue;

		if (spawn->getObjectID() == resourceID) {
			found = true;
			break;
		}
	}

	if (!found)
		return;

	if (isActive()) {
		deactivate();
		resourceType = resourceID;
		activate(player);
	}

	scheduleTickTask(true);
}

void HarvesterObjectImplementation::takeSurvey() {
	if (surveyList.size() > 0) {
		surveyList.removeAll();
	}

	Vector<ManagedReference<ResourceSpawn*> > resourceList;

	ResourceManager* resourceManager = getZoneServer()->getResourceManager();
	resourceManager->getResourceListByType(resourceList, getInstallationType(), getZone()->getZoneName());

	for (int i = 0; i < resourceList.size(); i++) {
		surveyList.add(resourceList.get(i));
	}

	InstallationSynchronizedUi* ui = getSynchronizedUi();

	if (ui)
		ui->refresh();

	lastSurveyTime.updateToCurrentTime();
}

InstallationSynchronizedUi* HarvesterObjectImplementation::getSynchronizedUi() {
	if (syncUi == nullptr) {
		syncUi = new InstallationSynchronizedUi();
		syncUi->setOwner(asSceneObject());
		syncUi->refresh();
	}

	return syncUi;
}

Vector<ManagedReference<ResourceSpawn*> > HarvesterObjectImplementation::getSurveyTypes() {
	if (surveyList.size() == 0 || lastSurveyTime.miliDifference() > 60 * 60 * 1000) {
		surveyList.removeAll();
		takeSurvey();
	}

	return surveyList;
}

void HarvesterObjectImplementation::emptyHopper(CreatureObject* player, uint64 resourceID, int amount, bool discard, uint8 sequenceID) {
	if (player == nullptr)
		return;

	if (amount == 0)
		return;

	SceneObject* inventory = player->getSlottedObject("inventory");

	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr)
		return;

	Reference<ResourceSpawn*> resourceSpawn = zoneServer->getObject(resourceType).castTo<ResourceSpawn*>();

	if (resourceSpawn == nullptr)
		return;

	int amountToRemove = 0;
	int amountInHopper = hopperContents->get(resourceID);

	if (amount < 0 || amount > amountInHopper)
		amountToRemove = amountInHopper;

	if (!discard) {
		if (amountToRemove > ResourceContainer::MAXSIZE)
			amountToRemove = ResourceContainer::MAXSIZE;

		Reference<ResourceContainer*> newResource = resourceSpawn->createResource(amountToRemove);

		if (!inventory->isContainerFullRecursive()) {
			if (inventory->transferObject(newResource, -1, true)) {
				inventory->broadcastObject(newResource, true);
			} else {
				newResource->destroyObjectFromDatabase(true);
				return;
			}
		} else {
			StringIdChatParameter stringId("error_message", "inv_full");
			player->sendSystemMessage(stringId);
			return;
		}
	}

	addResource(resourceID, -amountToRemove);

	InstallationSynchronizedUi* ui = getSynchronizedUi();

	if (ui)
		ui->refresh();

	GenericResponse* gr = new GenericResponse(player, 0xED, true, sequenceID);
	player->sendMessage(gr);

}

void HarvesterObjectImplementation::synchronizedUIListen(CreatureObject* player) {
	if (!player->isPlayerCreature() || !isOnAdminList(player) || getZone() == nullptr)
		return;

	addOperator(player);

	InstallationSynchronizedUi* ui = getSynchronizedUi();

	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this.getReferenceUnsafeStaticCast(), ui);
	player->sendMessage(msg);
}

void HarvesterObjectImplementation::synchronizedUIStopListen(CreatureObject* player) {
	if (!player->isPlayerCreature())
		return;

	removeOperator(player);
}

void HarvesterObjectImplementation::broadcastDeltas() {
	InstallationSynchronizedUi* ui = getSynchronizedUi();

	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this.getReferenceUnsafeStaticCast(), ui);

	broadcastMessage(msg, false);
}

void HarvesterObjectImplementation::broadcastToOperators() {
	if (currentOperators.size() == 0)
		return;

	InstallationSynchronizedUi* ui = getSynchronizedUi();

	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this.getReferenceUnsafeStaticCast(), ui);

	for (int i = currentOperators.size() - 1; i >= 0; i--) {
		CreatureObject* player = currentOperators.get(i);

		if (player == nullptr || !player->isOnline()) {
			currentOperators.remove(i);
			continue;
		}

		player->sendMessage(msg);
	}
}
