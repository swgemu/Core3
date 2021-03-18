#ifndef COMMANDQUEUEIMMEDIATEEVENT_H_
#define COMMANDQUEUEIMMEDIATEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

class CommandQueueImmediateEvent : public Task {
	ManagedWeakReference<CreatureObject*> creature;

public:
	CommandQueueImmediateEvent(CreatureObject* creo) : Task() {
		creature = creo;

	}

	void run() {
		ManagedReference<CreatureObject*> creature = this->creature.get();

		if (creature == nullptr) {
			return;
		}

		try {
			Locker creatureLocker(creature);

			creature->activateImmediateAction();

		} catch (Exception& e) {
			creature->error(e.getMessage());
			e.printStackTrace();
		} catch (...) {

			throw;
		}
	}
};

#endif /*COMMANDQUEUEIMMEDIATEEVENT_H_*/