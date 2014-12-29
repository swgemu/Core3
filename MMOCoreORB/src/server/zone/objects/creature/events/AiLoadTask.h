/*
 * AiLoadTask.h
 *
 *  Created on: Jul 14, 2014
 *      Author: swgemu
 */

#ifndef AILOADTASK_H_
#define AILOADTASK_H_

#include "server/zone/managers/creature/AiMap.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/CreatureFlag.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class AiLoadTask : public Task {
	ManagedWeakReference<AiAgent*> creature;
	String aiTemp;

public:
	AiLoadTask(AiAgent* pl) : Task(1000) {
		creature = pl;
		aiTemp = "";
	}

	AiLoadTask(AiAgent* pl, String t) : Task(1000) {
		creature = pl;
		aiTemp = t;
	}

	virtual ~AiLoadTask() {
	}

	void run() {
		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		strongRef->clearBehaviorList();

		if (aiTemp.isEmpty()) {
			if (strongRef->getParentID() != 0 || ((CloseObjectsVector*) strongRef->getCloseObjects()) == NULL)
				strongRef->setCreatureBitmask(strongRef->getCreatureBitmask() | CreatureFlag::STATIC);
			strongRef->setupBehaviorTree();
		} else
			strongRef->setupBehaviorTree(AiMap::instance()->getTemplate(aiTemp));

		strongRef->activateMovementEvent();
	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;



#endif /* AILOADTASK_H_ */
