/*
 * Sequence.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#include "SequenceBehavior.h"

SequenceBehavior::SequenceBehavior(AiAgent* _agent, String className) : CompositeBehavior(_agent, className) {

}

void SequenceBehavior::childSucceeded() {
	if (currentPos == children.size() - 1)
		endWithSuccess();
	else {
		currentPos++;
		Reference<Behavior*> currentChild = children.get(currentPos);
		if (currentChild == NULL || !currentChild->checkConditions())
			endWithFailure();
	}
}

void SequenceBehavior::childFailed() {
	endWithFailure();
}

