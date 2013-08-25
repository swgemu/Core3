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
void BehaviorTree::tick() {
	Behavior* stop = NULL;
	blist.add(stop);
	while(step()) {
		continue;
	}
}
bool BehaviorTree::step() {
	Behavior* current = blist.remove();
	if (current == NULL)
		return false;
	current->tick();
	if (current->status != RUNNING && current->canObserve()) {
		current->observe(current->status);
	} else {
		blist.add(current);
	}
	return true;
}
