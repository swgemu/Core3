/*
 * ResourceDeedImplementation.cpp
 *
 *  Created on: Sep 8, 2010
 *      Author: elvaron
 */

#include <stddef.h>
#include <algorithm>

#include "system/lang/ref/Reference.h"
#include "system/lang/ref/WeakReference.h"
#include "system/platform.h"

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "engine/service/proto/BaseMessage.h"

#include "server/zone/QuadTreeEntry.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/tangible/deed/resource/ResourceDeed.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/callbacks/ResourceDeedSuiCallback.h"


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

	if (!isASubChildOf(creature))
		return 0;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL || ghost->hasSuiBoxWindowType(SuiWindowType::FREE_RESOURCE)) {
		//ghost->closeSuiWindowType(SuiWindowType::FREE_RESOURCE);
		ghost->removeSuiBoxType(SuiWindowType::FREE_RESOURCE);

		return 0;
	}

	ManagedReference<ResourceManager*> resourceManager = server->getZoneServer()->getResourceManager();

	ManagedReference<SuiListBox*> sui = new SuiListBox(creature, SuiWindowType::FREE_RESOURCE);
	sui->setUsingObject(_this.getReferenceUnsafeStaticCast());
	sui->setCallback(new ResourceDeedSuiCallback(server->getZoneServer(), "Resource"));
	sui->setPromptTitle("@veteran:resource_title"); //Resources
	sui->setPromptText("@veteran:choose_class"); //Choose resource class
	sui->setOtherButton(true, "@back");
	sui->setCancelButton(true, "@cancel");
	sui->setOkButton(true, "@ok");

	resourceManager->addNodeToListBox(sui, "resource");

	ghost->addSuiBox(sui);
	creature->sendMessage(sui->generateMessage());

	return 1;
}

void ResourceDeedImplementation::destroyDeed() {
	if (parent.get() != NULL) {
		destroyObjectFromWorld(true);
	}

	if (isPersistent())
		destroyObjectFromDatabase(true);

	generated = true;
}
