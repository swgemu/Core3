/*
 * BehaviorTree.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIORTREE_H_
#define BEHAVIORTREE_H_

#include "Behavior.h"
#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
class BehaviorTree {
public:
	BehaviorTree();
	virtual ~BehaviorTree();
	void start(Behavior* behavior);
	void stop(Behavior* behavior, Status result);
	void tick();
	bool step();
protected:
	ArrayQueue<Behavior*> blist;
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;

#endif /* BEHAVIORTREE_H_ */
