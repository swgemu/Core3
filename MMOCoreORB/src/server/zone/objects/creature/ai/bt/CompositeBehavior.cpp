/*
 * CompositeBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "CompositeBehavior.h"
#include "Behavior.h"
#include "server/zone/managers/creature/AiMap.h"

CompositeBehavior::CompositeBehavior(AiAgent* _agent, const String& className) : Behavior(_agent, className) {
	currentPos = 0;
}

CompositeBehavior::CompositeBehavior(const CompositeBehavior& b) : Behavior(b) {
	children = b.children;
	currentPos = b.currentPos;
}

void CompositeBehavior::start() {
	currentPos = 0;

	for (int i = 0; i < children.size(); i++) {
		Behavior* currentChild = children.get(i);

		if (currentChild == NULL) {
			Reference<AiAgent*> agent = this->agent.get();

			agent->error("NULL child in CompositeBehavior");
			continue;
		}

		currentChild->setStatus(AiMap::SUSPEND);
	}

	Behavior::start();
}

void CompositeBehavior::doAction(bool directlyExecuted) {
	AiAgent* agent = this->agent.getReferenceUnsafeStaticCast();

	if (agent->isDead() || agent->isIncapacitated() || (agent->getZone() == NULL)) {
		agent->setFollowObject(NULL);
		return;
	}

	if (!started())
		this->start();
	else if (!checkConditions())
		endWithFailure();

	if (finished()) {
		Behavior::doAction(directlyExecuted);
		return;
	}

	Behavior* currentChild;

	do {
		currentChild = children.get(currentPos);

		if (currentChild == NULL) {
			agent->error("NULL child or empty children list in CompositeBehavior");
			endWithError();
			Behavior::doAction(directlyExecuted);
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

	if (currentChild->finished())
		Behavior::doAction(directlyExecuted);
}

String CompositeBehavior::print() {
	StringBuffer stream;
	stream << Behavior::print() << "[";
	for (int i = 0; i < children.size(); i ++) {
		stream << children.get(i)->print() << " ";
	}
	stream << "]";
	return stream.toString();
}

bool CompositeBehavior::checkConditions() {
	return children.size() > 0 && Behavior::checkConditions();
}


