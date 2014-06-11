/*
 * SelectorBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "SelectorBehavior.h"

SelectorBehavior::SelectorBehavior(AiAgent* _agent, String className) : CompositeBehavior(_agent, className) {

}

void SelectorBehavior::childSucceeded() {
	endWithSuccess();
}

void SelectorBehavior::childFailed() {
	Reference<Behavior*> currentChild;

	try {
		do {
			currentPos++;
			currentChild = children.get(currentPos);

			if (currentChild == NULL) { // uh oh, this shouldn't happen
				currentPos = 0;
				endWithError();
				return;
			}

		} while (!currentChild->checkConditions());
	} catch (ArrayIndexOutOfBoundsException &e) { // this is fine, it just means we've gone through all the children
		currentChild = NULL;
		currentPos = 0;
		endWithFailure();
	}
}
