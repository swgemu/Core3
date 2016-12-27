/*
 * SelectorBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "SelectorBehavior.h"

SelectorBehavior::SelectorBehavior(AiAgent* _agent, const String& className) : CompositeBehavior(_agent, className) {

}

void SelectorBehavior::childSucceeded() {
	endWithSuccess();
}

void SelectorBehavior::childFailed() {
	Behavior* currentChild;

	try {
		do {
			currentPos++;

			// TODO (dannuic): This if block is here because the out of bounds exception doesn't work like expected
			if (currentPos >= children.size()) {
				currentChild = NULL;
				currentPos = 0;
				endWithFailure();
				return;
			}

			currentChild = children.get(currentPos);

			if (currentChild == NULL) { // uh oh, this shouldn't happen
				currentPos = 0;
				endWithError();
				return;
			}

		} while (!currentChild->checkConditions());
	} catch (ArrayIndexOutOfBoundsException &e) { // TODO (dannuic): Why doesn't this ever happen? currentPos just decrements and no exception is thrown...
		currentChild = NULL;
		currentPos = 0;
		endWithFailure();
	}
}
