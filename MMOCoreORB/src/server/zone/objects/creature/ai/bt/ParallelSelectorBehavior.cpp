/*
 * ParallelSelectorBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "ParallelSelectorBehavior.h"

#include "server/zone/objects/creature/ai/bt/ParallelBehavior.h"

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

ParallelSelectorBehavior::ParallelSelectorBehavior(AiAgent* _agent, const String& className) : ParallelBehavior(_agent, className) {
}

void ParallelSelectorBehavior::finish() {
	if (numSucceeded > 0)
		endWithSuccess();
	else
		endWithFailure();
}


