/*
 * AiActorImplementation.cpp
 *
 *  Created on: May 7, 2012
 *      Author: da
 */

#include "AiActor.h"
#include "components/AiStateComponent.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/templates/AiTemplate.h"

#include "engine/core/ManagedObject.h"

void AiActorImplementation::initializeTransientMembers() {
	ObservableImplementation::initializeTransientMembers();

	defaultStateName = aiTemplate->getDefaultName();
	currentStateName = defaultStateName;
	currentState = ComponentManager::instance()->getComponent<AiStateComponent*>(currentStateName);

	transitions = aiTemplate->getTransitions();
}

void AiActorImplementation::next(uint16 msg) {
	currentStateName = transitions.get(currentStateName + msg);
	currentState = ComponentManager::instance()->getComponent<AiStateComponent*>(currentStateName);
}

void AiActorImplementation::next() {
	currentStateName = transitions.get(currentStateName + currentMessage);
	currentState = ComponentManager::instance()->getComponent<AiStateComponent*>(currentStateName);
}

void AiActorImplementation::doAwarenessCheck(Coordinate &start, uint64 time, CreatureObject* target) {
	currentState->doAwarenessCheck(_this, start, time, target);
}

void AiActorImplementation::addTransition(const String& stateName, uint16 msg, const String& resultState) {
	transitions.put(stateName + String::valueOf(msg), resultState);
}

