/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/player/PlayerManager.h"

void ShipControlDeviceImplementation::generateObject(CreatureObject* player) {
	//info("generating ship", true);
	//return;

	ZoneServer* zoneServer = getZoneServer();

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	Locker clocker(controlledObject, player);

	controlledObject->initializePosition(player->getPositionX(), player->getPositionZ() + 10, player->getPositionY());

	player->getZone()->transferObject(controlledObject, -1, true);
	//controlledObject->insertToZone(player->getZone());

	//removeObject(controlledObject, true);

	controlledObject->transferObject(player, 5, true);
	player->setState(CreatureState::PILOTINGSHIP);
	//controlledObject->inflictDamage(player, 0, System::random(50), true);

	updateStatus(1);

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL)
		ghost->setTeleporting(true);
}

void ShipControlDeviceImplementation::storeObject(CreatureObject* player, bool force) {
	player->clearState(CreatureState::PILOTINGSHIP);

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject == NULL)
		return;

	Locker clocker(controlledObject, player);

	if (!controlledObject->isInQuadTree())
		return;

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	zone->transferObject(player, -1, false);
	
	controlledObject->destroyObjectFromWorld(true);

	transferObject(controlledObject, 4, true);
	
	updateStatus(0);
}

void ShipControlDeviceImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	//ControlDeviceImplementation::fillObjectMenuResponse(menuResponse, player);

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (!controlledObject->isInQuadTree()) {
		menuResponse->addRadialMenuItem(60, 3, "Launch Ship"); //Launch
	} else
		menuResponse->addRadialMenuItem(61, 3, "Land Ship"); //Launch
	//menuResponse->addRadialMenuItem(61, 3, "Launch Ship"); //Launch
}

bool ShipControlDeviceImplementation::canBeTradedTo(CreatureObject* player, CreatureObject* receiver, int numberInTrade) {
	ManagedReference<SceneObject*> datapad = receiver->getSlottedObject("datapad");

	if (datapad == NULL)
		return false;

	ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

	int shipsInDatapad = numberInTrade;
	int maxStoredShips = playerManager->getBaseStoredShips();

	for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
		Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

		if (obj != NULL && obj->isShipControlDevice() ){
			shipsInDatapad++;
		}
	}

	if( shipsInDatapad >= maxStoredShips){
		player->sendSystemMessage("That person has too many ships in their datapad");
		receiver->sendSystemMessage("You already have the maximum number of ships that you can own.");
		return false;
	}

	return true;
}
