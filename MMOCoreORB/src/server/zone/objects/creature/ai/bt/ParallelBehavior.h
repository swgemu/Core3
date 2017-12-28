/*
 * ParallelBehavior.h
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#ifndef PARALLELBEHAVIOR_H_
#define PARALLELBEHAVIOR_H_

#include <algorithm>

#include "CompositeBehavior.h"
#include "system/lang/String.h"
#include "system/platform.h"
#include "system/util/Vector.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
class AiAgent;
}  // namespace ai
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class Behavior;

class ParallelBehavior : public CompositeBehavior {
protected:
	Vector<Behavior*> unfinishedChildren;
	uint16 numFailed;
	uint16 numSucceeded;

public:
	ParallelBehavior(AiAgent* _agent, const String& className);
	void start();
	void end();
	void doAction(bool directlyExecuted = false);
	void childSucceeded();
	void childFailed();

	virtual void finish() = 0;
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;





#endif /* PARALLELBEHAVIOR_H_ */
