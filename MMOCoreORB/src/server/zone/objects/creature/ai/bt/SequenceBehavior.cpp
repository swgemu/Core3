/*
 * Sequence.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#include "SequenceBehavior.h"

#include <stddef.h>

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/CompositeBehavior.h"
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

SequenceBehavior::SequenceBehavior(AiAgent* _agent, const String& className) : CompositeBehavior(_agent, className) {

}

void SequenceBehavior::childSucceeded() {
	if (currentPos == children.size() - 1)
		endWithSuccess();
	else {
		currentPos++;
		Behavior* currentChild = children.get(currentPos);
		if (currentChild == NULL || !currentChild->checkConditions())
			endWithFailure();
	}
}

void SequenceBehavior::childFailed() {
	endWithFailure();
}

