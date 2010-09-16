/*
 * ResourceDeedImplementation.cpp
 *
 *  Created on: Sep 8, 2010
 *      Author: elvaron
 */

#include "ResourceDeed.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

void ResourceDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("ResourceDeed");
}

int ResourceDeedImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 20) // not use object
		return 1;

	if (player != NULL)
		useObject(player);

	return 0;
}

int ResourceDeedImplementation::useObject(PlayerCreature* player) {
	if (player == NULL)
		return 0;

	ManagedReference<ResourceManager*> resourceManager = server->getZoneServer()->getResourceManager();

	SuiListBox* sui1 = new SuiListBox(player, SuiWindowType::FREE_RESOURCE, SuiListBox::HANDLETWOBUTTON);//beginning of sui chain

	sui1->setPromptTitle("Resources");
	sui1->setPromptText("Choose resource class.");
	sui1->setCancelButton(true, "");
	player->addSuiBox(sui1);
	String base = "resource";
	resourceManager->addChildrenToDeedListBox(base, sui1);

	sui1->setUsingObject(_this);

	player->sendMessage(sui1->generateMessage());

	return 1;
}

void ResourceDeedImplementation::destroyDeed() {

	getParent()->removeObject(_this, true);

	if (isPersistent())
		destroyObjectFromDatabase(true);
}
