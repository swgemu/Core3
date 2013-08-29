/*
 * Behaviour.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "engine/engine.h"
#include "../AiActor.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

enum Status {INVALID=0,SUCCESS=1,FAILURE=2,RUNNING=3,SUSPENDED=4};

class Behavior {

public:
	Behavior() {
	}
	virtual ~Behavior(){}
	Status tick(AiActor* actor) {
		if (actor->getBehaviorStatus(this) == INVALID || actor->getBehaviorStatus(this) == -1) { onInitialize(actor); }
		Status status = update(actor);
		if (status != RUNNING) { onTerminate(actor,status); }
		return status;
	}
	virtual Status update(AiActor* actor) = 0;
	virtual void onInitialize(AiActor* actor) { actor->setBehaviorStatus(this,INVALID);}
	virtual void onTerminate(AiActor* actor, Status s) {}
	virtual void observe(AiActor* actor){}
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
