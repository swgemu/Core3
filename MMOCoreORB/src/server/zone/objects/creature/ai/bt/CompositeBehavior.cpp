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

	Reference<Behavior*> currentChild = children.get(currentPos);

	if (currentChild == NULL) {
		agent->error("NULL child or empty children list in CompositeBehavior");
		endWithError();
		Behavior::doAction();
		return;
	}

	if (!currentChild->started())
		currentChild->start();
	if (currentChild->finished()) {
		if (currentChild->succeeded())
			this->childSucceeded();
		else if (currentChild->failed())
			this->childFailed();

		currentChild->end();
	} else {
		currentChild->doAction();
	}

	Behavior::doAction();
	if (!currentChild->finished())
		agent->setCurrentBehavior(currentChild);
}


