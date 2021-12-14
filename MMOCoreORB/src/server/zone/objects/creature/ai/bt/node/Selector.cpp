/*
 * Selector.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "server/zone/objects/creature/ai/bt/node/Selector.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

using namespace server::zone::objects::creature::ai::bt;
using namespace server::zone::objects::creature::ai::bt::node;

Behavior::Status Selector::execute(AiAgent* agent, unsigned int startIdx) const {
	// loop through children and return SUCCESS on first one that succeeded
	// as always, return RUNNING if any child returns RUNNING
	for (; startIdx < children.size(); ++startIdx) {
		Behavior* currentChild = children.get(startIdx);
		assert(currentChild != nullptr);

		Behavior::Status result = currentChild->doAction(agent);

		if (result == FAILURE)
			continue;

		return result;
	}

	// We made it all the way through the list without a success
	return FAILURE;
}

Behavior::Status ParallelSelector::execute(AiAgent* agent, unsigned int startIdx) const {
	// loop through children and return SUCCESS if one child succeeded,
	// but execute them all
	// as always, return RUNNING as soon as a child returns running (don't
	// finish execution if this is the case -- design decision)
	Behavior::Status finalResult = FAILURE;
	for (; startIdx < children.size(); ++startIdx) {
		Behavior* currentChild = children.get(startIdx);
		assert(currentChild != nullptr);

		Behavior::Status result = currentChild->doAction(agent);

		if (result == RUNNING)
			return RUNNING;

		if (result == SUCCESS)
			finalResult = SUCCESS;
	}

	return finalResult;
}

Behavior::Status RandomSelector::execute(AiAgent* agent, unsigned int startIdx) const {
	// Same behavior as Selector, but randomize order of children. Disregard startIdx
	// as it makes no sense in this context, and handle a RUNNING result as a FAILURE.
	// btree designers should not include children to an ND parent that could return
	// running as it makes no sense.
	Vector<Reference<Behavior*> > ranChildren = shuffleChildren();
	for (int i = 0; i < ranChildren.size(); ++i) {
		Behavior* currentChild = ranChildren.get(i);
		assert(currentChild != nullptr);

		Behavior::Status result = currentChild->doAction(agent);

		if (result == FAILURE)
			continue;

		return result;
	}

	return FAILURE;
}
