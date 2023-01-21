/*
 * ShipDeedImplementation.cpp
 *
 *  Created on: Jan. 19, 2023
 *  Author: H
 */


#include "server/zone/objects/tangible/deed/ship/ShipDeed.h"
#include"server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/ShipDeedTemplate.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/Zone.h"

void ShipDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	ShipDeedTemplate* deedData = dynamic_cast<ShipDeedTemplate*>(templateData);

	if (deedData == nullptr) {
		error() << "Ship Deed Data is null";
		return;
	}

	generatedObjectTemplate = deedData->getGeneratedObjectTemplate();
	controlDeviceTemplate = deedData->getControlDeviceObjectTemplate();
}

void ShipDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("volume", 1);

	StringBuffer certName;
	certName << "@skl_n:" << getCertificationRequired();
	alm->insertAttribute("pilotskillrequired", certName.toString());

	float maxCond = getMaxHitPoints();
	float currentHp = maxCond - getHitPointsDamage();
	StringBuffer hp;
	hp << Math::getPrecision(currentHp, 5) << "/" << Math::getPrecision(maxCond, 5);

	info(true) << currentHp << " " << maxCond << " " << hp.toString();

	alm->insertAttribute("chassishitpoints", hp.toString());
	alm->insertAttribute("chassismass", Math::getPrecision(getMass(), 3));
	alm->insertAttribute("parking_spot", getParkingLocaiton());
}

void ShipDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();
}

void ShipDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {

	//hitPoints = values->getCurrentValue("hit_points");
}

void ShipDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if (isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@sui:create_vehicle"); // ('string/en/sui.stf', 52, 'create_vehicle', 'Generate Ship'),
}

int ShipDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (player == nullptr)
		return 1;

	if (selectedID == 20) {
		if (generated || !isASubChildOf(player))
			return 1;

		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

		if (datapad == nullptr) {
			error() << "Players datapad is a nullptr";
			return 1;
		}

		ZoneServer* zoneServer = player->getZoneServer();

		if (zoneServer == nullptr)
			return 1;

		// Check if this will exceed maximum number of vehicles allowed
		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		if (playerManager == nullptr)
			return 1;

		int totalShips = 0;
		int pobShips = 0;
		int maxStoredShips = playerManager->getBaseStoredShips();

		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

			if (obj == nullptr)
				continue;

			if (obj->isShipControlDevice()) {
				totalShips++;

				ShipControlDevice* shipDevice = obj.castTo<ShipControlDevice*>();

				if (shipDevice != nullptr && shipDevice->isPobShipController())
					pobShips++;
			}
		}

		if (totalShips >= maxStoredShips) {
			StringIdChatParameter maxShips("space_interaction", "toomanyships"); // You have too many ships in your datapad already!
			player->sendSystemMessage(maxShips);

			return 1;
		}

		if (pobShips > 1) {
			StringIdChatParameter maxPobShips("space_interaction", "too_many_pobs"); // You cannot launch another ship with an interior. Empty out one of your other ships and you may take off with this ship.
			player->sendSystemMessage(maxPobShips);

			return 1;
		}

		ManagedReference<ShipControlDevice*> shipControlDevice = (zoneServer->createObject(controlDeviceTemplate.hashCode(), 1)).castTo<ShipControlDevice*>();

		if (shipControlDevice == nullptr) {
			error() << "Problem generating ship control device template: " << controlDeviceTemplate;
			return 1;
		}

		// Locker control device to the player
		Locker clocker(shipControlDevice, player);

		ManagedReference<ShipObject*> ship = (zoneServer->createObject(generatedObjectTemplate.hashCode(), 1)).castTo<ShipObject*>();

		if (ship == nullptr) {
			shipControlDevice->destroyObjectFromDatabase(true);
			error() << "Failed to generate ship object from template: " << generatedObjectTemplate;
			return 1;
		}

		// Lock the ship to the Control Device
		Locker slocker(ship, shipControlDevice);

		ship->setMaxCondition(getMaxHitPoints());
		ship->setConditionDamage(getHitPointsDamage());

		ship->setControlDeviceID(shipControlDevice->getObjectID());
		ship->createChildObjects();

		if (!shipControlDevice->transferObject(ship, 4, true)) {
			ship->destroyObjectFromWorld(true);
			ship->destroyObjectFromDatabase(true);

			shipControlDevice->destroyObjectFromWorld(true);
			shipControlDevice->destroyObjectFromDatabase(true);
			return 1;
		}

		shipControlDevice->setControlledObject(ship);
		shipControlDevice->updateStatus(0);

		// Release the ship cross lock
		slocker.release();

		if (!datapad->transferObject(shipControlDevice, -1)) {
			ship->destroyObjectFromWorld(true);
			ship->destroyObjectFromDatabase(true);

			shipControlDevice->destroyObjectFromWorld(true);
			shipControlDevice->destroyObjectFromDatabase(true);
			return 1;
		}

		datapad->broadcastObject(shipControlDevice, true);

		destroyObjectFromWorld(true);
		destroyObjectFromDatabase(true);

		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}