/*
 * Sequence.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#include "server/zone/objects/creature/ai/bt/node/Sequence.h"

using namespace server::zone::objects::creature::ai::bt;

Status Sequence::execute(AiAgent* agent, unsigned int startIdx) const {
	// loop through children and return FAILURE on first one that failed
	// as always, return RUNNING if any child returns RUNNING
	for (; startIdx < children.size(); ++startIdx) {
		Behavior* currentChild = children.at(startIdx);
		if (currentChild == NULL) {
			children.remove(startIdx--);
			continue;
		}

		Status result = currentChild->doAction(agent);

		if (result == SUCCESS)
			continue;

		return result;
	}
	
	// We made it all the way through the list without a failure
	return SUCCESS;
}
