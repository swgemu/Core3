/*
 * Sequence.cpp
 */

#include "server/zone/objects/ship/ai/bt/node/Sequence.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

using namespace server::zone::objects::ship::ai::bt;
using namespace server::zone::objects::ship::ai::bt::node;

Behavior::Status Sequence::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	// loop through children and return FAILURE on first one that failed
	// as always, return RUNNING if any child returns RUNNING
	for (; startIdx < children.size(); ++startIdx) {
		Behavior* currentChild = children.get(startIdx);
		assert(currentChild != nullptr);

		Behavior::Status result = currentChild->doAction(agent);

		if (result == SUCCESS)
			continue;

		return result;
	}

	// We made it all the way through the list without a failure
	return SUCCESS;
}

Behavior::Status ParallelSequence::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	// loop through ALL children and return failure if any fail
	Behavior::Status finalResult = SUCCESS;
	for (; startIdx < children.size(); ++startIdx) {
		Behavior* currentChild = children.get(startIdx);
		assert(currentChild != nullptr);

		Behavior::Status result = currentChild->doAction(agent);

		if (result == RUNNING)
			return RUNNING;

		if (result == FAILURE)
			finalResult = FAILURE;
	}

	return finalResult;
}

Behavior::Status RandomSequence::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	Vector<Reference<Behavior*> > ranChildren = shuffleChildren();
	for (int i = 0; i < ranChildren.size(); ++i) {
		Behavior* currentChild = ranChildren.get(i);
		assert(currentChild != nullptr);

		Behavior::Status result = currentChild->doAction(agent);

		if (result == SUCCESS)
			continue;

		return result;
	}

	return SUCCESS;
}
