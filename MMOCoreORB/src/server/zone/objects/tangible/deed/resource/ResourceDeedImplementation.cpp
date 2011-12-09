/*
 * ResourceDeedImplementation.cpp
 *
 *  Created on: Sep 8, 2010
 *      Author: elvaron
 */

#include "ResourceDeed.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sui/callbacks/ResourceDeedSuiCallback.h"

#include "server/zone/packets/object/ObjectMenuResponse.h"

void ResourceDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("ResourceDeed");
}

void ResourceDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItem(20, 3, "@ui_radial:item_use"); //use
}

int ResourceDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20) // not use object
		return 1;

	if (player != NULL)
		useObject(player);

	return 0;
}

int ResourceDeedImplementation::useObject(CreatureObject* creature) {
	if (creature == NULL)
		return 0;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL || ghost->hasSuiBoxWindowType(SuiWindowType::FREE_RESOURCE)) {
		return 0;
	}

	ManagedReference<ResourceManager*> resourceManager = server->getZoneServer()->getResourceManager();

	ManagedReference<SuiListBox*> sui = new SuiListBox(creature, SuiWindowType::FREE_RESOURCE);
	sui->setUsingObject(_this);
	sui->setCallback(new ResourceDeedSuiCallback(server->getZoneServer(), "Resource"));
	sui->setPromptTitle("@veteran:resource_title"); //Resources
	sui->setPromptText("@veteran:choose_class"); //Choose resource class
	sui->setOtherButton(true, "@back");
	sui->setOkButton(true, "@ok");

	resourceManager->addNodeToListBox(sui, "resource");

	ghost->addSuiBox(sui);
	creature->sendMessage(sui->generateMessage());

	return 1;
}

void ResourceDeedImplementation::destroyDeed() {
	if (parent != NULL) {
		/*getParent()->removeObject(_this, true);
		broadcastDestroy(_this, false);*/
		destroyObjectFromWorld(true);
	}

	if (isPersistent())
		destroyObjectFromDatabase(true);

	generated = true;
}
