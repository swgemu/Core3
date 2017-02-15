/*
 * InstallationObjectImplementation.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: crush
 */

#include "server/zone/objects/installation/InstallationObject.h"
#include "sui/InsertPowerSuiCallback.h"

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/faction/FactionManager.h"

#include "server/zone/packets/installation/InstallationObjectMessage3.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage3.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage7.h"
#include "server/zone/packets/installation/InstallationObjectMessage6.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"

#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/Zone.h"
#include "templates/installation/SharedInstallationObjectTemplate.h"
#include "SyncrhonizedUiListenInstallationTask.h"
#include "components/TurretDataComponent.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/params/OptionBitmask.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

void InstallationObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	StructureObjectImplementation::loadTemplateData(templateData);

	if (!templateData->isSharedInstallationObjectTemplate())
		return;

	SharedInstallationObjectTemplate* inso = dynamic_cast<SharedInstallationObjectTemplate*>(templateData);

	installationType = inso->getInstallationType();

}

void InstallationObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//send buios here

	BaseMessage* buio3 = new InstallationObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(buio3);

	BaseMessage* buio6 = new InstallationObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(buio6);


	if ((getObjectTemplate()->getGameObjectType() == SceneObjectType::MINEFIELD || getObjectTemplate()->getGameObjectType() == SceneObjectType::DESTRUCTIBLE) && player->isCreatureObject())
			sendPvpStatusTo(cast<CreatureObject*>(player));

}

void InstallationObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	//TangibleObjectImplementation::fillAttributeList(alm, object);

	if (isOnAdminList(object)) {

		//Add the owner name to the examine window.
		ManagedReference<SceneObject*> obj = object->getZoneServer()->getObject(ownerObjectID);

		if(obj != NULL) {
			alm->insertAttribute("owner", obj->getDisplayedName());
		}
	}
	if(isTurret() && dataObjectComponent != NULL){

		TurretDataComponent* turretData = cast<TurretDataComponent*>(dataObjectComponent.get());
			if(turretData == NULL)
				return;

			turretData->fillAttributeList(alm);
	}

}

void InstallationObjectImplementation::setOperating(bool value, bool notifyClient) {
	//updateInstallationWork();

	if (operating == value)
		return;

	if (value) {

		if(currentSpawn == NULL)
			return;

		spawnDensity = currentSpawn->getDensityAt(getZone()->getZoneName(), getPositionX(), getPositionY());

		if(spawnDensity < .10) {
			return;
		}

		if (getBasePowerRate() != 0 && surplusPower <= 0) {
			StringIdChatParameter stringId("player_structure", "power_deposit_incomplete");
			ChatSystemMessage* msg = new ChatSystemMessage(stringId);

			broadcastToOperators(msg);
			return;
		}

		if (getMaintenanceRate() != 0 && surplusMaintenance <= 0) {
			StringIdChatParameter stringId("shared", "harvester_no_maint_4");
			ChatSystemMessage* msg = new ChatSystemMessage(stringId);

			broadcastToOperators(msg);
			return;
		}
	}

	Time timeToWorkTill;

	operating = value;
	extractionRemainder = 0;

	if (operating) {
		setOptionBit(OptionBitmask::ACTIVATED, false);

		lastStartTime.updateToCurrentTime();
	} else {
		clearOptionBit(OptionBitmask::ACTIVATED, false);

		lastStopTime.updateToCurrentTime();
	}

	InstallationObjectDeltaMessage3* delta = new InstallationObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
	delta->updateOperating(value);
	delta->updateOptionsBitmask();
	delta->close();

	InstallationObjectDeltaMessage7* delta7 = new InstallationObjectDeltaMessage7(_this.getReferenceUnsafeStaticCast());
	delta7->updateOperating(value);
	delta7->close();

	Vector<BasePacket*> messages;
	messages.add(delta);
	messages.add(delta7);

	broadcastMessages(&messages, true);

	if (value) {
		resourceHopperTimestamp.updateToCurrentTime();
	}

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this.getReferenceUnsafeStaticCast());
	inso7->updateExtractionRate(getActualRate());
	inso7->close();

	broadcastToOperators(inso7);
}

void InstallationObjectImplementation::setActiveResource(ResourceContainer* container) {

	Time timeToWorkTill;

	if (resourceHopper.size() == 0) {
		addResourceToHopper(container);
		currentSpawn = container->getSpawnObject();

		spawnDensity = currentSpawn->getDensityAt(getZone()->getZoneName(), getPositionX(), getPositionY());

		return;
	}

	updateInstallationWork();

	int i = 0;
	for (; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry == container) {
			if (i == 0)
				return;

			ManagedReference<ResourceContainer*> oldEntry = resourceHopper.get(0);

			InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this.getReferenceUnsafeStaticCast());
			inso7->updateHopper();
			inso7->startUpdate(0x0D);

			resourceHopper.set(0, container, inso7, 2);

			if(oldEntry->getQuantity() > 0)
				resourceHopper.set(i, oldEntry, inso7, 0);
			else
				resourceHopper.remove(i, inso7, 0);

			currentSpawn = container->getSpawnObject();
			spawnDensity = currentSpawn->getDensityAt(getZone()->getZoneName(), getPositionX(), getPositionY());

			inso7->updateHopperSize(getHopperSize());
			inso7->updateExtractionRate(getActualRate());
			inso7->close();

			broadcastToOperators(inso7);
		}
	}
}

void InstallationObjectImplementation::handleStructureAddEnergy(CreatureObject* player) {
	try {
		StringBuffer sstext, ssTotalEnergy;

		ManagedReference<SuiTransferBox*> energyBox = new SuiTransferBox(player, SuiWindowType::STRUCTURE_ADD_ENERGY);
		energyBox->setUsingObject(_this.getReferenceUnsafeStaticCast());
		energyBox->setPromptTitle("@player_structure:add_power");

		sstext	<< "@player_structure:select_power_amount"
				<<"\n\n@player_structure:current_power_value " << (int) surplusPower;

		energyBox->setPromptText(sstext.toString());

		ResourceManager* resourceManager = getZoneServer()->getResourceManager();

		ssTotalEnergy << resourceManager->getAvailablePowerFromPlayer(player);

		energyBox->addFrom("@player_structure:total_energy", ssTotalEnergy.toString(), ssTotalEnergy.toString(), "1");
		energyBox->addTo("@player_structure:to_deposit", "0", "0", "1");

		energyBox->setCallback(new InsertPowerSuiCallback(server->getZoneServer()));
		player->getPlayerObject()->addSuiBox(energyBox);
		player->sendMessage(energyBox->generateMessage());

	} catch (Exception& e) {
		e.printStackTrace();
		error("unreported exception in InstallationObjectImplementation::handleStructureAddEnergy");
	}
}

float InstallationObjectImplementation::getHopperSize() {
	float hopperSize = 0.0f;

	for (int i = 0; i < resourceHopper.size(); i++) {
		ResourceContainer* entry = resourceHopper.get(i);
		hopperSize += entry->getQuantity();
	}

	return hopperSize;
}

int InstallationObjectImplementation::getHopperItemQuantity(ResourceSpawn* spawn) {
	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry->getSpawnObject() == spawn)
			return entry->getQuantity();
	}

	return -1;
}

ResourceContainer* InstallationObjectImplementation::getContainerFromHopper(ResourceSpawn* spawn) {
	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* entry = resourceHopper.get(i);

		if (entry->getSpawnObject() == spawn)
			return entry;
	}

	return NULL;
}

void InstallationObjectImplementation::updateInstallationWork() {

	Time timeToWorkTill;

	bool shutdownAfterWork = updateMaintenance(timeToWorkTill);
	updateHopper(timeToWorkTill, shutdownAfterWork);
}

bool InstallationObjectImplementation::updateMaintenance(Time& workingTime) {

	Time now;
	
	int currentTime = time(0);
	int lastTime = lastMaintenanceTime.getTime();

	int elapsedTime = currentTime - lastTime;
	int workTimePermitted = elapsedTime;

	float payAmount = ((float)elapsedTime / 3600.0f) * getMaintenanceRate();

	bool shutdownWork = false;


	if (payAmount > surplusMaintenance) {

		workTimePermitted = surplusMaintenance / getMaintenanceRate() * 3600;

		Time workTill(lastMaintenanceTime.getTime() + (int) workTimePermitted);
		workingTime = workTill;

		shutdownWork = true;
	}

	if (workTimePermitted > 0) {
		elapsedTime = workTimePermitted;
	}

	addMaintenance(-1.0f * payAmount);

	int basePowerRate = getBasePowerRate();

	if (isOperating() && basePowerRate != 0) {
		float energyAmount = (elapsedTime / 3600.0) * basePowerRate;

		if (energyAmount > surplusPower) {
			energyAmount = surplusPower;

			float workPowerPermitted = (surplusPower / basePowerRate) * 3600;

			if (workPowerPermitted < elapsedTime) {
				Time workTill(lastMaintenanceTime.getTime() + (int) workPowerPermitted);
				workingTime = workTill;
			}

			shutdownWork = true;
		}

		addPower(-1.0f * energyAmount);

	}

	lastMaintenanceTime.updateToCurrentTime();

	return shutdownWork;
}

void InstallationObjectImplementation::updateHopper(Time& workingTime, bool shutdownAfterUpdate) {

	Locker locker(_this.getReferenceUnsafeStaticCast());
	
	if (getZone() == NULL)
		return;

	Time timeToWorkTill;

	if (!isOperating()) {
		if(lastStopTime.compareTo(resourceHopperTimestamp) != -1)
			return;
	}

	if (resourceHopper.size() == 0) { // no active spawn
		if(currentSpawn == NULL)
			return;

		Locker locker(currentSpawn);
		addResourceToHopper(currentSpawn->createResource(0));
	}

	ManagedReference<ResourceContainer*> container = resourceHopper.get(0);

	if(currentSpawn == NULL)
		currentSpawn = container->getSpawnObject();

	Time currentTime = workingTime;

	Time spawnExpireTimestamp((uint32)currentSpawn->getDespawned());
	// if (t1 < t2) return 1 - if spawnTime is sooner currentTime, use spawnTime, else use spawn time
	uint32 harvestUntil = (spawnExpireTimestamp.compareTo(currentTime) > 0) ? spawnExpireTimestamp.getTime() : currentTime.getTime();
	uint32 lastHopperUpdate = resourceHopperTimestamp.getTime();

	int elapsedTime = (harvestUntil - lastHopperUpdate);

	float harvestAmount = (elapsedTime / 60.0) * (spawnDensity * getExtractionRate());

	int availableCapacity = (int)(getHopperSizeMax() - getHopperSize());
	harvestAmount = harvestAmount > availableCapacity ? availableCapacity : harvestAmount;

	if(harvestAmount < 0)
		harvestAmount = 0;

	harvestAmount += extractionRemainder;
	extractionRemainder = harvestAmount - (int) harvestAmount;
	harvestAmount = (int) harvestAmount;

	float currentQuantity = container->getQuantity();


	if(harvestAmount > 0 || !isOperating()) {
		Locker spawnLocker(currentSpawn);

		currentSpawn->extractResource(getZone()->getZoneName(), harvestAmount);

		spawnLocker.release();

		updateResourceContainerQuantity(container, (currentQuantity + harvestAmount), true);
	}

	// Update Timestamp
	resourceHopperTimestamp.updateToCurrentTime();

	if((int)getHopperSize() >= (int)getHopperSizeMax())
		shutdownAfterUpdate = true;

	if(spawnExpireTimestamp.compareTo(currentTime) > 0) {
		shutdownAfterUpdate = true;
	}

	if (shutdownAfterUpdate)
		setOperating(false);

	/*InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this.getReferenceUnsafeStaticCast());
	inso7->startUpdate(0x0D);
	resourceHopper.set(0, container, inso7, 1);
	inso7->updateHopperSize(getHopperSize());
	inso7->close();

	broadcastToOperators(inso7);*/

}


void InstallationObjectImplementation::clearResourceHopper() {

	Time timeToWorkTill;

	if (resourceHopper.size() == 0)
		return;

	setOperating(false);

	//lets delete the containers from db
	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* container = resourceHopper.get(i);
		if (container != NULL) {
			Locker locker(container);
			container->destroyObjectFromDatabase(true);
		}
	}

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this.getReferenceUnsafeStaticCast());
	inso7->updateHopper();
	inso7->startUpdate(0x0D);

	resourceHopper.removeAll(inso7);

	inso7->updateActiveResourceSpawn(getActiveResourceSpawnID());
	inso7->updateHopperSize(getHopperSize());
	inso7->updateExtractionRate(getActualRate());

	inso7->close();

	broadcastToOperators(inso7);
}

void InstallationObjectImplementation::addResourceToHopper(ResourceContainer* container) {
	if (resourceHopper.contains(container))
		return;

	Time timeToWorkTill;

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this.getReferenceUnsafeStaticCast());
	inso7->updateHopper();
	inso7->startUpdate(0x0D);

	resourceHopper.add(container, inso7, 1);

	inso7->close();

	broadcastToOperators(inso7);
}

void InstallationObjectImplementation::changeActiveResourceID(uint64 spawnID) {

	// Logic:
	// 1) If operating, and already has an active resource ID - make sure the hopper gets updated
	// 2) Get the spawn information & set the active resource id
	// 3) If hopper size is zero for the resource + is operating, send a packet to the operators to add a zero element for delta packets

	info("updating active ");

	if (isOperating()) {
		updateInstallationWork();
	}

	currentSpawn = getZoneServer()->getObject(spawnID).castTo<ResourceSpawn*>();
	if (currentSpawn == NULL) {
		error("new spawn null");
		return;
	}

	Time timeToWorkTill;

	Time currentTime;

	resourceHopperTimestamp.updateToCurrentTime();

	ManagedReference<ResourceContainer*> container = getContainerFromHopper(currentSpawn);

	if (container == NULL) {
		Locker locker(currentSpawn);
		container = currentSpawn->createResource(0);

		addResourceToHopper(container);
		setActiveResource(container);
	} else {
		setActiveResource(container);
	}

	InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this.getReferenceUnsafeStaticCast());
	inso7->updateExtractionRate(getActualRate());
	inso7->updateActiveResourceSpawn(getActiveResourceSpawnID());
	inso7->close();

	broadcastToOperators(inso7);
}

void InstallationObjectImplementation::broadcastToOperators(BasePacket* packet) {
#ifdef LOCKFREE_BCLIENT_BUFFERS
	Reference<BasePacket*> pack = packet;
#endif

	for (int i = 0; i < operatorList.size(); ++i) {
		CreatureObject* player = operatorList.get(i);
#ifdef LOCKFREE_BCLIENT_BUFFERS
		player->sendMessage(pack);
#else
		player->sendMessage(packet->clone());
#endif
	}

#ifndef LOCKFREE_BCLIENT_BUFFERS
	delete packet;
#endif
}

void InstallationObjectImplementation::activateUiSync() {
	if (operatorList.size() == 0)
		return;

	try {

		if (syncUiTask == NULL)
			syncUiTask = new SyncrhonizedUiListenInstallationTask(_this.getReferenceUnsafeStaticCast());

		if (!syncUiTask->isScheduled())
			syncUiTask->schedule(5000);
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void InstallationObjectImplementation::verifyOperators() {
	if (operatorList.size() <= 0)
		return;

	// won't fully clean up at once because indexes would change once you remove one - but should clean up
	for (int i = 0; i < operatorList.size(); i++) {
		ManagedReference<CreatureObject*> obj = operatorList.get(i);

		if (!obj->isOnline()) {
			operatorList.remove(i);

			--i;
		}
	}

}

void InstallationObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	StructureObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	if (!destroyContainedObjects)
		return;

	ManagedReference<SceneObject*> deed = getZoneServer()->getObject(deedObjectID);

	if (deed != NULL) {
		Locker locker(deed);
		deed->destroyObjectFromDatabase(true);
	}

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* container = resourceHopper.get(i);

		Locker locker(container);
		container->destroyObjectFromDatabase(true);
	}
}

void InstallationObjectImplementation::updateResourceContainerQuantity(ResourceContainer* container, int newQuantity, bool notifyClient) {

	Time timeToWorkTill;

	container->setQuantity(newQuantity, false, true);

	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* cont = resourceHopper.get(i);

		if (cont == container) {
			InstallationObjectDeltaMessage7* inso7 = new InstallationObjectDeltaMessage7( _this.getReferenceUnsafeStaticCast());
			inso7->updateHopper();
			inso7->startUpdate(0x0D);
			if(container->getQuantity() == 0 && (!isOperating() || (isOperating() && i != 0)))
				resourceHopper.remove(i, inso7, 1);
			else
				resourceHopper.set(i, container, inso7, 1);
			inso7->updateHopperSize(getHopperSize());
			inso7->updateExtractionRate(getActualRate());
			inso7->close();

			if (notifyClient)
				broadcastToOperators(inso7);
			else
				delete inso7;
		}
	}

	if(resourceHopper.size() == 0)
		setOperating(false);

	//broadcastToOperators(new InstallationObjectDeltaMessage7(_this.getReferenceUnsafeStaticCast()));
}

uint64 InstallationObjectImplementation::getActiveResourceSpawnID() {
	if (currentSpawn == NULL) {
		return 0;
	} else {

		if(currentSpawn->getDespawned() < time(0))
			return 0;

		return currentSpawn->getObjectID();
	}
}

float InstallationObjectImplementation::getActualRate() {
	if (!isOperating())
		return 0.0f;

	if (resourceHopper.size() == 0)
		return 0;

	return extractionRate * spawnDensity;
}

void InstallationObjectImplementation::setExtractionRate(float rate){
	extractionRate = rate;
}

void InstallationObjectImplementation::setHopperSizeMax(float size){
	hopperSizeMax = size;
}

void InstallationObjectImplementation::updateStructureStatus() {
	if(isCivicStructure())
		return;

	updateInstallationWork();

	if (surplusMaintenance < 0) {
		setConditionDamage(-surplusMaintenance, true);

	} else {
		setConditionDamage(0, true);
	}
}

bool InstallationObjectImplementation::isAggressiveTo(CreatureObject* target) {
	if (!isAttackableBy(target) || target->isVehicleObject())
		return false;

	if (getFaction() != 0 && target->getFaction() != 0 && getFaction() != target->getFaction())
		return true;

	SharedInstallationObjectTemplate* instTemplate = templateObject.castTo<SharedInstallationObjectTemplate*>();

	if (instTemplate != NULL) {
		String factionString = instTemplate->getFactionString();

		if (!factionString.isEmpty()) {
			if (target->isAiAgent()) {
				AiAgent* targetAi = target->asAiAgent();

				if (FactionManager::instance()->isEnemy(factionString, targetAi->getFactionString()))
					return true;
			} else if (target->isPlayerCreature()) {
				PlayerObject* ghost = target->getPlayerObject();

				if (ghost == NULL)
					return false;

				if (ghost->getFactionStanding(factionString) <= -3000)
					return true;

				FactionMap* fMap = FactionManager::instance()->getFactionMap();

				const Faction& faction = fMap->get(factionString);
				const SortedVector<String>* enemies = faction.getEnemies();

				for (int i = 0; i < enemies->size(); ++i) {
					const String& enemy = enemies->get(i);

					if (ghost->getFactionStanding(enemy) >= 3000)
						return true;
				}
			}
		}
	}

	return false;
}

bool InstallationObjectImplementation::isAttackableBy(CreatureObject* object) {
	if (!(getPvpStatusBitmask() & CreatureFlag::ATTACKABLE)) {
		return false;
	}

	unsigned int thisFaction = getFaction();
	unsigned int otherFaction = object->getFaction();

	if (otherFaction != 0 && thisFaction != 0) {
		if (otherFaction == thisFaction) {
			return false;
		}

	}

	if (object->isPet()) {
		ManagedReference<CreatureObject*> owner = object->getLinkedCreature().get();

		if (owner == NULL)
			return false;

		return isAttackableBy(owner);

	} else if (object->isPlayerCreature() && thisFaction != 0) {
		if (object->getFactionStatus() == 0) {
			return false;
		}

		if ((getPvpStatusBitmask() & CreatureFlag::OVERT) && object->getFactionStatus() != FactionStatus::OVERT) {
			return false;
		}
	}

	SharedInstallationObjectTemplate* instTemplate = templateObject.castTo<SharedInstallationObjectTemplate*>();

	if (instTemplate != NULL) {
		String factionString = instTemplate->getFactionString();

		if (!factionString.isEmpty()) {
			if (object->isAiAgent() && !FactionManager::instance()->isEnemy(factionString, object->asAiAgent()->getFactionString()))
				return false;
			else if (object->isPlayerCreature() && getObjectTemplate()->getFullTemplateString().contains("turret_fs_village"))
				return false;
		}
	}

	return true;
}

void InstallationObjectImplementation::createChildObjects() {
	if (isTurret()) {
		SharedInstallationObjectTemplate* inso = dynamic_cast<SharedInstallationObjectTemplate*>(getObjectTemplate());

		if (inso != NULL) {
			uint32 defaultWeaponCRC = inso->getWeapon().hashCode();

			if (getZoneServer() != NULL) {
				Reference<WeaponObject*> defaultWeapon = (getZoneServer()->createObject(defaultWeaponCRC, getPersistenceLevel())).castTo<WeaponObject*>();

				if (defaultWeapon == NULL) {
					return;
				}

				if (!transferObject(defaultWeapon, 4)) {
					defaultWeapon->destroyObjectFromDatabase(true);
					return;
				}

				if (dataObjectComponent != NULL) {
					TurretDataComponent* turretData = cast<TurretDataComponent*>(dataObjectComponent.get());

					if (turretData != NULL) {
						turretData->setWeapon(defaultWeapon);
					}
				}
			}
		}
	} else if (isMinefield()) {
		this->setContainerDefaultAllowPermission(ContainerPermissions::MOVEIN);
		this->setContainerDefaultDenyPermission(ContainerPermissions::MOVEOUT);
		this->setContainerDefaultAllowPermission(ContainerPermissions::OPEN);

	} else {
		StructureObjectImplementation::createChildObjects();
	}
}

float InstallationObjectImplementation::getHitChance() {
		SharedInstallationObjectTemplate* inso = dynamic_cast<SharedInstallationObjectTemplate*>(getObjectTemplate());

		if (inso == NULL)
			return 0;

		return inso->getChanceHit();
}
