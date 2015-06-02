/*
 * ParallelSelectorBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "ParallelSelectorBehavior.h"

ParallelSelectorBehavior::ParallelSelectorBehavior(AiAgent* _agent, const String& className) : ParallelBehavior(_agent, className) {
}

void ParallelSelectorBehavior::finish() {
	if (numSucceeded > 0)
		endWithSuccess();
	else
		endWithFailure();
}


