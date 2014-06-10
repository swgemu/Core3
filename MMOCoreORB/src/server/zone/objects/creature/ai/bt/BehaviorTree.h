/*
 * BehaviorTree.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIORTREE_H_
#define BEHAVIORTREE_H_

#include "engine/engine.h"
#include "Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {

class AiAgent;

namespace ai {
namespace bt {

class BehaviorTree {
protected:
	SortedVector<Reference<Behavior*> > behaviors;

public:
	BehaviorTree();
	virtual ~BehaviorTree();

	void addBehavior(Behavior* b) {
		behaviors.add(b);
	}

	void clear() {
		behaviors.removeAll();
	}

	/*
	void start(Behavior* behavior,AiAgent* actor);
	void stop(Behavior* behavior, AiAgent* actor);
	void tick(AiAgent* actor);
	bool step(AiAgent* actor);*/
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;

#endif /* BEHAVIORTREE_H_ */
