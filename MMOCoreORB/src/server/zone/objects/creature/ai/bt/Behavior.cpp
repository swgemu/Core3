/*
 * Behavior.cpp
 *
 *  Created on: Jun 10, 2014
 *      Author: swgemu
 */

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

using namespace server::zone::objects::creature::ai::bt;

bool Behavior::checkConditions(AiAgent* agent) const {
	// placeholder for more robust checkConditions
	return agent != NULL &&
		   !agent->isDead() &&
		   !agent->isIncapacitated() &&
		   agent->getZone() != NULL;
}

Behavior::Status Behavior::doAction(Reference<AiAgent*> agent) const {
	//agent->info(id, true);
	
	if (!this->checkConditions(agent)) {
		if (agent != NULL) {
			// TODO: Should this be done here or in realizations of specific actions?
			agent->clearCombatState(true);
			agent->setOblivious();
			agent->info("Invalid return from " + print(), true);
		}

		return INVALID; // TODO: should this be FAILURE?
	}
	
	// Step 1:	check if this behavior is in the running chain
	//			If it isn't, call start()
	//			We can assume here that if we are running here, that this is the
	//			leaf that is actually running because all other running states
	//			will be composites and would have a different reaction to being
	//			in the running vector
	if (!agent->isRunningBehavior(id))
		this->start(agent);
	else
		agent->popRunningChain();
		
	// Step 2:	evaluate the action result (method to do this will be abstract
	//			and implemented in the concrete behaviors)
	Behavior::Status result = this->execute(agent);
	
	// Step 3:	If the result is RUNNING, clear the agent's run chain and and
	//			add this->id to the front. As the chain unwinds, the composite
	//			parents will push_front to the chain until the root node
	if (result == RUNNING) {
		agent->clearRunningChain();
		agent->addRunningID(id);
	} else
		this->end(agent);
	
	// Step 4:	If the result is anything else (TODO: SUSPEND?) just return that
	//			value; the parent will deal with the next action based on the
	//			type of parent.
	return result;
}
