/*
 * NonDeterministicBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "NonDeterministicBehavior.h"

#include "server/zone/objects/creature/ai/bt/CompositeBehavior.h"
#include "system/lang/System.h"
#include "system/util/Vector.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
class AiAgent;
namespace bt {
class Behavior;
}  // namespace bt
}  // namespace ai
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server

NonDeterministicBehavior::NonDeterministicBehavior(AiAgent* _agent, const String& className) : CompositeBehavior(_agent, className) {

}

void NonDeterministicBehavior::start() {
	// this is literally just a shuffle algorithm
	Behavior* temp;
	int index;
	for (int i = 0; i < children.size(); i++) {
		index = (int) System::random(children.size() - 1 - i) + i;
		temp = children.set(i, children.get(index));
		children.set(index, temp);
	}

	CompositeBehavior::start();
}


