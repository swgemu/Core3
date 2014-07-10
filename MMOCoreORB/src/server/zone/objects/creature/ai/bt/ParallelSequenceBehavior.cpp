/*
 * ParallelSequenceBehavior.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */


#include "ParallelSequenceBehavior.h"

ParallelSequenceBehavior::ParallelSequenceBehavior(AiAgent* _agent, String className) : ParallelBehavior(_agent, className) {
}

void ParallelSequenceBehavior::finish() {
	if (numFailed > 0)
		endWithFailure();
	else
		endWithSuccess();
}


