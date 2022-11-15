/*
 * RadialManagerImplementation.cpp
 *
 *  Created on: 12/08/2009
 *      Author: victor
 */

#include "server/zone/managers/radial/RadialManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/ZoneServer.h"

RadialManagerImplementation::RadialManagerImplementation(ZoneServer* server) : ManagedObjectImplementation(), Logger() {
	setLoggingName("RadialManager");

	setGlobalLogging(true);
	setLogging(false);

	zoneServer = server;
}

void RadialManagerImplementation::handleObjectMenuRequest(CreatureObject* player, ObjectMenuResponse* defaultMenuResponse, uint64 objectID) {
	//Pre: Player is WLOCKED
	//Post: Player is WLOCKED
	ManagedReference<SceneObject*> menuObject = zoneServer->getObject(objectID);

	if (menuObject != nullptr) {
		Locker clocker(menuObject, player);

		debug("entering object menu request");

		menuObject->fillObjectMenuResponse(defaultMenuResponse, player);
	}

	defaultMenuResponse->finish();

	player->sendMessage(defaultMenuResponse->clone());

	if (menuObject != nullptr) {
		menuObject->notifyObservers(ObserverEventType::OBJECTRADIALOPENED, player, 0);
	}
}

void RadialManagerImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectID, uint64 objectID) {
	//Pre: player is NOT wlocked upon entry
	//Post: nothing is WLOCKED

	//System::out << "entering radial call 1" << endl;

	if (zoneServer == nullptr || zoneServer->isServerShuttingDown()) {
		player->info() << "Zone Server shutting down -- RadialManagerImplementation::handleObjectMenuSelect(player=" << player->getObjectID() << ", selectID=" << selectID << ", objectID=" << objectID << "): accessed radial menu.";
		return;
	}

	ManagedReference<SceneObject*> selectedObject = zoneServer->getObject(objectID);

	if (selectedObject == nullptr) {
		player->error() << "RadialManagerImplementation::handleObjectMenuSelect(player=" << player->getObjectID() << ", selectID=" << selectID << ", objectID=" << objectID << "): Failed to get selectedObject from zone server.";
		return;
	}

	try {
		Locker locker(player);
		Locker clocker(selectedObject, player);

		ManagedReference<BuildingObject*> rootParent = cast<BuildingObject*>(selectedObject->getRootParent());

		if (rootParent != nullptr && (!rootParent->isAllowedEntry(player) || rootParent != player->getRootParent()))
			return;

		/*if (!selectedObject->checkContainerPermission(player, ContainerPermissions::USE))
			return;*/

		selectedObject->debug() << "entering radial call " << selectID;
		selectedObject->handleObjectMenuSelect(player, selectID);

		selectedObject->notifyObservers(ObserverEventType::OBJECTRADIALUSED, player, selectID);
	} catch (const Exception& e) {
		error("exception caught in void RadialManagerImplementation::handleObjectMenuSelect");

		error(e.getMessage());
		e.printStackTrace();
	}
}
