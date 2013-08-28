/*
 * SequenceBehavior
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef SEQUENCEBEHAVIOR_H_
#define SEQUENCEBEHAVIOR_H_

#include "CompositeBehavior.h"
#include "BehaviorTree.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class SequenceBehavior: public CompositeBehavior {
public:
	SequenceBehavior(BehaviorTree* sequenceTree);
	virtual ~SequenceBehavior();
protected:
	BehaviorTree* tree;
	virtual void onInitialize();
	virtual Status update() { return RUNNING; }
	virtual void observe(Status s);
	virtual bool canObserve() { return true; }
	int position;
	int end;
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;

#endif /* SEQUENCEBEHAVIOR_H_ */
