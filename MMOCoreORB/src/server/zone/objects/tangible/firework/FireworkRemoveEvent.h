/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIREWORKREMOVEEVENT_H_
#define FIREWORKREMOVEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/staticobject/StaticObject.h"

class FireworkRemoveEvent : public Task {
	ManagedReference<StaticObject*> firework;
	ManagedReference<CreatureObject*> player;

public:
	FireworkRemoveEvent(CreatureObject* player, StaticObject* firework) : Task(1000) {
		this->player = player;
		this->firework = firework;
	}

	void run() {
		if (firework == NULL)
			return;

		try {
			Locker locker(firework);

			firework->destroyObjectFromWorld(true);
		} catch (Exception& e) {
			player->error("unreported exception on FireworkEvent::run()");
		}

		firework = NULL;
		player = NULL;
	}
};


#endif /* FIREWORKREMOVEEVENT_H_ */
