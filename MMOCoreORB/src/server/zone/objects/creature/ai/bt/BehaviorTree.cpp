/*
 * BehaviorTree.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#include "BehaviorTree.h"
#include "Behavior.h"
#include "engine/engine.h"

BehaviorTree::BehaviorTree() {
}

BehaviorTree::~BehaviorTree() {
}

void BehaviorTree::start(Behavior* behavior) {
	blist.add(behavior);
}
void BehaviorTree::stop(Behavior* behavior, Status result) {
	if (result != RUNNING) {
		behavior->status = result;
	}
	if (behavior->canObserve()) {
		behavior->observe(result);
	}
}
void BehaviorTree::tick(AiActor* actor) {
	Behavior* stop = NULL;
	if (actor == NULL)
		return;
	Locker actorLock(actor);
	blist.add(stop);
	while(step(actor)) {
		continue;
	}
}
bool BehaviorTree::step(AiActor* actor) {
	Behavior* current = blist.remove();
	if (current == NULL)
		return false;
	current->tick(actor);
	if (current->status != RUNNING && current->canObserve()) {
		current->observe(current->status);
	} else {
		blist.add(current);
	}
	return true;
}
