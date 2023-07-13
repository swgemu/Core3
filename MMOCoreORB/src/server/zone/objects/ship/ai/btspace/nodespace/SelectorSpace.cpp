/*
 * SelectorSpace.cpp
 */

#include "server/zone/objects/ship/ai/btspace/nodespace/SelectorSpace.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

using namespace server::zone::objects::ship::ai::btspace;
using namespace server::zone::objects::ship::ai::btspace::nodespace;

BehaviorSpace::Status SelectorSpace::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	// loop through children and return SUCCESS on first one that succeeded
	// as always, return RUNNING if any child returns RUNNING
	for (; startIdx < children.size(); ++startIdx) {
		BehaviorSpace* currentChild = children.get(startIdx);
		assert(currentChild != nullptr);

		BehaviorSpace::Status result = currentChild->doAction(agent);

		if (result == FAILURE)
			continue;

		return result;
	}

	// We made it all the way through the list without a success
	return FAILURE;
}

BehaviorSpace::Status ParallelSelectorSpace::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	// loop through children and return SUCCESS if one child succeeded,
	// but execute them all
	// as always, return RUNNING as soon as a child returns running (don't
	// finish execution if this is the case -- design decision)
	BehaviorSpace::Status finalResult = FAILURE;

	for (; startIdx < children.size(); ++startIdx) {
		BehaviorSpace* currentChild = children.get(startIdx);
		assert(currentChild != nullptr);

		BehaviorSpace::Status result = currentChild->doAction(agent);

		if (result == RUNNING)
			return RUNNING;

		if (result == SUCCESS)
			finalResult = SUCCESS;
	}

	return finalResult;
}

BehaviorSpace::Status RandomSelectorSpace::execute(ShipAiAgent* agent, unsigned int startIdx) const {
	// Same behavior as Selector, but randomize order of children. Disregard startIdx
	// as it makes no sense in this context, and handle a RUNNING result as a FAILURE.
	// btree designers should not include children to an ND parent that could return
	// running as it makes no sense.
	Vector<Reference<BehaviorSpace*>> ranChildren = shuffleChildren();

	for (int i = 0; i < ranChildren.size(); ++i) {
		BehaviorSpace* currentChild = ranChildren.get(i);
		assert(currentChild != nullptr);

		BehaviorSpace::Status result = currentChild->doAction(agent);

		if (result == FAILURE)
			continue;

		return result;
	}

	return FAILURE;
}
