/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOOTCOMMAND_H_
#define LOOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/group/GroupLootTask.h"

class LootCommand : public QueueCommand {
public:

	LootCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<AiAgent*> ai = server->getZoneServer()->getObject(target).castTo<AiAgent*>();

		if (ai == NULL)
			return INVALIDTARGET;

		Locker locker(ai, creature);

		if (!ai->isDead() || creature->isDead())
			return GENERALERROR;

		if (ai->getDistanceTo(creature) > 16) {
			creature->sendSystemMessage("@error_message:target_out_of_range"); // Your target is out of range for this action.
			return GENERALERROR;
		}

		//Get the corpse's inventory.
		SceneObject* lootContainer = ai->getSlottedObject("inventory");
		if (lootContainer == NULL)
			return GENERALERROR;

		//Determine the loot rights.
		bool looterIsOwner = (lootContainer->getContainerPermissions()->getOwnerID() == creature->getObjectID());
		bool groupIsOwner = (lootContainer->getContainerPermissions()->getOwnerID() == creature->getGroupID());

		if (!looterIsOwner && !groupIsOwner) {
			//Handle picking up items when full inventory and group is disbanded.
			if (!pickupOwnedItems(creature, lootContainer)) {
				StringIdChatParameter noPermission("error_message","no_corpse_permission"); //You do not have permission to access this corpse.
				creature->sendSystemMessage(noPermission);
				return GENERALERROR;
			}

			return SUCCESS;
		}

		//Handle picking up items when full inventory in RANDOM loot mode.
		ManagedReference<GroupObject*> group = creature->getGroup();
		int lootRule = -1;
		if (group != NULL)
			lootRule = group->getLootRule();

		if (lootRule == GroupManager::RANDOM) {
			if (pickupOwnedItems(creature, lootContainer)) {
				creature->getZoneServer()->getPlayerManager()->rescheduleCorpseDestruction(creature, ai);
				return SUCCESS;
			}
		}

		bool lootAll = arguments.toString().beginsWith("all");

		//Handle group looting rules if looter is in a group.
		if (groupIsOwner) {
			if (group == NULL)
				return GENERALERROR;

			GroupLootTask* task = new GroupLootTask(group, creature, ai, lootAll);
			task->execute();
			return SUCCESS;
		}

		//Allow player to loot the corpse if looter is not in a group.
		if (lootAll) {
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->lootAll(creature, ai);
		} else {
			ai->notifyObservers(ObserverEventType::LOOTCREATURE, creature, 0);
			lootContainer->openContainerTo(creature);
		}

		return SUCCESS;
	}

	bool pickupOwnedItems(CreatureObject* creature, SceneObject* lootContainer) const {
		bool pickedUpItem = false;

		int totalItems = lootContainer->getContainerObjectsSize();
		if (totalItems < 1) return false;

		ContainerPermissions* contPerms = lootContainer->getContainerPermissions();
		if (contPerms == NULL) return false;

		//Check each loot item to see if the player owns it.
		for (int i = totalItems - 1; i >= 0; --i) {
			SceneObject* object = lootContainer->getContainerObject(i);
			if (object == NULL) continue;

			ContainerPermissions* itemPerms = object->getContainerPermissions();
			if (itemPerms == NULL) continue;

			//If player owns the loot item, transfer it to them.
			if (itemPerms->getOwnerID() == creature->getObjectID()) {
				//Transfer the item to the player.
				SceneObject* playerInventory = creature->getSlottedObject("inventory");
				if (playerInventory == NULL) return true;

				if (playerInventory->isContainerFullRecursive()) {
					StringIdChatParameter full("group", "you_are_full"); //"Your Inventory is full."
					creature->sendSystemMessage(full);
					return true;
				}

				uint64 originalOwner = contPerms->getOwnerID();
				contPerms->setOwner(creature->getObjectID());

				creature->getZoneServer()->getObjectController()->transferObject(object, playerInventory, -1, true);

				contPerms->setOwner(originalOwner);
				pickedUpItem = true;
			}
		}

		return pickedUpItem;
	}

};

#endif //LOOTCOMMAND_H_
