/*
 * GroupLootTask.h
 *
 *  Created on: March 8, 2015
 *      Author: Anakis
 */

#ifndef GROUPLOOTTASK_H_
#define GROUPLOOTTASK_H_
#include "engine/engine.h"
#include "server/zone/objects/group/GroupObject.h"

class GroupLootTask : public Task {
	ManagedReference<GroupObject*> group;
	ManagedReference<CreatureObject*> player;
	ManagedReference<AiAgent*> corpse;

	bool lootAll;

public:
	GroupLootTask(GroupObject* gr, CreatureObject* pl, AiAgent* ai, bool all) {
		group = gr;
		player = pl;
		corpse = ai;
		lootAll = all;

	}

	void run() {
		if (group == NULL || player == NULL || corpse == NULL)
			return;

		Locker plocker(player);
		Locker glocker(group, player);

		switch (group->getLootRule()) {
		case GroupManager::FREEFORALL:
			//We allow the ninja to loot.
			break;
		case GroupManager::MASTERLOOTER:
			if (!group->checkMasterLooter(player)) {
				StringIdChatParameter masterOnly("group","master_only"); //"Only the Master Looter is allowed to loot!"
				masterOnly.setTO(group->getMasterLooterID());
				player->sendSystemMessage(masterOnly);
				return;
			}
			break;
		case GroupManager::LOTTERY:
			//TODO: Send player and corpse to Lottery rule handler.
			break;
		case GroupManager::RANDOM:
			//TODO: Send player and corpse to Random rule handler.
			break;
		default:
			return;
		}

		glocker.release();

		Locker clocker(corpse, player);

		//Get the corpse's inventory.
		SceneObject* creatureInventory = corpse->getSlottedObject("inventory");
		if (creatureInventory == NULL)
			return;

		//Allow player to loot the corpse.
		if (lootAll) {
			PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
			playerManager->lootAll(player, corpse);
		} else {
			corpse->notifyObservers(ObserverEventType::LOOTCREATURE, player, 0);
			creatureInventory->openContainerTo(player);
		}

	}
};


#endif /* GROUPLOOTTASK_H_ */
