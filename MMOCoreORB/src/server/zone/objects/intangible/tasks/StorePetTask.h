/*
 * StorePetTask.h
 *
 *  Created on: Dec 11, 2013
 *      Author: TheAnswer
 */

#include "engine/engine.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/managers/creature/PetManager.h"

class StorePetTask : public Task {
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<AiAgent*> pt;
public:
	StorePetTask(CreatureObject* player, AiAgent* pet) {
		this->play = player;
		this->pt = pet;
	}

	void run() {
		ManagedReference<CreatureObject*> player = play.get();
		ManagedReference<AiAgent*> pet = pt.get();

		if (player == NULL || pet == NULL)
			return;

		Locker locker(player);
		Locker clocker(pet, player);

		if (pet->containsPendingTask("droid_power"))
			pet->removePendingTask( "droid_power" );
          
		if (pet->containsPendingTask("droid_skill_mod"))
			pet->removePendingTask( "droid_skill_mod" );

		if (pet->containsPendingTask("store_pet"))
			pet->removePendingTask( "store_pet" );

		if (pet->getHAM(CreatureAttribute::HEALTH) < 1)
			pet->setHAM(CreatureAttribute::HEALTH, 1);
		if (pet->getHAM(CreatureAttribute::ACTION) < 1)
			pet->setHAM(CreatureAttribute::ACTION, 1);
		if (pet->getHAM(CreatureAttribute::MIND) < 1)
			pet->setHAM(CreatureAttribute::MIND, 1);

		pet->setPosture(CreaturePosture::UPRIGHT, true);
		pet->clearCombatState(true);
		pet->setOblivious();
		pet->storeFollowObject();
		if (pet->isDroidObject()) {
			DroidObject* droid = cast<DroidObject*>(pet.get());
			if( droid != NULL ) {
				droid->onStore();
				droid->unloadSkillMods(player);
			}
		}

		pet->destroyObjectFromWorld(true);
		pet->setCreatureLink(NULL);

		ManagedReference<PetControlDevice*> controlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();
		if( controlDevice != NULL ) {
			Locker deviceLocker(controlDevice);
			controlDevice->updateStatus(0);
			controlDevice->setLastCommandTarget(NULL);
			controlDevice->setLastCommand(PetManager::FOLLOW);
		}


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


