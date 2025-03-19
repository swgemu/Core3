/*
 * NavicomputerDeedImplementation.cpp
 *
 *  Created on: March 7, 2025
 *  Author: Halyn
 */


#include "server/zone/objects/tangible/deed/navicomputer/NavicomputerDeed.h"
#include"server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/NavicomputerDeedTemplate.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"

void NavicomputerDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	NavicomputerDeedTemplate* navicomputerDeedData = dynamic_cast<NavicomputerDeedTemplate*>(templateData);

	if (navicomputerDeedData == nullptr) {
		error() << "Navicomputer Deed Data is null";
		return;
	}

	controlDeviceTemplate = navicomputerDeedData->getControlDeviceObjectTemplate();
	datapadTemplate = navicomputerDeedData->getDatapadObjectTemplate();
}

void NavicomputerDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("volume", 1);
}

void NavicomputerDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();
}

void NavicomputerDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
}

void NavicomputerDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if (isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@pet/pet_menu:init_navicomp_dpad"); //Initialize Flight-Computer Core storage unit for use
}

int NavicomputerDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (player == nullptr)
		return 1;

	if (selectedID == 20) {
		if (generated || !isASubChildOf(player))
			return 1;

		ManagedReference<SceneObject*> datapad = player->getDatapad();

		if (datapad == nullptr) {
			error() << "Player datapad is a nullptr";
			return 1;
		}

		ZoneServer* zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return 1;
		}

		Reference<PetControlDevice*> flightComputer = (server->getZoneServer()->createObject(controlDeviceTemplate.hashCode(), 1)).castTo<PetControlDevice*>();

		if (flightComputer == nullptr) {
			player->sendSystemMessage("Error in flight computer: " + controlDeviceTemplate);
			return 1;
		}

		Reference<TangibleObject*> computerStorage = (server->getZoneServer()->createObject(datapadTemplate.hashCode(), 1)).castTo<TangibleObject*>();

		if (computerStorage == nullptr) {
			player->sendSystemMessage("Storage error in flight computer: " + controlDeviceTemplate);
			return 1;
		}		

		if (!flightComputer->transferObject(computerStorage, 4)) {
			computerStorage->destroyObjectFromDatabase(true);
			flightComputer->destroyObjectFromDatabase(true);
			player->sendSystemMessage("Storage transfer error in flight computer: " + controlDeviceTemplate);
			return 1;
		}

		Locker locker(flightComputer, player);

		flightComputer->setPetType(PetManager::FLIGHTCOMPUTER);

		if (!datapad->transferObject(flightComputer, -1)) {
			flightComputer->destroyObjectFromDatabase(true);
			player->sendSystemMessage("Control device transfer error in flight computer: " + controlDeviceTemplate);
			return 1;
		}

		flightComputer->setObjectName(*getObjectName(), false);
		datapad->broadcastObject(flightComputer, true);


		destroyObjectFromWorld(true);
		destroyObjectFromDatabase(true);

		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}
