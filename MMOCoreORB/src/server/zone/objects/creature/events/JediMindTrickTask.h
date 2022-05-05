/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SPICEDOWNERANIMATIONTASK_H_
#define SPICEDOWNERANIMATIONTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class JediMindTrickTask : public Task {
	ManagedWeakReference<CreatureObject*> pet;

public:
	JediMindTrickTask(CreatureObject* pet) : Task() {
		this->pet = pet;
	}

	void run() {
		CreatureObject* petCreo = pet.get();

		if (petCreo == nullptr)
			return;

		AiAgent* petAgent = petCreo->asAiAgent();

		if (petAgent == nullptr)
			return;

		CreatureObject* owner = petAgent->getLinkedCreature().get();

		if (owner == nullptr)
			return;

		printf("Jedi mind task called \n");

		Locker locker(petAgent);

		petAgent->setCreatureBitmask(petAgent->getCreatureBitmask() & CreatureFlag::PET);
		petAgent->setFaction(owner->getFaction());

		petAgent->setAITemplate();
		petAgent->broadcastPvpStatusBitmask();

		petAgent->setFollowObject(owner);
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*JediMindTrickTask_H_*/