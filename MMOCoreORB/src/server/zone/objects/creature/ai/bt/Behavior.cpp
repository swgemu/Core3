/*
 * Behavior.cpp
 *
 *  Created on: Jun 10, 2014
 *      Author: swgemu
 */

#include "Behavior.h"
#include "server/zone/managers/creature/AiMap.h"

Behavior::Behavior(AiAgent* _agent, const String& className) {
	agent = _agent;
	result = AiMap::SUSPEND;
	parent = nullptr;
	interface = AiMap::instance()->getBehavior(className);
	id = 0;

	if (interface == nullptr) {
		_agent->error("Null interface in Behavior: " + className);
	}
}

void Behavior::start() {
	if (!checkConditions()) {
		endWithFailure();
		return;
	}

	result = AiMap::RUNNING;

	if (interface != nullptr) {
		AiAgent* strongReference = agent.getReferenceUnsafeStaticCast();

		interface->start(strongReference);
	}
}

void Behavior::end() {
	if (interface != nullptr) {
		AiAgent* strongReference = agent.getReferenceUnsafeStaticCast();

		interface->end(strongReference);
	}
}

void Behavior::doAction(bool directlyExecuted) {
	AiAgent* agent = this->agent.getReferenceUnsafeStaticCast();

	if (agent->isDead() || agent->isIncapacitated() || (agent->getZone() == nullptr)) {
		agent->setFollowObject(nullptr);
		return;
	}

	//agent->info(id, true);
	agent->setCurrentBehavior(id);

	if (!started())
		this->start();
	else if (!this->checkConditions())
		endWithFailure();

	agent = this->agent.getReferenceUnsafeStaticCast();

	if (finished()) {
		if (parent == nullptr) {
			this->end();
			result = AiMap::SUSPEND;
			agent->activateMovementEvent(); // this is an automatic recycle decorator for the root node
		} else if (directlyExecuted) {
			agent->setCurrentBehavior(parent->id);
			parent->doAction(true);
		}

		return;
	}

	int res = AiMap::INVALID;
	if (interface != nullptr)
		res = interface->doAction(agent);

	switch(res) {
	case AiMap::SUCCESS:
		endWithSuccess();
		break;
	case AiMap::FAILURE:
		endWithFailure();
		break;
	case AiMap::INVALID:
		if (agent == nullptr)
			return;

		agent->resetBehaviorList();
		break;
	default:
		if (agent == nullptr)
			return;

		break;
	}

	if (!finished() || parent == nullptr)
		agent->activateMovementEvent();
	else if (directlyExecuted) {
		agent->setCurrentBehavior(parent->id);

		parent->doAction(true);
	}
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
	return result == AiMap::SUCCESS || result == AiMap::FAILURE || result == AiMap::INVALID;
}

bool Behavior::started() {
	return result != AiMap::SUSPEND;
}
