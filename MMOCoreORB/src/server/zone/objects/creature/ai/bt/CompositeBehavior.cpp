/*
 * CompositeBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "CompositeBehavior.h"
#include "server/zone/managers/creature/AiMap.h"

void CompositeBehavior::start() {
	currentPos = 0;

	for (int i = 0; i < children.size(); i++) {
		Reference<Behavior*> currentChild = children.get(i);

		if (currentChild == NULL) {
			agent->error("NULL child in CompositeBehavior");
			continue;
		}

		currentChild->setStatus(AiMap::SUSPEND);
	}

	Behavior::start();
}

void CompositeBehavior::doAction() {
	if (agent->isDead() || agent->isIncapacitated() || (agent->getZone() == NULL)) {
		agent->setFollowObject(NULL);
		return;
	}

	if (!started())
		this->start();
	else if (!checkConditions())
		endWithFailure();

	if (finished()) {
		Behavior::doAction();
		return;
	}

	Behavior* currentChild;

	do {
		currentChild = children.get(currentPos).get();

		if (currentChild == NULL) {
			agent->error("NULL child or empty children list in CompositeBehavior");
			endWithError();
			Behavior::doAction();
			return;
		}

		if (!currentChild->started())
			currentChild->start();
		else if (!currentChild->checkConditions()) // if this isn't here, I can get a single recursion where the child will call the parent's (this) doAction()
			endWithFailure();

		if (!currentChild->finished())
			currentChild->doAction();

		if (currentChild->finished()) {
			if (currentChild->succeeded())
				this->childSucceeded();
			else if (currentChild->failed())
				this->childFailed();

			currentChild->end();
		}
	} while (currentChild != NULL && currentChild->finished() && !this->finished() && currentPos < children.size());

	Behavior::doAction();
}


