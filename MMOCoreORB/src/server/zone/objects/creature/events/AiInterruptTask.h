/*
 * AiInterruptTask.h
 *
 *  Created on: Jul 14, 2014
 *      Author: swgemu
 */

#ifndef AIINTERRUPTTASK_H_
#define AIINTERRUPTTASK_H_

#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/scene/SceneObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class AiInterruptTask : public Task {
	ManagedWeakReference<AiAgent*> creature;
	ManagedWeakReference<SceneObject*> source;
	int64 msg;

public:
	AiInterruptTask(AiAgent* pl, SceneObject* t, int64 m) : Task(1000) {
		creature = pl;
		source = t;
		msg = m;
	}

	virtual ~AiInterruptTask() {
	}

	void run() {
		ManagedReference<AiAgent*> strongRef = creature.get();
		ManagedReference<SceneObject*> sourceRef = source.get();

		if (strongRef == NULL || sourceRef == NULL)
			return;

		Locker locker(strongRef);

		strongRef->interrupt(sourceRef, msg);
	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;



#endif /* AIINTERRUPTTASK_H_ */
