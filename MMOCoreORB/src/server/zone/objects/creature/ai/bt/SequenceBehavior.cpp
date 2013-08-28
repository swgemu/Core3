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

void SequenceBehavior::onInitialize() {
	position = 0;
	end = children.size();
	tree->start(children.get(0));
}
void SequenceBehavior::observe(Status s) {
	Behavior* child = children.get(position);
	if (child->status == FAILURE) {
		tree->stop(this,FAILURE);
		return;
	}
	if (child->status == SUCCESS) {
		if (++position > end) {
			tree->stop(this,SUCCESS);
		} else {
			tree->start(children.get(position));
		}
	}
}

