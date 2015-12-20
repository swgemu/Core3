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
			creature->sendSystemMessage("@error_message:target_out_of_range"); //"Your target is out of range for this action."
			return GENERALERROR;
		}

		bool lootAll = arguments.toString().beginsWith("all");

		//Get the corpse's inventory.
		SceneObject* lootContainer = ai->getSlottedObject("inventory");
		if (lootContainer == NULL)
			return GENERALERROR;

		//Determine the loot rights.
		bool looterIsOwner = (lootContainer->getContainerPermissions()->getOwnerID() == creature->getObjectID());
		bool groupIsOwner = (lootContainer->getContainerPermissions()->getOwnerID() == creature->getGroupID());

		//Allow player to loot the corpse if they own it.
		if (looterIsOwner) {
			if (lootAll) {
				PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
				playerManager->lootAll(creature, ai);
			} else {
				ai->notifyObservers(ObserverEventType::LOOTCREATURE, creature, 0);
				lootContainer->openContainerTo(creature);
			}

			return SUCCESS;
		}

		//If player and their group don't own the corpse, pick up any owned items left on corpse due to full inventory, then fail.
		if (!looterIsOwner && !groupIsOwner) {
			int pickupResult = pickupOwnedItems(creature, lootContainer);
			if (pickupResult != 1) { //Player did not pickup any owned items.
				StringIdChatParameter noPermission("error_message","no_corpse_permission"); //"You do not have permission to access this corpse."
				creature->sendSystemMessage(noPermission);
				return GENERALERROR;
			}

			return SUCCESS;
		}

		//If looter's group is the owner, attempt to pick up any owned items, then process group loot rule.
		if (groupIsOwner) {
			int pickupResult = pickupOwnedItems(creature, lootContainer);
			if (pickupResult == 1) {
				creature->getZoneServer()->getPlayerManager()->rescheduleCorpseDestruction(creature, ai);
				return SUCCESS;
			} else if (pickupResult == 2) { //Player did not pickup an item, but there is one there for someone else.
				ai->notifyObservers(ObserverEventType::LOOTCREATURE, creature, 0);
				lootContainer->openContainerTo(creature);
			}

			ManagedReference<GroupObject*> group = creature->getGroup();
			if (group == NULL)
				return GENERALERROR;

			GroupLootTask* task = new GroupLootTask(group, creature, ai, lootAll);
			task->execute();
			return SUCCESS;
		}

		return GENERALERROR;

	}

	int pickupOwnedItems(CreatureObject* creature, SceneObject* lootContainer) const {
		/* Return codes:
		 * 0: No item picked up, no items available for pickup.
		 * 1: An item was picked up by the player.
		 * 2: No item picked up, but one is available for someone else to pickup.
		 */

		bool pickedUpItem = false;
		bool pickupItemAvailable = false;

		int totalItems = lootContainer->getContainerObjectsSize();
		if (totalItems < 1) return 0;

		ContainerPermissions* contPerms = lootContainer->getContainerPermissions();
		if (contPerms == NULL) return 0;

		//Check each loot item to see if the player owns it.
		for (int i = totalItems - 1; i >= 0; --i) {
			SceneObject* object = lootContainer->getContainerObject(i);
			if (object == NULL) return 0;

			ContainerPermissions* itemPerms = object->getContainerPermissions();
			if (itemPerms == NULL) return 0;

			//If player owns the loot item, transfer it to them.
			uint64 itemOwnerID = itemPerms->getOwnerID();
			if (itemOwnerID == creature->getObjectID()) {
				pickedUpItem = true;

				//Transfer the item to the player.
				SceneObject* playerInventory = creature->getSlottedObject("inventory");
				if (playerInventory == NULL) return 0;

				if (playerInventory->isContainerFullRecursive()) {
					StringIdChatParameter full("group", "you_are_full"); //"Your Inventory is full."
					creature->sendSystemMessage(full);
					return 1;
				}

				uint64 originalOwner = contPerms->getOwnerID();
				contPerms->setOwner(creature->getObjectID());

				if (creature->getZoneServer()->getObjectController()->transferObject(object, playerInventory, -1, true)) {
					itemPerms->clearDenyPermission("player", ContainerPermissions::OPEN);
					itemPerms->clearDenyPermission("player", ContainerPermissions::MOVECONTAINER);
				}

				contPerms->setOwner(originalOwner);

			} else if (itemOwnerID != 0)
				pickupItemAvailable = true;
		}

		if (pickedUpItem)
			return 1;
		if (pickupItemAvailable)
			return 2;

		return 0;
	}

};

#endif //LOOTCOMMAND_H_
