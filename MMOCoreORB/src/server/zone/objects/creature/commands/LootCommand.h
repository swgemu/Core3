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

		if (!ai->isDead())
			return GENERALERROR;

		if (ai->getDistanceTo(creature) > 16) {
			creature->sendSystemMessage("@error_message:target_out_of_range"); // Your target is out of range for this action.
			return GENERALERROR;
		}

		//Get the corpse's inventory.
		SceneObject* creatureInventory = ai->getSlottedObject("inventory");
		if (creatureInventory == NULL)
			return GENERALERROR;

		//Determine the loot rights.
		bool looterIsOwner = (creatureInventory->getContainerPermissions()->getOwnerID() == creature->getObjectID());
		bool groupIsOwner = (creatureInventory->getContainerPermissions()->getOwnerID() == creature->getGroupID());

		if (!looterIsOwner && !groupIsOwner) {
			StringIdChatParameter noPermission("error_message","no_corpse_permission"); //You do not have permission to access this corpse.
			creature->sendSystemMessage(noPermission);
			return GENERALERROR;
		}

		bool lootAll = arguments.toString().beginsWith("all");

		//Handle group looting rules.
		if (groupIsOwner) {
			ManagedReference<GroupObject*> group = creature->getGroup();
			if (group == NULL)
				return GENERALERROR;

			GroupLootTask* task = new GroupLootTask(group, creature, ai, lootAll);
			task->execute();
			return SUCCESS;
		}

		//Allow player to loot the corpse.
		if (lootAll) {
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->lootAll(creature, ai);
		} else {
			ai->notifyObservers(ObserverEventType::LOOTCREATURE, creature, 0);
			creatureInventory->openContainerTo(creature);
		}

		return SUCCESS;
	}

};

#endif //LOOTCOMMAND_H_
