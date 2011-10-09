/*
 * ResourceDeedSuiCallback.h
 *
 *  Created on: Aug 17, 2011
 *      Author: crush
 */

#ifndef RESOURCEDEEDSUICALLBACK_H_
#define RESOURCEDEEDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class ResourceDeedSuiCallback : public SuiCallback {
	String nodeName;

public:
	ResourceDeedSuiCallback(ZoneServer* serv, const String& name) : SuiCallback(serv) {
		nodeName = name;
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( sui);

		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if (obj == NULL || !obj->isDeedObject())
			return;

		Deed* deed = cast<Deed*>( obj.get());

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == NULL || !deed->isASubChildOf(inventory)) //No longer in inventory.
			return;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return;

		bool backPressed = false;
		int index = -1;

		try {
			backPressed = Bool::valueOf(args->get(0).toString());
			index = Integer::valueOf(args->get(1).toString());
		} catch (Exception& e) {
			creature->error("Invalid parameters passed to ResourceDeedSuiCallback.");
			return;
		}

		ManagedReference<ResourceManager*> resourceManager = creature->getZoneServer()->getResourceManager();

		ManagedReference<ResourceSpawn*> spawn = resourceManager->getResourceSpawn(nodeName);

		//They chose the resource, eat the deed and give them what they want...fuck it.
		if (spawn != NULL) {
			resourceManager->givePlayerResource(creature, nodeName, ResourceManager::RESOURCE_DEED_QUANTITY);
			deed->broadcastDestroy(deed, false);
			inventory->removeObject(deed, true);
			return;
		}

		if (!backPressed && index >= 0 && index < listBox->getMenuSize())
			nodeName = listBox->getMenuItemName(index);

		listBox->removeAllMenuItems();

		spawn = resourceManager->getResourceSpawn(nodeName); //Check again, this means they are looking at stats.

		if (backPressed) {
			nodeName = resourceManager->addParentNodeToListBox(listBox, nodeName);
		} else {
			if (spawn != NULL) {
				spawn->addStatsToDeedListBox(listBox);
			} else {
				resourceManager->addNodeToListBox(listBox, nodeName);
			}
		}

		ghost->addSuiBox(listBox);
		creature->sendMessage(listBox->generateMessage());
	}
};

#endif /* RESOURCEDEEDSUICALLBACK_H_ */
