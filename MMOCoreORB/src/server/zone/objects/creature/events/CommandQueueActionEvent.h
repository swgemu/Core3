/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMMANDQUEUEACTIONEVENT_H_
#define COMMANDQUEUEACTIONEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

class CommandQueueActionEvent : public Task {
	ManagedWeakReference<CreatureObject*> creature;
	int type;
public:
	const static int IMMEDIATE = 1;
	const static int NORMAL = 2;

public:
	CommandQueueActionEvent(CreatureObject* pl, int type = NORMAL) : Task() {
		creature = pl;
		this->type = type;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = this->creature.get();

		if (creature == nullptr)
			return;

		Locker creatureLocker(creature);

		try {

			//player->info("activating command queue action");

			if (type == NORMAL)
				creature->activateQueueAction();
			else
				creature->activateImmediateAction();

			//player->info("command queue action activated");

		} catch (const Exception& e) {
			auto aiAgent = creature->asAiAgent();

			if (aiAgent != nullptr) {
				aiAgent->handleException(e, "CommandQueueActionEvent");
			} else {
				auto trace = e.getStackTrace();
				creature->error()
					<< "Unhandled exception in CommandQueueActionEvent: " << e.getMessage()
					<< " STACK: " << trace.toStringData();
			}
		} catch (...) {
			//creature = nullptr;

			throw;
		}
	}
};

#endif /*COMMANDQUEUEACTIONEVENT_H_*/
