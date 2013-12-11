/*
 * StorePetTask.h
 *
 *  Created on: Dec 11, 2013
 *      Author: TheAnswer
 */

#include "engine/engine.h"

class StorePetTask : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<CreatureObject*> pet;
public:
	StorePetTask(CreatureObject* player, CreatureObject* pet) {
		this->player = player;
		this->pet = pet;
	}

	void run() {
		Locker locker(player);
		Locker clocker(pet, player);

		if (pet->containsPendingTask("droid_power"))
			pet->removePendingTask( "droid_power" );

		pet->setPosture(CreaturePosture::UPRIGHT, false);
		pet->setTargetObject(NULL);
		pet->setFollowObject(NULL);
		pet->destroyObjectFromWorld(true);

		pet->setCreatureLink(NULL);


		CreatureTemplate* creoTemp = pet->getCreatureTemplate();

		if (creoTemp != NULL) {
			pet->setFaction(creoTemp->getFaction().hashCode());
			pet->setPvpStatusBitmask(creoTemp->getPvpBitmask(), false);
		} else {
			pet->setFaction(0);
			pet->setPvpStatusBitmask(0, false);
		}

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		ghost->removeFromActivePets(pet);

		ManagedReference<GroupObject*> group = pet->getGroup();

		locker.release();

		if (group != NULL)
			GroupManager::instance()->leaveGroup(group, pet);
	}
};


