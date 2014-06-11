/*
 * Behavior.cpp
 *
 *  Created on: Jun 10, 2014
 *      Author: swgemu
 */

#include "Behavior.h"
#include "CompositeBehavior.h"
#include "server/zone/managers/creature/AiMap.h"
#include "LuaBehavior.h"

Behavior::Behavior(AiAgent* _agent, String className) : Object() {
	agent = _agent;
	result = AiMap::SUSPEND;
	parent = NULL;
	interface = AiMap::instance()->getBehavior(className);
}

void Behavior::start() {
	if (!checkConditions()) {
		endWithFailure();
		return;
	}

	result = AiMap::RUNNING;

	interface->start(agent);
}

void Behavior::end() {
	result = AiMap::SUSPEND;
	interface->end(agent);
}

void Behavior::doAction() {
	if (!started())
		this->start();

	if (finished()) {
		if (parent != NULL) {
			agent->setCurrentBehavior(parent);
			parent->doAction();
			return;
		} else {
			this->end();
			agent->activateMovementEvent();
			return;
		}
	}

	int res = interface->doAction(agent);

	switch(res) {
	case AiMap::SUCCESS:
		endWithSuccess();
		break;
	case AiMap::FAILURE:
		endWithFailure();
		break;
	case AiMap::INVALID:
		agent->resetBehaviorList();
		break;
	default:
		break;
	}

	agent->activateMovementEvent();
}

void Behavior::endWithFailure() {
	this->result = AiMap::FAILURE;
}

void Behavior::endWithSuccess() {
	this->result = AiMap::SUCCESS;
}

void Behavior::endWithError() {
	this->result = AiMap::INVALID;
}

bool Behavior::succeeded() {
	return result == AiMap::SUCCESS;
}

bool Behavior::failed() {
	return result == AiMap::FAILURE;
}

bool Behavior::finished() {
	return result != AiMap::RUNNING && result != AiMap::SUSPEND;
}

bool Behavior::started() {
	return result != AiMap::SUSPEND;
}
