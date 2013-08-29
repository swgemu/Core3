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
	for(int i=0;i<children.size();i++) {
		actor->setBehaviorStatus(children.get(0),INVALID);
	}
	position = 0;
	end = children.size();
	tree->start(children.get(0));
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
			tree->start(children.get(position));
		}
	}
}

