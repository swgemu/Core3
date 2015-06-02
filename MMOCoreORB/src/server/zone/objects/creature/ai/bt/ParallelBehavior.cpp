/*
 * ParallelBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "ParallelBehavior.h"

ParallelBehavior::ParallelBehavior(AiAgent* _agent, const String& className) : CompositeBehavior(_agent, className) {
	numFailed = 0;
	numSucceeded = 0;
}

void ParallelBehavior::start() {
	unfinishedChildren = children;
	numFailed = 0;
	numSucceeded = 0;

	CompositeBehavior::start();
}

void ParallelBehavior::end() {
	unfinishedChildren.removeAll();
	CompositeBehavior::end();
}

void ParallelBehavior::doAction(bool directlyExecuted) {
	if (finished()) {
		Behavior::doAction(directlyExecuted);
		return;
	}

	if (!started())
		this->start();

	for (int i = 0; i < children.size(); i++) {
		Behavior* currentChild = children.get(i);

		if (currentChild == NULL) { // this shouldn't happen. Bail.
			agent->error("NULL child or empty children list in ParallelBehavior");
			endWithError();
			Behavior::doAction(directlyExecuted);
			return;
		}

		if (!unfinishedChildren.contains(currentChild)) // we don't want to process a child after it has already ended
			continue;

		if (!currentChild->started())
			currentChild->start();
		else if (currentChild->finished()) {
			if (currentChild->succeeded())
				this->childSucceeded();
			else if (currentChild->failed())
				this->childFailed();

			currentChild->end();
			unfinishedChildren.removeElement(currentChild);
		} else {
			currentChild->doAction();
		}
	}

	if (unfinishedChildren.isEmpty())
		this->finish();

	Behavior::doAction(directlyExecuted);
}

void ParallelBehavior::childFailed() {
	numFailed++;
}

void ParallelBehavior::childSucceeded() {
	numSucceeded++;
}
