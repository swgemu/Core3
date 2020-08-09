/*
 * ShipDeedImplementation.cpp
 *
 *  Created on: Jul 19, 2020
 *      Author: brakiss
 */

#include "server/zone/objects/tangible/ship/crafted/ShipDeed.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/ShipDeedTemplate.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/FighterShipObject.h"

#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/managers/ship/ShipManager.h"

#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/objects/player/PlayerObject.h"

void ShipDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	ShipDeedTemplate* deedData = dynamic_cast<ShipDeedTemplate*>(templateData);

	if (deedData == nullptr)
		return;

	shipControlObject = deedData->getShipControlObject();

	error() << "In loadTemplateData, deedData TemplateFileName is: " << deedData->getTemplateFileName();
	error() << "In loadTemplateData, shipControlObject is: " << shipControlObject;
}

void ShipDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("hit_points", hitPoints);
}

void ShipDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("ShipDeed");
}

void ShipDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/*
	 * Values available:	Range:
	 *
	 * hitpoints			varies, integrity of vehicle
	 */

	hitPoints = (int) values->getCurrentValue("hit_points");
}

void ShipDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if (isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@sui:create_vehicle");
}

int ShipDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 20) {
		if (generated || !isASubChildOf(player))
			return 1;

		if (player->isInCombat() || player->getParentRecursively(SceneObjectType::BUILDING) != nullptr) {
			player->sendSystemMessage("@pet/pet_menu:cant_call_vehicle"); //You can only unpack vehicles while Outside and not in Combat.
			return 1;
		}

		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

		if (datapad == nullptr) {
			player->sendSystemMessage("Datapad doesn't exist when trying to create vehicle");
			return 1;
		}

		// Check if this will exceed maximum number of vehicles allowed
		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		int shipsInDatapad = 0;
		int maxStoredShips = playerManager->getBaseStoredShips();

		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

			if (obj != nullptr && obj->isShipControlDevice())
				shipsInDatapad++;

		}

		if (shipsInDatapad >= maxStoredShips) {
			player->sendSystemMessage("@pet/pet_menu:has_max_vehicle"); // You already have the maximum number of vehicles that you can own.
			return 1;
		}

		debug() << "In handleObjectMenuSelect, shipControlObject is: " << shipControlObject << " hashCode is: " << shipControlObject.hashCode();

		Reference<ShipControlDevice*> shipControlDevice = (server->getZoneServer()->createObject(shipControlObject.hashCode(), 1)).castTo<ShipControlDevice*>();

		if (shipControlDevice == nullptr) {
			player->sendSystemMessage("wrong ship control device object template " + shipControlObject);
			return 1;
		}

		Locker locker(shipControlDevice);

		debug() << "In handleObjectMenuSelect, generatedObjectTemplate is: " << generatedObjectTemplate << " hashCode is: " << generatedObjectTemplate.hashCode();

		ManagedReference<ShipObject*> ship = ShipManager::instance()->generateShip(generatedObjectTemplate);

		//Reference<ShipObject*> vehicle = (server->getZoneServer()->createObject(generatedObjectTemplate.hashCode(), 1)).castTo<ShipObject*>();

		if (ship == nullptr) {
			shipControlDevice->destroyObjectFromDatabase(true);
			player->sendSystemMessage("wrong vehicle object template " + generatedObjectTemplate);
			return 1;
		}

		Locker vlocker(ship, player);

	    ship->setChassisMaxHealth(1000.0f);
	    ship->setCurrentChassisHealth(1000.0f);
	    ship->setOwner(player);

		shipControlDevice->setControlledObject(ship);
		if (!shipControlDevice->transferObject(ship, 4))
			info("Adding of ship to device failed");

		if (datapad->transferObject(shipControlDevice, -1)) {
			datapad->broadcastObject(shipControlDevice, true);
			//shipControlDevice->generateObject(player);

			player->getPlayerObject()->addShip(ship);

			generated = true;

			destroyObjectFromWorld(true);
			destroyObjectFromDatabase(true);

			return 0;
		} else {
			shipControlDevice->destroyObjectFromDatabase(true);
			return 1;
		}
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}

