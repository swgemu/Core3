/*
 * Sequence.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#include "SequenceBehavior.h"

SequenceBehavior::SequenceBehavior() {
}

SequenceBehavior::~SequenceBehavior() {
}

void SequenceBehavior::onInitialize() {
	currentChild = 0;
	tree->start(children.get(currentChild));
}
void SequenceBehavior::observe(Status s) {
	Behavior* child = children.get(0);
	if (child->status == FAILURE) {
		tree->stop(this,FAILURE);
		return;
	}
	if (child->status == SUCCESS) {
		if (++currentChild == children.size()) {
			tree->stop(this,SUCCESS);
		} else {
			tree->start(children.get(currentChild));
		}
	}
}

