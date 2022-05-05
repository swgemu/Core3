/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JEDIMINDTRICKREMOVALTASK_H_
#define JEDIMINDTRICKREMOVALTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/tasks/StorePetTask.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class JediMindTrickRemovalTask : public Task {
	ManagedWeakReference<CreatureObject*> pet;
	ManagedWeakReference<CreatureObject*> owner;

public:
	JediMindTrickRemovalTask(CreatureObject* pet, CreatureObject* owner) : Task() {
		this->pet = pet;
		this->owner = owner;
	}

	void run() {
		CreatureObject* petCreo = pet.get();
		CreatureObject* petOwner =  owner.get();

		if (petCreo == nullptr || petOwner == nullptr)
			return;

		AiAgent* petAgent = petCreo->asAiAgent();

		if (petAgent == nullptr)
			return;

		Locker locker(petAgent);

		ManagedReference<PetControlDevice*> controlDevice = petAgent->getControlDevice().get().castTo<PetControlDevice*>();

		if (controlDevice != nullptr && controlDevice->getPetType() == PetManager::FACTIONPET) {
			petAgent->addCreatureFlag(CreatureFlag::FACTION_PET);
		} else {
			petAgent->addCreatureFlag(CreatureFlag::PET);
		}

		petAgent->setMindTricked(false);
		petAgent->setCreatureLink(petOwner);

		uint32 ownerPvpStatusBitmask = petOwner->getPvpStatusBitmask();

		if (ownerPvpStatusBitmask & CreatureFlag::PLAYER)
			ownerPvpStatusBitmask &= ~CreatureFlag::PLAYER;

		petAgent->setPvpStatusBitmask(ownerPvpStatusBitmask);

		if (petAgent->isDead()) {
			Reference<StorePetTask*> task = new StorePetTask(petOwner, petAgent);
			task->execute();
		} else {
			petAgent->setFollowObject(petOwner);
			petAgent->storeFollowObject();

			petAgent->setHomeLocation(petOwner->getPositionX(), petOwner->getPositionZ(), petOwner->getPositionY(), petOwner->getParent().get().castTo<CellObject*>());
			petAgent->setNextStepPosition(petOwner->getPositionX(), petOwner->getPositionZ(), petOwner->getPositionY(), petOwner->getParent().get().castTo<CellObject*>());
			petAgent->clearPatrolPoints();

			petAgent->setMovementState(AiAgent::FOLLOWING);
		}

		petAgent->setAITemplate();
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*JediMindTrickRemovalTask_H_*/