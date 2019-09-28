/*
 * LootLotterySessionImplementation.cpp
 *
 *  Created on: March 18, 2015
 *      Author: Anakis
 */

#include "engine/engine.h"
#include "server/zone/objects/player/sessions/LootLotterySession.h"
#include "server/zone/objects/player/sessions/LootLotteryBallot.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/objects/group/tasks/LootLotteryTimeoutTask.h"
#include "server/zone/ZoneServer.h"

int LootLotterySessionImplementation::initializeSession() {
	//This task initiates the lottery draw if a player's client does not respond with selections in time (LD).
	Reference<LootLotteryTimeoutTask*> timeoutTask = new LootLotteryTimeoutTask(_this.get());
	corpse->addPendingTask("lottery", timeoutTask, 35000);

	//Make sure corpse doesn't despawn during lottery.
	Reference<DespawnCreatureTask*> despawnTask = corpse->getPendingTask("despawn").castTo<DespawnCreatureTask*>();
	if (despawnTask != nullptr) {
		AtomicTime despawnTime;
		Core::getTaskManager()->getNextExecutionTime(despawnTask, despawnTime);
		if (despawnTime.miliDifference() > -120000) { //Less than 2 minutes to despawn.
			despawnTask->cancel();
			despawnTask->reschedule(120000);
		}
	}

	return 0;
}

void LootLotterySessionImplementation::addPlayerSelections(CreatureObject* player, LootLotteryBallot* ballot) {
	if (isLotteryFinished())
			return;

	playerSelections.add(ballot);
	removeEligiblePlayer(player);
}

void LootLotterySessionImplementation::doLotteryDraw() {
	Locker clocker(corpse);

	//Cancel the timeout task if it's running.
	Reference<LootLotteryTimeoutTask*> task = corpse->getPendingTask("lottery").castTo<LootLotteryTimeoutTask*>();
	if (task != nullptr) {
		if (task->isScheduled())
		task->cancel();
	}

	//Get the corpse's inventory and container permissions.
	SceneObject* lootContainer = corpse.get()->getSlottedObject("inventory");
	if (lootContainer == nullptr)
		return;

	ContainerPermissions* contPerms = lootContainer->getContainerPermissionsForUpdate();

	//Check if the group that owns the corpse is still active or not.
	ManagedReference<GroupObject*> group = corpse->getZoneServer()->getObject(groupID).castTo<GroupObject*>();
	bool stillGrouped = (group != nullptr) && (group->getGroupSize() > 1); //GroupObject can still exist when disbanded, so check group size too.

	//Loop through each loot item, pick a winner and attempt to transfer it to them.
	int totalItems = lootContainer->getContainerObjectsSize();
	for (int i = totalItems - 1; i >= 0; --i) {
		//Get the loot item.
		SceneObject* object = lootContainer->getContainerObject(i);
			if (object == nullptr)
				continue;
		uint64 objectID = object->getObjectID();

		//Determine which players want the item.
		Vector<CreatureObject*> candidates;
		for (int j = 0; j < playerSelections.size(); ++j) {
			LootLotteryBallot* ballot = playerSelections.get(j);
			if (ballot->hasSelection(objectID)) {
				CreatureObject* player = ballot->getPlayer();
				if (player == nullptr)
					continue;
				candidates.add(ballot->getPlayer());
			}
		}

		//If nobody wanted the item, leave it on corpse for anyone to pick up.
		if (candidates.size() < 1) {
			if (stillGrouped) {
				StringIdChatParameter noTakers("group", "no_one_wanted"); //"No one wanted the %TO."
				noTakers.setTO(objectID);
				group->sendSystemMessage(noTakers);
			}
			ContainerPermissions* itemPerms = object->getContainerPermissionsForUpdate();
			if (itemPerms == nullptr)
				continue;

			itemPerms->clearDenyPermission("player", ContainerPermissions::MOVECONTAINER);
			continue;
		}

		//Pick a winner for the item.
		ManagedReference<CreatureObject*> winner = candidates.get(System::random(candidates.size() - 1));
		if (winner == nullptr)
			continue;
		uint64 winnerID = winner->getObjectID();

		Locker wclocker(winner, corpse);

		//Temporarily set the winner as the loot container's owner to allow the item transfer to work if the group is disbanded.
		contPerms->setOwner(winner->getObjectID());

		//Transfer the item to the winner.
		GroupManager::instance()->transferLoot(group, winner, object, stillGrouped);
	}

	//Reset the owner of the loot container.
	contPerms->setOwner(groupID);
	setLotteryFinished(true);

	//Reschedule corpse destruction.
	if (stillGrouped) {
		ManagedReference<CreatureObject*> leader = group->getLeader();

		if (leader != nullptr) {
			Locker lclocker(leader, corpse);
			leader->getZoneServer()->getPlayerManager()->rescheduleCorpseDestruction(leader, corpse);
			return;
		}
	}
}
