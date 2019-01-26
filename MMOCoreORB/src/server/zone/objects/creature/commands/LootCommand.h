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
	enum {
		NOPICKUPITEMS = 0,
		ITEMFOROTHER = 1,
		PICKEDANDREMAINING = 2,
		PICKEDANDEMPTY = 3
	};

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

		if (!checkDistance(ai, creature, 16)) {
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
				//Check if the corpse's inventory contains any items.
				if (lootContainer->getContainerObjectsSize() < 1) {
  					creature->sendSystemMessage("@error_message:corpse_empty"); //"You find nothing else of value on the selected corpse."
  					creature->getZoneServer()->getPlayerManager()->rescheduleCorpseDestruction(creature, ai);
  				} else {
					ai->notifyObservers(ObserverEventType::LOOTCREATURE, creature, 0);
					lootContainer->openContainerTo(creature);
				}
			}

			return SUCCESS;
		}

		//If player and their group don't own the corpse, pick up any owned items left on corpse due to full inventory, then fail.
		if (!groupIsOwner) {
			int pickupResult = pickupOwnedItems(creature, lootContainer);
			if (pickupResult < 2) { //Player didn't pickup an item nor is one available for them.
				StringIdChatParameter noPermission("error_message","no_corpse_permission"); //"You do not have permission to access this corpse."
				creature->sendSystemMessage(noPermission);
				return GENERALERROR;
			} else if (pickupResult == PICKEDANDEMPTY) {
				creature->getZoneServer()->getPlayerManager()->rescheduleCorpseDestruction(creature, ai);
				return SUCCESS;
			}

			return SUCCESS;
		}

		//If looter's group is the owner, attempt to pick up any owned items, then process group loot rule.
		int pickupResult = pickupOwnedItems(creature, lootContainer);
		switch (pickupResult) {
		case NOPICKUPITEMS: //No items available for anyone to pickup.
			break;
		case ITEMFOROTHER: //No items available for looter to pickup, but one is available for someone else.
			ai->notifyObservers(ObserverEventType::LOOTCREATURE, creature, 0);
			lootContainer->openContainerTo(creature);
			return SUCCESS;
		case PICKEDANDREMAINING: //An item was available for the looter, there are items remaining.
			return SUCCESS;
		case PICKEDANDEMPTY: //An item was available for the looter, there are NO items remaining.
			creature->getZoneServer()->getPlayerManager()->rescheduleCorpseDestruction(creature, ai);
			return SUCCESS;
		default:
			break;
		}

		ManagedReference<GroupObject*> group = creature->getGroup();
		if (group == NULL)
			return GENERALERROR;

		GroupLootTask* task = new GroupLootTask(group, creature, ai, lootAll);
		task->execute();
		return SUCCESS;

	}

	int pickupOwnedItems(CreatureObject* creature, SceneObject* lootContainer) const {
		/* Return codes:
		 * NOPICKUPITEMS: No items available for anyone to pickup.
		 * ITEMFOROTHER: No items available for looter to pickup, but one is available for someone else.
		 * PICKEDANDREMAINING: An item was available for the looter, there are items remaining.
		 * PICKEDANDEMPTY: An item was available for the looter, there are NO items remaining.
		 */

		bool attemptedPickup = false;
		bool pickupAvailableOther = false;

		int totalItems = lootContainer->getContainerObjectsSize();
		if (totalItems < 1) return NOPICKUPITEMS;

		ContainerPermissions* contPerms = lootContainer->getContainerPermissions();
		if (contPerms == NULL) return NOPICKUPITEMS;

		SceneObject* playerInventory = creature->getSlottedObject("inventory");
		if (playerInventory == NULL) return NOPICKUPITEMS;

		//Check each loot item to see if the player owns it.
		for (int i = totalItems - 1; i >= 0; --i) {
			SceneObject* object = lootContainer->getContainerObject(i);
			if (object == NULL) continue;

			ContainerPermissions* itemPerms = object->getContainerPermissions();
			if (itemPerms == NULL) continue;

			//Check if player owns the loot item.
			uint64 itemOwnerID = itemPerms->getOwnerID();
			if (itemOwnerID == creature->getObjectID()) {

				//Attempt to transfer the item to the player.
				attemptedPickup = true;
				if (playerInventory->isContainerFullRecursive()) {
					StringIdChatParameter full("group", "you_are_full"); //"Your Inventory is full."
					creature->sendSystemMessage(full);
					return PICKEDANDREMAINING;
				}

				uint64 originalOwner = contPerms->getOwnerID();
				contPerms->setOwner(creature->getObjectID());

				if (creature->getZoneServer()->getObjectController()->transferObject(object, playerInventory, -1, true)) {
					itemPerms->clearDenyPermission("player", ContainerPermissions::OPEN);
					itemPerms->clearDenyPermission("player", ContainerPermissions::MOVECONTAINER);
				}

				contPerms->setOwner(originalOwner);

			} else if (itemOwnerID != 0)
				pickupAvailableOther = true;
		}

		//Determine which result code to return.
		if (attemptedPickup) {
			if (lootContainer->getContainerObjectsSize() > 0)
				return PICKEDANDREMAINING;
			else
				return PICKEDANDEMPTY;
		}

		if (pickupAvailableOther)
			return ITEMFOROTHER;

		return NOPICKUPITEMS;
	}

};

#endif //LOOTCOMMAND_H_
