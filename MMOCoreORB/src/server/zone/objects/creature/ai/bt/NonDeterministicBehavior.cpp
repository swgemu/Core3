/*
 * NonDeterministicBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "NonDeterministicBehavior.h"

NonDeterministicBehavior::NonDeterministicBehavior(AiAgent* _agent, String className) : CompositeBehavior(_agent, className) {

}

void NonDeterministicBehavior::start() {
	// this is literally just a shuffle algorithm
	Behavior* temp;
	int index;
	for (int i = 0; i < children.size(); i++) {
		index = (int) System::random(children.size() - 1 - i) + i;
		temp = children.set(i, children.get(index));
		children.set(index, temp);
	}

	CompositeBehavior::start();
}


