/*
 * Sequence.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#include "SequenceBehavior.h"

SequenceBehavior::SequenceBehavior(BehaviorTree* sequenceTree) {
	this->tree = sequenceTree;
}

SequenceBehavior::~SequenceBehavior() {
}

void SequenceBehavior::onInitialize(AiActor* actor) {
	Behavior::onInitialize(actor);
	position = 0;
	end = children.size();
	tree->start(children.get(0),actor);
}
void SequenceBehavior::observe(AiActor* actor) {
	Behavior* child = children.get(position);
	if (actor->getBehaviorStatus(child) == FAILURE) {
		tree->stop(this,actor);
		return;
	}
	if (actor->getBehaviorStatus(child) == SUCCESS) {
		if (++position > end) {
			tree->stop(this,actor);
		} else {
			tree->start(children.get(position),actor);
		}
	}
}

