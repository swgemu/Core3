/*
 * Behaviour.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/AiAgent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class Behavior {

public:
	Behavior() {
	}
	static const int INVALID = 0;
	static const int SUCCESS = 1;
	static const int FAILURE = 2;
	static const int RUNNING = 3;
	static const int SUSPENDED = 4;
	virtual ~Behavior(){}
	int tick(AiAgent* actor) {
		if (actor->getBehaviorStatus(this) == INVALID || actor->getBehaviorStatus(this) == -1) { onInitialize(actor); }
		int status = update(actor);
		if (status != RUNNING) { onTerminate(actor,status); }
		return status;
	}
	virtual int update(AiAgent* actor) = 0;
	virtual void onInitialize(AiAgent* actor) { actor->setBehaviorStatus(this,INVALID);}
	virtual void onTerminate(AiAgent* actor, int s) {}
	virtual void observe(AiAgent* actor){}
	virtual bool canObserve() { return false; }
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;
#endif /* BEHAVIOR_H_ */
