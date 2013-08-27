/*
 * Behaviour.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

enum Status {INVALID,SUCCESS,FAILURE,RUNNING,SUSPENDED};

class Behavior {

public:
	Behavior() {
		status = INVALID;
	}
	virtual ~Behavior(){}
	Status status;
	Status tick() {
		if (status == INVALID) { onInitialize(); }
		status = update();
		if (status != RUNNING) { onTerminate(status); }
		return status;
	}
	virtual Status update() = 0;
	virtual void onInitialize() {}
	virtual void onTerminate(Status s) {}
	virtual void observe(Status s){}
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
