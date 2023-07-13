/*
 * SequenceSpace.cpp
 */

#include "SequenceSpace.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

using namespace server::zone::objects::ship::ai::btspace;
using namespace server::zone::objects::ship::ai::btspace::nodespace;

BehaviorSpace::Status SequenceSpace::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	// loop through children and return FAILURE on first one that failed
	// as always, return RUNNING if any child returns RUNNING
	for (; startIdx < children.size(); ++startIdx) {
		BehaviorSpace* currentChild = children.get(startIdx);
		assert(currentChild != nullptr);

		BehaviorSpace::Status result = currentChild->doAction(agent);

		if (result == SUCCESS)
			continue;

		return result;
	}

	// We made it all the way through the list without a failure
	return SUCCESS;
}

BehaviorSpace::Status ParallelSequenceSpace::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	// loop through ALL children and return failure if any fail
	BehaviorSpace::Status finalResult = SUCCESS;

	for (; startIdx < children.size(); ++startIdx) {
		BehaviorSpace* currentChild = children.get(startIdx);
		assert(currentChild != nullptr);

		BehaviorSpace::Status result = currentChild->doAction(agent);

		if (result == RUNNING)
			return RUNNING;

		if (result == FAILURE)
			finalResult = FAILURE;
	}

	return finalResult;
}

BehaviorSpace::Status RandomSequenceSpace::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	Vector<Reference<BehaviorSpace*>> ranChildren = shuffleChildren();

	for (int i = 0; i < ranChildren.size(); ++i) {
		BehaviorSpace* currentChild = ranChildren.get(i);

		assert(currentChild != nullptr);

		BehaviorSpace::Status result = currentChild->doAction(agent);

		if (result == SUCCESS)
			continue;

		return result;
	}

	return SUCCESS;
}
