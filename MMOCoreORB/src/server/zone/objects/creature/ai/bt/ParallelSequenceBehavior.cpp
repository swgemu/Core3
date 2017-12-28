/*
 * ParallelSequenceBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */


#include "ParallelSequenceBehavior.h"

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

ParallelSequenceBehavior::ParallelSequenceBehavior(AiAgent* _agent, const String& className) : ParallelBehavior(_agent, className) {
}

void ParallelSequenceBehavior::finish() {
	if (numFailed > 0)
		endWithFailure();
	else
		endWithSuccess();
}


