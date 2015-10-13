/*
 * Composite.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#include "server/zone/objects/creature/ai/bt/node/Composite.h"

using namespace server::zone::objects::creature::ai::bt;

Status Composite::doAction(Reference<AiAgent*> agent) const {
	if (!this->checkConditions(agent))
		return INVALID;

    // Step 1:  check if this behavior is in the running chain
    //          if it isn't, then call start(), but if it is,
    //          then we need to assume all previous children
    //          resulted in whatever status that would cause
    //          this behavior to execute (ie, if this is a
    //          selector, then all previous were fails and if
    //          this is a sequence, all previous were
    //          successes) and continue execution in order
    unsigned int currentIdx = 0;
    if (!agent->isRunningBehavior(id))
        this->start(agent);
    else { // we need to find the child that is running and start from there
    	agent->popRunningChain();

		Behavior* currentChild = NULL;
		for (; currentIdx < children.size(); ++currentIdx) {
			currentChild = children.at(currentIdx);
			if (currentChild == NULL) // TODO: this should probably throw an error or something
				children.remove(currentIdx--);
			else if (currentChild->getID() == agent->peekRunningChain())
				break;
		}

        if (currentIdx >= children.size()) {
        	// this shouldn't happen, but in case we can't find the running
        	// child, clear the chain (it's already mangled) and run as if
        	// there was no running chain
        	agent->clearRunningChain();
        	currentChild = children.at(0);
        }
    }

    // Step 2:  evaluate the action result. The method to do this will differ
    //			depending on the type of composite this is, so this will just
    //			call the abstract method to do it.
    Status result = this->execute(agent, currentIdx);

    // Step 3:  if the child result is running, then set this
    //          state to running and push the behavior to the
    //          front of the AI's running chain
    if (result == RUNNING)
    	agent->addRunningID(id);
    else
    	this->end(agent);

    // Step 4:  return the result
    return result;
}

String Composite::print() const {
	StringBuffer stream;
	stream << Behavior::print() << "[";
	for (int i = 0; i < children.size(); i ++) {
		stream << children.get(i)->print() << " ";
	}
	stream << "]";
	return stream.toString();
}
