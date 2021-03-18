#ifndef COMMANDQUEUEREMOVEEVENT_H_
#define COMMANDQUEUEREMOVEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

class CommandQueueRemoveEvent : public Task {
	ManagedWeakReference<CreatureObject*> creature;

public:
	CommandQueueRemoveEvent(CreatureObject* creo) : Task() {
		creature = creo;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = this->creature.get();

		if (creature == nullptr) {
			return;
		}

		if (!creature->hasAttackDelay() || !creature->hasPostureChangeDelay()) {
			return;
		}

		const CommandQueueActionVector* commandQueue = creature->getCommandQueue();

		if (commandQueue->size() == 0) {
			return;
		}

		Reference<CommandQueueAction*> action = commandQueue->get(0);

		for (int i = 0; i < commandQueue->size(); i++) {
			Reference<CommandQueueAction*> actionToDelete = commandQueue->get(i);

			if (action->getCommand() == actionToDelete->getCommand() && action->getActionCounter() == actionToDelete->getActionCounter() && action->getCompareToCounter() == actionToDelete->getCompareToCounter()) {
				creature->removeQueueAction(i);
				break;
			}
		}
	}

};

#endif /*COMMANDQUEUEREMOVEEVENT_H_*/